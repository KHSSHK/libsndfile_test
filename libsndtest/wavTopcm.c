#include "main.h"

int Wav_to_Pcm(char *wavin, char *filename)
{
	SNDFILE *in, *out;
	SF_INFO sf_info;
	int		infoerr = 0;

	char	*outname = NULL, *pcmname = NULL;
	short	*inData, *outData;
	
	FILE	*pcm_info; // SF_INFO에서 제공되는 채널, 샘플링 정보등을 저장

	int i;

	printf("wav->pcm\n");

	outname = (char *)malloc(sizeof(char)*strlen(filename)+5);
	sprintf(outname, "%s.pcm", filename);

	in = sf_open(wavin, SFM_READ, &sf_info);
	if(in == NULL)
	{
		printf("%s\n", sf_strerror(in));
		printf("WAV ERROR\n");
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
	
	/* WAV INFO -> PCM INFO */	
	sf_info.format	= 0X00040002; // main format :raw pcm, subformat: pcm16
	
	out = sf_open(outname, SFM_WRITE, &sf_info);
	if(out == NULL)
	{
		printf("%s\n", sf_strerror(out));
		printf("PCM ERROR\n");
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
	free(outData);
	free(inData);
	free(outname);

	/* wav 헤더 정보 저장 */
	{
		pcmname = (char *)malloc(sizeof(char)*strlen(filename)+10);

		sprintf(pcmname, "%s_info.txt", filename);

		pcm_info = fopen(pcmname, "w");
		if(pcm_info == NULL)
		{
			printf("TEXT FILE ERROR\n");
			fclose(pcm_info);
			system("PAUSE");
			return -1;
		}

		fprintf(pcm_info, "%s's INFORMATION\n\n", filename);
		fprintf(pcm_info, "Channels     = %d\n", sf_info.channels);
		fprintf(pcm_info, "Samplerate   = %d\n", sf_info.samplerate);
				
		fclose(pcm_info);
		free(pcmname);
	}

	return 0;
}