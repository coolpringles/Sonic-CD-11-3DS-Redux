#include "RetroEngine.hpp"

#include <algorithm>
#include <vector>

InputData keyPress = InputData();
InputData keyDown  = InputData();

bool anyPress = false;

int touchDown[8];
int touchX[8];
int touchY[8];
int touchID[8];
int touches = 0;

int hapticEffectNum = -2;

enum AndroidHapticIDs {
    HAPTIC_ALERT1                         = 63,
    HAPTIC_ALERT10                        = 72,
    HAPTIC_ALERT2                         = 64,
    HAPTIC_ALERT3                         = 65,
    HAPTIC_ALERT4                         = 66,
    HAPTIC_ALERT5                         = 67,
    HAPTIC_ALERT6                         = 68,
    HAPTIC_ALERT7                         = 69,
    HAPTIC_ALERT8                         = 70,
    HAPTIC_ALERT9                         = 71,
    HAPTIC_BOUNCE_100                     = 9,
    HAPTIC_BOUNCE_33                      = 11,
    HAPTIC_BOUNCE_66                      = 10,
    HAPTIC_BUMP_100                       = 6,
    HAPTIC_BUMP_33                        = 8,
    HAPTIC_BUMP_66                        = 7,
    HAPTIC_DOUBLE_BUMP_100                = 18,
    HAPTIC_DOUBLE_BUMP_33                 = 20,
    HAPTIC_DOUBLE_BUMP_66                 = 19,
    HAPTIC_DOUBLE_SHARP_CLICK_100         = 12,
    HAPTIC_DOUBLE_SHARP_CLICK_33          = 14,
    HAPTIC_DOUBLE_SHARP_CLICK_66          = 13,
    HAPTIC_DOUBLE_STRONG_CLICK_100        = 15,
    HAPTIC_DOUBLE_STRONG_CLICK_33         = 17,
    HAPTIC_DOUBLE_STRONG_CLICK_66         = 16,
    HAPTIC_ENGINE1_100                    = 112,
    HAPTIC_ENGINE1_33                     = 114,
    HAPTIC_ENGINE1_66                     = 113,
    HAPTIC_ENGINE2_100                    = 115,
    HAPTIC_ENGINE2_33                     = 117,
    HAPTIC_ENGINE2_66                     = 116,
    HAPTIC_ENGINE3_100                    = 118,
    HAPTIC_ENGINE3_33                     = 120,
    HAPTIC_ENGINE3_66                     = 119,
    HAPTIC_ENGINE4_100                    = 121,
    HAPTIC_ENGINE4_33                     = 123,
    HAPTIC_ENGINE4_66                     = 122,
    HAPTIC_EXPLOSION1                     = 73,
    HAPTIC_EXPLOSION10                    = 82,
    HAPTIC_EXPLOSION2                     = 74,
    HAPTIC_EXPLOSION3                     = 75,
    HAPTIC_EXPLOSION4                     = 76,
    HAPTIC_EXPLOSION5                     = 77,
    HAPTIC_EXPLOSION6                     = 78,
    HAPTIC_EXPLOSION7                     = 79,
    HAPTIC_EXPLOSION8                     = 80,
    HAPTIC_EXPLOSION9                     = 81,
    HAPTIC_FAST_PULSE_100                 = 45,
    HAPTIC_FAST_PULSE_33                  = 47,
    HAPTIC_FAST_PULSE_66                  = 46,
    HAPTIC_FAST_PULSING_100               = 48,
    HAPTIC_FAST_PULSING_33                = 50,
    HAPTIC_FAST_PULSING_66                = 49,
    HAPTIC_IMPACT_METAL_100               = 96,
    HAPTIC_IMPACT_METAL_33                = 98,
    HAPTIC_IMPACT_METAL_66                = 97,
    HAPTIC_IMPACT_RUBBER_100              = 99,
    HAPTIC_IMPACT_RUBBER_33               = 101,
    HAPTIC_IMPACT_RUBBER_66               = 100,
    HAPTIC_IMPACT_WOOD_100                = 93,
    HAPTIC_IMPACT_WOOD_33                 = 95,
    HAPTIC_IMPACT_WOOD_66                 = 94,
    HAPTIC_LONG_BUZZ_100                  = 27,
    HAPTIC_LONG_BUZZ_33                   = 29,
    HAPTIC_LONG_BUZZ_66                   = 28,
    HAPTIC_LONG_TRANSITION_RAMP_DOWN_100  = 39,
    HAPTIC_LONG_TRANSITION_RAMP_DOWN_33   = 41,
    HAPTIC_LONG_TRANSITION_RAMP_DOWN_66   = 40,
    HAPTIC_LONG_TRANSITION_RAMP_UP_100    = 33,
    HAPTIC_LONG_TRANSITION_RAMP_UP_33     = 35,
    HAPTIC_LONG_TRANSITION_RAMP_UP_66     = 34,
    HAPTIC_SHARP_CLICK_100                = 0,
    HAPTIC_SHARP_CLICK_33                 = 2,
    HAPTIC_SHARP_CLICK_66                 = 1,
    HAPTIC_SHORT_BUZZ_100                 = 30,
    HAPTIC_SHORT_BUZZ_33                  = 32,
    HAPTIC_SHORT_BUZZ_66                  = 31,
    HAPTIC_SHORT_TRANSITION_RAMP_DOWN_100 = 42,
    HAPTIC_SHORT_TRANSITION_RAMP_DOWN_33  = 44,
    HAPTIC_SHORT_TRANSITION_RAMP_DOWN_66  = 43,
    HAPTIC_SHORT_TRANSITION_RAMP_UP_100   = 36,
    HAPTIC_SHORT_TRANSITION_RAMP_UP_33    = 38,
    HAPTIC_SHORT_TRANSITION_RAMP_UP_66    = 37,
    HAPTIC_SLOW_PULSE_100                 = 51,
    HAPTIC_SLOW_PULSE_33                  = 53,
    HAPTIC_SLOW_PULSE_66                  = 52,
    HAPTIC_SLOW_PULSING_100               = 54,
    HAPTIC_SLOW_PULSING_33                = 56,
    HAPTIC_SLOW_PULSING_66                = 55,
    HAPTIC_STRONG_CLICK_100               = 3,
    HAPTIC_STRONG_CLICK_33                = 5,
    HAPTIC_STRONG_CLICK_66                = 4,
    HAPTIC_TEXTURE1                       = 102,
    HAPTIC_TEXTURE10                      = 111,
    HAPTIC_TEXTURE2                       = 103,
    HAPTIC_TEXTURE3                       = 104,
    HAPTIC_TEXTURE4                       = 105,
    HAPTIC_TEXTURE5                       = 106,
    HAPTIC_TEXTURE6                       = 107,
    HAPTIC_TEXTURE7                       = 108,
    HAPTIC_TEXTURE8                       = 109,
    HAPTIC_TEXTURE9                       = 110,
    HAPTIC_TICK_100                       = 24,
    HAPTIC_TICK_33                        = 26,
    HAPTIC_TICK_66                        = 25,
    HAPTIC_TRANSITION_BOUNCE_100          = 60,
    HAPTIC_TRANSITION_BOUNCE_33           = 62,
    HAPTIC_TRANSITION_BOUNCE_66           = 61,
    HAPTIC_TRANSITION_BUMP_100            = 57,
    HAPTIC_TRANSITION_BUMP_33             = 59,
    HAPTIC_TRANSITION_BUMP_66             = 58,
    HAPTIC_TRIPLE_STRONG_CLICK_100        = 21,
    HAPTIC_TRIPLE_STRONG_CLICK_33         = 23,
    HAPTIC_TRIPLE_STRONG_CLICK_66         = 22,
    HAPTIC_WEAPON1                        = 83,
    HAPTIC_WEAPON10                       = 92,
    HAPTIC_WEAPON2                        = 84,
    HAPTIC_WEAPON3                        = 85,
    HAPTIC_WEAPON4                        = 86,
    HAPTIC_WEAPON5                        = 87,
    HAPTIC_WEAPON6                        = 88,
    HAPTIC_WEAPON7                        = 89,
    HAPTIC_WEAPON8                        = 90,
    HAPTIC_WEAPON9                        = 91,
};

