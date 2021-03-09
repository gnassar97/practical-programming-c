#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double measure_Avg_time(char * command, int num_trial)
{
    double Avg_time = 0;
    for(int i=1; i<=num_trial ;i++)
    {
        time_t start_time = time(NULL);
        system(command);
        Avg_time += difftime(time(NULL), start_time);
    }
    return Avg_time/num_trial;
}

int main(int argc , char * argv[]) {
    // Here, the average is taken over 3 trials
    printf("The average time of running %s is %g sec.\n",argv[1],measure_Avg_time(argv[1],3));
    return 0;
}