// status_screen.cpp
// In der draw_status_screen Funktion:

void MarlinUI::draw_status_screen() {
  #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
    // Modus-Anzeige
    const char* mode_text = (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) ? 
                            "LASER MODE" : "3D PRINT MODE";
    lcd.setCursor(0, 0);
    lcd.print(mode_text);
    
    // Arbeitsbereich-Info
    if (mode_switch.get_current_mode() == ModeSwitch::MODE_LASER) {
      lcd.setCursor(0, 1);
      lcd.print("Area: ");
      lcd.print(work_area_handler.get_current_size_x());
      lcd.print("x");
      lcd.print(work_area_handler.get_current_size_y());
      
      lcd.setCursor(0, 2);
      lcd.print("Offset: ");
      lcd.print(work_area_handler.get_current_offset_x());
      lcd.print(",");
      lcd.print(work_area_handler.get_current_offset_y());
    }
  #endif

  // Bestehender Status-Screen Code...
}