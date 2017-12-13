/* Define a macro swap(t,x,y) that interchanges two arguments of type t, 
   (block structure will help). */
#include <stdio.h>

#define swap(t,x,y) {t temp; temp=(x); (x)=(y); (y)=temp;}

int main(void)
{
  int x = 3, y = 7;

  swap(int, x, y);
  printf("x=%d, y=%d", x, y);
  return 0;
}
