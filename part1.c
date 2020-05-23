#include <stdio.h>
#include<stdlib.h>
#include <time.h>
// #include <unistd.h>
#include <string.h>


/*
 apparently strtok does not works well in this situation 
 The pointer is such a mess 
 
*/ 

// int valid_date(int day, int mon, int year)    
// {
//     int is_valid = 1, is_leap = 0;
    
//     if (year >= 1800 && year <= 9999) 
//     {
 
//         //  check whether year is a leap year
//         if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
//         {
//             is_leap = 1;
//         }
        
//         // check whether mon is between 1 and 12
//         if(mon >= 1 && mon <= 12)
//         {
//             // check for days in feb
//             if (mon == 2)
//             {
//                 if (is_leap && day == 29) 
//                 {
//                     is_valid = 1;
//                 }
//                 else if(day > 28) 
//                 {
//                     is_valid = 0;
//                 }
//             }
            
//             // check for days in April, June, September and November
//             else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
//             {
//                 if (day > 30)
//                 {
//                     is_valid = 0;
//                 }
//             }
 
//             // check for days in rest of the months 
//             // i.e Jan, Mar, May, July, Aug, Oct, Dec
//             else if(day > 31)
//             {            
//                 is_valid = 0;
//             }        
//         }
        
//         else
//         {
//             is_valid = 0;
//         }
 
//     }
//     else
//     {
//         is_valid = 0;
//     }
    
//     return is_valid;
// }

// int* remaining(int yyNow, int mmNow, int ddNow, int yy, int mm, int dd)
// {
//     int dd_diff, mm_diff, yy_diff;
//     int *diff = malloc(sizeof (char) * 3);

//     // time_t t = time(NULL);
//     // struct tm tm = *localtime(&t);

//     // ddNow = tm.tm_mday;
//     // mmNow = tm.tm_mon + 1;
//     // yyNow = tm.tm_year + 1900;

//     if(!valid_date(ddNow, mmNow, yyNow))
//     {
//         printf("First date is invalid.\n");
//         // return 0;
//     }
    
//     if(!valid_date(dd, mm, yy))
//     {
//         printf("Second date is invalid.\n");
//         // return 0;
//     }       
    
//     if(dd < ddNow)
//     {      
//         // borrow days from february
//         if (mm == 3)
//         {
//             //  check whether year is a leap year
//             if ((yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0)) 
//             {
//                 dd += 29;
//             }
            
//             else
//             {
//                 dd += 28;
//             }                        
//         }
        
//         // borrow days from April or June or September or November
//         else if (mm == 5 || mm == 7 || mm == 10 || mm == 12) 
//         {
//            dd += 30; 
//         }
                
//         // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
//         else
//         {
//            dd += 31;
//         }
        
//         mm = mm - 1;
//     }
    
//     if (mm < mmNow)
//     {
//         mm += 12;
//         yy -= 1;
//     }       
    
//     dd_diff = dd - ddNow;
//     diff[0] = dd_diff;
//     mm_diff = mm - mmNow;
//     diff[1] = mm_diff;
//     yy_diff = yy - yyNow;
//     diff[2] = yy_diff;
    
//     return diff;
// }


void getsubstring(char origin[], char cpy[], int from, int end){
    if(end < 0){
        end = strlen(origin);
    }
    // printf("from %d to %d", from, end);
    // printf("%d\n", end-from);
    strncpy(cpy, &origin[from], end - from);
    cpy[end] = 0;
    // printf("test %s, from %d to %d\n", cpy, from, end);
}


