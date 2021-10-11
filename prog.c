#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX_SIZE (128)
#define EMAIL_MAX_SIZE (128)
#define BUFFER_SIZE (512)
#define CONTACT_MAX_SIZE (100)
#define INVALID_OPTION (-1)

#define NR_OF_MOCK_CONTACTS (10)


typedef struct m_contact
{
	char name[NAME_MAX_SIZE];
	char email[EMAIL_MAX_SIZE];
	unsigned int phone;
}Contact;


Contact readContact();
void getLine(char buffer[], int bufferSize);
void mstrcpy(char dst[], char src[]);
char getMenuOption();
void printAllContacts(Contact contacts[], int nrOfContacts, bool showId);
void printContact(Contact c);
void showFindMenu(Contact contacts[], int nrOfContacts);
int getIntFromConsole();
int fillContactsWithMockData(Contact contacts[], int maxContactSize);
bool deleteContact(Contact contacts[], int maxContactSize);
bool deleteCascadeContact(Contact contacts[], int maxContactSize);


int main()
{
	Contact contacts[CONTACT_MAX_SIZE];
	int nrOfContacts = 0;
	
	nrOfContacts = fillContactsWithMockData(contacts, CONTACT_MAX_SIZE);

	while(true)
	{
		printf("s - Show all contacts\n");
		printf("a - add contact\n");
		printf("f - find contact\n");
		printf("d - delete contact\n");
		printf("r - delete contact cascade\n");
		printf("q - quit\n");
		
		printf("\n> ");
		
		char option;
		
		
		option = getMenuOption();
		
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
			case 's':
				printAllContacts(contacts, nrOfContacts,false);
				break;
			
			case 'f':
				showFindMenu(contacts, nrOfContacts);
				break;
				
			case 'd':
				if(deleteContact(contacts, nrOfContacts))
					nrOfContacts--;
				break;
				
			case 'r':
				if(deleteCascadeContact(contacts, nrOfContacts))
					nrOfContacts--;
				break;
			
			default:
				printf("Invalid input\n\n");
				break;
			
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
	c.phone = getIntFromConsole();
	
	return c;
}


char getMenuOption()
{
	char buffer[BUFFER_SIZE];
	
	getLine(buffer, BUFFER_SIZE);
	
	if(strlen(buffer) == 1)
		return buffer[0];
		
	return INVALID_OPTION;
}


void printAllContacts(Contact contacts[], int nrOfContacts, bool showId)
{
	printf("------------------------------------------------------\n");
	
	for(int i = 0; i < nrOfContacts; ++i)
	{
		if(showId)
			printf("ID : %d\t\t", i);
			
		printContact(contacts[i]);
	}
	printf("Contacts Count %d\n", nrOfContacts);
	printf("------------------------------------------------------\n");
}

void printContact(Contact c)
{
	printf("Name: %s\t\t\tEmail: %s\t\t\tPhone:%d\n", c.name, c.email, c.phone);
}

void showFindMenu(Contact contacts[], int nrOfContacts)
{
	char buffer[BUFFER_SIZE];
	while(true)
	{		
		printf("----- n - find by name\n");
		printf("----- e - find by email\n");
		printf("----- p - find by phone\n");
		printf("----- i - find by index\n");
		printf("----- q - go back to prev menu\n");
		
		printf("----- > ");
		char option = getMenuOption();
		
		switch(option)
		{
			case 'n':
				
				printf("----- [Name] ? ");
				getLine(buffer, BUFFER_SIZE);
				
				for(int i = 0; i < nrOfContacts; ++i)
				{
					if(strcmp(contacts[i].name,buffer) == 0)
					{
						printContact(contacts[i]);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'e':
				printf("----- [Email] ? ");
				getLine(buffer, BUFFER_SIZE);
				
				for(int i = 0; i < nrOfContacts; ++i)
				{
					if(strcmp(contacts[i].email,buffer) == 0)
					{
						printContact(contacts[i]);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'p':
				
				printf("----- [Phone] ? ");
				
				int phone = getIntFromConsole();
				
				for(int i = 0; i < nrOfContacts; ++i)
				{
					if(phone == contacts[i].phone)
					{
						printContact(contacts[i]);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'i':
			
				printf("----- [Index] ? ");
				int i = getIntFromConsole();
				
				
				if(i >= nrOfContacts || i < 0)
				{
					printf("Contact doesn't exist\n");
				}
				else
				{
					printContact(contacts[i]);
					printf("\n");
				}
				return;
			case 'q':
				return;
			default:
				printf("----- Invalid input\n\n");
				break;
		}
		
		
	}
}

int getIntFromConsole()
{
	int val;
	char buffer[BUFFER_SIZE];
	scanf("%d",&val);
	
	getLine(buffer, BUFFER_SIZE);
	return val;
}

int fillContactsWithMockData(Contact contacts[], int maxContactSize)
{
	char buffer[NR_OF_MOCK_CONTACTS];
	
	for(int i = 0; i < NR_OF_MOCK_CONTACTS; ++i)
	{
		sprintf(buffer, "contact-%d", i);
		strcpy(contacts[i].name, buffer);
		
		
		sprintf(buffer, "email-%d", i);
		strcpy(contacts[i].email, buffer);
		
		contacts[i].phone = i+1000;
	}
	
	return NR_OF_MOCK_CONTACTS;
}


bool deleteContact(Contact contacts[], int totalContacts)
{
	printAllContacts(contacts, totalContacts, true);
	
	printf("[Delete Contact] Id? ");
	int id = getIntFromConsole();
	
	if(id < 0 || id > totalContacts)
	{
		printf("Invalid id \n\n");
		return false;
	}
	
	Contact lastContact = contacts[totalContacts-1];
	
	contacts[id] = lastContact;
	
	return true;
}


bool deleteCascadeContact(Contact contacts[], int totalContacts)
{
	//TODO CHANGE ME PLEASEEEEE
	printAllContacts(contacts, totalContacts, true);
	
	printf("[Delete Contact] Id? ");
	int id = getIntFromConsole();
	
	if(id < 0 || id > totalContacts)
	{
		printf("Invalid id \n\n");
		return false;
	}
	//END TODO
	
	for(int i = id; i < totalContacts-1; ++i)
	{
		contacts[i] = contacts[i+1];
	}
	
	return true;
}
