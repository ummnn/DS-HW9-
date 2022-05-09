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

/* 노드구조체 선언 */
typedef struct node {
	int key;
	struct node *left; //왼쪽노드 (노드의 key 보다 작은값)
	struct node *right; //오른쪽노드 (노드의 key 보다 큰값)
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
    printf("[----- [이동현] [2019038027] -----]\n\n");
    
	char command;
	int key;
	Node* head = NULL;  //헤드노드 초기화
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
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
            case 'z': case 'Z': //command가 z나 Z일 때
                initializeBST(&head); //initializeBST함수 실행
                break;
            case 'q': case 'Q': //command가 q나 Q일 때
                freeBST(head); //freeBST 함수 실행
                break;
            case 'n': case 'N': //command가 n이나 N일 때
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력 받는다
                insert(head, key); //insert 함수 실행
                break;
            case 'd': case 'D': //command가 d나 D일 때
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력받는다
                deleteLeafNode(head, key); //deleteLeafnode 함수 실행
                break;
            case 'f': case 'F': //command가 f나 F일 때
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력받는다
                ptr = searchIterative(head, key); //searchIterative 함수 리턴값 저장
                if(ptr != NULL) //key를 찾았다면
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else //찾지 못했다면
                    printf("\n Cannot find the node [%d]\n", key);
                break;
            case 's': case 'S': //command가 s나 S일 때
                printf("Your Key = ");
                scanf("%d", &key); //key를 입력받는다
                ptr = searchRecursive(head->left, key); //searchRecursive 함수 리턴값 저장
                if(ptr != NULL) //key를 찾았다면
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else //찾지 못했다면
                    printf("\n Cannot find the node [%d]\n", key);
                break;

            case 'i': case 'I': //command가 i나 I라면
                inorderTraversal(head->left); //inorderTraversal 함수 실행
                break;
            case 'p': case 'P': //command가 p나 P라면
                preorderTraversal(head->left); //preorderTraversal 함수 실행
                break;
            case 't': case 'T': //command가 t나 T라면
                postorderTraversal(head->left); //postorderTraversal 함수 실행
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

/* 이진검색노드 선언 함수 */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //Node의 크기만큼 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;   
	(*h)->key = -9999;
	return 1;
}

/* 중위순회 */
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

/* 전위순회 */
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

/* 후위순회 */
void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

/* 노드 삽입 함수 */
int insert(Node* head, int key)
{
    //newNode 초기화
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node의 크기만큼 메모리 할당
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { //newNode의 left가 NULL이라면
		head->left = newNode; //newNode의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL; //parentNode NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아니라면 반복

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

/* leafNode삭제 함수 */
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) { //ptr이 NULL이 아니라면 반복

		if(ptr->key == key) { //ptr의 key값과 같다면
			if(ptr->left == NULL && ptr->right == NULL) { //ptr의 left나 right가 NULL이라면

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL; //parentNode의 left 초기화
				else
					parentNode->right = NULL; //parentNode의 right 초기화

				free(ptr); //ptr 메모리 해제
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
	if(ptr == NULL) //ptr이 NULL이라면 NULL반환
		return NULL;

	if(ptr->key < key) //key값이 더 크다면
		ptr = searchRecursive(ptr->right, key); //노드의 오른쪽 탐색
	else if(ptr->key > key) //key값이 더 작다면
		ptr = searchRecursive(ptr->left, key); //노드의 왼쪽 탐색

	/* if ptr->key == key */
	return ptr; //ptr반환

}

/* Iterative */
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL) //ptr이 NULL이 아니면 반복
	{
		if(ptr->key == key) //key값과 같다면
			return ptr; //ptr 반환

		if(ptr->key < key) ptr = ptr->right; //key값이 더 크다면 ptr의 right를 저장
		else
			ptr = ptr->left; //key값이 더 작다면 ptr의 left 저장
	}

	return NULL;
}

/* 노드 메모리 해제 함수 */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //freeNode함수 실행 left 메모리 해제 
		freeNode(ptr->right); //freeNode함수 실행 right 메모리 해제 
		free(ptr); //ptr메모리 해제
	}
}

/* 트리 메모리 해제 함수 */
int freeBST(Node* head)
{

	if(head->left == head) //left가 head 라면
	{
		free(head); //head메모리 할당 해제
		return 1;
	}

	Node* p = head->left; //head의 left p에 저장

	freeNode(p); //freenode 함수 실행

	free(head); //head 메모리 할당 해제
	return 1;
}





