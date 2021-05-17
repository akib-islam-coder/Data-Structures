#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define QUEUE_FULL		1
#define QUEUE_NOT_FULL	0

#define QUEUE_EMPTY		1
#define QUEUE_NOT_EMPTY	0

#define SUCCESS			1
#define ERROR			0

#define MAX_QUEUE_SIZE  100


/*
* Node of the tree
*/
typedef struct node
{
	int data;
	struct node * lchild;
	struct node * rchild;
}Node;

/*
* Temporary queue structure for creating binary tree
*/
typedef struct queue
{
	struct node* arr[MAX_QUEUE_SIZE];
	int front;
	int rear;
}Queue;

int isQueueFull(Queue* bt_queue)
{
	if (bt_queue->rear == MAX_QUEUE_SIZE - 1)
	{
		return QUEUE_FULL;
	}
	else
	{
		return QUEUE_NOT_FULL;
	}
}

int isQueueEmpty(Queue* bt_queue)
{
	if (bt_queue->front == -1)
	{
		return QUEUE_EMPTY;
	}
	else
	{
		return QUEUE_NOT_EMPTY;
	}
}

int enqueue(Queue* bt_queue, Node * element)
{
	if (isQueueFull(bt_queue))
	{
		return ERROR;
	}

	if (bt_queue->front == -1)	//Queue is empty, increment the front after insertion
	{
		bt_queue->front = 0;
	}

	bt_queue->arr[++(bt_queue->rear)] = element;
	return SUCCESS;
}

Node * dequeue(Queue* bt_queue)
{
	if (isQueueEmpty(bt_queue))
	{
		return ERROR;
	}

	Node* ret_element = bt_queue->arr[bt_queue->front];
	
	if (bt_queue->front == bt_queue->rear)
	{
		bt_queue->front = -1;
		bt_queue->rear  = -1;
	}
	else
	{
		(bt_queue->front)++;
	}

	return ret_element;
}


Node * create_binary_tree(Node* root)
{
	if (root != NULL)
	{
		printf("Binary tree already created\r\n");
		return root;
	}

	Queue binary_tree_queue;
	binary_tree_queue.front = -1;
	binary_tree_queue.rear  = -1;

	int element;
	printf("Enter the root element (-1 if NULL)\r\n");
	scanf_s("%d", &element);

	Node* root_node = (Node*)malloc(sizeof(Node));
	if (!root_node)
	{
		printf("Error in allocating memory from heap\r\n");
		return root;
	}
	root_node->data = element;
	root_node->lchild = NULL;
	root_node->rchild = NULL;

	root = root_node;

	enqueue(&binary_tree_queue, root_node);


	while (isQueueEmpty(&binary_tree_queue) == QUEUE_NOT_EMPTY)
	{

		Node* p = dequeue(&binary_tree_queue);

		printf("Enter the left child data of %d (-1 if null)\r\n", p->data);
		scanf_s("%d", &element);
		if (element == -1)
		{
			p->lchild = NULL;
		}
		else
		{
			Node* lchild_node = (Node*)malloc(sizeof(Node));
			if (lchild_node)
			{
				lchild_node->data = element;
				lchild_node->lchild = NULL;
				lchild_node->rchild = NULL;
				p->lchild = lchild_node;
			}
			else
			{
				printf("Error in allocating heap memory\r\n");
				exit(0);
			}

			enqueue(&binary_tree_queue, lchild_node);
		}

		printf("Enter the right child data of %d (-1 if null) \r\n", p->data);
		scanf_s("%d", &element);
		if (element == -1)
		{
			p->rchild = NULL;
		}
		else
		{
			Node* rchild_node = (Node *)malloc(sizeof(Node));
			if (rchild_node)
			{
				rchild_node->data = element;
				rchild_node->lchild = NULL;
				rchild_node->rchild = NULL;
				p->rchild = rchild_node;
			}
			else
			{
				printf("Error in allocating heap memory\r\n");
				exit(0);
			}

			enqueue(&binary_tree_queue, rchild_node);
		}
	}

	return root;
}

/*
*  Node, Left Subtree, Right Subtree
*/
void preorder_recursion(Node * root)
{

	Node* trav_ptr = root;

	if (trav_ptr != NULL)
	{
		printf("%d ", trav_ptr->data);
		preorder_recursion(trav_ptr->lchild);
		preorder_recursion(trav_ptr->rchild);
	}
}

/*
*  Left Subtree, Node, Right Subtree
*/
void inorder_recursion(Node* root)
{
	Node* trav_ptr = root;

	if (trav_ptr != NULL)
	{
		inorder_recursion(trav_ptr->lchild);
		printf("%d ", trav_ptr->data);
		inorder_recursion(trav_ptr->rchild);
	}
}

/*
*  Left Subtree, Right Subtree, Node
*/
void postorder_recursion(Node* root)
{
	Node* trav_ptr = root;

	if (trav_ptr != NULL)
	{
		postorder_recursion(trav_ptr->lchild);
		postorder_recursion(trav_ptr->rchild);
		printf("%d ", trav_ptr->data);
	}
}


int main(void)
{
	int input;
	
	Node* root = NULL;

	do
	{
		printf("Enter your choice\r\n"
			"1. Create a binary tree\r\n"
			"2. Preorder  print via recusrion\r\n"
			"3. Inorder   print via recursion\r\n"
			"4. Postorder print via recursion\r\n"
			"5. Preorder  print via iteration\r\n"
			"6. Inorder   print via iteration\r\n"
			"7. Postorder print via iteration\r\n"
			"10. Exit Program\r\n");
		scanf_s("%d", &input);

		switch (input)
		{
		case 1:
			root = create_binary_tree(root);
			break;

		case 2:
			preorder_recursion(root);
			break;

		case 3:
			inorder_recursion(root);
			break;

		case 4:
			postorder_recursion(root);
			break;

		case 10:
			exit(0);

		default:
			break;
		}
	} while (input != 10);

	return 0;

}