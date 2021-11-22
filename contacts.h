#ifndef MY_CONTACTS
#define MY_CONTACTS

#include <stdbool.h>
#include <stdio.h>
#include "datetime.h"

#define NAME_MAX_SIZE (128)
#define EMAIL_MAX_SIZE (128)

typedef struct m_contact
{
	char name[NAME_MAX_SIZE];
	char email[EMAIL_MAX_SIZE];
	unsigned int phone;
	DateTime created;
}Contact;

bool canAddContact();
bool addContact(Contact* c);
Contact* getContactAt(int idx);
int getContactsCount();
bool deleteContactAtIdx(int idx);
bool deleteContactAtIdxCascade(int idx);
bool writeContactsToFile(FILE* fp);
int readContactsFromFile(FILE* fp);
Contact* findContact(void* key, bool(* pred)(Contact* c, void* key));

#endif
