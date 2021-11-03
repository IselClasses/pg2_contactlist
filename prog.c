#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "datetime.h"
#include "contacts.h"
#include "consolehelpers.h"

#define BUFFER_SIZE (512)
#define INVALID_OPTION (-1)

#define NR_OF_MOCK_CONTACTS (10)






Contact readContact();
void printAllContacts(bool showId);
void printContact(Contact c);
void showFindMenu();
void fillContactsWithMockData();
bool deleteContact();
bool deleteCascadeContact();

void saveContacts();
void loadContacts();

Contact readContactFromString(char line[]);
void testdatetime()
{
	char buffer[1234];
	DateTime dt = getCurrentDateTime();
	datetimeToString(dt,buffer);
	
	printf("%s\n", buffer);
	
}

int main()
{
	fillContactsWithMockData();

	while(true)
	{
		printf("s - Show all contacts\n");
		printf("a - add contact\n");
		printf("f - find contact\n");
		printf("d - delete contact\n");
		printf("r - delete contact cascade\n");
		printf("l - load contacts\n");
		printf("w - save contacts\n");
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
				
				if(canAddContact() == false)
				{
					printf("Contact book full\n");
					break;
				}
				
				Contact c = readContact();
				if(addContact(c))
					printf("Contact added\n");
				else
					printf("Failed to add contact\n");
				
				break;
			}
			case 's':
				printAllContacts(false);
				break;
			
			case 'f':
				showFindMenu();
				break;
				
			case 'd':
				if(deleteContact())
					printf("Contact deleted\n");
				else
					printf("Error deleting contact \n");
				break;
				
			case 'r':
				if(deleteCascadeContact())
					printf("Contact deleted\n");
				else
					printf("Error deleting contact \n");
				break;
				
			case 'l':
				if(canAddContact() == false)
				{
					printf("Contact book full\n");
					break;
				}
			
				loadContacts();
				break;
				
			case 'w':
				saveContacts();
				break;
			default:
				printf("Invalid input\n\n");
				break;
			
		}
		
	}
	return 0;
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
	
	c.created = getCurrentDateTime();
	return c;
}


void printAllContacts(bool showId)
{
	printf("------------------------------------------------------\n");
	
	int contactSize = getContactsCount();
	for(int i = 0; i < contactSize; ++i)
	{
		if(showId)
			printf("ID : %d\t\t", i);
			
		printContact(getContactAt(i));
	}
	printf("Contacts Count %d\n", contactSize);
	printf("------------------------------------------------------\n");
}

void printContact(Contact c)
{
	char buffer[BUFFER_SIZE];
	datetimeToString(c.created, buffer);
	printf("Name: %s\t\tEmail: %s\t\tPhone:%d\t\tCreated: %s\n", c.name, c.email, c.phone, buffer);
	//printf("Name: %s\t\tEmail: %s\t\tPhone:%d\t\tCreated: %d\n", c.name, c.email, c.phone, c.created.date);

}

void showFindMenu()
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
		
		
		int contactSize = getContactsCount();
		
		switch(option)
		{
			case 'n':
				
				printf("----- [Name] ? ");
				getLine(buffer, BUFFER_SIZE);
				
	
				for(int i = 0; i < contactSize; ++i)
				{
					Contact contact = getContactAt(i);
					if(strcmp(contact.name,buffer) == 0)
					{
						printContact(contact);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'e':
				printf("----- [Email] ? ");
				getLine(buffer, BUFFER_SIZE);
				
				for(int i = 0; i < contactSize; ++i)
				{
					Contact contact = getContactAt(i);
					if(strcmp(contact.email,buffer) == 0)
					{
						printContact(contact);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'p':
				
				printf("----- [Phone] ? ");
				
				int phone = getIntFromConsole();
				
				for(int i = 0; i < contactSize; ++i)
				{
					Contact contact = getContactAt(i);
					if(phone == contact.phone)
					{
						printContact(contact);
						return;
					}
				}
				
				printf("Contact doesn't exist\n\n");
				return;
			case 'i':
			
				printf("----- [Index] ? ");
				int i = getIntFromConsole();
				
				
				if(i >= getContactsCount() || i < 0)
				{
					printf("Contact doesn't exist\n");
				}
				else
				{
					printContact(getContactAt(i));
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


void fillContactsWithMockData()
{
	char buffer[BUFFER_SIZE];
	
	for(int i = 0; i < NR_OF_MOCK_CONTACTS; ++i)
	{
		Contact c;
		sprintf(buffer, "contact-%d", i);
		strcpy(c.name, buffer);
		
		
		sprintf(buffer, "email-%d", i);
		strcpy(c.email, buffer);
		
		c.phone = i+1000;
		
		c.created = getCurrentDateTime();
		
		if(addContact(c) == false)
			return;
	}
	
	
	
	
	
}


bool deleteContact()
{
	int totalContacts = getContactsCount();
	printAllContacts( true);
	
	printf("[Delete Contact] Id? ");
	int id = getIntFromConsole();
	
	if(id < 0 || id > totalContacts)
	{
		printf("Invalid id \n\n");
		return false;
	}
	
	return deleteContactAtIdx(id);
}


bool deleteCascadeContact()
{
	int totalContacts = getContactsCount();
	printAllContacts( true);
	
	printf("[Delete Contact] Id? ");
	int id = getIntFromConsole();
	
	if(id < 0 || id > totalContacts)
	{
		printf("Invalid id \n\n");
		return false;
	}
	
	return deleteContactAtIdxCascade(id);
	return true;
}



void writeContactToFile(Contact c, FILE* fp)
{
	fprintf(fp, "%s,%s,%d", c.name, c.email, c.phone);
	fprintf(fp, ",%d,%d", c.created.date, c.created.time);
	
	fputc('\n', fp);
}


void saveContacts()
{
	char fileName[BUFFER_SIZE];
	
	printf("[Save Contacts] File? ");
	getLine(fileName, BUFFER_SIZE);
	
	FILE* fp = fopen(fileName, "w");
	
	if(fp == NULL)
	{
		printf("Error opening %s\n", fileName);
		return;
	}
	
	writeContactsToFile(fp);
	
	
	fclose(fp);
	
	printf("Written <<%d>> contacts to <<%s>>\n", getContactsCount(), fileName);
}



void loadContacts()
{
	char fileName[BUFFER_SIZE];

	printf("[Load Contacts] File? ");
	getLine(fileName, BUFFER_SIZE);
	
	FILE* fp = fopen(fileName, "r");
	
	if(fp == NULL)
	{
		printf("Error opening %s\n", fileName);
		return;
	}
	
	int newContacts = readContactsFromFile(fp);
	
	fclose(fp);
	
	printf("Read <<%d>> contacts\n", newContacts);
	
	
}
