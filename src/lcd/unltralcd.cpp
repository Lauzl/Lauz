// src/lcd/ultralcd.cpp
void MarlinUI::status_screen() {
  // ... bestehender Status-Screen-Code ...

  #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    // Modus-Anzeige
    const char* mode_str = (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) ? 
                          "LASER MODE" : "3D PRINTER";
    lcd_moveto(0, 0);
    lcd_put_u8str(mode_str);

    // Im Laser-Modus: Arbeitsbereich-Info anzeigen
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
      char buffer[21];
      
      // Arbeitsbereich-Größe
      sprintf_P(buffer, PSTR("Area: %dx%d"), 
        (int)work_area_handler.get_current_size_x(),
        (int)work_area_handler.get_current_size_y()
      );
      lcd_moveto(0, 1);
      lcd_put_u8str(buffer);

      // Offset
      sprintf_P(buffer, PSTR("Offset: %d,%d"),
        (int)work_area_handler.get_current_offset_x(),
        (int)work_area_handler.get_current_offset_y()
      );
      lcd_moveto(0, 2);
      lcd_put_u8str(buffer);
    }
  #endif

  // ... weiterer Status-Screen-Code ...
}

// Boot-Screen anpassen
void MarlinUI::show_bootscreen() {
  #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    static const unsigned char bootscreen_bmp[] PROGMEM = {
      // Custom Boot-Screen Bitmap für LAUZ WORKSTATION
      // ... Bitmap-Daten ...
    };
    
    lcd_moveto((LCD_WIDTH - u8g.getStrWidth(CUSTOM_MACHINE_NAME)) / 2, 20);
    lcd_put_u8str(CUSTOM_MACHINE_NAME);
    
    u8g.drawBitmapP((LCD_WIDTH - 64) / 2, 30, 8, 32, bootscreen_bmp);
    
    lcd_moveto((LCD_WIDTH - u8g.getStrWidth(SHORT_BUILD_VERSION)) / 2, 60);
    lcd_put_u8str(SHORT_BUILD_VERSION);
  #endif
}