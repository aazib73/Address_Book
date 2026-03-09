#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	*/
	address_book->fp = fopen(DEFAULT_FILE, "r");
	if (address_book->fp != NULL)
		ret = 0;
	else
		ret = 1;

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		address_book->count = 0;
		
		/*
		 * Now we know that the file exists
		   store them into the list line by line
		*/
		char name[NAME_LEN];
		char phone[NUMBER_LEN];
		char email[EMAIL_ID_LEN];

		while (fscanf(address_book->fp,"%[^,],%[^,],%[^\n]\n", name, phone, email) == 3) {
			strcpy(address_book->list[address_book->count].name[0], name);
			strcpy(address_book->list[address_book->count].phone_numbers[0], phone);
			strcpy(address_book->list[address_book->count].email_addresses[0], email);
			address_book->list[address_book->count].si_no = address_book->count + 1;

			address_book->count++;
		}
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w");
		if (address_book->fp == NULL) {
			fprintf(stderr, "Unable to open file.\n");
			return e_fail;
		}

		address_book->count = 0;
	}

	fclose(address_book->fp);
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		fprintf(stderr, "Unable to open file.\n");
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	for (int i = 0; i < address_book->count; ++i) {
		fprintf(address_book->fp, "%s,%s,%s\n", address_book->list[i].name[0],
												address_book->list[i].phone_numbers[0],
												address_book->list[i].email_addresses[0]);
	}
	fclose(address_book->fp);

	return e_success;
}
