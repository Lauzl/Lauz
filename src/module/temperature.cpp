// Marlin/src/module/temperature.cpp
// Fügen Sie diese Implementierung zur bestehenden temperature.cpp hinzu:

uint8_t fanSpeeds[FAN_COUNT] = { 0 };

void set_fan_speed(uint8_t fan, uint8_t speed) {
    if (fan >= FAN_COUNT) return;
    
    fanSpeeds[fan] = speed;

    #if ENABLED(REPORT_FAN_CHANGE)
        SERIAL_ECHOLNPAIR("Fan ", fan, " set to ", speed);
    #endif
    
    analogWrite(FAN_PIN, speed);
}