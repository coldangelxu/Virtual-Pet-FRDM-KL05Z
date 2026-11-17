#ifndef SERVOS_H
#define SERVOS_H

#include <stdint.h>
//przypisanie kanalow TPM0 do nog 

#define SERVO_FL_CH 0 // Przednia lewa PTB11
#define SERVO_FR_CH 1 // Przednia prawa PTB10
#define SERVO_BL_CH 2 // Tylnia lewa PTB9
#define SERVO_BR_CH 3 // Tylnia prawa PTB8

// przypisujemy aliasy dla danych pozycji robota
typedef enum {
    POSTURE_STANDING = 0,
    POSTURE_SITTING = 1,
    POSTURE_LYING = 2
} RobotPosture_t;

//Funkcje interfejsu

void Servos_Init(void);
void Servo_SetAngle(uint8_t channel, uint8_t angle);
void Servo_MoveTo(uint8_t target_fl, uint8_t target_fr, uint8_t target_bl, uint8_t target_br, uint16_t step_delay_ms);
void Servo_SetPosture(RobotPosture_t posture, uint16_t step_delay_ms);
void delay_ms(uint32_t ms);

#endif