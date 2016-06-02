#ifndef _TINYTENSOR_FEATURES_H_
#define _TINYTENSOR_FEATURES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    
#define NUM_SAMPLES_TO_RUN_FFT (160)


void tinytensor_features_initialize(void);

void tinytensor_features_deinitialize(void);

void tinytensor_features_add_samples(const int16_t * samples, const uint32_t num_samples);

    
#ifdef __cplusplus
}
#endif


#endif //_TINYTENSOR_FEATURES_H_