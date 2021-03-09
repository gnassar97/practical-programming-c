/*
* George Nassar
* CSID: gnassar@ualberta.ca
* CCID: 1473504
* Date: 08/12/17
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

#define HV 0
#define VH 1

FILE *fp;
FILE *fpp;
int NUM_PT, i, create, reduction_factor_i;

int *reduction_factor;
char *out_name;
int total = 0;
int check(void);
int display_values(void);
int MTO(void);
int DFS(int);
int reduction_rate(void);
int get_overlap(int value);
char *otation(int, int);
int *intersect(int, int, int);
int overlap(int point_x, int point_y, int *c1, int *c2, int ch1, int ch2);
int read();

struct point{
  int index;        /* the order in the instance file              */
  int x;            /* x coordinate                                */
  int y;            /* y coordinate                                */
  int parent;       /* parent in the tree when added               */
  int num_children; /* has value 0 -- 8                            */
  int child[8];
  int overlap_hv;   /* total overlap when horizontal then vertical */
  int overlap_vh;   /* total overlap when the other way            */
  int out;
};
struct point* points;

int main(int argc, char *argv[]){

	int inputfile = 0, outputfile = 0;
  for (i = 1; i < argc; i++){
    if (strcmp (argv[i], "-i") == 0){
        inputfile = i+1;
    }
    else if (strcmp (argv[i], "-o") == 0){
        outputfile = i+1;
    }
  }
    if (inputfile == 0){
    	printf("./A3 -i inputfile [-o outputfile]\n");
        return -1;
    }
		if (outputfile > 0){
   		create = 1;
   		out_name = argv[outputfile];
   	}
   	read(argv[inputfile]);
   	if (check() == 0){
      MTO();
		}
    return 0;

}

int read(char in_file[]){

	if ((fp = fopen(in_file, "a+")) == NULL){
		printf("File Read Error\n");
		return -1;
	}
	return 0;
}


int check(void){

    int a;
    int num_line;
    int count = 0;
    char b;
    char line[256];
    int adult = -1;
    int kid = -1;
    int dist = -1;
    int MAX_X, MAX_Y;

    while (fgets(line, 256, fp) != NULL){
      if (line[0] == '#' || line[0] == '\n') continue;
      if ((sscanf(line, "%d %d %d", &MAX_X, &MAX_Y, &a) != 2)|| (sscanf(line, "%d %d %s", &MAX_X, &MAX_Y, &b) != 2)){
        printf("Error in reading the instance file!\n");
        create = 3;
        return -5;
      }
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
      if (NUM_PT < 1 || NUM_PT > 10000){
        printf("Error in reading the instance file!\n");
	      create = 3;
        return -8;
      }
      break;
    }
    if (((MAX_X+1)*(MAX_Y+1)) < NUM_PT){
      printf("Error in reading the instance file!\n");
	    create = 3;
      return -1;
    }
    points = malloc(NUM_PT * sizeof(*points));
    while (fgets(line, 256, fp) != NULL){
      if (line[0] == '#' || line[0] == '\n') continue;
      if (count < NUM_PT){
        points[count].x = -1;
        points[count].y = -1;
        points[count].index = -1;
        points[count].parent = -1;
        points[count].num_children = 0;
        points[count].overlap_hv = -1;
        points[count].overlap_vh = -1;

        for(i = 0; i < 8; i++){
          points[count].child[i] = -1;
        }

          if ((sscanf(line, "%d %d %d", &points[count].x, &points[count].y, &a) != 2 || sscanf(line, "%d %d %s", &points[count].x, &points[count].y, &b) != 2)){
            printf("Error in reading the instance file!\n");
  				  create = 3;
            return -9;
        }
        points[count].index = count;

        for (int k = 0; k < count;k++){
          if ((points[count].x == points[k].x) && (points[count].y == points[k].y)){
            create = 3;
            printf("Error in reading the instance file!\n");
            return -3;
          }
        }
        if (points[count].x > MAX_X || points[count].x < 0 || points[count].y > MAX_Y || points[count].y < 0){
          printf("Error in reading the instance file!\n");
  				create = 3;
          return -10;
        }
        count++;
      }
      else if(count == NUM_PT){
        if (sscanf(line, "%d %d %d %d", &adult, &kid, &dist, &a) != 3 || sscanf(line, "%d %d %d %s", &adult, &kid, &dist, &b) != 3){

          printf("Error in reading the instance file!\n");
  				create = 3;
          return -9;
        }
        total += dist;

        for(i = 0; i < count; i++){
          if(points[i].index == adult){
            points[i].child[points[i].num_children] = kid;
            points[i].num_children++;
            points[kid].parent = points[i].index;
          }
        }
        num_line++;
      }
    }
    if (count > NUM_PT ||count < NUM_PT){
      printf("Error in reading the instance file!\n");
			create = 3;
      return -11;
    }
    return 0;
}

