#include "main.h"

static int FileNameSize(char *str);
static void FileName(char *filename, char *str, int namesize);

void Convert(char *inname, int ch, int samplerate)
{
	char	*filename = NULL; // 파일명
	int		fs; // 파일명 크기 

	fs = FileNameSize(inname);

	filename = (char *)malloc(sizeof(char)*fs);

	FileName(filename, inname, fs);

	printf("Convert.\n");

	if(strcmp((inname + strlen(inname) - 4), ".pcm") == 0 || strcmp((inname + strlen(inname) - 4), ".PCM") == 0)
	{
		Pcm_to_Wav(inname, filename, ch, samplerate);
	}
	else if(strcmp((inname + strlen(inname) - 4), ".wav") == 0 || strcmp((inname + strlen(inname) - 4), ".WAV") == 0)
	{
		Wav_to_Pcm(inname, filename);
	}
	else
	{
		printf("Don't support the extention.\n");
	}

	printf("End.\n");

	free(filename);
}

static int FileNameSize(char *str)
{
	int i= 0;
	int cnt = 0;

	while(1)
	{
		if(str[i] == '.')
			break;

		i++;
		cnt++;
	}

	return cnt+1;
}

static void FileName(char *filename, char *str, int namesize)
{
	int  i;
	char tmp;

	for( i = 0 ; i < namesize ; i++)
	{
		if(i == namesize -1)
		{
			filename[i] = NULL;
			break;
		}

		tmp = str[i];
		filename[i] = tmp;
	}
}