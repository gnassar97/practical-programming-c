#include <stdio.h>
#include <stdbool.h>

void create_magic_square(int n, char magic_square[n][n]);
void print_magic_square(int n, char magic_square[n][n]);

int main(void){

  int n;

  printf("This program creates a magic square of a specified size.\n");
  printf("The size must be an odd number between 1 and 99.\n");
  printf("Enter size of magic square: ");
  scanf("%d", &n);

  char magic_square[n][n];
  create_magic_square(n, magic_square);
  print_magic_square(n, magic_square);

  return 0;
}

void create_magic_square(int n, char magic_square[n][n]){

  int i, j, rows = n / 2, col = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      magic_square[i][j] = 0;
  magic_square[col][rows] = 1;

  for (i = 1; i < n * n; i++)
    if (magic_square[(col + n - 1) % n][(rows + 1) % n] == 0)
      magic_square[col = (col + n - 1) % n][rows = (rows + 1) % n] = i + 1;
    else
      magic_square[col = (col + 1) % n][rows] = i + 1;
}

void print_magic_square(int n, char magic_square[n][n]){
  
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%6d", magic_square[i][j]);
    printf("\n");
  }
}