int MTO(void){

  int root = -1;
  if(create == 1){
    if((fpp = fopen(out_name, "w")) == NULL){
      printf("File Read error\n");
    }
  }
  display_values();
  for(i = 0; i < NUM_PT; i++){
    if(points[i].parent == -1){
      root = points[i].index;
      break;
    }
  }
  reduction_factor_i = NUM_PT - 1;
  reduction_factor = malloc(NUM_PT * sizeof(int));
  DFS(root);
  reduction_rate();
  return 0;
}

int display_values(void){

  if(NUM_PT == 1){
    return -1;
  }
  else if (NUM_PT > 1){
    if(create == 1){
      char buffer[10000];
      sprintf(buffer, "\np[1].index = %d\np[1].x = %d\np[1].y = %d\np[1].parent = %d\np[1].num_children = %d\np[1].child[8] = { ",points[1].index, points[1].x, points[1].y, points[1].parent, points[1].num_children);
      fputs(buffer, fpp);
      if(points[1].num_children >= 0){
        for(i = 0; i < points[1].num_children; i++){
          if(points[1].child[i] != -1){
            char buff[2000];
            sprintf(buff, "%d ", points[1].child[i]);
            fputs(buff, fpp);
            }
        }
      }
      fprintf(fpp,"}\n");
      if(points[1].overlap_hv == -1){
        fprintf(fpp, "p[1].overlap_hv = 0\n");
      }
      else{
        char bufff[2000];
        sprintf(bufff, "p[1].overlap_hv = %d\n", points[1].overlap_hv);
        fputs(bufff, fpp);
      }
      if(points[1].overlap_vh == -1){
        fprintf(fpp, "p[1].overlap_vh = 0\n\n");
      }
      else{
        char buffe[2000];
        sprintf(buffe, "p[1].overlap_vh = %d\n", points[1].overlap_vh);
        fputs(buffe, fpp);
      }

    }
    else{
      printf("\np[1].index = %d\np[1].x = %d\np[1].y = %d\np[1].parent = %d\np[1].num_children = %d\np[1].child[8] = { ",points[1].index, points[1].x, points[1].y, points[1].parent, points[1].num_children);
      if(points[1].num_children >= 0){
        for(int j = 0; j < points[1].num_children; j++){
          if(points[1].child[j] != -1){
            printf("%d ", points[1].child[j]);
            }
          }
        }
        printf("}\n");
        if(points[1].overlap_hv == -1){
          printf("p[1].overlap_hv = 0\n");
        }
        else{
          printf("p[1].overlap_hv = %d\n", points[1].overlap_hv);
       }
        if(points[1].overlap_vh == -1){
          printf("p[1].overlap_vh = 0\n\n");
        }
        else{
          printf("p[1].overlap_vh = %d\n\n", points[1].overlap_vh); 
        }
      }
      
    }
  return 0;
}

int DFS(int point_num){

  int j;
  reduction_factor[reduction_factor_i] = points[point_num].index;
  reduction_factor_i--;
  if(create == 1){
    fprintf(fpp,"p[%d].index = %d, .num_children = %d",point_num, points[point_num].index, points[point_num].num_children);
  }
  else{
    printf("p[%d].index = %d, .num_children = %d",point_num, points[point_num].index, points[point_num].num_children);
  }
  for(j = 0; j < points[point_num].num_children; j++){
    if(create == 1){
      fprintf(fpp,", .child[%d] = %d",j, points[point_num].child[j]);
    }
    else printf(", .child[%d] = %d",j, points[point_num].child[j]);
  }
  if(create == 1) fprintf(fpp,"\n");
  else printf("\n");
  for(j = 0; j < points[point_num].num_children; j++){
    DFS(points[point_num].child[j]);
  }
  return 0;
}

