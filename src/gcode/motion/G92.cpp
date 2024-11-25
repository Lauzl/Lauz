// src/gcode/motion/G92.cpp
void GcodeSuite::G92() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
            // Setze Arbeitsbereich-Nullpunkt
            bool didXYZ = false;
            
            if (parser.seen('X')) {
                current_position[X_AXIS] = work_area_handler.get_offset_x() + parser.value_linear_units();
                didXYZ = true;
            }
            
            if (parser.seen('Y')) {
                current_position[Y_AXIS] = work_area_handler.get_offset_y() + parser.value_linear_units();
                didXYZ = true;
            }
            
            if (parser.seen('Z')) {
                current_position[Z_AXIS] = parser.value_linear_units();
                didXYZ = true;
            }
            
            if (didXYZ)
                sync_plan_position();
        }
        else {
            // Normaler G92 Code
            bool didXYZ = false;
            
            if (parser.seen('X')) {
                current_position[X_AXIS] = parser.value_linear_units();
                didXYZ = true;
            }
            
            if (parser.seen('Y')) {
                current_position[Y_AXIS] = parser.value_linear_units();
                didXYZ = true;
            }
            
            if (parser.seen('Z')) {
                current_position[Z_AXIS] = parser.value_linear_units();
                didXYZ = true;
            }
            
            if (parser.seen('E')) {
                current_position[E_AXIS] = parser.value_linear_units();
            }
            
            if (didXYZ)
                sync_plan_position();
        }
    #else
        // Bestehender G92 Code...
    #endif
}