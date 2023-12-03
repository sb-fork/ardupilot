#pragma once

/// @file   AC_DroneShowLED_FlyAI.h
/// @brief  Drone show LED that sends its output to a NeoPixel LED strip.

#include <AP_Common/AP_Common.h>

#include "DroneShowLED.h"

typedef enum {
    DroneShowLED_FlyAIType_NeoPixel,
    DroneShowLED_FlyAIType_ProfiLED
} DroneShowLED_FlyAIType;

/**
 * RGB LED implementation that sends the current state of the RGB LED to a
 * NeoPixel LED strip.
 */
class DroneShowLED_FlyAI : public DroneShowLED {
public:
    DroneShowLED_FlyAI(
        DroneShowLED_FlyAIType type, uint8_t chan = 1, uint8_t num_leds = 16
    );

    /* Do not allow copies */
    DroneShowLED_FlyAI(const DroneShowLED_FlyAI &other) = delete;
    DroneShowLED_FlyAI &operator=(const DroneShowLED_FlyAI&) = delete;

protected:
    bool init(void) override;
    bool set_raw_rgb(uint8_t r, uint8_t g, uint8_t b) override;

private:
    uint8_t _chan;
    uint8_t _num_leds;
    DroneShowLED_FlyAIType _type;
};
