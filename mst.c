/*
* George Nassar
* CSID: gnassar@ualberta.ca
* CCID: 1473504
* Date: 15/11/17
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Global
FILE *fp;
int X_C[10001], Y_C[10001];
int x_coord[10001] = {0}, y_coord[10001]={0};
int NUM_PT, MAX_X, MAX_Y;
int create;
char *out_name;
int root[2];
int distances[10001];
int has_parent[10001];
int minimum[10001];
int inside_mst[10001];
int t_d;
int i, parent, min;
int check();
int read();
int roots();
int distance(int dist,int xi, int yi, int xj, int yj);
int set_tree();
int mst();
int find_parent(int a, int b);
int find_point();
int controls(int count, int a, int b);


int main(int argc, char *argv[]){
	int inputfile = 0, outputfile = 0;
	int i;
    for (i = 1; i < argc; i++){
        
        if (strcmp (argv[i], "-i") == 0){
            inputfile = i+1;
        }
        
        else if (strcmp (argv[i], "-o") == 0){
            outputfile = i+1;
        }
    }
    
    if (inputfile == 0){
    	printf("Assignment2.c [-i inputfile [-o outputfile]]\n");
        return -1;
    }
   	if (outputfile > 0){
   		create = 1;
   		out_name = argv[outputfile];
   	}
   	read(argv[inputfile]);
   	if(check() == 0){
   		set_tree();
   	}
    return 0;
}
// Function to read the sample file
int read(char in_file[]){

	if ((fp = fopen(in_file, "a+")) == NULL){
		printf("File Read Error\n");
		return -1;
	}
	
	return 0;
}

// Function to check through the input file
int check(void){
	
    int a; 
    int count = 0;
    char b;
    char line[256];
    
    
    while (fgets(line, 256, fp) != NULL){
        if (line[0] == '#' || line[0] == '\n') continue;
        // Checking for correct format of numbers
        if ((sscanf(line, "%d %d %d", &MAX_X, &MAX_Y, &a) != 2)|| (sscanf(line, "%d %d %s", &MAX_X, &MAX_Y, &b) != 2)){
            printf("Error in reading the instance file!\n");
	    create = 3;
            return -5;
        }
        // Checking values against max values
        if (MAX_X > 1000 || MAX_X < 0 || MAX_Y > 1000 || MAX_Y < 0){
            printf("Error in reading the instance file!\n");
	    create = 3;
            return -6;
        }
        break;
    }
    
    
    while (fgets(line, 256, fp) != NULL){
        if (line[0] == '#' || line[0] == '\n') continue;
        if (sscanf(line, "%d %d", &NUM_PT, &a) != 1 || sscanf(line, "%d %s", &NUM_PT, &b) != 1){
            printf("Error in reading the instance file!\n");
	    create = 3;
            return -7;
        }
        if (NUM_PT < 1 || NUM_PT > 10001){
        	// Checking NUM_PT for valid int
            printf("Error in reading the instance file!\n");
	    create = 3;
            return -8;
        }
        break;  
    }
  

    if (((MAX_X+1)*(MAX_Y+1)) < NUM_PT){
    	// Checking to see if board is large enough to hold specified number of points
        printf("Error in reading the instance file!\n");
	create = 3;
        return -1;
    }
    
    for (int i = 0;i < NUM_PT; i++){
        while (fgets(line, 256, fp) != NULL){
            if (line[0] == '#' || line[0] == '\n') continue;
            if (sscanf(line, "%d %d %d", &X_C[i], &Y_C[i], &a) != 2 || sscanf(line, "%d %d %s", &X_C[i], &Y_C[i], &b) != 2){
                printf("Error in reading the instance file!\n");
		create = 3;
                return -9;
	        }
	        x_coord[count] = X_C[i];
	        y_coord[count] = Y_C[i];
	        for (int k = 0; k < count;k++){
                if ((X_C[i] == x_coord[k]) && (Y_C[i] == y_coord[k])){
                create = 3;
                printf("Error in reading the instance file!\n");
                return -3;
                }           
            }
            count++;
            if (X_C[i] > MAX_X || X_C[i] < 0 || Y_C[i] > MAX_Y || Y_C[i] < 0){
                printf("Error in reading the instance file!\n");
		create = 3;
                return -10;
            }


        }
    }
    if (count > NUM_PT || count < NUM_PT){
        printf("Error in reading the instance file!\n");
	create = 3;
        return -11;
    }
    return 0;
	
}

//Finding the root
int roots(void){
	root[0] = x_coord[0];
	root[1] = y_coord[0];
	inside_mst[0] = 1;
	return 0;
}

//Finding the distance between points
int distance(int dist,int xi, int yi, int xj, int yj){
	distances[dist] = (fabs(xj - xi) + fabs(yj - yi));
	return 0;
}
//Setting parent values to default
int set_tree(void){
	roots();
	for(int i = 0; i < NUM_PT; i++){
		has_parent[i] = -1;
	}
	mst();
	return 0;
}

//Creating the minimum-weight spanning tree
int mst(void){
    bool filled = false, first = true;
	FILE *fpp;	
	if(create == 1){
		if((fpp = fopen(out_name, "w")) == NULL){
		printf("File Read Error\n");
		}
	}
	if(create == 1){
		fprintf(fpp,"Choosing point 0 as the root...\n");
	}
	else{
		printf("Choosing point 0 as the root...\n");
	} 
	for(i = 0; i < NUM_PT; i++){
		distance(i, root[0], root[1], x_coord[i], y_coord[i]);
		if(create == 1){
			char buffer[10001];
			sprintf(buffer, "Point %d has a distance %d to the tree, parent 0;\n", i, distances[i]);
			fputs(buffer, fpp);
		}
		else{
			printf("Point %d has a distance %d to the tree, parent 0;\n", i, distances[i]);

		}
	}
	fprintf(fp,"\n#Edges of the MST by Prim’s algorithm:\n");
    if(create == 1){
        fprintf(fpp,"#Edges of the MST by Prim’s algorithm:\n");
    }
    else{
        printf("#Edges of the MST by Prim’s algorithm:\n");
    }

    while(filled != true){
        int c = 0;
        int parent_min = -1;
        int point;
        for(i = 0; i < NUM_PT; i++){
            minimum[i] = 0;
        }
        if(first == false){
            int p_index[10001];
            int z = 0;
            for(i = 0; i < NUM_PT; i++){
                distances[i] = -1;
                if(inside_mst[i] == 1){
                    for(int j = 0; j < NUM_PT; j++){
                        if(inside_mst[j] == 0){
                            distance(j, x_coord[i], y_coord[i], x_coord[j], y_coord[j]);
                            if(parent_min == -1){
                                parent_min = distances[j];
                                p_index[z] = i;
                            }
                            else if(distances[j] == parent_min){
                                p_index[z] = i;
                            }
                            else if(distances[j] < parent_min){
                                for(int k = 0; k < NUM_PT; k++){
                                    p_index[k] = -1;
                                }
                                z = 0;
                                parent_min = distances[j];
                                p_index[z] = i;
                            }
                            z++;
                        }
                    }
                }
            }
            z = 0;
            for(i = 0; i < NUM_PT; i++){
                distances[i] = -1;
                if(p_index[i] != -1){
                    z++;
                }
            }
            while(z > 1){
                switch(find_parent(p_index[0], p_index[1])){
                    case 1: case 2: p_index[1] = p_index[z - 1];
                    break;
                    case 3: case 4: p_index[0] = p_index[z - 1];
                    break;
                }
                z--;
            }
            parent = p_index[0];
            for(i = 0; i < NUM_PT; i++){
                if(inside_mst[i] == 0 && has_parent[i] == -1){
                    distance(i, x_coord[parent], y_coord[parent], x_coord[i], y_coord[i]);
                }
            }
        }
        else{
            first = false;
            parent = 0;
        }
        min = -5;
        for(i = 1; i < NUM_PT; i++){
            if(inside_mst[i] == 0 && distances[i] != -1){
                if(min == -5){
                    min = distances[i];
                }
                else{
                    if(distances[i] < min){
                        for(int j = 0; j < NUM_PT; j++){
                            minimum[j] = 0;
                        }
                        min = distances[i];
                    }
                }
                if(distances[i] == min){
                    minimum[i] = 1;
                }
            }
        }

        point = find_point();

        char buffer[10001];
        sprintf(buffer, "%d       %d       %d \n", parent, point, distances[point]);
        if(create == 1){
            fputs(buffer, fpp);
        }
        else{
            printf("%d       %d       %d \n", parent, point, distances[point]);
        }
        fputs(buffer, fp);

        t_d = t_d + distances[point];
        inside_mst[point] = 1;
        has_parent[point] = parent;
        for(i = 0; i < NUM_PT; i++){
            if(inside_mst[i] == 1){
                c++;
            }
        }
        if(c == NUM_PT){
            filled = true;
        }
    }
    char buffer[10001];

    if(create == 1){
        sprintf(buffer, "The total length of the MST is %d.\n", t_d);
        fputs(buffer, fpp);
        fclose(fpp);
    }
    else{
        printf("The total length of the MST is %d.\n", t_d);
    }
    fclose(fp);
	return 0;
}

int find_parent(int a, int b){
    if(y_coord[a] > y_coord[b]){
        return 1;
    }
    else if(y_coord[a] == y_coord[b]){
        if(x_coord[a] >= x_coord[b]){
            return 2;
        }
        else{
            return 3;
        }
    }
    else{
        return 4;
    }
}

int find_point(void){
    int count = 0;
    for(i = 0; i < NUM_PT; i++){
        if(minimum[i] == 1){
            count++;
        }
    }
    if(count > 1){
        int index[10001], begin = 0;
        for(i = 0; i < count; i++){
            for(int j = begin; j < NUM_PT; j++){
                if(minimum[j] == 1 && inside_mst[j] == 0){
                    index[i] = j;
                    begin = (j + 1);
                    break;
                }
            }
        }
        while(count > 1){
            switch(controls(count, index[0], index[1])){
                case 1: case 2: index[1] = index[count - 1];
                break;
                case 3: case 4: index[0] = index[count - 1];
                break;
            }
            count--;
        }
        return index[0];
    }
    else{
        for(i = 0; i < NUM_PT; i++){
            if(minimum[i] == 1){
                count = i;
            }
        }
        return count;
    }
}

int controls(int count, int a, int b){
    if(fabs(y_coord[a] - y_coord[parent]) > fabs(y_coord[b] - y_coord[parent])){
        return 1;
    }
    else if(fabs(y_coord[a] - y_coord[parent]) == fabs(y_coord[b] - y_coord[parent])){
        if(x_coord[a] >= x_coord[b]){
            return 2;
        }
        else{
            return 3;
        }
    }
    else{
        return 4;
    }
}





