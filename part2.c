#include <stdio.h>
#include<stdlib.h>
#include <time.h>


#define plant_x  300;
#define plant_y  400;
#define plant_z  500;

struct Date //YYYY-MM-DD
{ 
    int year; 
    int month;
    int day; 
};

struct Order
{
    char *order_id;
    char *name; 
    struct Date order_due; 
    int quantity;
};

void FCFS(struct Order orderstack[], struct Date start, struct Date end, int plantprod)
{
    
   

}
void SJF(struct Order orderstack[], struct Date start, struct Date end, int plantprod)
{
    
   

}


int main(){


    //-----------------------GET INFO FROM PART 1--------------------------

    struct order input[];
    struct Date end;
    struct Date start;

    char *alg;

     //--------------------------------------------------------------------
    

    //FCFS, SJF, PR
    //get alg from outside
    

    if(strcmp(alg,"FCFS")==0 || strcmp(alg,"SJF")==0)
    {
            
    }
    else
    {
        printf("error input");
    }

    //send result stack to part 3

    return 0;
}
