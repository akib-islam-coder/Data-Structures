#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_EMPTY		1
#define STACK_NOT_EMPTY 0

#define STACK_FULL		1
#define STACK_NOT_FULL	0

#define QUEUE_FULL		1
#define QUEUE_NOT_FULL	0

#define QUEUE_EMPTY		1
#define QUEUE_NOT_EMPTY	0

#define SUCCESS			1
#define ERROR			0

#define MAX_QUEUE_SIZE  100
#define MAX_STACK_SIZE	100

/*
* Node of the tree
*/
typedef struct node
{
	int data;
	struct node * lchild;
	struct node * rchild;
}Node;

typedef struct stack
{
	Node* stack_arr[MAX_STACK_SIZE];
	int top;
}Stack;

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

/*
* Stack functions Implementation
*/
int isStackEmpty(Stack* tmp_stack)
{
	if (tmp_stack->top == -1)
	{
		return STACK_EMPTY;
	}
	else
	{
		return STACK_NOT_EMPTY;
	}
}

int isStackFull(Stack* tmp_stack)
{
	if (tmp_stack->top == MAX_STACK_SIZE - 1)
	{
		return STACK_FULL;
	}
	else
	{
		return STACK_NOT_FULL;
	}
}

void push(Stack* tmp_stack, Node* element)
{
	if (isStackFull(tmp_stack))
	{
		printf("Error: Stack Full \r\n");
		return;
	}

	tmp_stack->stack_arr[++(tmp_stack->top)] = element;
	return;
}

Node* pop(Stack* tmp_stack)
{
	if (isStackEmpty(tmp_stack))
	{
		printf("Error: Stack Empty \r\n");
		return NULL;
	}

	Node* ret_element = tmp_stack->stack_arr[(tmp_stack->top)--];
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

void preorder_iteration(Node* root)
{
	Node* trav_ptr = root;

	/*
	* In iterative approach, we need to store the address of previous node so that we can trackback the tree back to root element
	* So we need a stack for this.
	*/
	Stack tmp_stack; 
	memset(&(tmp_stack.stack_arr), NULL, sizeof(tmp_stack.stack_arr));
	tmp_stack.top = -1;

	while ((trav_ptr != NULL) || (isStackEmpty(&tmp_stack) != STACK_EMPTY))
	{
		if (trav_ptr != NULL)
		{
			printf("%d ", trav_ptr->data);
			push(&tmp_stack ,trav_ptr);
			trav_ptr = trav_ptr->lchild;
		}
		else
		{
			trav_ptr = pop(&tmp_stack);
			trav_ptr = trav_ptr->rchild;
		}
	}
	printf("\r\n");
	return;
}

void inorder_iteration(Node* root)
{
	Node* trav_ptr = root;

	Stack tmp_stack;
	memset(&(tmp_stack.stack_arr), NULL, sizeof(tmp_stack.stack_arr));
	tmp_stack.top = -1;

	while ((trav_ptr != NULL) || (isStackEmpty(&tmp_stack) != STACK_EMPTY))
	{
		if (trav_ptr != NULL)
		{
			push(&tmp_stack , trav_ptr );
			trav_ptr = trav_ptr->lchild;
		}
		else
		{
			trav_ptr = pop(&tmp_stack);
			printf("%d ", trav_ptr->data);
			trav_ptr = trav_ptr->rchild;
		}
	}
	printf("\r\n");
}

void levelorder_traversal(Node* root)
{
	Node* tmp_ptr = root;

	Queue levelorder_queue;
	levelorder_queue.front = -1;
	levelorder_queue.rear = -1;

	enqueue(&levelorder_queue, tmp_ptr);

	while (isQueueEmpty(&levelorder_queue) != QUEUE_EMPTY)
	{
		tmp_ptr = dequeue(&levelorder_queue);
		printf("%d ", tmp_ptr->data);

		if (tmp_ptr->lchild != NULL)
		{
			enqueue(&levelorder_queue, tmp_ptr->lchild);
		}
	    if (tmp_ptr->rchild != NULL)
		{
			enqueue(&levelorder_queue, tmp_ptr->rchild);
		}
	}
	printf("\r\n");
}

int no_of_nodes(Node* root)
{
	Node* tmp = root;
	int left_nodes = 0;
	int right_nodes = 0;

	if (tmp != NULL)
	{
		left_nodes  = no_of_nodes(tmp->lchild);
		right_nodes = no_of_nodes(tmp->rchild);
		return (1  +  left_nodes + right_nodes);
	}
	else
	{
		return 0;
	}
}

int height_of_tree(Node* root)
{
	Node* trav_ptr = root;
	int left_count = 0;
	int right_count = 0;

	if (trav_ptr != NULL)
	{
		left_count = height_of_tree(trav_ptr->lchild);
		right_count = height_of_tree(trav_ptr->rchild);

		if (left_count > right_count)
			return left_count + 1;
		else if (right_count > left_count)
			return right_count + 1;
		else if ((left_count == 0) && (right_count == 0))
			return 1;
		else if (left_count == right_count)
			return left_count + 1;
	}
	else
	{
		return 0;
	}
}

int main(void)
{
	int input, num_nodes, height;
	
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
			"8. Levelorder Traversal \r\n"
			"9. No of nodes in the tree \r\n"
			"10. Height of a binary tree \r\n"
			"20. Exit Program\r\n");
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

		case 5:
			preorder_iteration(root);
			break;

		case 6:
			inorder_iteration(root);
			break;

		case 8:
			levelorder_traversal(root);
			break;

		case 9:
			num_nodes = no_of_nodes(root);
			printf("No of nodes : %d\r\n", num_nodes);
		
		case 10:
			height = height_of_tree(root);
			printf("Height of tree : %d\r\n", height);

		case 20:
			exit(0);

		default:
			break;
		}
	} while (input != 20);

	return 0;

}