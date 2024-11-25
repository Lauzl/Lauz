// src/lcd/menu/menu_main.cpp


void menu_main() {
  START_MENU();
  MENU_BACK(MSG_INFO_SCREEN);

  // Hauptmenü mit Modusauswahl
  const bool is_printer_mode = (mode_switch.get_current_mode() == ModeSwitch::MODE_3D_PRINTER);
  
  // 3D-Drucker-Modus Button
  if (is_printer_mode) {
    MENU_ITEM_TOGGLE(
      true,                           // Aktiv
      "3D PRINTER",                   // Text
      nullptr,                        // Kein alternativer Text nötig
      []{ mode_switch.switch_mode(ModeSwitch::MODE_LASER); }  // Click Handler
    );
  }
  
  // Laser-Modus Button
  if (!is_printer_mode) {
    MENU_ITEM_TOGGLE(
      true,                           // Aktiv
      "LASER",                        // Text
      nullptr,                        // Kein alternativer Text nötig
      []{ mode_switch.switch_mode(ModeSwitch::MODE_3D_PRINTER); }  // Click Handler
    );
  }

  // Modusabhängige Menüpunkte
  if (is_printer_mode) {
    MENU_ITEM(submenu, "PRINT", menu_print);
    MENU_ITEM(submenu, "CONTROL", menu_motion);
    MENU_ITEM(submenu, "SETTINGS", menu_configuration);
    MENU_ITEM(submenu, "INFO", menu_info);
  }
  else {
    MENU_ITEM(submenu, "LASER CONTROL", menu_laser_control);
    MENU_ITEM(submenu, "LASER SETTINGS", menu_laser_settings);
    MENU_ITEM(submenu, "INFO", menu_info);
  }

  END_MENU();
}

// Startbildschirm mit Modusauswahl
void menu_mode_select() {
  START_MENU();
  
  MENU_ITEM_TOGGLE(
    true,
    "3D PRINTER MODE",
    nullptr,
    []{ 
      mode_switch.switch_mode(ModeSwitch::MODE_3D_PRINTER);
      ui.return_to_status();
    }
  );
  
  MENU_ITEM_TOGGLE(
    true,
    "LASER MODE",
    nullptr,
    []{ 
      mode_switch.switch_mode(ModeSwitch::MODE_LASER);
      ui.return_to_status();
    }
  );
  
  END_MENU();
}

// Boot-Screen anpassen
void MarlinUI::init() {
  init_lcd();
  
  // LAUZ WORKSTATION Boot Screen
  clear_lcd();
  draw_centered_text("LAUZ WORKSTATION", u8g.getHeight() / 3);
  refresh();
  
  safe_delay(2000);  // 2 Sekunden anzeigen
  
  // Direkt zum Modus-Auswahlmenü
  goto_screen(menu_mode_select);
}

// Status-Screen anpassen
void MarlinUI::draw_status_screen() {
  const char* mode_text = (mode_switch.get_current_mode() == ModeSwitch::MODE_3D_PRINTER) ? 
                          "3D PRINTER MODE" : "LASER MODE";
                          
  // Modus in Kopfzeile anzeigen
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(0, 8);
  u8g.print(mode_text);
  
  // Restlicher Status-Screen...
}

// Helper-Funktion für zentrierten Text
void MarlinUI::draw_centered_text(const char* text, uint8_t y) {
  uint8_t x = (u8g.getWidth() - (strlen(text) * 6)) / 2;
  u8g.setPrintPos(x, y);
  u8g.print(text);
}