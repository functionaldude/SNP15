#include <stdio.h>

int rry[] = {5,2,3,6,4,1};
int len = 6;

void check();
void bubble();
void quick();

int main()
{
  printf("bubble:   ");
  bubble(rry);
  check(rry);

  printf("quick:    ");
  quick(rry);
  check(rry);

  return 0;
}

void check()
{
  int ok = 1;
  for (int i = 0; i < len; i++)
  {
    printf("%d", rry[i]);

    if (rry[i] != (i + 1))
      ok = 0;
  }

  if (ok)
    printf(" PASS\n");
  else
    printf(" FAIL\n");
}

void bubble()
{
}

void quick()
{
}