#if !RETRO_USE_ORIGINAL_CODE
#include <algorithm>
#include <vector>

InputButton inputDevice[INPUT_BUTTONCOUNT];
int inputType = 0;

// mania deadzone vals lol
float LSTICK_DEADZONE   = 0.3;
float RSTICK_DEADZONE   = 0.3;
float LTRIGGER_DEADZONE = 0.3;
float RTRIGGER_DEADZONE = 0.3;

int mouseHideTimer = 0;
int lastMouseX     = 0;
int lastMouseY     = 0;

void ProcessInput()
{
    hidScanInput();
    u32 kHeld = hidKeysHeld();

    for (int i = 0; i < INPUT_ANY; i++) {
        if (kHeld & inputDevice[i].keyMappings) {
            inputDevice[i].setHeld();
            if (!inputDevice[INPUT_ANY].hold)
                inputDevice[INPUT_ANY].setHeld();
        }
        else if (inputDevice[i].hold)
            inputDevice[i].setReleased();
    }

    bool isPressed = false;
    for (int i = 0; i < INPUT_BUTTONCOUNT; i++) {
        if (kHeld & inputDevice[i].keyMappings) {
            isPressed = true;
            break;
        }
    }
    if (isPressed)
        inputType = 0;
    else if (inputType == 0)
        inputDevice[INPUT_ANY].setReleased();

    if (inputDevice[INPUT_ANY].press || inputDevice[INPUT_ANY].hold || touches > 1) {
        Engine.dimTimer = 0;
    }
    else if (Engine.dimTimer < Engine.dimLimit && !Engine.masterPaused) {
        ++Engine.dimTimer;
    }
}
#endif //! !RETRO_USE_ORIGINAL_CODE

