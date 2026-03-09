#ifndef __KNOB_H__
#define __KNOB_H__

#include "main.h"

typedef enum {
    KNOB_DIR_NONE = 0, // Î´Ðý×ª
    KNOB_DIR_LEFT = 1, // ×óÐý
    KNOB_DIR_RIGHT = 2, // ÓÒÐý
} KnobDirection;

void Knob_Init(void);
KnobDirection Knob_IsRotating(void);


#endif
