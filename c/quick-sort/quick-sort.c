#include <stdio.h>
#include <stdlib.h>

#define DATASET_LENGTH 1000

int dataset[DATASET_LENGTH] = {0};

void quick_sort(int *data, int start, int end);


int main()
{

	for (int i = 0; i < DATASET_LENGTH; i++)
	{
		dataset[i] = rand() % 10000;
	}

	printf("random number generate finish.\r\n");
	printf("start to sort\r\n");

	quick_sort(dataset, 0, DATASET_LENGTH-1);

	printf("quick sort finish.\r\n");

	for (int i = 0; i < DATASET_LENGTH; i++)
	{
		printf("%d === %d\r\n", i, dataset[i]);
	}

	return 0;
}

void quick_sort(int *data, int start, int end)
{
	if (start >= end)
	{
		return ;
	}

	// define two pointer, point to the begin and end
	int x = start, y = end;
	int base = data[start];

	while (x < y)
	{
		while (data[y] > base && x <y)
		{
			y--;
		}

		if (x < y)
		{
			data[x++] = data[y];
		}

		while (data[x] < base && x < y)
		{
			x++;
		}

		if (x < y)
		{
			data[y--] = data[x];
		}
	}

	data[x] = base;

	quick_sort(data, start, x-1);
	quick_sort(data, x+1, end);

	return;
}
