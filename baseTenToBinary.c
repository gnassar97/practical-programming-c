#include <stdio.h>
// PROGRAM PRINTS BINARY FROM NUMBER

void pb(int n);


int main(void){
	int n;
	printf("Enter a number:");
	scanf("%d", &n);
	pb(n);
	return 0;
}

void pb(int n){
	if(n!=0){
		pb(n/2);
		putchar('0' + n % 2);
	}
}
