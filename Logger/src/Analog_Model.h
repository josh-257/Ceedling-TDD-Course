#ifndef ANALOG_MODEL_H
#define ANALOG_MODEL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, NUM_ADC_CHANNELS} AdcChanel_t;

void AnalogModel_Init(void);
uint16_t AnalogModel_GetChannel(AdcChanel_t channel);


#endif // ANALOG_MODEL_H
