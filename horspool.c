#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void createShiftTable(int shiftTable[], char* str)
{
	
	int m = strlen(str);
	
	for(int i = 0; i < 256; ++i)
		shiftTable[i] = m;
	
	for(int i = 0; i < m-1; ++i)//m-1*************8
		shiftTable[str[i]] = m - 1 - i;
	
	//for(int i = 0; i < 256; ++i)
		//printf("%d - %d, ",  i, shiftTable[i]);
}

int horspool(char *text, char *pattern)
{
	int shiftTable[256];
	createShiftTable(shiftTable, pattern);
	
	int lenP = strlen(pattern);
	int lenT = strlen(text);
	int i = lenP - 1;
	
	while(i < lenT)//not (lenT - lenP + 1))****coz last string also might shift
	{
		int j = 0;
		
		while((j < lenP) && pattern[lenP - 1 - j] == text[i - j])
			++j;
		
		if(j == lenP)
			return (i - (lenP - 1));//*************brackets
		
		//printf("\n%d\n", shiftTable[text[i - j]]);
		i += shiftTable[text[i - j]];
		
		sleep(0.1);
	}
	
	return -1;
}

int main()
{

	int nt, np;
	
	np = 20;
	printf("The length of pattern is : %d\n", np);
	char *pattern = (char*)calloc(np+1, sizeof(char));
	
	for(int i = 0; i < np; ++i)
		pattern[i] = (char)(rand() % 26 + 97);
	pattern[np] = '\0';
	
	printf("pattern : %s\n", pattern);
	
	
	printf("Enter length of text : ");
	scanf("%d", &nt);
	char *text = (char*)calloc(nt+1, sizeof(char));
	
	for(int i = 0; i < nt; ++i)
		text[i] = (char)(rand() % 26 + 97);
	text[nt] = '\0';
	
	printf("text : %s\n", text);
	
	
	clock_t start, end;
	start = clock();
	int result = horspool(text, pattern);
	end = clock();
	
	
	double timeReq = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Result Index : %d\n", result);
	printf("The time it took is : %lf\n", timeReq);
	
	
	//char text[] = "in our life real gods are parents";
	//char pattern[] = "parents";
	
	free(pattern);
	free(text);
	
	return 0;
}
