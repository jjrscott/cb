/* Write a program to "fold" long input lines into two or more shorter lines 
   after the last non-blank character that occurs before the n-th column of input. 
   Make sure your program does somthing intelligent with very long lines, and
   if there are no banks or tabs before the specified column. */
#include <stdio.h>

#define COLUMN 5

int main(void)
{
  int c, i, j, k;
  char line[COLUMN+1];
  
  i = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')            // if line new print string and reset counter
      {
	line[i] = c;
	line[i+1] = '\0';
	printf("%s", line);
	i = 0;                // reset counter
      }
    else if (i <= COLUMN-1)   // if characters have not pass the column limit
      {
	line[i] = c;          // add the last read char to the string
	++i;
      }
    else
      {
	k = 0;
	for (j = i-1; (line[j] == ' ') && (j >= 0); --j) // go to the last non blank char
	  ++k ;                   
	line[j+1] = '\0';
	printf("%s", line);      // add NULL to the end and print string
	for (i = 0; i < k; ++i)  // add spaces back and the last char
	  line[i] = ' ';
	line[i] = c;             // add char to the next string
	++i;                     
      }
  line[i] = '\0';                // print the last chars
  printf("%s\n", line);

  return 0;
}
