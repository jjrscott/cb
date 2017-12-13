/* Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their
  propertes ought to be if an EOF is pushed back, then implement your design.*/
#include "stdio.h"
#include "stdlib.h"  // for atof()

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number wes found

int getop(char []);
void push (double);
double pop (void);

/* reverse Polish calculator */
int main(void)
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
    {
      switch (type)
	{
	case NUMBER:
	  push(atof(s));
	  break;
	case '+':
	  push(pop() + pop());
	  break;
	case '-':
	  op2 = pop();
	  push(pop() - op2);
	  break;
	case '*':
	  push (pop() * pop());
	  break;
	case '/':
	  op2 = pop();
	  if (op2 != 0.0)
	    push (pop() / op2);
	  break;
	case '\n':
	  printf("\t%.8g\n", pop());
	  break;
	default:
	  printf("error: unknown command %s\n", s);
	  break;
	}
    }  
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, con't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
    {
      printf("error: stack empty\n");
      return 0.0;
    }
}

#include "ctype.h"

int getch(void);
void ungetch(int);

/* getop: get next operator or numberic operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;                  // not a number
  i = 0;
  if (isdigit(c))              // collect integer part
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')                // collect fraction part
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  ungetch(c);
  return NUMBER;

}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free posotion in buf

int getch(void)      // get a (possibly pushed back) character
{
  /* if (buf[bufp -1] == EOF) */
  /*   printf("EOF");  // check to see if EOF was pushed back */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else buf[bufp++] = c;
}

