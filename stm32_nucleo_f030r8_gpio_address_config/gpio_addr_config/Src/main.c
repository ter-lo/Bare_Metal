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

/* AHB1 to access RCC */
#define AHB1_OFFSET			0x00020000UL
#define AHB1_PERIPH_BASE	PERIPH_BASE + AHB1_OFFSET		// 0x4002 0000

/* AHB2 to access GPIOA */
#define AHB2_OFFSET			0x08000000UL
#define AHB2_PERIPH_BASE	PERIPH_BASE + AHB2_OFFSET		// 0x4800 0000
#define GPIOA_BASE			AHB2_PERIPH_BASE				// 0x4800 0000

/*
 * Issue: Incorrectly set RCC_OFFSET to 0x00021000UL
 *
 * Solution:  Because AHB1_PERIPH_BASE is equal to 0x40020000
 * 			  When adding to RCC_BASE while defining RCC_AHBENR
 * 			  originally equalled 40041000 (notice the rogue 4 on
 * 			  bit 4. I changed RCC_OFFSET to 0x1000UL allowing the
 * 			  2 on bit 4 to stay.
 */
#define RCC_OFFSET			0x1000UL
#define RCC_BASE			AHB1_PERIPH_BASE + RCC_OFFSET	// 0x4002 0000 + 0000 1000 = 0x4002 1000
#define RCC_AHBENR_OFFSET	0x14							// 0x0000 0014
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

/* Write the execution */

int main(void)
{
	/* Enable clock access to port A */
	RCC_AHBENR |= GPIOA_CLK_EN;

	/* Configure LED Pin as output pins */
	GPIOA_MODER |= USER_LED2_MODER;

	/* Turn on LED using a while loop */
	while(1)
	{
		/* Turn on all LED (LD2) */
		// GPIOA_ODR |= USER_LED2;

		/* Toggle LED (LD2) using XOR ^
		 * I'm targeting bit 5 therefore
		 * XOR flips only bit 5 to produce
		 * the toggle effect
		 */
		GPIOA_ODR ^= USER_LED2;
		for(int i = 0; i < 1000000; i++){}

	}


}






























