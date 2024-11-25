#ifndef STATUS_SCREEN_DOGM_H
#define STATUS_SCREEN_DOGM_H

#include "../../inc/MarlinConfig.h"

#define STATUS_LASER_START_Y 10
#define STATUS_LASER_END_Y   19

void draw_status_screen();
void draw_status_message(bool blink);

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    void _draw_laser_status(bool blink);
#endif

#endif // STATUS_SCREEN_DOGM_H