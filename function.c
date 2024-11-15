#include "header.h"

int read_and_validate(int argc, char *argv[], List **head) {
    for (int i = 1; i < argc; i++) {
        char *temp = strstr(argv[i], ".");
        if (temp != NULL && strcmp(temp, ".txt") == 0) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("Unable to open the file or file doesn't exist\n");
                return FAILURE;
            }
            fseek(fp, 0, SEEK_END);
            int s = ftell(fp);
            if (s == 0) {
                printf("The file is empty\n");
                fclose(fp);
                return FAILURE;
            }
            List *new = malloc(sizeof(List));
            if (!new) {
                printf("Memory allocation failed\n");
                fclose(fp);
                return FAILURE;
            }
            new->file_name = strdup(argv[i]); // Use strdup to copy file name
            new->link = NULL;
            if (*head == NULL) {
                *head = new;
            } else {
                List *traverse = *head;
                List *prev = NULL;
                while (traverse != NULL) {
                    if (strcmp(traverse->file_name, new->file_name) == 0) {
                        printf("This %s is a duplicate file\n", new->file_name);
                        free(new);
                        new = NULL;
                        break;
                    }
                    prev = traverse;
                    traverse = traverse->link;
                }
                if (new != NULL && prev != NULL) {
                    prev->link = new;
                }
            }
            fclose(fp);
        } else {
            printf("Not a txt file\n");
        }
    }
    return SUCCESS;
}

int create_database(List **head1, Mnode **head2, Snode **head3, Hash *hash_table) {
    List *temp = *head1;
    char word[100];
    while (temp != NULL) {
        int ch;
        FILE *fp = fopen(temp->file_name, "r");
        if (fp == NULL) {
            printf("The file cannot be opened\n");
            return FAILURE;
        }
        while ((ch = fscanf(fp, "%s", word)) != EOF) {
            int index;
            if (isdigit(word[0])) {
                index = 26;
            } else if (isalpha(word[0])) {
                index = tolower(word[0]) - 'a';
            } else {
                index = 27;
            }
            add_to_database(hash_table, head2, head3, index, temp->file_name, word);
        }
        printf("The database created for %s\n", temp->file_name);
        fclose(fp);
        temp = temp->link;
    }
    return SUCCESS;
}

void create_mnode(char *word, Mnode **head2) {
    Mnode *mnew = malloc(sizeof(Mnode));
    if (!mnew) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(mnew->word, word);
    mnew->filecount = 1;
    mnew->mlink = NULL;
    *head2 = mnew;
}

void create_snode(char *filename, Snode **head3) {
    Snode *snew = malloc(sizeof(Snode));
    if (!snew) {
        printf("Memory allocation failed\n");
        return;
    }
    snew->wordcount = 1;
    strcpy(snew->filename, filename);
    snew->s_link = NULL;
    *head3 = snew;
}

void add_to_database(Hash *hash_table, Mnode **head2, Snode **head3, int i, char *file_name, char *word) {
    if (hash_table[i].hlink == NULL) {
        create_mnode(word, head2);
        create_snode(file_name, head3);
        (*head2)->slink = *head3;
        hash_table[i].hlink = *head2;
    } else {
        Mnode *temp2 = hash_table[i].hlink;
        while (temp2 != NULL) {
            if (strcmp(word, temp2->word) == 0) {
                Snode *temp3 = temp2->slink;
                while (temp3 != NULL) {
                    if (strcmp(temp3->filename, file_name) == 0) {
                        temp3->wordcount++;
                        return;
                    }
                    if (temp3->s_link == NULL) {
                        create_snode(file_name, head3);
                        temp3->s_link = *head3;
                        temp2->filecount++;
                        return;
                    }
                    temp3 = temp3->s_link;
                }
            } else if (temp2->mlink == NULL) {
                create_mnode(word, head2);
                create_snode(file_name, head3);
                (*head2)->slink = *head3;
                temp2->mlink = *head2;
                return;
            }
            temp2 = temp2->mlink;
        }
    }
}

