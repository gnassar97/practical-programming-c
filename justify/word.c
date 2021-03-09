#include <stdio.h>
#include "word.h"

#define MAX_WORD_LEN 20

int read_char(void){
	int ch = getchar();
	if(ch == '\n' || ch == '\t'){
		return ' ';
	}
	return ch;
}

void read_word(char *word, int len){
	int ch, pos = 0;
	while((ch = read_char()) == ' ')
	;
	while(ch != ' ' && ch != EOF){
		if(pos<len){
			word[pos++] = ch;
		}
		ch = read_char();
	}
	if(pos > MAX_WORD_LEN){
		word[MAX_WORD_LEN] = '*';
		pos = MAX_WORD_LEN + 1;
	}
	word[pos] = '\0';
}
	

