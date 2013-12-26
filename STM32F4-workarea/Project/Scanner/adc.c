#include "adc.h"

struct adc_tx_struct
{
    // Most significant byte
    unsigned int sleep      :1;
    unsigned int nap        :1;
    unsigned int gain       :1;
    unsigned int uni        :1; 
    unsigned int select     :2;
    unsigned int odd        :1;
    unsigned int sgl        :1;

    unsigned int padding    :8;
       
} adc_tx_struct;
