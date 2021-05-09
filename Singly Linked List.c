#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node;

Node* insert_beginning(Node* head, int item)
{
	Node* new_node = (Node*)malloc(sizeof(Node));	//Create a new node
	if (new_node == NULL)
	{
		printf("Error in allocating memory for new node\r\n");
		return head;
	}

	if (head == NULL)	//List is empty
	{
		new_node->next = head;
		head = new_node;
		new_node->data = item;
	}
	else
	{
		new_node->next = head;
		head = new_node;
		new_node->data = item;
	}
	return head;
}

Node* insert_end(Node* head, int item)
{
	Node* new_node = (Node*)malloc(sizeof(Node));	//Create a new node
	if (new_node == NULL)
	{
		printf("Error in allocating memory for new node\r\n");
		return head;
	}

	if (head == NULL)	//List is empty
	{
		new_node->next = head;
		head = new_node;
		new_node->data = item;
	}
	else
	{
		Node* trav_node = head;
		while (trav_node->next != NULL)		//Traverse till the end of the list
		{
			trav_node = trav_node->next;
		}

		new_node->next = trav_node->next;
		trav_node->next = new_node;
		new_node->data = item;	
	}
	return head;
}

Node* insert_element_after(Node* head, int item, int after_element)
{
	if (head == NULL)
	{
		printf("List is empty\r\n");
		return head;
	}

	//Search to see if the after_element is present in the list
	Node* trav_ptr = head;
	while ((trav_ptr != NULL) && (trav_ptr->data != after_element))
	{
		trav_ptr = trav_ptr->next;
	}

	if (trav_ptr == NULL)
	{
		printf("Element after which data needs to be inserted not found\r\n");
		return head;
	}
	else if (trav_ptr->data == after_element)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		if (new_node == NULL)
		{
			printf("Error in allocating memory for new node\r\n");
			return head;
		}

		new_node->next = trav_ptr->next;
		trav_ptr->next = new_node;
		new_node->data = item;
	}
	return head;
}

Node* insert_element_before(Node* head, int item, int before_element)
{
	if (head == NULL)
	{
		printf("List is Empty\r\n");
		return head;
	}

	//Search to see if the before_element is present in the list
	Node* trav_ptr = head;
	Node* prev_ptr = NULL;
	while ((trav_ptr != NULL) && (trav_ptr->data != before_element))
	{
		prev_ptr = trav_ptr;
		trav_ptr = trav_ptr->next;
	}

	if (trav_ptr == NULL)
	{
		printf("Element before which data needs to be inserted not found\r\n");
		return head;
	}
	else if (trav_ptr->data == before_element)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		if (new_node == NULL)
		{
			printf("Error in allocating memory for new node\r\n");
			return head;
		}

		if (prev_ptr == NULL)	//Insertion is at first place
		{
			head = new_node;
		}
		else
		{
			prev_ptr->next = new_node;
		}
		new_node->next = trav_ptr;
		new_node->data = item;
	}
	return head;
}

Node* insert_element_at_position(Node* head, int item, int position)
{
	if (head == NULL)
	{
		if (position == 0)
		{
			Node* new_node = (Node*)malloc(sizeof(Node));
			if (new_node == NULL)
			{
				printf("Error in allocating memory for new node\r\n");
				return head;
			}

			head = new_node;
			new_node->next = NULL;
			new_node->data = item;
		}
		else
		{
			printf("Position out of bounds\r\n");
			return head;
		}
	}
	else
	{
		Node* trav_ptr = head;
		Node* prev_ptr = NULL;
		int cur_pos = 0;

		while ((trav_ptr != NULL) && (cur_pos != position))
		{
			prev_ptr = trav_ptr;
			trav_ptr = trav_ptr->next;
			cur_pos++;
		}

		if ((trav_ptr == NULL) && (cur_pos == position))	//Insertion after last element
		{
			Node* new_node = (Node*)malloc(sizeof(Node));
			if (new_node == NULL)
			{
				printf("Error in allocating memory for new node\r\n");
				return head;
			}
			prev_ptr->next = new_node;
			new_node->next = NULL;
			new_node->data = item;
		}

		else if ((trav_ptr == NULL) && (cur_pos != position))
		{
			printf("Position out of bounds\r\n");
			return head;
		}

		else if ((trav_ptr != NULL) && (cur_pos == position))	//Insertion 
		{
			Node* new_node = (Node*)malloc(sizeof(Node));
			if (new_node == NULL)
			{
				printf("Error in allocating memory for new node\r\n");
				return head;
			}

			if (prev_ptr == NULL)	//Insertion at the head
			{	
				head = new_node;
			}
			else					//Insertion in between
			{
				prev_ptr->next = new_node;
			}
			new_node->next = trav_ptr;
			new_node->data = item;
		}
	}
	return head;
}

