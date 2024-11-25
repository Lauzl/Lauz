// Marlin/src/module/temperature.h
// Fügen Sie diese Deklarationen zur bestehenden temperature.h hinzu:

extern uint8_t fanSpeeds[FAN_COUNT];
void set_fan_speed(uint8_t fan, uint8_t speed);