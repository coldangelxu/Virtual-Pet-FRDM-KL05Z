#include "MKL05Z4.h" 
#include "systick.h"
#include "servos.h" 
int main(void) { 
    SystemInit();
    SysTick_Init();
    Servos_Init(); //start w pozycji stojacej 
    delay_ms(1000); // Odczekaj 1s po włączeniu zasilania
    while (1) { 
        Servo_SetPosture(POSTURE_SITTING, 15); //przejscie do siadania
        delay_ms(2000); 
        Servo_SetPosture(POSTURE_LYING, 15); // przejscie z siadania do lezenia
        delay_ms(2000);
        Servo_SetPosture(POSTURE_SITTING, 20); // wybudzenie i powrot do siadania
        delay_ms(2000); 
    } 
}