// Configuration_adv.h
#define CONFIGURATION_ADV_H_VERSION 02010300

//===========================================================================
//============================= Temperatur Einstellungen ====================
//===========================================================================

#define THERMAL_PROTECTION_HOTENDS
#define THERMAL_PROTECTION_BED
#define THERMAL_PROTECTION_PERIOD 40        // Sekunden
#define THERMAL_PROTECTION_HYSTERESIS 4     // Grad Celsius
#define WATCH_TEMP_PERIOD 20               // Sekunden
#define WATCH_TEMP_INCREASE 2              // Grad Celsius

//===========================================================================
//============================= Mechanische Einstellungen ===================
//===========================================================================

#define SOFT_ENDSTOPS_MENU_ITEM
#define SOFT_MIN_ENDSTOPS
#define SOFT_MAX_ENDSTOPS

#define X_SOFT_ENDSTOP_MIN 0
#define Y_SOFT_ENDSTOP_MIN 0
#define Z_SOFT_ENDSTOP_MIN 0
#define X_SOFT_ENDSTOP_MAX X_BED_SIZE
#define Y_SOFT_ENDSTOP_MAX Y_BED_SIZE
#define Z_SOFT_ENDSTOP_MAX Z_MAX_POS

//===========================================================================
//============================= LCD / Controller Einstellungen ==============
//===========================================================================

#define INDIVIDUAL_AXIS_HOMING_MENU
#define LCD_TIMEOUT_TO_STATUS 15000
#define LCD_SET_PROGRESS_MANUALLY
#define SHOW_REMAINING_TIME

//===========================================================================
//============================= Mode Switch Settings ========================
//===========================================================================

#ifdef DUAL_MODE_PRINTER_AND_LASER
  // Laser Mode Safety Features
  #define LASER_SAFETY_TIMEOUT
  #define LASER_MOTION_CONTROL
  #define LASER_PWR_CONTROL
  
  // Mode Switch Handler
  #define MODE_SWITCH_PIN          PC13  // Optional: Pin für Hardware Mode Switch
  #define MODE_SWITCH_SAFETY_DELAY 1000  // Verzögerung beim Moduswechsel
#endif

//===========================================================================
//============================= Filament Runout Settings ====================
//===========================================================================

#if ENABLED(FILAMENT_RUNOUT_SENSOR)
  #define FILAMENT_RUNOUT_DISTANCE_MM 7.0
  #define FILAMENT_MOTION_SENSOR
#endif

//===========================================================================
//============================= Power Loss Recovery ========================
//===========================================================================

#define POWER_LOSS_RECOVERY
#define POWER_LOSS_PIN         PB1   // Pin für Power Loss Detection
#define POWER_LOSS_STATE      LOW   // Pin State bei Power Loss

//===========================================================================
//============================= Extra Features =============================
//===========================================================================

#define BABYSTEPPING
#define DOUBLECLICK_FOR_Z_BABYSTEPPING
#define BABYSTEP_MULTIPLICATOR_Z  4

#define LINEAR_ADVANCE
#define LIN_ADVANCE_K 0.22

#define ARC_SUPPORT
#define MM_PER_ARC_SEGMENT 1
#define MIN_ARC_SEGMENTS 24

//===========================================================================
//============================= Debug Settings =============================
//===========================================================================

//#define DEBUG_LEVELING_FEATURE
//#define DEBUG_TEMPERATURE
//#define DEBUG_MOTION