int get_overlap(int value){

  int children = points[value].num_children;
  int point_x = points[value].x;
  int point_y = points[value].y;
  int size = pow(2, children);
  int orientation[size][children];

  for(i = 0; i < size; i++){
    char *orient = malloc(sizeof(*orient));
    orient = otation(i, children);
    for(int j = 0; j < children; j++){
      orientation[i][j] = orient[j]-'0';
    }
  }
  for(int l = 0; l < size; l++){
    for(int adult = 0; adult < 2; adult++){
      int t_overlap = 0;
      int reverse;
      if(adult == 0) reverse = 1;
      else reverse = 0;
      int *par = intersect(value, points[value].parent, reverse);
      if(par[0] == -1 && par[1] == -1){
        par[0] = points[points[value].parent].x;
        par[1] = points[points[value].parent].y;
      }

      for(int p = 0; p < children; p++){
        points[points[value].child[p]].out = 0;
      }
      points[points[value].parent].out = 0;
      if(children > 1){
        for(i = 0; i < children; i++){

          int *c1 = intersect(value, points[value].child[i],orientation[l][i]);
          if(points[points[value].child[i]].out == 1) continue;
          if(c1[0] == -1 && c1[1] == -1){
            c1[0] = points[points[value].child[i]].x;
            c1[1] = points[points[value].child[i]].y;
          }
          for(int j = i+1; j < children; j++){
            int *c2 = intersect(value, points[value].child[j], orientation[l][j]);
            if(points[points[value].child[j]].out == 1) continue;
            if(c2[0] == -1 && c2[1] == -1){
              c2[0] = points[points[value].child[j]].x;
              c2[1] = points[points[value].child[j]].y;
            }
            t_overlap += overlap(point_x, point_y, c1, c2, points[value].child[i], points[value].child[j]);
            if(points[points[value].child[i]].out == 1) break;
          }

        }
      }
      for(int j = 0; j < children; j++){
        if(orientation[l][j] == HV){
          t_overlap += points[points[value].child[j]].overlap_hv;
        }
        else{
          t_overlap += points[points[value].child[j]].overlap_vh;
        }
      }
      if(points[value].parent != -1){
        for(int j = 0; j < children; j++){
          int *c2 = intersect(value, points[value].child[j], orientation[l][j]);
          if(points[points[value].child[j]].out == 1) continue;
          if(c2[0] == -1 && c2[1] == -1){
            c2[0] = points[points[value].child[j]].x;
            c2[1] = points[points[value].child[j]].y;
          }
          if(points[points[value].parent].out == 1) continue;
          t_overlap += overlap(point_x, point_y, c2, par, points[value].child[j], points[value].parent);

          if(points[points[value].parent].out == 1) break;
        }
      }
      if(adult == HV && points[value].overlap_hv < t_overlap){
        points[value].overlap_hv = t_overlap;
      }
      else if(adult == VH && points[value].overlap_vh < t_overlap){
        points[value].overlap_vh = t_overlap;
      }
    }
  }
  return 0;
}
int overlap(int point_x, int point_y, int *c1, int *c2, int ch1, int ch2){
  if(c1[0] == c2[0]){
    if(point_y < c1[1] && point_y < c2[1]){
      if(c1[1] > c2[1]){
        points[ch2].out = 1;
        return c2[1]-point_y;
      }
      else{
        points[ch1].out = 1;
        return c1[1]-point_y;
      }
    }
    else if(point_y> c1[1] && point_y > c2[1]){
      if(c1[1] < c2[1]){
        points[ch2].out = 1;
        return fabs(c2[1]-point_y);
      }
      else{
        points[ch1].out = 1;
        return fabs(c1[1]-point_y);
      }
    }
  }
  else if(c1[1] == c2[1]){
    if(point_x < c1[0] && point_x < c2[0]){
      if(c1[0] > c2[0]){
        points[ch2].out = 1;
        return c2[0]-point_x;
      }
      else{
        points[ch1].out = 1;
        return c1[0]-point_x;
      }
    }
    else if(point_x> c1[0] && point_x > c2[0]){
      if(c1[0] < c2[0]){
        points[ch2].out = 1;
        return fabs(c2[0]-point_x);
      }
      else{
        points[ch1].out = 1;
        return fabs(c1[0]-point_x);
      }
    }
  }
  return 0;
}

char *otation(int index,int num_children){

  int binary = 0;
  int remainder, i = 1;

  while(index!=0){
    remainder = index%2;
    index /= 2;
    binary += remainder * i;
    i *=10;
  }
  char *str = malloc(sizeof(*str));
  sprintf(str, "%0*d", num_children, binary);
  return str;
}

int *intersect(int value, int child, int orient){

  int *corner;

  corner = malloc(2*sizeof(int));
  if((points[value].x == points[child].x)||(points[value].y == points[child].y)){
    corner[0]= -1;
    corner[1]=-1;
  }
  else if(orient == HV){
    corner[0] = points[value].x;
    corner[1] = points[child].y;
  }
  else if(orient == VH){
    corner[0] = points[child].x;
    corner[1] = points[value].y;
  }
  return corner;
}

int reduction_rate(void){

  int *start  = &reduction_factor[0];
  int ov;

  for(i = 0; i < NUM_PT; i++){
    if(points[*start].num_children == 0){
      points[*start].overlap_hv = 0;
      points[*start].overlap_vh = 0;
    }
    else if(points[*start].num_children > 0){
      get_overlap(*start);
    }
    if(points[*start].parent == -1){
      if(points[*start].overlap_hv > points[*start].overlap_vh) ov = points[*start].overlap_hv;
      else ov = points[*start].overlap_vh;
      if(create == 1){
        fprintf(fpp,"\nThe total overlap is %d\n", ov);
      }
      else{printf("\nThe total overlap is %d\n", ov);}
      break;
    }
    start++;
  }
  double rr;

  rr = (1.0*(ov))/(1.0*(total));
  if(create == 1) fprintf(fpp, "The reduction rate is %.2f\n", rr);
  else printf("The reduction rate is %.2f\n", rr);
  return 0;
}
