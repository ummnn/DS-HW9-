/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* ��屸��ü ���� */
typedef struct node {
	int key;
	struct node *left; //���ʳ�� (����� key ���� ������)
	struct node *right; //�����ʳ�� (����� key ���� ū��)
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
    printf("[----- [�̵���] [2019038027] -----]\n\n");
    
	char command;
	int key;
	Node* head = NULL;  //����� �ʱ�ȭ
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
            case 'z': case 'Z': //command�� z�� Z�� ��
                initializeBST(&head); //initializeBST�Լ� ����
                break;
            case 'q': case 'Q': //command�� q�� Q�� ��
                freeBST(head); //freeBST �Լ� ����
                break;
            case 'n': case 'N': //command�� n�̳� N�� ��
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է� �޴´�
                insert(head, key); //insert �Լ� ����
                break;
            case 'd': case 'D': //command�� d�� D�� ��
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է¹޴´�
                deleteLeafNode(head, key); //deleteLeafnode �Լ� ����
                break;
            case 'f': case 'F': //command�� f�� F�� ��
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է¹޴´�
                ptr = searchIterative(head, key); //searchIterative �Լ� ���ϰ� ����
                if(ptr != NULL) //key�� ã�Ҵٸ�
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else //ã�� ���ߴٸ�
                    printf("\n Cannot find the node [%d]\n", key);
                break;
            case 's': case 'S': //command�� s�� S�� ��
                printf("Your Key = ");
                scanf("%d", &key); //key�� �Է¹޴´�
                ptr = searchRecursive(head->left, key); //searchRecursive �Լ� ���ϰ� ����
                if(ptr != NULL) //key�� ã�Ҵٸ�
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else //ã�� ���ߴٸ�
                    printf("\n Cannot find the node [%d]\n", key);
                break;

            case 'i': case 'I': //command�� i�� I���
                inorderTraversal(head->left); //inorderTraversal �Լ� ����
                break;
            case 'p': case 'P': //command�� p�� P���
                preorderTraversal(head->left); //preorderTraversal �Լ� ����
                break;
            case 't': case 'T': //command�� t�� T���
                postorderTraversal(head->left); //postorderTraversal �Լ� ����
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Էµɶ����� �ݺ�

	return 1;
}

/* �����˻���� ���� �Լ� */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //Node�� ũ�⸸ŭ �޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;   
	(*h)->key = -9999;
	return 1;
}

/* ������ȸ */
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

/* ������ȸ */
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

/* ������ȸ */
void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

/* ��� ���� �Լ� */
int insert(Node* head, int key)
{
    //newNode �ʱ�ȭ
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node�� ũ�⸸ŭ �޸� �Ҵ�
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { //newNode�� left�� NULL�̶��
		head->left = newNode; //newNode�� left�� newNode ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL; //parentNode NULL�� �ʱ�ȭ
	while(ptr != NULL) { //ptr�� NULL�� �ƴ϶�� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/* leafNode���� �Լ� */
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head�� left�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) { //ptr�� NULL�� �ƴ϶�� �ݺ�

		if(ptr->key == key) { //ptr�� key���� ���ٸ�
			if(ptr->left == NULL && ptr->right == NULL) { //ptr�� left�� right�� NULL�̶��

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL; //parentNode�� left �ʱ�ȭ
				else
					parentNode->right = NULL; //parentNode�� right �ʱ�ȭ

				free(ptr); //ptr �޸� ����
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/* Recursive */
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) //ptr�� NULL�̶�� NULL��ȯ
		return NULL;

	if(ptr->key < key) //key���� �� ũ�ٸ�
		ptr = searchRecursive(ptr->right, key); //����� ������ Ž��
	else if(ptr->key > key) //key���� �� �۴ٸ�
		ptr = searchRecursive(ptr->left, key); //����� ���� Ž��

	/* if ptr->key == key */
	return ptr; //ptr��ȯ

}

/* Iterative */
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL) //ptr�� NULL�� �ƴϸ� �ݺ�
	{
		if(ptr->key == key) //key���� ���ٸ�
			return ptr; //ptr ��ȯ

		if(ptr->key < key) ptr = ptr->right; //key���� �� ũ�ٸ� ptr�� right�� ����
		else
			ptr = ptr->left; //key���� �� �۴ٸ� ptr�� left ����
	}

	return NULL;
}

/* ��� �޸� ���� �Լ� */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //freeNode�Լ� ���� left �޸� ���� 
		freeNode(ptr->right); //freeNode�Լ� ���� right �޸� ���� 
		free(ptr); //ptr�޸� ����
	}
}

/* Ʈ�� �޸� ���� �Լ� */
int freeBST(Node* head)
{

	if(head->left == head) //left�� head ���
	{
		free(head); //head�޸� �Ҵ� ����
		return 1;
	}

	Node* p = head->left; //head�� left p�� ����

	freeNode(p); //freenode �Լ� ����

	free(head); //head �޸� �Ҵ� ����
	return 1;
}





