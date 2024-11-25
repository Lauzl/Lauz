// Menü-Integration für EEPROM-Funktionen
// src/lcd/menu/menu_settings.cpp

void menu_settings() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        MENU_ITEM(function, "Save Mode Settings", []{ 
            EEPROMHandler::save_mode_settings();
            LCD_MESSAGEPGM("Settings Saved");
        });
        
        MENU_ITEM(function, "Load Mode Settings", []{ 
            if (EEPROMHandler::load_mode_settings())
                LCD_MESSAGEPGM("Settings Loaded");
            else
                LCD_MESSAGEPGM("Load Failed");
        });
        
        MENU_ITEM(function, "Reset Mode Settings", []{ 
            EEPROMHandler::reset_mode_settings();
            LCD_MESSAGEPGM("Settings Reset");
        });
    #endif
    
    // Bestehende Menüeinträge...
    END_MENU();
}