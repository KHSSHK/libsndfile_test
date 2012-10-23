#ifndef	__MAIN_HEADER__
#define __MAIN_HEADER__

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>

#define NUM 64

void Convert(char *inname, int ch, int samplerate);
int Wav_to_Pcm(char *wavin, char *filename);
int Pcm_to_Wav(char *pcmin, char *filename, int ch, int samplerate);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MAIN_HEADER__ */
