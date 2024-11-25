void draw_status_screen() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (laser_mode_active) {
            // Laser-Modus Status Screen
            const bool blink = get_blink();
            
            // Modus Anzeige
            lcd_put_u8str_P(5, 0, PSTR("LASER MODE"));
            
            // Position mit Offset
            float x = current_position[X_AXIS];
            float y = current_position[Y_AXIS];
            laser_offset.remove_offsets(x, y); // Zeige echte Position
            
            char buffer[21];
            sprintf_P(buffer, PSTR("X:%4.1f Y:%4.1f"), x, y);
            lcd_put_u8str(5, 15, buffer);
            
            // Arbeitsbereich
            sprintf_P(buffer, PSTR("Area: %dx%d"), 
                     (int)X_BED_SIZE, (int)Y_BED_SIZE);
            lcd_put_u8str(5, 30, buffer);
            
            // Offset
            sprintf_P(buffer, PSTR("Offset: %4.1f,%4.1f"),
                     laser_offset.get_x_offset(),
                     laser_offset.get_y_offset());
            lcd_put_u8str(5, 45, buffer);
        }
        else {
            // Normaler 3D Drucker Status Screen
            // Bestehender Status Screen Code...
        }
    #else
        // Bestehender Status Screen Code...
    #endif
}

#if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    void _draw_laser_status(bool blink) {
        #if HAS_GRAPHICAL_LCD
            // Zusätzliche Grafiken für Laser-Modus
            if (PAGE_CONTAINS(STATUS_LASER_START_Y, STATUS_LASER_END_Y)) {
                // Laser Icon
                u8g.drawBox(3, STATUS_LASER_START_Y + 1, 8, 7);
                
                // Aktive/Inaktiv Anzeige
                if (blink)
                    u8g.drawBox(13, STATUS_LASER_START_Y, 2, 9);
            }
        #endif
    }
#endif

void draw_status_message(bool blink) {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        if (laser_mode_active) {
            // Laser-Modus Statusmeldung
            _draw_laser_status(blink);
        }
    #endif

    // Bestehender Status Message Code...
}