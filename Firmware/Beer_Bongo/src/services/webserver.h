// Simple web server to control PWM_output via a slider
#ifndef SERVICE_WEBSERVER_H
#define SERVICE_WEBSERVER_H

#include "shared/dependencies.h"

// Provide a single WebServer instance via function-local static to avoid
// multiple-definition issues when included from multiple translation units.
inline WebServer &getWebServer()
{
    static WebServer server(80);
    return server;
}

// Starts the webserver and registers routes for the PWM slider UI.
inline void setup_WEBSERVER()
{
    WebServer &server = getWebServer();

    // Minimal HTML page with a single PWM slider (0..255)
    static const char PAGE[] PROGMEM = R"rawliteral(
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <title>PWM Control</title>
    <style>body{font-family:Arial,Helvetica,sans-serif;padding:1rem}.slider{width:100%}</style>
  </head>
  <body>
    <h3>PWM Output Control</h3>
    <input id="pwm" class="slider" type="range" min="0" max="255" value="0" />
    <div>Value: <span id="val">0</span></div>
    <script>
      const s = document.getElementById('pwm');
      const v = document.getElementById('val');
      function setVal(n){ v.textContent = n; }
      function send(n){ fetch('/set?value='+encodeURIComponent(n)).then(r=>r.json()).then(j=>setVal(j.value)).catch(e=>console.log('send error',e)); }
      // initialize from server
      fetch('/state').then(r=>r.json()).then(j=>{ s.value = j.value; setVal(j.value); }).catch(e=>console.log('init error',e));
      s.addEventListener('input', e => setVal(e.target.value));
      s.addEventListener('change', e => send(e.target.value));
    </script>
  </body>
</html>
)rawliteral";

    server.on("/", HTTP_GET, []()
              {
                  WebServer &srv = getWebServer();
                  srv.send_P(200, "text/html", PAGE); });

    // (removed duplicate/old handler that referenced mains_frequency)

    // Set PWM value: /set?value=NN
    server.on("/set", HTTP_GET, []()
              {
            WebServer &srv = getWebServer();
            String v = srv.arg("value");
            int val = v.toInt();
            if (val < 0)
              val = 0;
            if (val > 255)
              val = 255;
            PWM_output = (uint8_t)val;
            String resp = "{\"value\": " + String(PWM_output) + "}";
            srv.send(200, "application/json", resp); });

    // Get current state: { "value": NN }
    server.on("/state", HTTP_GET, []()
              {
            WebServer &srv = getWebServer();
            String resp = "{\"value\": " + String(PWM_output) + "}";
            srv.send(200, "application/json", resp); });
    server.begin();
    Serial.println("Webserver started");
}
// If you want to handle server tasks in loop explicitly, call this.
inline void webserver_handle()
{
    // WebServer for ESP32 does not require periodic handle call when using async
    // but call handleClient for compatibility.
    getWebServer().handleClient();
}

#endif // SERVICE_WEBSERVER_H
