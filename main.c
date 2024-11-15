/*
Name:L.Mohammed Inayath
Date:04/05/2024
Description:P1 - Inverted Search
*/

#include "header.h"

int main(int argc, char *argv[]) {
    int op, flag = 0;
    List *head1 = NULL;
    Mnode *head2 = NULL;
    Snode *head3 = NULL;
    Hash hash_table[28];

    for (int i = 0; i < 28; i++) {
        hash_table[i].index = i;
        hash_table[i].hlink = NULL;
    }

    if (argc == 1) {
        printf("The command line arguments are not passed\n");
        return 0;
    } else {
        if (read_and_validate(argc, argv, &head1) == SUCCESS) {
            printf("Read and validate function is successful\n");
        } else {
            printf("Error: Read and validate function is unsuccessful\n");
        }
    }

    while (1) {
        printf("\n1. Create the database\n");
        printf("2. Print the database\n");
        printf("3. Search element\n");
        printf("4. Save database\n");
        printf("5. Update the database\n");
        printf("6. Exit\n");
        printf("Enter the choice: ");

        scanf("%d", &op);
        switch (op) {
            case 1:
                if (create_database(&head1, &head2, &head3, hash_table) == SUCCESS) {
                    flag = 1;
                } else {
                    printf("Error: The database is not created\n");
                }
                break;
            case 2:
                if (print_database(hash_table) == FAILURE) {
                    printf("The database is empty\n");
                }
                break;
            case 3:
                {
                    char element[20];
                    printf("Enter the element to be searched: ");
                    scanf("%s", element);
                    if (search_element(hash_table, element) == FAILURE) {
                        printf("Error: Element not found\n");
                    }
                }
                break;
            case 4:
                {
                    char filename[50];
                    printf("Enter the .txt file name: ");
                    scanf("%s", filename);
                    if (save_database(filename, hash_table) == SUCCESS) {
                        printf("The database is saved in the file %s\n", filename);
                    } else {
                        printf("Error: Could not save into the file %s\n", filename);
                    }
                }
                break;
            case 5:
                if (flag == 1) {
                    printf("Error: The database is already created\n");
                } else {
                    char file[50];
                    printf("Enter the .txt file name: ");
                    scanf("%s", file);
                    if (update_database(hash_table, &head1, &head2, &head3, file) == SUCCESS) {
                        printf("The database is updated for %s\n", file);
                    } else {
                        printf("Error: The database not updated for %s\n", file);
                    }
                }
                break;
            case 6:
                return SUCCESS;
            default:
                printf("Enter the correct choice\n");
        }
    }
}
