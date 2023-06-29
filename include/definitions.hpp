#pragma once

// The version of this firmware in the YYYY.MDD.PATCH format. (e.g. 2022.1219.2 for the 2nd release on the 19th december 2022)
#define FIRMWARE_VERSION "2023.516.1"

// ┌───────────────────────────────────────────────────────────────────────────────────────────────────┐
// │                                                                                                   │
// │                                           !!!WARNING!!!                                           │
// │                                                                                                   │
// │      DO NOT CHANGE UNLESS ADVISED. MODIFIED VALUES MAY CAUSE AN INCONSISTENT KEYPAD BEHAVIOR      │
// │   THAT VIOLATES OSU'S RULES. CHANGING THIS MAY LEAD TO INCORRECT KEY PRESSES AND A RESTRICTION.   │
// │                                                                                                   │
// └───────────────────────────────────────────────────────────────────────────────────────────────────┘

// The minimum difference between the lower and upper hysteresis. This is important to not have the key continuously
// actuate if you do very very slight movements or if the fluctuation is simply too high. It also defines the gap there
// has to be between the defined TRAVEL_DISTANCE_IN_0_01MM and the upper hysteresis so the actuation logic cannot
// possibly get stuck if you press the key down but happen to not be able to get back up enough.
#define HYSTERESIS_TOLERANCE 10

// The minimum value for the rapid trigger sensitivities. This is important to not have the key continuously
// continuously actuate if you do very very slight movements or if the fluctuation is simply too high.
#define RAPID_TRIGGER_TOLERANCE 10

// The threshold when a key is considered fully released. 10 would mean if the key is <0.1mm pressed.
// This value is important to reset the rapid trigger state properly with continuous rapid trigger.
#define CONTINUOUS_RAPID_TRIGGER_THRESHOLD 10

// This number will be substracted from the rest position on calibration to introduce a deadzone at the boundaries.
// This might be desired since values might fluctuate. e.g. if the value fluctuates around 1970 but peaks at 1975,
// this would counteract it. 7 may seem like much at first but when "smashing" the button a lot it'll be just right.
#define AUTO_CALIBRATION_DEADZONE 7

// The resolution for the ADCs on the RP2040. The theoretical maximum value on it is 16 bit (uint16_t).
#define ANALOG_RESOLUTION 12

// The exponent for the amount of samples for the SMA filter. This filter reduces fluctuation of analog values.
// A value too high may cause unresponsiveness. 1 = 1 sample, 2 = 4 samples, 3 = 8 samples, 4 = 16 samples, ...
#define SMA_FILTER_SAMPLE_EXPONENT 4

// Hall effect switch magnet property definitions used for generating gauss-distance lookup table.
// All units are specified in meters, meaning 1mm = 0.001.
#define MAGNET_RADIUS 0.2
#define MAGNET_THICKNESS 0.2
#define MAGNET_RESIDUAL_INDUCTION 1280

// The travel distance of the switches, where 1 unit equals 0.01mm. This is used to map the values properly to
// guarantee that the unit for the numbers used across the firmware actually matches the milimeter metric.
#define TRAVEL_DISTANCE_IN_0_01MM 400

// Uncomment this line if the sensor readings go up when the key is being pressed down.
// By default, the firmware is made to handle the readings going down and not up.
// #define INVERT_SENSOR_READINGS

// The delay for the debounce on digital keys. This is necessary because the contacts on digital buttons "bounce",
// meaning instead of a steady HIGH signal you'll get a couple signal changes (e.g. HIGH LOW HIGH LOW HIGH)
// This millisecond delay is the minimum time between button presses for the HID signal to send to the host device.
#define DIGITAL_DEBOUNCE_DELAY 50

// Macro for getting the hall effect sensor pin of the specified key index. The pin order is being swapped here,
// meaning on a 3-key device the pins are 28, 27 and 26. This macro has to be adjusted, depending on how the PCB
// and hardware of the device using this firmware has been designed. The A0 constant is 26 in the RP2040 environment.
// NOTE: By the uint8 datatype, the amount of keys is limited to 255.
// NOTE: By the default config initialization, the amount of keys is limited to
//       around 26 since the characters are assigned backwards started from 'z'.
// NOTE: By the RP2040, the amount of analog pins (and therefore keys) is limited o 4.
#define HE_PIN(index) A0 + HE_KEYS - index - 1

