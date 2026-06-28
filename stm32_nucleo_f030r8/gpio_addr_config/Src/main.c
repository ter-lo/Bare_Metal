/*
 * Goal: Manually toggle the user LED (LD2)
 * w/out using any libraries or pre-existing
 * drivers
*/


/*
 * Where is the LED connected?
 * LEDs connect to found in the user guide:
 * Pin    (what pin(s))   5
 * Port   (what port(s))  A
 * Bus	  AHB1			  0x4002 0000
 * Bus    AHB2            0x4800 0000
 *
*/


#define PERIPH_BASE			0x40000000UL

/*
 * AHB1 to access RCC
 */
#define AHB1_OFFSET			0x00020000UL
#define AHB1_PERIPH_BASE	PERIPH_BASE + AHB1_OFFSET

/*
 * AHB2 to access GPIOA
 */
#define AHB2_OFFSET			0x08000000UL
#define AHB2_PERIPH_BASE	PERIPH_BASE + AHB2_OFFSET
#define GPIOA_OFFSET		0x08000000UL
#define GPIOA_BASE			AHB2_PERIPH_BASE + GPIOA_OFFSET

#define RCC_OFFSET			0x00021000UL
#define RCC_BASE			AHB1_PERIPH_BASE + RCC_OFFSET
#define RCC_AHBENR_OFFSET	0x14
/*
 * Typecast and dereference to a pointer
 * This creates the register
 */
#define RCC_AHBENR			(*(volatile unsigned int *)(RCC_BASE + RCC_AHBENR_OFFSET))

#define MODER_OFFSET		0x00UL
/*
 * Typecast and dereference to a pointer
 * This creates the register
 * I'm targeting MODER5 because LD2 is on Pin 5
 */
#define GPIOA_MODER			(*(volatile unsigned int *)(GPIOA_BASE + MODER_OFFSET))

#define ODR_OFFSET			0x14UL
#define GPIOA_ODR			(*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))

#define GPIOA_CLK_EN		(1U<<17)

#define USER_LED2_MODER		(1U<<10)

#define USER_LED2			(1U<<5)

/*
 * Write the execution
 */

int main(void)
{
	/*
	 * Enable clock access to port A
	 */
	RCC_AHBENR |= GPIOA_CLK_EN;

	/*
	 * Configure LED Pin as output pins
	 */
	GPIOA_MODER |= USER_LED2_MODER;

	/*
	 * Turn on LED using a while loop
	 */
	while(1)
	{
		GPIOA_ODR |= USER_LED2;
	}


}






























