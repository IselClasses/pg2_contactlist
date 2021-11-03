#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "consolehelpers.h"


#define BUFFER_SIZE (512)

void getLine(char buffer[], int bufferSize)
{
	if(bufferSize == 0)
		return;
		
	int i = 0;
	do
	{
		char c = getchar();

		if(c == '\n')
			break;
		
		buffer[i] = c;
		i++;
		
		if(i == bufferSize)
		{
			buffer[bufferSize-1] = 0;
			printf("Buffer full\n");
			return;
		}
		
		
	}while(true);
	
	buffer[i] = '\0';
}


void mstrcpy(char dst[], char src[])
{
	int i = 0;
	for(; src[i]; ++i)
		dst[i] = src[i];
		
	dst[i] = 0;
}


char getMenuOption()
{
	char buffer[BUFFER_SIZE];
	
	getLine(buffer, BUFFER_SIZE);
	
	if(strlen(buffer) == 1)
		return buffer[0];
		
	return INVALID_OPTION;
}

int getIntFromConsole()
{
	int val;
	char buffer[BUFFER_SIZE];
	scanf("%d",&val);
	
	getLine(buffer, BUFFER_SIZE);
	return val;
}
