#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"

#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20
int line_len = 0;
int num_words = 0;

struct node{
	char node_word[MAX_WORD_LEN + 1];
	struct node *next;
};
struct node *head = NULL;
struct node *tail = NULL;

void clear_line(void){
	struct node *temp;
	while(head){
		temp = head;
		head = head->next;
		free(temp);
	}
	tail = head;
	line_len = 0;
	num_words = 0;
}

void add_word(const char *word){

	if(!head){
		head = malloc(sizeof(struct node));
		if(!word){
			printf("Error: malloc failed in line.c\n");
			exit(EXIT_FAILURE);
		}
		strcpy(head->node_word, word);
		head->next = NULL;
		tail = head;
	}
	else{
		struct node *new_node = malloc(sizeof(struct node));
		if(!new_node){
			printf("Error: malloc failed in line.c\n");
			exit(EXIT_FAILURE);
		}
		strcpy(new_node->node_word, word);
		new_node->next = NULL;
		tail->next = new_node;
		tail = new_node;
	}
	line_len += strlen(word);
	num_words++;
}


int space_remaining(void){
	return MAX_LINE_LEN - line_len - num_words;
}

void write_line(void){
	int extra_spaces, spaces_to_insert, i;
	extra_spaces = MAX_LINE_LEN - line_len - num_words;

	
	while(head){
		printf("%s", head->node_word);
		if(head->next){
			putchar(' ');
			spaces_to_insert = extra_spaces / (num_words - 1);
			if((extra_spaces > 1) && (num_words % 2)){
				++spaces_to_insert;
			}
			for(i = 0; i < spaces_to_insert; i++){
				putchar(' ');
			}
			extra_spaces -= spaces_to_insert;
			num_words--;
		}
		head = head->next;
	}
	putchar('\n');
	return;
}

void flush_line(void){
	if(head){
		write_line();
	}
}			










		










