#pragma once

#include <cstdint>

namespace StringHelper
{
    void getArgumentAt(char *input, char delimiter, uint8_t index, char *output);
    void toLower(char *input);
    void replace(char *input, char target, char replacement);
    void makeSafename(char *str);
};
