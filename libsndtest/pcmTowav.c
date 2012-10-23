#include "main.h"

int Pcm_to_Wav(char *pcmin, char *filename, int ch, int samplerate)
{
	SNDFILE *in, *out;
	SF_INFO sf_info;
	int		infoerr = 0;

	char *outname = NULL, *wavname = NULL;
	short *inData, *outData;

	int i;

	printf("pcm->wav\n");

	wavname = (char *)malloc(sizeof(char)*strlen(filename)+5);
	sprintf(wavname, "%s.wav", filename);

	sf_info.channels = ch;
	sf_info.format = 0x00040002;
	sf_info.frames = 1;
	sf_info.samplerate = samplerate;
	sf_info.sections = 1;
	sf_info.seekable = 1;

	in = sf_open(pcmin, SFM_READ, &sf_info);
	if(in == NULL)
	{
		printf("%s\n", sf_strerror(in));
		printf("PCM ERROR\n");
		sf_close(in);
		system("PAUSE");
		return -1;
	}

	/* 파일 정보 검사 */
	infoerr = sf_format_check(&sf_info);
	if(infoerr == 0)
	{
		printf("SF_INFO ERROR\n");
		sf_close(in);
		system("PAUSE");
		return -2;
	}
	
	/* PCM INFO -> WAV INFO */	
	sf_info.format	= 0x00010002; // main format :wav, subformat: pcm16
	
	out = sf_open(wavname, SFM_WRITE, &sf_info);
	
	if(out == NULL)
	{
		printf("%s\n", sf_strerror(out));
		printf("WAV ERROR\n");
		sf_close(out);
		sf_close(in);
		return -1;
	}
	
	
	inData = (short *)malloc(sizeof(short)*NUM);
	outData = (short *)malloc(sizeof(short)*NUM);

	while(sf_read_short(in, inData, NUM) == NUM)
	{
		for(i = 0; i < NUM; i++)
		{
			outData[i] = inData[i];
		}

			sf_write_short(out, outData, NUM);	
	}

	sf_close(out);
	sf_close(in);
	free(inData);
	free(outData);
	free(outname);
	

	return 0;
}