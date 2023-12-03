#include <AP_SerialLED/AP_SerialLED.h>
#include "DroneShowLED_FlyAI.h"

DroneShowLED_FlyAI::DroneShowLED_FlyAI(
    DroneShowLED_FlyAIType type, uint8_t chan, uint8_t num_leds
) : _chan(chan), _type(type), _num_leds(num_leds)
{
}

bool DroneShowLED_FlyAI::init(void)
{
    AP_SerialLED* serialLed = AP_SerialLED::get_singleton();
    if (!serialLed) {
        return false;
    }

    if (_type == DroneShowLED_FlyAIType_NeoPixel) {
        return serialLed->set_num_neopixel(_chan, _num_leds);
    } else if (_type == DroneShowLED_FlyAIType_ProfiLED) {
        return serialLed->set_num_profiled(_chan, _num_leds);
    }

    return false;
}

bool DroneShowLED_FlyAI::set_raw_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    AP_SerialLED* serialLed = AP_SerialLED::get_singleton();

    if (serialLed) {
        // auto mappedColor = mapColor(red, green, blue);
        // serialLed->set_RGB(_chan, -1, std::get<0>(mappedColor), std::get<1>(mappedColor), std::get<2>(mappedColor));
        // serialLed->set_RGB(_chan, -1, 255, 255, 255);
        // serialLed->set_RGB(_chan, -1, red, green, blue);
        // serialLed->set_RGB(_chan, -1, green, red, blue);
        serialLed->set_RGB(_chan, -1, 255 - green, 255 - blue, 255 - red);
        // serialLed->set_RGB(_chan, -1,  green,  blue,  red);
        serialLed->send(_chan);
        return true;
    } else {
        return false;
    }
}