int main()
{
    struct Date 
    {
        int day[100];
        int mon[100];
        int year[100];
    };
    struct Order
    {
        char *orderID[100];
        char *productName[100]; 
        int quantity[100];
    };

    // buffers
    char* from, userInput[100];
    char req[30];
    char * startDate[100];
    char * endDate[100];
    char * dueDate[100];

    // status codes    
    int i = 0, status, n, j = 0;
    char * blank = " ";
    char * stp = "-";
    char * token;

    // orders 
    struct Date start[20];
    struct Date end[20];
    struct Date due[20];
    struct Order input[20];

    printf("~~WELCOME TO PLS~~\n");
    while (status == 0)
    {
        printf("Please enter:\n");
        printf("i is now %d\n", i);
        fgets(userInput, sizeof userInput, stdin);

        from = userInput;
        // token = strtok(from, blank);

    
        int from1, end1;

        // find the space
        for(int k = 0; k < strlen(from); k++){
            if(from[k] != ' '){
                from1 = k; 
                end1 = k; 
                while(from[end1] != ' ' && end1 < strlen(from))   end1++;
                // printf("from is %d, end is %d\n", from1, end1); 
                getsubstring(from, req, from1, end1);
                // printf("its %s\n", req);
                break;
            }
        }

        // req[j] = token;
        // token = strtok(NULL, blank);
        printf("%s\n", req);
        if (strcmp(req, "addPERIOD") == 0)
        {

            char tempdate[30];
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            char date1[15];
            printf("%s\n", tempdate);
            int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            start->year[0] = atoi(date1);
            printf("check2 %d\n", start->year[0]);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            printf("check %s\n", date1);
            start->mon[0] = atoi(date1);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            printf("check %s\n", date1);
            start->day[0] = atoi(date1);

            /* DATE 1 IS DONE */ 

            memset(tempdate, 0, 30);

            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            printf("%s\n", tempdate);
            from2 = end2 = 0;
            // int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            start->year[0] = atoi(date1);
            printf("check2 %d\n", start->year[0]);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            printf("check %s\n", date1);
            start->mon[0] = atoi(date1);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            printf("check %s\n", date1);
            start->day[0] = atoi(date1);
            
        }
        else if (strcmp(req, "addORDER") == 0)
        {
            printf("this is addORDER\n");

            char tempdate[30];
            /*Split again*/
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            // printf("ez %s\n", tempdate);
            input->orderID[i] = tempdate; 
            memset(tempdate, 0, 30);

            // the date 
            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }
            
            char date1[15];
            // printf("%s\n", tempdate);
            int from2, end2; 
            /* split the - in the date */
             for(int k = 0; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            due->year[i] = atoi(date1);
            // printf("check2 %d\n", start->year[0]);

            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            // printf("check %s\n", date1);
            due->mon[i] = atoi(date1);
            memset(date1, 0, 30);

            for(int k = end2; k < strlen(tempdate); k++){ 
                if(tempdate[k] != '-'){
                    from2 = k; 
                    end2 = k; 
                    while(tempdate[end2] != '-' && end2 < strlen(tempdate)) end2++;
                    getsubstring(tempdate, date1, from2, end2);
                    break;
                }
            }
            // printf("check %s\n", date1);
            due->day[i] = atoi(date1);

            memset(tempdate, 0, 30);

            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            printf("ez %s\n", tempdate);
            input->quantity[i] = atoi(tempdate);


            memset(tempdate, 0, 30);

            for(int k = end1; k < strlen(from); k++){
                
                if(from[k] != ' '){
                    from1 = k; 
                    end1 = k; 
                    while(from[end1] != ' ' && end1 < strlen(from)) end1++;
                    getsubstring(from, tempdate, from1, end1);
                    break;
                }
            }

            printf("ez %s\n", tempdate);
            input->productName[i] = tempdate;
            i++;
            // split the date


        //     input->orderID[i] = token;
        //     token = strtok(NULL, blank);
        //     dueDate[i] = token;
        //     token = strtok(NULL, blank);
        //     input->quantity[i] = atoi(token);
        //     token = strtok(NULL, blank);
        //     input->productName[i] = token;
        //     printf("%s\n", input->orderID[i]);
        //     // printf("%s\n", dueDate[i]);
        //     // printf("%d\n", input->quantity[i]);
        //     // printf("%s\n", input->productName[i]);

        //     token = strtok(dueDate[i], stp);
        //     due->year[i] = atoi(token); 
        //     token = strtok(NULL, stp);
        //     due->mon[i] = atoi(token);
        //     token = strtok(NULL, stp);
        //     due->day[i] = atoi(token);
        //     // printf("%d\n", due->year[i]);
        //     // printf("%d\n", due->mon[i]);
        //     // printf("%d\n", due->day[i]);

        //     // for (n = 0; n < 3; n++)
        //     // {
        //     //     printf("%s",input->orderID[n]);
        //     // }  
        //     i++;
        }
        else if (strcmp(req, "exitPLS") == 0)
        {
            printf("Bye-bye!\n");
            status = 1;
            
        }
        else if (strcmp(req, "runPLS") == 0)
        {
            printf("this is runPLS\n");
            for(int n = 0; n < i; n++){
                printf("%s\n", input->orderID[n]);
            }
            // char * alg = token;
            // token = strtok(NULL, blank);
            // printf("%s\n", input->orderID[0]);

            // Schedule(input, start, end, due, alg, i);    dal's function
        }
        else
        {
            printf("Invalid Input!\n");   
        }
        // for (n = 0; n < 3; n++)
        // {
        //     printf("%s",req[n]);
        // }  
        // printf("%d", j);
        j++;
    }
}