void CheckKeyPress(InputData *input, byte flags)
{
    if (flags & 0x1)
        input->up = inputDevice[INPUT_UP].press;
    if (flags & 0x2)
        input->down = inputDevice[INPUT_DOWN].press;
    if (flags & 0x4)
        input->left = inputDevice[INPUT_LEFT].press;
    if (flags & 0x8)
        input->right = inputDevice[INPUT_RIGHT].press;
    if (flags & 0x10)
        input->A = inputDevice[INPUT_BUTTONA].press;
    if (flags & 0x20)
        input->B = inputDevice[INPUT_BUTTONB].press;
    if (flags & 0x40)
        input->C = inputDevice[INPUT_BUTTONC].press;
    if (flags & 0x80)
        input->start = inputDevice[INPUT_START].press;
    if (flags & 0x80) {
        anyPress = inputDevice[INPUT_ANY].press;
        if (!anyPress) {
            for (int t = 0; t < touches; ++t) {
                if (touchDown[t])
                    anyPress = true;
            }
        }

        SetGlobalVariableByName("input.pressButton", anyPress);
    }
}

void CheckKeyDown(InputData *input, byte flags)
{
    if (flags & 0x1)
        input->up = inputDevice[INPUT_UP].hold;
    if (flags & 0x2)
        input->down = inputDevice[INPUT_DOWN].hold;
    if (flags & 0x4)
        input->left = inputDevice[INPUT_LEFT].hold;
    if (flags & 0x8)
        input->right = inputDevice[INPUT_RIGHT].hold;
    if (flags & 0x10)
        input->A = inputDevice[INPUT_BUTTONA].hold;
    if (flags & 0x20)
        input->B = inputDevice[INPUT_BUTTONB].hold;
    if (flags & 0x40)
        input->C = inputDevice[INPUT_BUTTONC].hold;
    if (flags & 0x80)
        input->start = inputDevice[INPUT_START].hold;
}

#if RETRO_USE_HAPTICS
void QueueHapticEffect(int hapticID)
{
    if (Engine.hapticsEnabled) {
        // Haptic ID seems to be the ID for "Universal Haptic Layer"'s haptic effect library
        hapticEffectNum = hapticID;
    }
}

void PlayHaptics(int left, int right, int power) {}
void PlayHapticsID(int hapticID) {}
void StopHaptics(int hapticID) {}
#endif
