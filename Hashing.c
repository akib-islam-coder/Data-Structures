#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_OF_DATA_ITEMS	20
#define HASHTABLE_SIZE		10

int data_arr[NO_OF_DATA_ITEMS] = { 47, 7, 37, 76, 97, 1, 69, 67, 87, 10, 678, 456, 23, 65, 78, 97, 75, 89, 69, 456};

typedef struct node
{
	int data;
	struct node* next;
}Node;

Node * separate_chaining_hashtable[HASHTABLE_SIZE] = {NULL};

int hash_function(int num)
{
	return (num % 10);
}

void separate_chaining(int search_element)
{
	 //Insert the items in the hashtable
	int i = 0;

	for (i = 0; i < NO_OF_DATA_ITEMS; i++)
	{
		int index = hash_function(data_arr[i]);

		Node * new_node = (Node *)malloc(sizeof(Node));

		if (separate_chaining_hashtable[index] == NULL)	//Index doesn't contain any elements
		{
			separate_chaining_hashtable[index] = new_node;
			new_node->next = NULL;
			new_node->data = data_arr[i];
		}

		else //Data is already present. Insert in a ascending sorted order
		{
			Node* new_node = (Node*)malloc(sizeof(Node));
			if (new_node != NULL)
			{
				new_node->data = data_arr[i];
			}
			else
			{
				exit(0);
			}

			Node* trav_ptr = separate_chaining_hashtable[index];
			Node* prev_ptr = NULL;

			while (trav_ptr != NULL)
			{
				if (data_arr[i] > trav_ptr->data)
				{
					prev_ptr = trav_ptr;
					trav_ptr = trav_ptr->next;
				}
				else
				{
					break;
				}
			}

			if (trav_ptr != NULL)
			{
				if (prev_ptr == NULL)	//Insertion at the head
				{
					new_node->next = separate_chaining_hashtable[index];
					separate_chaining_hashtable[index] = new_node;
				}
				else
				{
					new_node->next = prev_ptr->next;
					prev_ptr->next = new_node;
				}
			}
			else	//Reached at end of linkedlist
			{
				if (prev_ptr != NULL)
				{
					prev_ptr->next = new_node;
					new_node->next = NULL;
				}
			}
		}
	}

	//Print the hash table contents
	i = 0;
	printf("Contents of separate chaining hashtable are :\r\n");
	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		printf("index : %d, Contents : ", i);

		Node* trav_ptr = separate_chaining_hashtable[i];
		while (trav_ptr != NULL)
		{
			printf("%d -> ", trav_ptr->data);
			trav_ptr = trav_ptr->next;
		}
		printf("NULL\r\n");
	}

	//Searching the element
	int search_index = hash_function(search_element);

	Node* trav_ptr = separate_chaining_hashtable[search_index];
	while (trav_ptr != NULL)
	{
		if (trav_ptr->data == search_element)
		{
			printf("Element found in the hash table\r\n");
			break;
		}
		else
		{
			trav_ptr = trav_ptr->next;
		}
	}

	if (trav_ptr == NULL)
	{
		printf("Element not found in the hash table\r\n");
	}
}


int main(void)
{
	int input, element;

	printf("Enter the hashing technique\r\n"
		"1. Open hashing (Separate Chaining)\r\n");
	scanf_s("%d", &input);

	switch (input)
	{
	case 1:
		printf("Enter the element to be searched in the hashtable\r\n");
		scanf_s("%d", &element);
		separate_chaining(element);	
		break;

	default:
		break;
	}


	return 0;
}