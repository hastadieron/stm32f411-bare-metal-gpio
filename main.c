
#include<stdint.h>

#define GPIOA_EN    (1U << 0)
#define GPIOC_EN    (1U << 2)
#define PIN13        13

int main(void)
{
	volatile uint32_t *pRCC_AHB1ENR =	(uint32_t*)0x40023830;
	volatile uint32_t *pGPIOA_MODER =	(uint32_t*)0x40020000;
	volatile uint32_t *pGPIOA_PUPDR =	(uint32_t*)0x4002000C;
	volatile uint32_t *pGPIOA_IDR   =	(uint32_t*)0x40020010;
	volatile uint32_t *pGPIOC_MODER =	(uint32_t*)0x40020800;
	volatile uint32_t *pGPIOC_ODR	  = (uint32_t*)0x40020814;

	// 1. Enable clock for GPIOA and GPIOC peripherals
	*pRCC_AHB1ENR |= (GPIOA_EN | GPIOC_EN);

	// 2. Configure PA0 internal pull-down resistor (bits [1:0] = 0b10)
	*pGPIOA_PUPDR &= ~(3U << 0);
	*pGPIOA_PUPDR |=  (2U << 0);

	// 3. Configure PA0 as input mode (bits [1:0] = 0b00)
	*pGPIOA_MODER &= ~(3U << (0 * 2));

	// 4. Configure PC13 as general purpose output mode (bits [27:26] = 0b01)
	*pGPIOC_MODER &= ~(3U << (PIN13 * 2));
	*pGPIOC_MODER |=  (1U << (PIN13 * 2));

    while(1){
    	if(*pGPIOA_IDR & (1U << 0))
    	{
    		// 5. PA0 is HIGH -> turn ON onboard LED (drive PC13 LOW)
    		*pGPIOC_ODR &= ~(1U << PIN13);
    	} else {
    		// 6. PA0 is LOW -> turn OFF onboard LED (drive PC13 HIGH)
    		*pGPIOC_ODR |= (1U << PIN13);
    	}
    }
}
