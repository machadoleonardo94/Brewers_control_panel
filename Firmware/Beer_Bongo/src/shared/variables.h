#if !defined(PROJECT_GLOBAL_VARIABLES)
#define PROJECT_GLOBAL_VARIABLES

//* ---------------------- GLOBAL COMPONENT VARIABLES ----------------------

bool ads_started = false;
//* OLED display
bool display_started = false;
//* SD card
bool sdcard = false;

uint32_t loopTimer = 0;
uint32_t globalTimer = 0;
uint32_t loopCounter = 0;

uint8_t PWM_output = 0;

// Interrupt flags/count for main_detect_pin
volatile bool main_detect_triggered = false;
volatile uint32_t main_detect_count = 0;
float mains_frequency = 60.0;

uint8_t macAdress[6] = {0, 0, 0, 0, 0, 0};

typedef struct ledstrip
{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t color = 0;
    uint8_t brightness = 25;
    uint32_t update_time = 50;
    int8_t index = 0;
} struct_ledstrip;

struct_ledstrip onboard_led;

typedef struct buttonState
{
    bool currentState = HIGH;
    bool lastState = HIGH;
    uint32_t lastDebounceTime = 0;
    uint32_t debounceDelay = 50;
    uint8_t counter = 0;
} struct_buttonState;

struct_buttonState button_states[4]; // Assuming 4 buttons

#endif // PROJECT_GLOBAL_VARIABLES
