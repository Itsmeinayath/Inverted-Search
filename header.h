#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>


#define SUCCESS 0
#define FAILURE -1
#define LIST_EMPTY -2

typedef struct node 
{
	char *file_name;
	int status;
	struct node *link;
}List;

typedef struct hnode
{
	int index;
	struct mainnode *hlink;
}Hash;

typedef struct mainnode
{
	int filecount;
	char word[20];
	struct subnode *slink;
	struct mainnode *mlink;
}Mnode;

typedef struct subnode
{
	int wordcount;
	char filename[20];
	struct subnode *s_link;
}Snode;

int read_and_validate(int argc,char *argv[],List **head);

int create_database(List **head1,Mnode **head2,Snode **head3,Hash *hash_table);

void add_to_database(Hash *hash_table,Mnode **head2,Snode **head3,int i,char *file_name,char *word);

void creat_mnode(char *word,Mnode **head2);

void creat_snode(char *filename,Snode **head3);

int print_database(Hash *hash_table);

int search_element(Hash *hash_table,char *element);

int save_database (char *filename,Hash *hash_table);

int update_database(Hash *hash_table,List **head1,Mnode **head2,Snode **head3,char *filename);

#endif