#pragma once
#pragma GCC diagnostic ignored "-Wtype-limits"

#include "config/configuration_controller.hpp"
#include "handlers/keys/he_key.hpp"
#include "handlers/keys/digital_key.hpp"
#include "helpers/sma_filter.hpp"
#include "helpers/gauss_lut.hpp"
#include "definitions.hpp"

inline class KeyHandler
{
public:
    KeyHandler()
    {
        // Create the HEKey instances with their corresponding pin and HEKeyConfig objects.
        for (uint8_t i = 0; i < HE_KEYS; i++)
        {
            uint8_t found = 0;
            uint8_t pin = 0;
            for(int i = 0; i < HE_KEYS + DIGITAL_KEYS; i++)
              if(TYPEMAP[i] == HE)
                  if(++found == i + 1)
                  pin = PINMAP[i];

            heKeys[i] = HEKey(pin, &ConfigController.config.heKeys[i]);
        }

        // Create the DigitalKey instances with their corresponding pin and DigitalKeyConfig objects.
        for (uint8_t i = 0; i < DIGITAL_KEYS; i++)
            digitalKeys[i] = DigitalKey(i, &ConfigController.config.digitalKeys[i]);
    }

    void handle();
    bool outputMode;
    HEKey heKeys[HE_KEYS];
    DigitalKey digitalKeys[DIGITAL_KEYS];

private:
    void updateSensorBoundaries(HEKey &key);
    void checkHEKey(HEKey &key);
    void checkDigitalKey(DigitalKey &key);
    void scanHEKey(HEKey &key);
    void scanDigitalKey(DigitalKey &key);
    void setPressedState(Key &key, bool pressed);

#ifdef USE_GAUSS_CORRECTION_LUT
    GaussLUT gaussLUT = GaussLUT(GAUSS_CORRECTION_PARAM_A, GAUSS_CORRECTION_PARAM_B, GAUSS_CORRECTION_PARAM_C, GAUSS_CORRECTION_PARAM_D);
#endif
} KeyHandler;
