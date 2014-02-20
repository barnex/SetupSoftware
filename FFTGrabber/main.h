#ifndef _MAIN_H
#define _MAIN_H

#define SAMPLE_RATE 48000
#define min(x, y) (((x) < (y)) ? (x) : (y))

/*
 * This struct will be passed to the Portaudio callback function (see directly below)
 * as the user's data. It holds pointer to where the samples need te be copied, along with
 * how many have been and should be copied into this buffer. Lastly a mutex is present
 * to prevent reading/writing at the wrong time.
 */
typedef struct
{
    float   *buffer;
    int	    index;
    int	    maxIndex;
    pthread_mutex_t *lock;
} PACallbackData;

typedef struct
{
    PACallbackData  *paArgs;
    PaStream	    *stream;
} handleData;


#endif
