#include <stdio.h>
#include<stdlib.h>
#include <time.h>

void FCFS(char *order_id[], int order_due[], int order_quant[], char *order_name, int plant_prod, char *resultstack)
{
    

   

}
void SJF(char *order_id[], int order_due[], int order_quant[], char *order_name, int plant_prod)
{
    

    
    
}
void PR(char *order_id[], int order_due[], int order_quant[], char *order_name, int plant_prod)
{
    

    
    
}

int main(){

    //start period
    int day;
    int mon;
    int year;

    //end period
    int day1;
    int mon1;
    int year1;

    //-----------------------GET INFO FROM PART 1--------------------------

    int startperiod[];  // array[0]= year, array[1] = month, array[2] = date
    int endperiod[];    // array[0]= year, array[1] = month, array[2] = date

    char *orderid[];    //order number
    int orderdue[];     //due date: array[n]= year, array[n+1] = month, array[n+2] = date
    int orderquant[];   //Quantity
    char *ordername[];  //Product name

     //--------------------------------------------------------------------

    //plant parameters
    int plant_x = 300;
    int plant_y = 400;
    int plant_z = 500;

    // edit these using function and send to part 3

    int orderstack[];   //production orders in stack, lower index first , array[n] = order id, array[n+1] = order start, array[n+2] = order end
    

    //FCFS, SJF, PR
    //get alg from outside
    char *alg;

    if(strcmp(alg,"FCFS")==0)
    {

    }
    else if(strcmp(alg,"SJF")==0)
    {

    }
    else if(strcmp(alg,"PR")==0)
    {
        
    }

    //send result stack to part 3

    return 0;
}
