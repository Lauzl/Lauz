// src/gcode/custom_commands.cpp
#include "custom_commands.h"
#include "../module/motion.h"
#include "../module/planner.h"

void CustomGCodeHandler::process_M600() {
    if (!parser.seen('S')) return;
    
    uint8_t new_mode = parser.value_byte();
    if (new_mode <= 1) {
        mode_switch.switch_mode((ModeSwitch::PrinterMode)new_mode);
    }
}

void CustomGCodeHandler::process_M601() {
    if (mode_switch.get_current_mode() != ModeSwitch::MODE_LASER) return;
    
    if (parser.seen('X')) {
        float x_size = parser.value_float();
        work_area_handler.set_size_x(x_size);
    }
    if (parser.seen('Y')) {
        float y_size = parser.value_float();
        work_area_handler.set_size_y(y_size);
    }
}

void CustomGCodeHandler::process_M602() {
    if (mode_switch.get_current_mode() != ModeSwitch::MODE_LASER) return;
    
    if (parser.seen('X')) {
        float x_offset = parser.value_float();
        work_area_handler.set_offset_x(x_offset);
    }
    if (parser.seen('Y')) {
        float y_offset = parser.value_float();
        work_area_handler.set_offset_y(y_offset);
    }
}