Node* delete(Node* head, int item)
{
	if (head == NULL)
	{
		printf("List is empty\r\n");
		return head;
	}

	//Search for the item to be deleted
	Node* trav_ptr = head;
	Node* prev_ptr = NULL;

	while ((trav_ptr != NULL) && (trav_ptr->data != item))
	{
		prev_ptr = trav_ptr;
		trav_ptr = trav_ptr->next;
	}

    if (trav_ptr == NULL)
	{
		printf("Cannot delete item -Data item not present in the list\r\n");
		return head;
	}
	else if (trav_ptr->data == item)	//Trav_ptr points to current element and prev_ptr points to previous element
	{
		if (trav_ptr == head)	//Deleted item is present at the head 
		{
			head = trav_ptr->next;
		}
		else
		{
			prev_ptr->next = trav_ptr->next;
		}

		trav_ptr->next = NULL;
		free(trav_ptr);
	}
	return head;
	
}

void print_elements(Node* head)
{
	if (head == NULL)
	{
		printf("List is empty");
		return;
	}

	Node* trav_ptr = head;

	while (trav_ptr != NULL)
	{
		printf("%d ", trav_ptr->data);
		trav_ptr = trav_ptr->next;
	}
	printf("\r\n");
	return;
}

void search_item(Node* head, int item)
{
	if (head == NULL)
	{
		printf("List Empty, Item not found\r\n");
		return;
	}

	Node* trav_ptr = head;
	int pos = 0;

	while ((trav_ptr != NULL) && (trav_ptr->data != item))
	{
		trav_ptr = trav_ptr->next;
		pos++;
	}

	if (trav_ptr == NULL)
	{
		printf("Item Not Found\r\n");
	}
	else
	{
		printf("Item (%d) found at location %d", item, pos);
	}
	return;
}


int main(void)
{
	Node* head = NULL;
	int choice, item, position, element;

	do
	{
		printf("\r\nEnter the linkedlist operation\r\n"
			"1. Add at beginning\r\n"
			"2. Add at the end\r\n"
			"3. Add after node\r\n"
			"4. Add before node\r\n"
			"5. Add at position\r\n"
			"6. Delete an item from a linkedlist \r\n"
			"7. Print all the items in the linked list\r\n"
			"8. Search an data item\r\n"
			"9. Reverse the linkedlist\r\n"
			"10. Terminate the operation\r\n");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter the data to be inserted\r\n");
			scanf_s("%d", &item);
			head = insert_beginning(head, item);
			break;

		case 2:
			printf("Enter the data to be inserted\r\n");
			scanf_s("%d", &item);
			head = insert_end(head, item);
			break;

		case 3:
			printf("Enter the data to be inserted\r\n");
			scanf_s("%d", &item);
			printf("Enter the element after which it will be inserted\r\n");
			scanf_s("%d", &element);
			head = insert_element_after(head, item, element);
			break;

		case 4: 
			printf("Enter the data to be inserted\r\n");
			scanf_s("%d", &item);
			printf("Enter the element before which it will be inserted\r\n");
			scanf_s("%d", &element);
			head = insert_element_before(head, item, element);
			break;
			
		case 5:
			printf("Enter the data to be inserted\r\n");
			scanf_s("%d", &item);
			printf("Enter the position at which it will be inserted (Position starts from 0)\r\n");
			scanf_s("%d", &position);
			head = insert_element_at_position(head, item, position);
			break;

		case 6:
			printf("Enter the data to be deleted\r\n");
			scanf_s("%d", &item);
			head = delete(head, item);
			break;

		case 7:
			printf("Elements in the linkedlist are : \r\n");
			print_elements(head);
			break;

		case 8:
			printf("Enter the item to be searched\r\n");
			scanf_s("%d", &item);
			search_item(head, item);
			break;

		case 9:
			
			break;

		case 10:
			exit(0);
			break;

		}

	} while (choice != 10);
}