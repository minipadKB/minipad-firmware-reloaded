#pragma once

#include "config/configuration_controller.hpp"
#include "helpers/sma_filter.hpp"
#include "handlers/key_state.hpp"
#include "definitions.hpp"

inline class KeypadHandler
{
public:
    KeypadHandler()
    {
        // Initialize the SMA filters.
        for (uint8_t i = 0; i < KEYS; i++)
            _keyStates[i] = KeyState();
    }

    void handle();
    bool outputMode;

private:
    KeyState _keyStates[KEYS];

    uint16_t read(const Key &key);
    uint16_t mapToTravelDistance(const Key &key, uint16_t value);
    void checkTraditional(const Key &key, uint16_t value);
    void checkRapidTrigger(const Key &key, uint16_t value);
    bool checkRapidTriggerPressKey(const Key &key, uint16_t value);
    bool checkRapidTriggerReleaseKey(const Key &key, uint16_t value);
    void pressKey(const Key &key);
    void releaseKey(const Key &key);
} KeypadHandler;