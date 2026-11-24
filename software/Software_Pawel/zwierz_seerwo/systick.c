#include "systick.h" 
#include "MKL05Z4.h"

static volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
    msTicks++; //inkrementacja zliczonych ms
}

void SysTick_Init(void){
    SysTick_Config(SystemCoreClock /1000);
}
void delay_ms(uint32_t ms){
    uint32_t startTicks = msTicks;
    while((msTicks - startTicks) < ms){
        // Czekanie na naliczenie odpowiedniej liczby milisekund przez przerwanie
    }
}