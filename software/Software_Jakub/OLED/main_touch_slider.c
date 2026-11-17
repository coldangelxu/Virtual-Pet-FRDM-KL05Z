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

int main(void){
	TSI_INIT();
	static uint8_t current_value [5];
	while(1){
		
		uint8_t value = TSI_ReadSlider();
		current_value[0] = current_value[1];
		current_value[1] = current_value[2];
		current_value[2] = current_value[3];
		current_value[3] = current_value[4];
		current_value[4] = value;

		if (current_value[0] < current_value[1] && 
				current_value[1] < current_value[2] && 
				current_value[2] < current_value[3] && 
				current_value[3] < current_value[4]){
					//do animation and sound
				}
		for (int i = 0; i < 5; i++){
			current_value[i] = 0;
		}	
	}
}
