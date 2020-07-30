#include "stm32f4xx.h" 
#include "RCC.h"


void TIM6_DAC_IRQHandler() {
 
    TIM6->SR = 0;
    GPIOD->ODR ^= GPIO_ODR_ODR_13;  
	
}

void set_values(unsigned int psc,unsigned int arr){
     TIM6->PSC = psc  ;
     TIM6->ARR = arr  ;

}

int main() {
	 int counter = 0;
	//5 sec
	  unsigned int psc1 = 41999;
		unsigned int arr1 = 1999;
	
	  unsigned int psc2 = 41999;
		unsigned int arr2 = 100;
	
	  unsigned int psc3 = 41999;
		unsigned int arr3 = 100;
	  //500 ms
	  unsigned int psc4 = 20999;
	  unsigned int arr4 = 9999;
 
   	RCC->AHB1ENR |= 0x00000009;   // Enable GPIOD clock and GPIOA
    GPIOD->MODER |= GPIO_MODER_MODER13_0;   // Enable output mode for
 
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;   // Enable TIM6 clock 
    TIM6->DIER |= TIM_DIER_UIE;   // Enable interrupt on update event
	//setting prescaler and arr values (default values)
     TIM6->PSC = 0  ;
     TIM6->ARR = 0  ;
	
    TIM6->CR1 |= TIM_CR1_CEN;   // Enable TIM6 counter
 
    while(1) {
 
      if(GPIOA->IDR & 0x000000001 && counter == 0){
				set_values(psc1,arr1);
			 NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ
				counter ++;
			
			}
     else if(GPIOA->IDR & 0x000000001 && counter == 1)	
		 {			 
      set_values(psc2,arr2);
			 NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ
				counter ++;
    }
		else if(GPIOA->IDR & 0x000000001 && counter == 2){
		
		   set_values(psc3,arr3);
			 NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ
				counter ++;
			}
		
		else if(GPIOA->IDR & 0x000000001 && counter == 3){
		
		   set_values(psc4,arr4);
			 NVIC_EnableIRQ(TIM6_DAC_IRQn); // Enable TIM6 IRQ
				counter = 0;
		
		}
   
}
		
 }






