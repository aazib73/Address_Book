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
	printf("%s", msg);

    int ret = 0;
	if (type == NONE) {
		scanf("%c", &ret);
	}
	else if (type == NUM) {
		scanf("%d", &ret);
	}
    else if (type == CHAR) {
        scanf("%c", &ret);
    }
    return ret;
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

	return e_success;
}


void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (!strcmp(str, "\0"))
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
				break;
				/* Add your implementation to call list_contacts function here */
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
	int option;
	char name[NAME_LEN] = "";
	char number[NUMBER_LEN] = "";
	char email[EMAIL_ID_LEN] = "";
	do {
		// printing out the Add Contact menu
		menu_header("Add Contact:");
		printf("0. Back		   \n");
		printf("1. Name		  : %s\n", name);		
		printf("2. Phone No 1 : %s\n", number);
		printf("3. Email ID 1 : %s\n", email);

		//get user input
		option = get_option(NUM, "Please select an option: ");

		switch (option) {
			case e_second_opt:
				fgets(name, NAME_LEN, stdin);	//gets the input and limits the buffer to NAME_LEN so there's no overflow.
				break;
			case e_third_opt:
				fgets(number, NUMBER_LEN, stdin);
				break;
			case e_fourth_opt:
				fgets(email, EMAIL_ID_LEN, stdin);
				break;
			case e_first_opt:
				break;
		}

	} while (option != e_first_opt);

	/* Two things:
	1. name is a pointer, so this condition is invalid.
	2. name is already a char*, so you only need one [] at the end
	3. You forgot to increment address_book-> count after all of this.
	*/
	if (strlen(name) > 0) strcpy(address_book->list[address_book->count].name[0], name);
	if (strlen(number) > 0) strcpy(address_book->list[address_book->count].phone_numbers[0], number);
	if (strlen(email) > 0) strcpy(address_book->list[address_book->count].email_addresses[0], email);

	address_book->count++;
	
	return e_success;
} 

Status search_contact(AddressBook *address_book)
{
    int option;
    char search_str[32];
	do {		// added a do while; keep coming back to this menu, even if a contact is found
		menu_header("Search Contact by:");	// use the menu_header for consistent formatting
		printf("0. Exit\n");
		printf("1. Name\n");
		printf("2. Phone Number\n");
		printf("3. Email\n");
		printf("4. Serial Number\n"); 	//not implemented yet

		option = get_option(NUM, "Please select an option: ");

		switch(option)
		{
			case e_second_opt:
				printf("Enter the Name: ");
				fgets(search_str, 32, stdin);
				search(search_str, address_book, address_book->count, 0, "Press: [q] | Cancel: ", e_search);
				break;
			case e_third_opt:
				printf("Enter the Phone: ");
				fgets(search_str, 32, stdin);
				search(search_str, address_book, address_book->count, 1, "Press: [q] | Cancel: ", e_search);
				break;
			case e_fourth_opt:
				printf("Enter the Email: ");
				fgets(search_str, 32, stdin);
				search(search_str, address_book, address_book->count, 2, "Press: [q] | Cancel: ", e_search); // we definitely do not return the value from search function
				break;																				// we just run; but do we check status of search maybe ??
			case e_fifth_opt:
				printf("Enter the Serial No: ");
				fgets(search_str, 32, stdin);
				search(search_str, address_book, address_book->count, 3, "Press: [q] | Cancel: ", e_search);
				break;
			case e_first_opt:
				break;
		}
	} while (option != e_exit);
    return e_success;
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
	int index = -1;
	char name[NAME_LEN]; // NAME_LEN is preset to 32 bytes but it needs to be up here
	while(1)
	{
		printf("Name of Contact to edit (q to quit): ");
		// scanf needs the address of the variable, char* is a pointer already so you don't need the &
		scanf("%s", name); 

		// This is still a comparison but strcmp returns an int, it will automatically be true
		if(strcmp(name, "q") == 0)
			return e_back;

		for(int i = 0; i < address_book->count; i++)
		{
			// Same Issue from Line 255
			if(strcmp(name, address_book->list->name[0]) == 0)				// problem fixed: "address_book->list", but list also has to be dereferenced because it is a pointer. so "list->"
			{
				index = i;
				break;
			}
		}

		// This is an infinite loop so there still needs to be a way to exit
		if (index != -1)
			break;

		printf("Name not found try again\n");
	}

	/* Syntax Errors:
		Refer to Line 251 for scanf error
		char* name is already defined earlier in the code
	*/
	printf("New name of contact: ");
	char new_name[NAME_LEN];
	scanf("%s", new_name);
	strcpy(address_book->list[index].name[0], new_name);

	printf("New number: ");
	char new_num[NUMBER_LEN];
	scanf("%s", new_num);
	strcpy(address_book->list[index].phone_numbers[0], new_num);

	printf("New email: ");
	char new_email[EMAIL_ID_LEN];
	scanf("%s", new_email);
	strcpy(address_book->list[index].email_addresses[0], new_email);

	return e_success;
}

/* Recent commit: Many of the errors from the edit_contact
   were also found here, you can refer to the comments I
   made above about some of the errors since they're pretty
   much the same from the previous function.
   Feel free to delete this after you looked at them.
*/
Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	int index = -1;
	char name[NAME_LEN];
	while(1)
	{
		menu_header("Search Contact to Delete by:");
		scanf("%s", name);

		if(strcmp(name, "q") == 0)
			return e_back;

		for(int i = 0; i < address_book->count; i++)
		{
			if(strcmp(name, address_book->list->name[0]) == 0)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
			break;

		printf("Name not found, try again\n");
	}

	strcpy(address_book->list[index].name[0], "");
	strcpy(address_book->list[index].phone_numbers[0], "");
	strcpy(address_book->list[index].email_addresses[0], "");

	return e_success;
}
