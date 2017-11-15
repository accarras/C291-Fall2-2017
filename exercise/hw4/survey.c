/**************************************************************
File creaed by: Tony Carrasco
Date: 11/14/17
Class C291
filename: survey.c
Summary: This program prints a menu asking users about issues 
that are important to them. It will then create a table with 
all of the information.
**************************************************************/
#include <stdio.h>   // for printf and scanf satements

void printResults(char *topics[5], int responses[5][10]);

int main()
{
   int choice = 0; // stores user input
   int person=0;
   
   char *topics[5] = {"War in the Middle East:       ", "Global Warming:             ", "Russia's growing influence:    ", "Nuclear Proliferation:       ", "Issues with the US President: "}; 
   int responses[5][10]; // [x][y]
   for(int g=0;g<5;g++){
       for(int h=0;h<10;h++){
           responses[g][h]=0;
       }
   }
   
   
   while(person<5){       
   // program repeats until all users have answered
       printf("You are user %d \n", person+1);
       printf("There are %d resonders who need to answer\n", (5-(person+1)));
       /*Displaying on screen*/
       printf("On a scale of 1-10, rate how important each cause is to you:\n");
       printf("War in the Middle East: \n");
       scanf("%d", &choice);
       responses[0][choice] = responses[0][choice]++;
       printf("Global Warming: \n");
       scanf("%d", &choice);
       responses[1][choice] = responses[1][choice]++;
       printf("Russia's growing world influence: \n");
       scanf("%d", &choice);
       responses[2][choice] = responses[2][choice]++;
       printf("Nuclear Proliferation: \n");
       scanf("%d", &choice);
       responses[3][choice] = responses[3][choice]++;
       printf("Issues with the US President: \n");
       scanf("%d", &choice);
       responses[4][choice] = responses[4][choice]++;
       printf("Next User(unless you are last): \n");
       
       
       
       person++; //next user
   }
   
   printResults(topics, responses); //prints the array
      
   
    return 0;
}

void printResults(char *topics[5], int responses[5][10]){
     printf("\t\t\t\t\t\t\t\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\ttotal\t avg\n");
        for(int i = 0; i < 5; i++){
        printf("%s", topics[i]);
        //printf("\t");
        for(int j = 0; j<10; j++){
            printf("\t");
            printf("%d", responses[i][j]);
        }
        printf("  \t ");
        int total=0;
        for(int k = 0; k<10; k++){total += responses[i][k];}
        printf("%d", total);
        printf("\t ");
        printf("%d\n", (total/10));
    }
}


