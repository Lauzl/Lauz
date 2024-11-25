// Marlin/src/module/motion.cpp

void prepare_move_to_destination() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (laser_mode_active) {
            // Offset für Laser-Modus anwenden
            float target_x = destination[X_AXIS];
            float target_y = destination[Y_AXIS];
            laser_offset.apply_offsets(target_x, target_y);
            
            // Arbeitsbereich prüfen
            if (target_x < 0 || target_x > X_BED_SIZE ||
                target_y < 0 || target_y > Y_BED_SIZE) {
                SERIAL_ECHOLNPGM("Move outside work area!");
                return;
            }
            
            // Modifizierte Zielposition setzen
            destination[X_AXIS] = target_x;
            destination[Y_AXIS] = target_y;
        }
    #endif

    // Bestehender motion code...
}

// Neue Funktionen für Laser-Modus
#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    void apply_work_offset() {
        if (laser_mode_active) {
            current_position[X_AXIS] += laser_offset.get_x_offset();
            current_position[Y_AXIS] += laser_offset.get_y_offset();
            sync_plan_position();
        }
    }

    void remove_work_offset() {
        if (laser_mode_active) {
            current_position[X_AXIS] -= laser_offset.get_x_offset();
            current_position[Y_AXIS] -= laser_offset.get_y_offset();
            sync_plan_position();
        }
    }
#endif