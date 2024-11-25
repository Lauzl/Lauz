// Marlin/src/lcd/menu/menu_temperature.cpp
// Fügen Sie diese Funktion zum Temperaturmenü hinzu für LCD-Kontrolle:

void menu_fan_control() {
    START_MENU();
    MENU_BACK(MSG_TEMPERATURE);

    // Fan/Laser Steuerung
    MENU_ITEM_EDIT_CALLBACK(uint8, MSG_FAN_SPEED, &fanSpeeds[0], 0, 255, []{ 
        set_fan_speed(0, fanSpeeds[0]); 
    });

    END_MENU();
}