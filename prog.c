#include <stdio.h>
#include <stdbool.h>

#define NAME_MAX_SIZE (128)
#define EMAIL_MAX_SIZE (128)
#define BUFFER_SIZE (512)
#define CONTACT_MAX_SIZE (100)

typedef struct m_contact
{
	char name[NAME_MAX_SIZE];
	char email[EMAIL_MAX_SIZE];
	unsigned int phone;
}Contact;


Contact readContact();
void getLine(char buffer[], int bufferSize);
void mstrcpy(char dst[], char src[]);

int main()
{
	Contact contacts[CONTACT_MAX_SIZE];
	int nrOfContacts = 0;

	while(true)
	{
		printf("s - Show all contacts\n");
		printf("a - add contact\n");
		printf("f - find contact\n");
		printf("d - delete contact\n");
		printf("q - quit\n");
		
		printf("\n> ");
		
		char option;
		scanf("%c", &option);
		getchar(); // TODO CHANGE THIS!!!
		
		switch(option)
		{
			case 'q':
				return 0;
				
			case 'a':
			{
				Contact c = readContact();
				contacts[nrOfContacts] = c;
				nrOfContacts += 1;
				break;
			}
			
		}
		
	}
	return 0;
}



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

Contact readContact()
{
	Contact c;
	char buffer[BUFFER_SIZE];
	
	printf("[Add Contact] Name? ");
	getLine(buffer, BUFFER_SIZE);
	mstrcpy(c.name, buffer);
	
	printf("[Add Contact] Email? ");
	getLine(buffer, BUFFER_SIZE);
	mstrcpy(c.email, buffer);
	
	
	printf("[Add Contact] Phone? ");
	scanf("%d", &c.phone);
	
	return c;
}
