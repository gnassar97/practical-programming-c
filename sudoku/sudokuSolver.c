#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>



int puzzle[9][9];

FILE *fp;
int i,j;
int read_file(char array[]);
int getpuzzle(void);


int read_file(char in_file[]){
	if ((fp = fopen(in_file, "r")) == NULL){
		printf("File Read Error\n");
		return -1;
	}
	printf("File Read!");
	return 0;
}
int getpuzzle(void){
	int a,b,c,d,e,f,g,h,j;
    // counter for checking if the lines are correct
    int count = 0;

    char line[256];
    for (i = 0; i < 9; i++){
    	while (fgets(line, 256,fp) != NULL){
    		if ((sscanf(line, "%d %d %d %d %d %d %d %d %d", &a,&b,&c,&d,&e,&f,&g,&h,&j))){
    		}
    		puzzle[count][0] = a;
    		puzzle[count][1] = b;
    		puzzle[count][2] = c;
    		puzzle[count][3] = d;
   			puzzle[count][4] = e;
   			puzzle[count][5] = f;
   			puzzle[count][6] = g;
   			puzzle[count][7] = h;
   			puzzle[count][8] = j;
   			count++;
    	}
	}
	fclose(fp);
	return 0;
}
int isempty(int row, int col, int num)
{
    int i, j;
    for(i=0; i<9; ++i)
        if( (puzzle[row][i] == num) || (puzzle[i][col] == num )  )//checking in row and col
            return 0;

     //checking in the grid
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;

    for(i=rowStart; i<(rowStart+3); ++i)
    {
        for(j=colStart; j<(colStart+3); ++j)
        {
            if(puzzle[i][j] == num )
                return 0;
        }
    }

    return 1;
}

int solve(int row, int col)
{
    int i;
    if( row < 9 && col < 9 )
    {
        if(puzzle[row][col] != 0 )//pre filled
        {
            if((col+1) < 9 )
                return solve( row, col+1);
            else if( (row+1) < 9 )
                return solve( row+1, 0);
            else
                return 1;
        }
        else
        {
            for(i=0; i<9; i++)
            {
                if( isempty(row, col, i+1) )
                {
                    puzzle[row][col] = i+1;

                    if( (col+1)<9 )
                    {
                       if( solve( row, col +1) )
                           return 1;
                        else
                            puzzle[row][col] = 0;
                    }
                    else if( (row+1)<9 )
                    {
                        if( solve( row+1, 0) )
                            return 1;
                        else
                            puzzle[row][col] = 0;
                    }
                    else
                        return 1;
                }
            }
        }
        return 0;
    }
    else
    {
        return 1;
    }
}


int main(int argc, char *argv[]){
	int inputfile = 0;

	for (i = 1; i < argc; i++){

    if (strcmp(argv[i], "-i") == 0){
        inputfile = i+1;
        }
    }
	if (inputfile == 0){
		printf ("Invalid input format");
		return -1;
	}
	read_file(argv[inputfile]);
	getpuzzle();
	printf("\n+------+------+------+\n");

	for (i = 0; i < 9;i++){
		printf("|");
		for (j = 0; j<9;j++){
			printf("%d ",puzzle[i][j]);

			if ((j == 2)||(j == 5)||(j==8)){
				printf("|");
			}
		}
		if ((i == 2)||(i==5)||(i==8)){
			printf("\n+------+------+------+");
		}
		printf("\n");
	}
	if (solve(0,0)){
		printf("\nSOLVED\n+------+------+------+\n");

		for (i = 0; i < 9;i++){
			printf("|");
			for (j = 0; j<9;j++){
				printf("%d ",puzzle[i][j]);

				if ((j == 2)||(j == 5)||(j==8)){
					printf("|");
				}
			}
			if ((i == 2)||(i==5)||(i==8)){
				printf("\n+------+------+------+");
		}
		printf("\n");
		}
	}
	return 0;

}
