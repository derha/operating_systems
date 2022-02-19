#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define THREADS_NUM 3
#define VAL_NUM 5


void *summation (void *file_num)
{
    char file_name[] = "inputX.txt";
    file_name[5] = (char)(file_num);
    char thread_no = (char)(file_num);
    
    FILE *my_file;
    float my_var;
    float sum = 0;
    
    my_file = fopen(file_name, "r");
    
    int i;
    for(i = 1; i <= VAL_NUM; ++i) 
    {
        fscanf(my_file, "%f", &my_var);
        sum += my_var;
        
        printf("Thread%c reads %d. The value is %f. The sum is : %f\n", thread_no, i, my_var, sum);
    }
    
    fclose(my_file);
    
    printf("Thread%c Sum is : %f\n", thread_no, sum);
    
    pthread_exit(NULL);
}


int main()
{
    pthread_t threads[THREADS_NUM];
    
    for (int i = 0; i < THREADS_NUM; ++i) 
    {
        pthread_create(&threads[i], NULL, summation, (void *)(i + 1 + '0'));
    }
    
    pthread_exit(NULL);

    return 0;
}
