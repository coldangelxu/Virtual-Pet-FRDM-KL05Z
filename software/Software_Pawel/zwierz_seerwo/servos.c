#include "servos.h" 
#include "MKL05Z4.h"

static uint8_t current_angles[4] = {90,90,90,90}; // tablica przechowujaca aktualne katy 4 serw (startowo 90 st)

void delay_ms(uint32_t ms){
    volatile uint32_t i;
    for (i =0; i < ms * 3000; i++){
        ;
    }
}

//Inicjalizacja timera TPMO0 oraz pinow z PORTB dla serw
void Servos_Init(void){
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

    SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    PORTB->PCR[11] = PORT_PCR_MUX(2); // FL CH0
    PORTB->PCR[10] = PORT_PCR_MUX(2); // FR CH1
    PORTB->PCR[9] = PORT_PCR_MUX(2); // BL CH2
    PORTB->PCR[8] = PORT_PCR_MUX(2); // BR CH3

    TPM0->SC = 0;
    TPM0->MOD = 60000 - 1;
    
    for(uint8_t i = 0; i < 4; i++){
        TPM0->CONTROLS[i].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
    }

    TPM0->SC |= TPM_SC_CMOD(1) | TPM_SC_PS(4);

    for(uint8_t i = 0; i < 4; i++){
        Servo_SetAngle(i, 90);
    }
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
