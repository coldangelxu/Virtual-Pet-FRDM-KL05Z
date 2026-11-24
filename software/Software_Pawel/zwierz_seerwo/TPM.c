#include "TPM.h"
void PWM_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;			// Dołączenie sygnału zegara do portu B
	// Wybór odpowiedniej roli pinu portu B
	PORTB->PCR[8] |= PORT_PCR_MUX(2);		// BR
	PORTB->PCR[9] |= PORT_PCR_MUX(2);		// BL
	PORTB->PCR[10] |= PORT_PCR_MUX(2);      // FR
	PORTB->PCR[11] |= PORT_PCR_MUX(2);	    // FL
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;				// Dołączenie sygnału zegara do TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);			  // Wybierz źródło taktowania TPMx MCGFLLCLK=41943040Hz
	
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;					//	TPM0 w trybie zliczanie "w przód"
	TPM0->SC |= TPM_SC_PS(4);								//	Preskaler = 16 (dla 48 MHz daje taktowanie licznika 3 MHz)
	TPM0->MOD = 60000 - 1;													//	Rejestr MODULO=60000 - fwy=50Hz
	TPM0->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;	//	TPM0, kanał 0 (przednia lewa) tryb "Edge-Aligned PWM High-True (ELSB)"
	TPM0->CONTROLS[0].CnV = 4500;					// Pozycja startowa 90 stopni (1.5 ms)
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;	//	TPM0, kanał 1 (przednia prawa) tryb "Edge-Aligned PWM High-True (ELSB)"
	TPM0->CONTROLS[1].CnV = 4500;					// Pozycja startowa 90 stopni (1.5 ms)
	TPM0->CONTROLS[2].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;	//	TPM0, kanał 2 (tylnia lewa) tryb "Edge-Aligned PWM High-True (ELSB)"
	TPM0->CONTROLS[2].CnV = 4500;					// Pozycja startowa 90 stopni (1.5 ms)
	TPM0->CONTROLS[3].CnSC = TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK;	//	TPM0, kanał 3 (tylnia prawa) tryb "Edge-Aligned PWM High-True (ELSB)"
	TPM0->CONTROLS[3].CnV = 4500;					// Pozycja startowa 90 stopni (1.5 ms)
	TPM0->SC |= TPM_SC_CMOD(1);							// Włącz licznik TPM0
}
