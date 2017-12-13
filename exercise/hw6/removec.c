/*
Author:	Tony Carrasco
Class: C291 Fall 2017
File name: removec.c
Last updated: December 10, 2017
*/

/*
Testing the different types of john.
In every case, john, 'john, "john",
the string is read in as typed.
No character is ignored.

tony@tony-Q302LA:~/Desktop/assignment6$ g++ removec.c
tony@tony-Q302LA:~/Desktop/assignment6$ ./a.out 
Enter a string: 
john
String as read: john
Cleansed string: john
tony@tony-Q302LA:~/Desktop/assignment6$ ./a.out 
Enter a string: 
'john'
String as read: 'john'
Cleansed string: john
tony@tony-Q302LA:~/Desktop/assignment6$ ./a.out 
Enter a string: 
"john"
String as read: "john"
Cleansed string: john
*/

#include <stdio.h>
#include <string.h>

void cleanQuotes( char * string);

int main() {
  char myString[256];
  printf("Enter a string: \n");
  scanf("%s", myString);
  printf( "String as read: %s\n", myString );
  cleanQuotes( myString);
  printf( "Cleansed string: %s\n", myString );

  getchar();
  return 0;
}

void cleanQuotes( char * string){
  for( unsigned int i = 0; i < strlen( string ); i++ ){
    if( string[i] == '\"' ){
      strcpy( string + i, string + i + 1 );
	// removes "
    }
    if( string[i] == '\'' ){
      strcpy( string + i, string + i + 1 );
	// removes '
    }
  }
}

