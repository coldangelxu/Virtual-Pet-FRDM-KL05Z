	#include "MKL05Z4.h"
	#include "frdm_bsp.h"
	#include "lcd1602.h"
	#include "klaw.h"
	#include "TPM.h"
	#include "tsi.h"
	#include "i2c.h"
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#define LED_RED 0

	static const uint32_t MaskLED[] = {1UL << 8};
	static void LED_Init (void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[8] = PORT_PCR_MUX(1UL);
	PTB->PDDR |= MaskLED[LED_RED];
	}
	static void LED_Blink (void) {
	uint32_t i = 0;
	PTB->PTOR = MaskLED[LED_RED];
	for(i = 0; i < 3000000; i++)__NOP();
	}
	int main (){
		LED_Init();
		TSI_Init();
		static uint8_t gesturePhase = 0;
		static uint8_t gestureTime = 0;
		int8_t currentValue = 0;
		int8_t previousValue= 0;
		int8_t difference = 0;
		while(1){
		currentValue = TSI_ReadSlider();
		difference = currentValue - previousValue;
		if (currentValue > 5 && previousValue > 5){
			gestureTime = 0;
			switch(gesturePhase){
			case 0:
								if( difference > 5 ){
									 gesturePhase = 1;
								}
								break;
			case 1:
								if( difference < -5 ){
									 gesturePhase = 2;
								}
								break;
			case 2:
								if( difference > 5 ){
									 gesturePhase = 0;
									 LED_Blink();
								}
								break;
			}
		}else{
		 gestureTime++;
		 }
		if (gestureTime > 10) {
		gesturePhase = 0;
		}
		previousValue = currentValue;
		DELAY(500);
		}
	}