int print_database(Hash *hash_table) {
    printf("Index\tWord\tFile count\tFile name\tWord count\n");
    for (int i = 0; i < 28; i++) {
        if (hash_table[i].hlink != NULL) {
            Mnode *temp = hash_table[i].hlink;
            while (temp != NULL) {
                printf("[%d]\t%s\t%d\t\t", i, temp->word, temp->filecount);
                Snode *temp1 = temp->slink;
                while (temp1 != NULL) {
                    printf("%s\t\t%d\t\t", temp1->filename, temp1->wordcount);
                    temp1 = temp1->s_link;
                }
                printf("\n");
                temp = temp->mlink;
            }
        }
    }
    return SUCCESS;
}

int search_element(Hash *hash_table, char *element) {
    int i;
    if (isdigit(element[0])) {
        i = 26;
    } else if (isalpha(element[0])) {
        i = tolower(element[0]) - 'a';
    } else {
        i = 27;
    }
    Mnode *temp = hash_table[i].hlink;
    while (temp != NULL) {
        if (strcmp(temp->word, element) == 0) {
            printf("The element is found in %d files\n", temp->filecount);
            Snode *temp1 = temp->slink;
            while (temp1 != NULL) {
                printf("%s and the Wordcount is %d\n", temp1->filename, temp1->wordcount);
                temp1 = temp1->s_link;
            }
            return SUCCESS;
        }
        temp = temp->mlink;
    }
    return FAILURE;
}

int save_database(char *filename, Hash *hash_table) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return FAILURE;
    }
    for (int i = 0; i < 28; i++) {
        if (hash_table[i].hlink != NULL) {
            Mnode *temp = hash_table[i].hlink;
            while (temp != NULL) {
                fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->filecount);
                Snode *temp1 = temp->slink;
                while (temp1 != NULL) {
                    fprintf(fp, "%s;%d;", temp1->filename, temp1->wordcount);
                    temp1 = temp1->s_link;
                }
                fprintf(fp, "#\n");
                temp = temp->mlink;
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}

int update_database(Hash *hash_table, List **head1, Mnode **head2, Snode **head3, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return FAILURE;
    }
    char str[100];
    int prei = -1;
    Mnode *prem = NULL;
    while (fscanf(fp, "%s", str) != EOF) {
        if (str[0] == '#') {
            int i = atoi(strtok(&str[1], ";"));
            Mnode *mnew = malloc(sizeof(Mnode));
            if (!mnew) {
                printf("Memory allocation failed\n");
                fclose(fp);
                return FAILURE;
            }
            Snode *snew = malloc(sizeof(Snode));
            if (!snew) {
                free(mnew);
                printf("Memory allocation failed\n");
                fclose(fp);
                return FAILURE;
            }
            if (hash_table[i].hlink == NULL) {
                hash_table[i].hlink = mnew;
            } else if (i == prei && prem != NULL) {
                prem->mlink = mnew;
            }
            prei = i;
            prem = mnew;
            strcpy(mnew->word, strtok(NULL, ";"));
            mnew->filecount = atoi(strtok(NULL, ";"));
            mnew->slink = snew;
            mnew->mlink = NULL;
            Snode *pres = mnew->slink;
            for (int j = 0; j < mnew->filecount; j++) {
                strcpy(pres->filename, strtok(NULL, ";"));
                List *temp = *head1;
                while (temp != NULL) {
                    if (strcmp(pres->filename, temp->file_name) == 0) {
                        temp->status = 1;
                        break;
                    }
                    temp = temp->link;
                }
                pres->wordcount = atoi(strtok(NULL, ";"));
                if (j < mnew->filecount - 1) {
                    Snode *snext = malloc(sizeof(Snode));
                    if (!snext) {
                        printf("Memory allocation failed\n");
                        fclose(fp);
                        return FAILURE;
                    }
                    pres->s_link = snext;
                    pres = snext;
                } else {
                    pres->s_link = NULL;
                }
            }
        }
    }
    fclose(fp);
    return SUCCESS;
}
