#include "servos.h" 
#include "systick.h"
#include "TPM.h"
#include "MKL05Z4.h"

static uint8_t current_angles[4] = {90,90,90,90}; // tablica przechowujaca aktualne katy 4 serw (startowo 90 st)

//Inicjalizacja timera TPMO0 oraz pinow z PORTB dla serw
void Servos_Init(void){
   PWM_Init();
}
// zmiana kata pojedynczego serwa i aktualizacja pozycji w pamieci
void Servo_SetAngle(uint8_t channel, uint8_t angle){
    if (channel > 3) return;
    if (angle > 180) angle = 180;

    //przeliczanie kata na czas impulsu PWM

    uint16_t cnv_val = 1500 + ((uint32_t)angle * 5700) / 180;
    TPM0->CONTROLS[channel].CnV = cnv_val;

    current_angles[channel] = angle;
}
// plynna zmiana katow 
void Servo_MoveTo(uint8_t target_fl, uint8_t target_fr, uint8_t target_bl, uint8_t target_br, uint16_t step_delay_ms){
    uint8_t target_angles[4] = {target_fl, target_fr, target_bl, target_br};
    uint8_t all_reached = 0;
    
    while(!all_reached){
        all_reached = 1; //cel osiagniety

        for(uint8_t i = 0; i < 4; i++){
            if(current_angles[i] < target_angles[i]){
                current_angles[i]++;
                Servo_SetAngle(i, current_angles[i]);
                all_reached = 0;
            }
            else if (current_angles[i] > target_angles[i]){
                current_angles[i]--;
                Servo_SetAngle(i, current_angles[i]);
                all_reached = 0;

            }
        }
        // Uzycie sprzetowego opoznienia SysTick
        delay_ms(step_delay_ms);
    }
}
//plynna zmiana 4 nozek
void Servo_SetPosture(RobotPosture_t posture, uint16_t step_delay_ms){
    switch(posture){
        case POSTURE_STANDING:
            Servo_MoveTo(90,90,90,90, step_delay_ms);
            break;
        case POSTURE_SITTING:
            Servo_MoveTo(90,90,160,160, step_delay_ms);
            break;
        case POSTURE_LYING:
            Servo_MoveTo(170,170,170,170, step_delay_ms);
            break;
    }
}
