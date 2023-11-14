#include <AP_SerialLED/AP_SerialLED.h>
#include "DroneShowLED_SerialLED.h"
#include <map>
#include <tuple>

DroneShowLED_SerialLED::DroneShowLED_SerialLED(
    DroneShowLED_SerialLEDType type, uint8_t chan, uint8_t num_leds
) : _chan(chan), _type(type), _num_leds(num_leds)
{
}

bool DroneShowLED_SerialLED::init(void)
{
    AP_SerialLED* serialLed = AP_SerialLED::get_singleton();
    if (!serialLed) {
        return false;
    }

    if (_type == DroneShowLED_SerialLEDType_NeoPixel) {
        return serialLed->set_num_neopixel(_chan, _num_leds);
    } else if (_type == DroneShowLED_SerialLEDType_ProfiLED) {
        return serialLed->set_num_profiled(_chan, _num_leds);
    }

    return false;
}

std::map<std::tuple<int, int, int>, std::tuple<int, int, int>> colorMap = {
    {{255, 0, 0}, {128, 0, 128}},
    {{128, 0, 128}, {255, 0, 0}},
    {{0, 0, 139}, {255, 255, 0}},
    {{255, 255, 0}, {0, 0, 139}},
    {{0, 128, 0}, {0, 255, 255}},
    {{0, 255, 255}, {0, 128, 0}},
    {{255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {255, 255, 255}}
};

std::tuple<int, int, int> mapColor(int red, int green, int blue) {
    auto it = colorMap.find({red, green, blue});
    if (it != colorMap.end()) {
        return it->second;
    } else {
        // Linear interpolation
        for (const auto &entry : colorMap) {
            const auto &start = entry.first;
            const auto &end = entry.second;
            if ((start < std::tie(red, green, blue)) && (std::tie(red, green, blue) < end)) {
                float t = 0.5; // Interpolation factor, you can choose any value between 0 and 1
                return std::make_tuple(
                    std::get<0>(start) + t * (std::get<0>(end) - std::get<0>(start)),
                    std::get<1>(start) + t * (std::get<1>(end) - std::get<1>(start)),
                    std::get<2>(start) + t * (std::get<2>(end) - std::get<2>(start))
                );
            }
        }
        return {red, green, blue}; // Default transformation
    }
}

bool DroneShowLED_SerialLED::set_raw_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    AP_SerialLED* serialLed = AP_SerialLED::get_singleton();

    if (serialLed) {
        // auto mappedColor = mapColor(red, green, blue);
        // serialLed->set_RGB(_chan, -1, std::get<0>(mappedColor), std::get<1>(mappedColor), std::get<2>(mappedColor));
        // serialLed->set_RGB(_chan, -1, 255, 255, 255);
        // serialLed->set_RGB(_chan, -1, red, green, blue);
        serialLed->set_RGB(_chan, -1, red, 255 - green, 255 - blue);
        serialLed->send(_chan);
        return true;
    } else {
        return false;
    }
}
