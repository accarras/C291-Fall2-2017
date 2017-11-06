#include<stdio.h>

int main(void){

	char ch;
	int marks; // stores the test score
	do{
		
		printf("Enter marks: " );
		scanf("%d", &marks);
		printf("\n" );
		while(marks<0 || marks > 100){
		    // makes sure that the test number 
		    // is within valid range
		    printf("Please input a number from 0 and 100: ");
		    scanf("%d", &marks);
		    printf("\n" );
		}
		printGrade(marks);
		printf("\nDo you want to continue? (Y/N)");
		scanf(" %c",&ch); //do not modify this.
	}while(ch == 'y'|| ch == 'Y');
	return 0;
}

void printGrade(int marks){
    // simple program that prints
    // the appropriate grade for the score
    if (marks > 90){
        printf("Your grade is: A\n");
    }
    else if (marks > 80){
        printf("Your grade is: B\n");
    }
    else if(marks > 70){
        printf("Your grade is: C\n");
    }
    else {
        printf("You have failed\n");
    }
}