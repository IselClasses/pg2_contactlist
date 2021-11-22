#include "contacts.h"
#include <stdio.h>


#define BUFFER_SIZE (512)
#define CONTACT_MAX_SIZE (100)

static Contact contacts[CONTACT_MAX_SIZE];
static int nrOfContacts = 0;

static bool validIndex(int idx)
{
	return idx >= 0 && idx < nrOfContacts;
}

bool canAddContact()
{
	return nrOfContacts < CONTACT_MAX_SIZE;	
}
bool addContact(Contact* c)
{
	if(canAddContact() == false)
		return false;
		
	contacts[nrOfContacts] = *c;
	nrOfContacts += 1;
	return true;
}


Contact* getContactAt(int idx)
{
	if(validIndex(idx) == false)
		return NULL;
		
	return contacts + idx;
}

int getContactsCount()
{
	return nrOfContacts;
}

bool deleteContactAtIdx(int idx)
{
	
	if(validIndex(idx) == false)
		return false;
	
	Contact lastContact = contacts[nrOfContacts-1];
	
	contacts[idx] = lastContact;
	
	nrOfContacts--;
	
	return true;
}


bool deleteContactAtIdxCascade(int idx)
{
	if(validIndex(idx) == false)
		return false;
		
	for(int i = idx; i < nrOfContacts-1; ++i)
	{
		contacts[i] = contacts[i+1];
	}	
	
	return true;
}

static void writeContactToFile(Contact c, FILE* fp)
{
	fprintf(fp, "%s,%s,%d", c.name, c.email, c.phone);
	fprintf(fp, ",%d,%d", c.created.date, c.created.time);
	
	fputc('\n', fp);
}

bool writeContactsToFile(FILE* fp)
{
	for(int i = 0; i < nrOfContacts; ++i)
	{
		writeContactToFile(contacts[i], fp);
	}
	
	return true;
}

/*
	Reads characters from line until it reaches a comma (,) and places
	the read chars in buffer. The function returns -1 if the end of string 
	is reached or the index of the founded comma +1.
	The buffer value on return should be a string (should have the terminator character)
e.g name,email,phone,date,time
* 	xxx,yyy,1234,12345,12345

 */
static int extractFromLine(char buffer[], int startIdx, char line[])
{
	int j = 0;
	int i = startIdx;
	for(;line[i] != '\0' && line[i] != ',' && line[i] != '\n';++i, j++)
	{
		buffer[j] = line[i];
	}
	
	buffer[j] = 0;
	
	//return (line[i] || line[i] == '\n') ? -1 : i+1;
	
	if(line[i] == 0 || line[i] == '\n')
		return -1;
		
	return i + 1;
}

static Contact readContactFromString(char line[])
{
	Contact c;
	char buffer[BUFFER_SIZE];
	
	int idx = extractFromLine(c.name, 0, line);
	idx = extractFromLine(c.email, idx, line);
	
	idx = extractFromLine(buffer, idx, line);
	sscanf(buffer, "%d", &c.phone);
	
	
	idx = extractFromLine(buffer, idx, line);
	sscanf(buffer, "%d", &c.created.date);
	
	idx = extractFromLine(buffer, idx, line);
	sscanf(buffer, "%hd", &c.created.time);
	
	return c;
	
}
	
int readContactsFromFile(FILE* fp)
{
	char buffer[BUFFER_SIZE];
		
	int initialContacts = nrOfContacts;
	
	while(nrOfContacts < CONTACT_MAX_SIZE && 		//space for a new contact
		  fgets(buffer, BUFFER_SIZE, fp) != NULL && // read a line from the file
		  buffer[0] != 0) //line is not empty
	{
		Contact c = readContactFromString(buffer);
		contacts[nrOfContacts] = c;
		nrOfContacts++;
	}
	
	return nrOfContacts - initialContacts;
}


Contact* findContact(void* key, bool (*pred)(Contact* c, void* key))
{
	for(int i = 0; i < nrOfContacts; ++i)
	{
		if(pred(&contacts[i], key))
			return contacts + i;
	}
	
	return NULL;
}
