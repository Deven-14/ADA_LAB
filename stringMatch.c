#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int stringMatch(char *text, char *pattern)
{
	int np = strlen(pattern);
	int size = strlen(text) - np + 1;//*******************************
	
	for(int i = 0; i < size; ++i)
	{
		int j = 0;
		while(j < np && text[i+j] == pattern[j])
		{
			sleep(0.1);
			++j;
		}
		if(j == np)
			return i;
	}
	return -1;
}

int main()
{
	int nt, np = 10000;
	
	printf("Enter length of pattern : ");
	scanf("%d", &np);
	//printf("The length of pattern : 10000");
	char *pattern = (char*)calloc(np+1, sizeof(char));
	
	for(int j = 0; j < np; ++j)
		//scanf("%s", pattern);
		pattern[j] = (char)(rand() % 26 + 97);
	pattern[np] = '\0';

	printf("pattern : %s\n", pattern);
	
	//for(int i = 0; i < 10; ++i)
	//{
		//printf("\n%dth time\n", i+1);
		printf("Enter length of text : ");
		scanf("%d", &nt);
		char *text = (char*)calloc(nt+1, sizeof(char));
		
		for(int i = 0; i < nt; ++i)
			text[i] = (char)(rand() % 26 + 97);
		text[nt] = '\0';
		
		printf("text : %s\n", text);
		
		clock_t start, end;
		start = clock();
		int result = stringMatch(text, pattern);
		end = clock();
		
		double timeReq = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Result Index : %d\n", result);
		printf("The time it took is : %lf\n", timeReq);
		
		free(text);
	//}
	
	free(pattern);
	
	return 0;
}
/*printf("Enter text : ");
scanf("%s", text);
printf("Enter pattern : ");
scanf("%s", pattern);*/
