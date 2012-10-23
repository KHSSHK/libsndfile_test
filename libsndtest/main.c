#include "main.h"

int main(int argc, char **argv)
{
	char  *inname; // 파일명
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
		printf("PCM > WAV : libsndtest 숫자(ch) 숫자(Samplerate) 입력파일명\n");
		printf("WAV > PCM : libsndtest 입력파일명\n");
		system("PAUSE");
		return -3;
	}

	Convert(inname, ch, samplerate);

	system("PAUSE");

	return 0;
}