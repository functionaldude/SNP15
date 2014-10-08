#include <stdio.h>
#include <string.h>

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
  int array_tmp[6];
  memcpy(array_tmp, rry, len*sizeof(int));
  int counter1, counter2, tmp;
  for (counter1 = 1; counter1 < len; counter1++) {
    for (counter2 = 0; counter2 < len - 1; counter2++) {
      if (array_tmp[counter2] > array_tmp[counter2 + 1]) {
        tmp = array_tmp[counter2];
        array_tmp[counter2] = array_tmp[counter2 + 1];
        array_tmp[counter2 + 1] = tmp;
      }
    }
  }
  memcpy(rry, array_tmp, len*sizeof(int));
}

void quick()
{
}
