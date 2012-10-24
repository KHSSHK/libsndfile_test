#include "main.h"

int main(int argc, char **argv)
{
	char  *inname; // ÆÄÀÏ¸í
	int   ch, samplerate;

	if(argc == 4)
	{
		inname = argv[3];
		samplerate = atoi(argv[2]);
		ch = atoi(argv[1]);
	}
	else if(argc == 2)
	{
		inname = argv[1];
		samplerate = 48000;
		ch = 1;
	}
	else
	{
		printf("Usage\n");
		printf("PCM > WAV : libsndtest (ch) (Samplerate) (file name).pcm\n");
		printf("WAV > PCM : libsndtest (file name).wav\n");
		system("PAUSE");
		return -3;
	}

	Convert(inname, ch, samplerate);

	system("PAUSE");

	return 0;
}