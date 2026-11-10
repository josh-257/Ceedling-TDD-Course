#include "LED.h"

#define LED_0_BIT   (18)
#define LED_1_BIT   (20)
#define LED_2_BIT   (21)
#define LED_3_BIT   (23)

#define LED_PORT LPC_GPIO1
#define LED_PIN_BIT(bit) (0x3u << ((bit & 0x0F) << 1))

static const int LED_BitMap[] = {LED_0_BIT, LED_1_BIT, LED_2_BIT, LED_3_BIT};

void LED_Init(void)
{   
    LED_PORT->FIOSET = BIT_TO_MASK(LED_0_BIT) | BIT_TO_MASK(LED_1_BIT) | BIT_TO_MASK(LED_2_BIT) | BIT_TO_MASK(LED_3_BIT);
    
    LED_PORT->FIODIR |= BIT_TO_MASK(LED_0_BIT) | BIT_TO_MASK(LED_1_BIT) | BIT_TO_MASK(LED_2_BIT) | BIT_TO_MASK(LED_3_BIT);
    
    LPC_PINCON->PINSEL3 &= ~(LED_PIN_BIT(LED_0_BIT) | LED_PIN_BIT(LED_1_BIT) | LED_PIN_BIT(LED_2_BIT) | LED_PIN_BIT(LED_3_BIT));
    
    LPC_PINCON->PINMODE3 &= ~(LED_PIN_BIT(LED_0_BIT) | LED_PIN_BIT(LED_1_BIT) | LED_PIN_BIT(LED_2_BIT) | LED_PIN_BIT(LED_3_BIT));  
}

void LED_Toggle(LED_ID_T id)
{
    if(id < LED0 || id >= NUM_LED)
    {
        return;
    }

    uint32_t mask = BIT_TO_MASK(LED_BitMap[id]);

    if(mask & LED_PORT->FIOPIN)
    {
        LED_PORT->FIOCLR = mask;
    }
    else
    {
        LED_PORT->FIOSET = mask;
    }
}

void LED_On(LED_ID_T id)
{
    if(id < LED0 || id >= NUM_LED)
    {
        return;
    }
    LED_PORT->FIOSET = BIT_TO_MASK(LED_BitMap[id]);
}

void LED_Off(LED_ID_T id)
{
    if(id < LED0 || id >= NUM_LED)
    {
        return;
    }

    LED_PORT->FIOCLR = BIT_TO_MASK(LED_BitMap[id]);
}