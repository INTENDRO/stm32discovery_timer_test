#include <stm32f4xx.h>


void timer9InitOutputCompare(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	
	TIM9->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0;
	
	TIM9->CNT = 0;
	TIM9->PSC = 0;
	TIM9->ARR = 20000;
	TIM9->CCR1 = 16000;
	
	TIM9->EGR = TIM_EGR_UG;
	
	
	TIM9->CCER = TIM_CCER_CC1E;
	TIM9->CR1 = TIM_CR1_CEN;
	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	
	GPIOF->MODER |= GPIO_MODER_MODE0_1;
	GPIOF->AFR[0] = GPIO_AFRL_AFRL0_0 | GPIO_AFRL_AFRL0_1;
}

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

int main(void)
{
	SystemInit();
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN;
	
	GPIOG->MODER |= GPIO_MODER_MODE13_0 | GPIO_MODER_MODE14_0;
	
	timer9Init();
	
	while(1)
	{
		GPIOG->ODR |= GPIO_ODR_OD13;
		wait1ms(1000);
		GPIOG->ODR &= ~GPIO_ODR_OD13;
		wait1ms(1000);
	}

	
	while(1)
	{
		if(GPIOA->IDR & GPIO_IDR_ID0)
		{
			GPIOG->ODR |= GPIO_ODR_OD13;
			GPIOG->ODR &= ~GPIO_ODR_OD14;
		}
		else
		{
			GPIOG->ODR |= GPIO_ODR_OD14;
			GPIOG->ODR &= ~GPIO_ODR_OD13;
		}
	}
}
