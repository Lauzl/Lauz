// Integration in die Bewegungssteuerung
// src/module/motion.cpp

void prepare_move_to_destination() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (!PositionMonitor::validate_move(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS])) {
            SERIAL_ECHOLNPGM("Move outside work area!");
            return;
        }
    #endif

    // Bestehender Bewegungscode...
}

// Erweiterung der Homingfunktion
void homeaxis(const AxisEnum axis) {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
            // Nach dem Homing Offset berücksichtigen
            if (axis == X_AXIS || axis == Y_AXIS) {
                float offset_x = (axis == X_AXIS) ? work_area_handler.get_offset_x() : 0;
                float offset_y = (axis == Y_AXIS) ? work_area_handler.get_offset_y() : 0;
                
                current_position[axis] = (axis == X_AXIS) ? offset_x : offset_y;
                sync_plan_position();
            }
        }
    #endif
    
    // Bestehender Homing-Code...
}