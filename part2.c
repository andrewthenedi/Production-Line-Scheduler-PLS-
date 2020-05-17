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

void FCFS(struct Order orderstack[],struct Order resultstack[], struct Date start, struct Date end, int plantprod, int length)
{
    
   for(int i = 0;i < length; i++ )
   {
       
   }


   return resultstac;
}
void SJF(struct Order orderstack[],struct Order resultstack[], struct Date start, struct Date end, int plantprod, int length)
{
    for(int i = 0;i < length; i++ )
   {
       
   }
   
    return resultstac;
}


int main(){


    //-----------------------GET INFO FROM PART 1--------------------------

    struct Order input[];
    int inputlength;
    struct Date end;
    struct Date start;

    char *alg;

     //--------------------------------------------------------------------
    

    //FCFS, SJF, PR
    //get alg from outside

    struct order resultx[];
    struct order resulty[];
    struct order resultz[];
    

    if(strcmp(alg,"FCFS")==0 || strcmp(alg,"SJF")==0)
    {
        FCFS(struct input, struct resultx, struct start,struct end, plant_x, inputlength);
        FCFS(struct input, struct resulty, struct start,struct end, plant_y, inputlength);
        FCFS(struct input, struct resultz, struct start,struct end, plant_z, inputlength);
        //send to part3
        SJF(struct input, struct result, struct start,struct end, plant_x, inputlength);
        SJF(struct input, struct result, struct start,struct end, plant_y, inputlength);
        SJF(struct input, struct result, struct start,struct end, plant_z, inputlength);
    }
    else
    {
        printf("error input");
    }

    //send result stack to part 3

    return 0;
}
