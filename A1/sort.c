#include <stdio.h>

int rry[] = {5,2,3,6,4,1};
int len = 6;

void check();
void bubble();
void quick();
void q_sort();

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
  int array_tmp[6];
  memcpy(array_tmp, rry, len*sizeof(int));
  q_sort(array_tmp, 0, len - 1);
  memcpy(rry, array_tmp, len*sizeof(int));
}

void q_sort(int array[], int left, int right)
{
  int pivot, l_hold, r_hold;

  l_hold = left;
  r_hold = right;
  pivot = array[left];
  while (left < right)
  {
    while ((array[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      array[left] = array[right];
      left++;
    }
    while ((array[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      array[right] = array[left];
      right--;
    }
  }
  array[left] = pivot;
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot)
    q_sort(array, left, pivot-1);
  if (right > pivot)
    q_sort(array, pivot+1, right);
}