#include "Definitions.h"
#include <stdint.h>

uint16_t analogRead_average(int pin_to_read) {
  uint16_t sample_value = 0;

  for (int i = 0; i < NUMBER_OF_READINGS; i++)
    sample_value += (uint16_t)analogRead(pin_to_read);

  sample_value /=  NUMBER_OF_READINGS;
  return sample_value;
}

