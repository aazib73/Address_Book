#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "address_book.h"
#include "address_book_menu.h"

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 
	bool_t list_contacts =1;
	char choice;
	if( address_book -> count == 0){

		printf("There are no contacts, please add them");
	}else{
		while( list_contacts){
			for( int i= *index; i<address_book -> count && i<(*index + PAGE_SIZE);i++){

				printf("Name: %s\n", address_book->list[i].name[0]);
				printf("Phone: %s\n", address_book -> list[i].phone_numbers[0]);
				printf("Email: %s\n", address_book -> list[i].email_addresses[0]);
				}

			if(*index + PAGE_SIZE< address_book -> count){

				printf("Do you want to print the next page? Y/N\n");
				scanf(" %c", &choice);

				if(choice == 'Y'||choice == 'y'){

				*index = *index + PAGE_SIZE;

				}else{

					list_contacts = 0;

				}

			}else{

				list_contacts = 0;
			}
				
		}

	}

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;
	int current_index = 0;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
			list_contacts(address_book , "list contacts", &index, "", e_list);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
    int option;
    char search_str[32];

    printf("\nSearch Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");

    printf("Enter option: ");
    scanf("%d", &option);

    printf("Enter search value: ");
    scanf("%s", search_str);

    switch(option)
    {
        case 1:
            return search(search_str, address_book, address_book->count, 0, "Name Search", e_search);

        case 2:
            return search(search_str, address_book, address_book->count, 1, "Phone Search", e_search);

        case 3:
            return search(search_str, address_book, address_book->count, 2, "Email Search", e_search);

        default:
            printf("Invalid option\n");
    }

    return e_fail;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
    int i, j;
    int found = 0;

    for(i = 0; i < address_book->count; i++)
    {
        if(field == 0) // Name search
        {
            if(strcmp(address_book->list[i].name[0], str) == 0)
            {
                printf("\nMatch Found:\n");
                printf("Name: %s\n", address_book->list[i].name[0]);

                for(j = 0; j < PHONE_NUMBER_COUNT; j++)
                {
                    if(strlen(address_book->list[i].phone_numbers[j]) > 0)
                        printf("Phone: %s\n", address_book->list[i].phone_numbers[j]);
                }

                for(j = 0; j < EMAIL_ID_COUNT; j++)
                {
                    if(strlen(address_book->list[i].email_addresses[j]) > 0)
                        printf("Email: %s\n", address_book->list[i].email_addresses[j]);
                }

                found = 1;
            }
        }

        else if(field == 1) // Phone search
        {
            for(j = 0; j < PHONE_NUMBER_COUNT; j++)
            {
                if(strcmp(address_book->list[i].phone_numbers[j], str) == 0)
                {
                    printf("\nMatch Found:\n");
                    printf("Name: %s\n", address_book->list[i].name[0]);
                    printf("Phone: %s\n", address_book->list[i].phone_numbers[j]);
                    found = 1;
                }
            }
        }

        else if(field == 2) // Email search
        {
            for(j = 0; j < EMAIL_ID_COUNT; j++)
            {
                if(strcmp(address_book->list[i].email_addresses[j], str) == 0)
                {
                    printf("\nMatch Found:\n");
                    printf("Name: %s\n", address_book->list[i].name[0]);
                    printf("Email: %s\n", address_book->list[i].email_addresses[j]);
                    found = 1;
                }
            }
        }
    }

    if(!found)
    {
        printf("\nNo contact found\n");
        return e_no_match;
    }

    return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