// Macro for getting the pin of the specified index of the digital key. The pin order is not swapped here, meaning
// the first digital key is on pin 0, the second on 1, and so on.
// NOTE: This way, the amount of keys is limited to 26 since the 27th key overlaps with the first analog port, 26.
#define DIGITAL_PIN(index) 0 + DIGITAL_KEYS - index - 1

// Add a compiler error if the firmware is being tried to built with more than the supported 4 keys.
// (only 4 ADC pins available)
#if HE_KEYS > 4
#error As of right now, the firmware only supports up to 4 hall effect keys.
#endif

// Add a compiler error if the firmware is being tried to built with more than the supported 26 digital keys.
// (limited amount of ports + characters)
#if DIGITAL_KEYS > 26
#error As of right now, the firmware only supports up to 26 digital keys.
#endif

// If the debug flag is not set via compiler parameters, default it to 0 since it's required for if statements.
#ifndef DEV
#define DEV 0
#endif

inline uint16_t lut[4096] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1, 2, 2, 2, 2, 2,
        2, 3, 3, 3, 3, 3, 4, 4,
        4, 4, 4, 4, 5, 5, 5, 5,
        5, 5, 6, 6, 6, 6, 6, 7,
        7, 7, 7, 7, 7, 8, 8, 8,
        8, 8, 8, 9, 9, 9, 9, 9,
        10, 10, 10, 10, 10, 10, 11, 11,
        11, 11, 11, 12, 12, 12, 12, 12,
        12, 13, 13, 13, 13, 13, 14, 14,
        14, 14, 14, 14, 15, 15, 15, 15,
        15, 15, 16, 16, 16, 16, 16, 17,
        17, 17, 17, 17, 18, 18, 18, 18,
        18, 18, 19, 19, 19, 19, 19, 20,
        20, 20, 20, 20, 20, 21, 21, 21,
        21, 21, 22, 22, 22, 22, 22, 23,
        23, 23, 23, 23, 23, 24, 24, 24,
        24, 24, 25, 25, 25, 25, 25, 26,
        26, 26, 26, 26, 26, 27, 27, 27,
        27, 27, 28, 28, 28, 28, 28, 29,
        29, 29, 29, 29, 30, 30, 30, 30,
        30, 30, 31, 31, 31, 31, 31, 32,
        32, 32, 32, 32, 33, 33, 33, 33,
        33, 34, 34, 34, 34, 34, 35, 35,
        35, 35, 35, 36, 36, 36, 36, 36,
        37, 37, 37, 37, 37, 38, 38, 38,
        38, 38, 39, 39, 39, 39, 39, 40,
        40, 40, 40, 40, 41, 41, 41, 41,
        41, 42, 42, 42, 42, 42, 43, 43,
        43, 43, 43, 44, 44, 44, 44, 44,
        45, 45, 45, 45, 45, 46, 46, 46,
        46, 47, 47, 47, 47, 47, 48, 48,
        48, 48, 48, 49, 49, 49, 49, 49,
        50, 50, 50, 50, 51, 51, 51, 51,
        51, 52, 52, 52, 52, 53, 53, 53,
        53, 53, 54, 54, 54, 54, 54, 55,
        55, 55, 55, 56, 56, 56, 56, 56,
        57, 57, 57, 57, 58, 58, 58, 58,
        58, 59, 59, 59, 59, 60, 60, 60,
        60, 60, 61, 61, 61, 61, 62, 62,
        62, 62, 63, 63, 63, 63, 63, 64,
        64, 64, 64, 65, 65, 65, 65, 66,
        66, 66, 66, 67, 67, 67, 67, 67,
        68, 68, 68, 68, 69, 69, 69, 69,
        70, 70, 70, 70, 71, 71, 71, 71,
        72, 72, 72, 72, 73, 73, 73, 73,
        73, 74, 74, 74, 74, 75, 75, 75,
        75, 76, 76, 76, 76, 77, 77, 77,
        78, 78, 78, 78, 79, 79, 79, 79,
        80, 80, 80, 80, 81, 81, 81, 81,
        82, 82, 82, 82, 83, 83, 83, 83,
        84, 84, 84, 85, 85, 85, 85, 86,
        86, 86, 86, 87, 87, 87, 87, 88,
        88, 88, 89, 89, 89, 89, 90, 90,
        90, 91, 91, 91, 91, 92, 92, 92,
        92, 93, 93, 93, 94, 94, 94, 94,
        95, 95, 95, 96, 96, 96, 96, 97,
        97, 97, 98, 98, 98, 99, 99, 99,
        99, 100, 100, 100, 101, 101, 101, 101,
        102, 102, 102, 103, 103, 103, 104, 104,
        104, 105, 105, 105, 105, 106, 106, 106,
        107, 107, 107, 108, 108, 108, 109, 109,
        109, 110, 110, 110, 111, 111, 111, 111,
        112, 112, 112, 113, 113, 113, 114, 114,
        114, 115, 115, 115, 116, 116, 116, 117,
        117, 117, 118, 118, 118, 119, 119, 120,
        120, 120, 121, 121, 121, 122, 122, 122,
        123, 123, 123, 124, 124, 124, 125, 125,
        126, 126, 126, 127, 127, 127, 128, 128,
        128, 129, 129, 130, 130, 130, 131, 131,
        131, 132, 132, 133, 133, 133, 134, 134,
        135, 135, 135, 136, 136, 136, 137, 137,
        138, 138, 138, 139, 139, 140, 140, 141,
        141, 141, 142, 142, 143, 143, 143, 144,
        144, 145, 145, 145, 146, 146, 147, 147,
        148, 148, 148, 149, 149, 150, 150, 151,
        151, 152, 152, 152, 153, 153, 154, 154,
        155, 155, 156, 156, 157, 157, 157, 158,
        158, 159, 159, 160, 160, 161, 161, 162,
        162, 163, 163, 164, 164, 165, 165, 166,
        166, 167, 167, 168, 168, 169, 169, 170,
        170, 171, 171, 172, 172, 173, 173, 174,
        174, 175, 176, 176, 177, 177, 178, 178,
        179, 179, 180, 180, 181, 182, 182, 183,
        183, 184, 184, 185, 186, 186, 187, 187,
        188, 189, 189, 190, 190, 191, 192, 192,
        193, 193, 194, 195, 195, 196, 197, 197,
        198, 199, 199, 200, 201, 201, 202, 203,
        203, 204, 205, 205, 206, 207, 207, 208,
        209, 209, 210, 211, 212, 212, 213, 214,
        214, 215, 216, 217, 217, 218, 219, 220,
        220, 221, 222, 223, 224, 224, 225, 226,
        227, 228, 228, 229, 230, 231, 232, 233,
        233, 234, 235, 236, 237, 238, 239, 240,
        241, 241, 242, 243, 244, 245, 246, 247,
        248, 249, 250, 251, 252, 253, 254, 255,
        256, 257, 258, 259, 260, 261, 262, 263,
        264, 265, 266, 268, 269, 270, 271, 272,
        273, 274, 276, 277, 278, 279, 280, 282,
        283, 284, 285, 287, 288, 289, 291, 292,
        293, 295, 296, 297, 299, 300, 301, 303,
        304, 306, 307, 309, 310, 312, 313, 315,
        317, 318, 320, 321, 323, 325, 326, 328,
        330, 332, 333, 335, 337, 339, 341, 343,
        345, 347, 349, 351, 353, 355, 357, 359,
        361, 363, 365, 368, 370, 372, 375, 377,
        379, 382, 384, 387, 389, 392, 395, 398,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400,
        400, 400, 400, 400, 400, 400, 400, 400};
