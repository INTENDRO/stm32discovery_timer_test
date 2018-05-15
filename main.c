#include <stm32f4xx.h>


//void timer9InitOutputCompare(void)
//{
//	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
//	
//	TIM9->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0;
//	
//	TIM9->CNT = 0;
//	TIM9->PSC = 0;
//	TIM9->ARR = 20000;
//	TIM9->CCR1 = 16000;
//	
//	TIM9->EGR = TIM_EGR_UG;
//	
//	
//	TIM9->CCER = TIM_CCER_CC1E;
//	TIM9->CR1 = TIM_CR1_CEN;
//	
//	
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
//	
//	GPIOF->MODER |= GPIO_MODER_MODE0_1;
//	GPIOF->AFR[0] = GPIO_AFRL_AFRL0_0 | GPIO_AFRL_AFRL0_1;
//}

void timer9Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	
	TIM9->CNT = 0;
	TIM9->PSC = 0;
	TIM9->ARR = 16000;
	TIM9->EGR = TIM_EGR_UG;
	TIM9->SR = 0;
}

void wait1ms(uint16_t u16Factor)
{
	uint16_t i;
	
	for(i=0;i<u16Factor;i++)
	{
		TIM9->CR1 = TIM_CR1_CEN;
		while(!(TIM9->SR & TIM_SR_UIF));
		TIM9->SR = 0;
	}
}

void timer3PWMInit(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    
    GPIOG->MODER |= GPIO_MODER_MODE14_1;
    GPIOG->AFR[1] |= GPIO_AFRH_AFSEL14_1;
    
    TIM3->CR1 = 0;
    TIM3->CR2 = 0;
    TIM3->SMCR = 0;
    TIM3->DIER = 0;
    
    TIM3->PSC = 6;
    TIM3->EGR = (1<<0);
    TIM3->ARR = 60000;
    TIM3->CCMR1 = (0x6<<4);
    TIM3->CCER = (1<<0);
    TIM3->CCR1 = 10000;
    
    TIM3->CR1 = (1<<0);
    
}


int main(void)
{
	SystemInit();
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	
	GPIOG->MODER |= GPIO_MODER_MODE13_0;
	
	timer9Init();
    
    timer3PWMInit();
	
	while(1)
	{
		GPIOG->ODR |= GPIO_ODR_OD13;
		wait1ms(1000);
		GPIOG->ODR &= ~GPIO_ODR_OD13;
		wait1ms(1000);
	}
}
