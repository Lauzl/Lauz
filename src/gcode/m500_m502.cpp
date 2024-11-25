// src/gcode/M500_M502.cpp

void GcodeSuite::M500() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        EEPROMHandler::save_mode_settings();
    #endif
    
    // Bestehender M500 Code...
}

void GcodeSuite::M501() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        EEPROMHandler::load_mode_settings();
    #endif
    
    // Bestehender M501 Code...
}

void GcodeSuite::M502() {
    #if ENABLED(DUAL_MODE_PRINTER_AND_LASER)
        EEPROMHandler::reset_mode_settings();
    #endif
    
    // Bestehender M502 Code...
}