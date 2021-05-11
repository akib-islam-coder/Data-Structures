#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_OF_DATA_ITEMS	10

//int data_arr[NO_OF_DATA_ITEMS] = { 47, 75, 86, 100, 100, 1, 69, 67, 87, 47 };		//Unsorted array
int data_arr[NO_OF_DATA_ITEMS] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };		//Already sorted elements

void swap(int * num1, int * num2)
{
	int tmp = 0;
	tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

void print_elements(int* arr)
{
	int i = 0;
	for (i = 0; i < NO_OF_DATA_ITEMS; i++)
	{
		printf("%d ", arr[i]);
		printf("\r\n");
	}
}

void bubble_sort(int data_arr[NO_OF_DATA_ITEMS])
{
	/*
	* Complexity of Bubble Sort - Best Time (when list is already sorted) - O(n), Worst time - O(n^2)
	* Bubble sort implementation will be adaptive and stable (order will be maintained for duplicates)
	* The bubble sort algorithm compares consecutive elements and after completing one pass, largest element will be seperated and pused at the
	* end of the array index.
	* If there are n elements and we do k passes, then we will get the kth largest element after completing kth pass of bubble sort.
	*/

	/* Print the array*/
	printf("Elements in array before bubble sort : \r\n");
	print_elements(data_arr);

	int pass = 0;	//Total number of passes
	bool swap_done = false;

	int i = 0;
	for (pass = 0; pass < NO_OF_DATA_ITEMS-1; pass++)	//Loop for no of passes - (n-1) pass required
	{
		swap_done = false;
		for (i = 0; i < NO_OF_DATA_ITEMS - 1 - pass; i++)
		{
			if (data_arr[i] > data_arr[i + 1])
			{
				swap(&data_arr[i], &data_arr[i + 1]);
				swap_done = true;
			}
		}

		if (swap_done == false)	//No swapping done -> Already sorted
		{
			break;
		}
	}

	/* Print the array*/
	printf("Elements in array after bubble sort : \r\n");
	print_elements(data_arr);


}

int main(void)
{
	int input;

	printf("Enter the sorting algorithm\r\n"
		"1.  Bubble Sort\r\n");
	scanf_s("%d", &input);

	switch (input)
	{
		case 1:
			bubble_sort(data_arr);
			break;


		default:
			break;
	}


	return 0;
}