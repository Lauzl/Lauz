// src/gcode/motion/G0_G1.cpp

void GcodeSuite::G0_G1(bool fast_move) {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
            // Relative Positionierung im Arbeitsbereich
            if (parser.seen('X')) {
                float x = parser.value_float();
                if (relative_mode) {
                    destination[X_AXIS] = current_position[X_AXIS] + x;
                } else {
                    destination[X_AXIS] = work_area_handler.get_offset_x() + x;
                }
            }
            
            if (parser.seen('Y')) {
                float y = parser.value_float();
                if (relative_mode) {
                    destination[Y_AXIS] = current_position[Y_AXIS] + y;
                } else {
                    destination[Y_AXIS] = work_area_handler.get_offset_y() + y;
                }
            }
            
            // Z-Achse normal verarbeiten
            if (parser.seen('Z')) {
                destination[Z_AXIS] = parser.value_linear_units() + 
                    (relative_mode ? current_position[Z_AXIS] : 0);
            }
        }
        else {
            // Normaler 3D-Drucker G0/G1 Code
            if (parser.seen('X')) destination[X_AXIS] = parser.value_linear_units();
            if (parser.seen('Y')) destination[Y_AXIS] = parser.value_linear_units();
            if (parser.seen('Z')) destination[Z_AXIS] = parser.value_linear_units();
            if (parser.seen('E')) destination[E_AXIS] = parser.value_linear_units();
        }
    #else
        // Bestehender G0/G1 Code...
    #endif

    prepare_move_to_destination();
}