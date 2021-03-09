#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
bool pal = true;
char *sentence;

int main(void){
	sentence = malloc(10000);
	char *pos = &sentence[0];
	char x;
	int i = 0;
	printf("Enter a Message:");
	while((x=getchar())!='\n'){
		if(x != ' ' && x != '.' && x != ',' && x != '-' && x != '!' && x != '?'){
			*pos = x;
			pos++;
			i++;
		}
	}

	char *low = &sentence[0];
	pos--;
	for(int c = i-1; c > -1; c--){
		if (*pos != *low){
			pal = false;
		}
		pos--;
		low++;
	}
	if(pal == false){
		printf("Not a palindrome\n");
	}
	else{
		printf("Palindrome\n");
	}

	return 0;
}
