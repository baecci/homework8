#include<stdio.h>
#include<stdlib.h>

/* 노드 형식 구조체 */
typedef struct Node {
	int key;             //노드의 데이터
	struct Node* llink;  //후방리스트를 가리키는 링크
	struct Node* rlink;  //전방리스트를 가리키는 링크
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;  //헤더노드 선언 

	do{
		printf("  ------------------- [배기원] [2021041081] -----------------  \n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) {
		case 'z': case 'Z':
			/* 헤더노드 메모리 할당 함수 호출 */
			initialize(&headnode);  
			break;
		case 'p': case 'P':
			/* 노드 리스트 출력 함수 호출 */
			printList(headnode);
			break;
		case 'i': case 'I':
			/* 리스트에 노드 삽입 함수 호출 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			/* key에 대한 노드 삭제 함수 호출 */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			/* 리스트 마지막 노드로 삽입 함수 호출 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			/* 마지막 노드 삭제 함수 호출 */
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			/* 리스트 첫 노드로 삽입 함수 호출 */
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			/* 첫 노드 삭제 함수 호출 */
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			/* 리스트 링크를 역순으로 하는 함수 호출 */
			invertList(headnode);
			break;
		case 'q': case 'Q':
			/* 리스트의 모든 메모리를 해제 */
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headnode가 공백이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headnode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}


int freeList(listNode* h){

	/* 리스트에 headnode뿐이라면 headnode 메모리만 해제 */
	if(h->rlink == h)
	{
		free(h);
		return 1;
	}

	/* headnode부터 리스트 끝까지 전체 메모리 해제 */
	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	/* headnode가 공백이라면 문구 출력 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;  //headnode의 rlink 주소를 p에 저장

	/* p의 rlink를 시작으로 NULL이 나올때까지 노드 출력 */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* headnode의 llink, node, rlink 주소 출력 */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	/* 모든 노드들의 llink, node, rlink 주소 출력 */
	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



int insertLast(listNode* h, int key) {

	/* headnode가 공백이면 함수 종료 */
	if (h == NULL) return -1;

	/* 삽입할 노드 메모리 할당 후 노드 구조체 멤버변수 세팅 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* 노드 리스트에 headnode 밖에 없다면 첫 노드로 삽입 */
	if (h->rlink == h) 
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} 
	/* 아니면 마지막 노드로 삽입 */
	else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}



int deleteLast(listNode* h) {

	/* headnode가 본인을 가리키거나 가리키는 다른 노드가 없다면 오류 문구 출력 */
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	/* headnode의 llink가 가리키는 주소를 복사 */
	listNode* nodetoremove = h->llink;

	/* llink 정리 */
	nodetoremove->llink->rlink = h; 
	h->llink = nodetoremove->llink;

	/* 노드 삭제에 사용된 임시 노드 메모리 해제 */
	free(nodetoremove);

	return 1;
}



int insertFirst(listNode* h, int key) {

	/* 삽입할 노드 메모리 할당 후 노드 구조체 멤버변수 세팅 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* 삽입할 노드와 주변의 노드 연결 세팅 */
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}



int deleteFirst(listNode* h) {

	/* headnode가 본인을 가리키거나 가리키는 다른 노드가 없다면 오류 문구 출력 */
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;

}



int invertList(listNode* h) {

	/* headnode가 본인을 가리키거나 가리키는 다른 노드가 없다면 오류 문구 출력 */
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	/* 리스트 링크 역순을 위한 임시노드 세팅 */
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* 링크 역순 배치 */
	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}



int insertNode(listNode* h, int key) {

	/* headnode가 공백이면 함수 종료 */
	if(h == NULL) return -1;

	/* 삽입할 노드 메모리 할당 후 노드 구조체 멤버변수 세팅 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* 노드 리스트에 headnode 밖에 없다면 insertFirst함수 호출 */
	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	/* 입력받은 key이거나, 보다 큰 값을 가진 노드 앞에 새로운 노드 삽입 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			if(n == h->rlink) {  //맨 앞에 노드를 삽입하는 case
				insertFirst(h, key);
			} else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 모든 key가 입력받은 key보다 작은 경우, insertLast함수 호출 */
	insertLast(h, key);
	return 0;
}



int deleteNode(listNode* h, int key) {

	/* headnode가 본인을 가리키거나 가리키는 다른 노드가 없다면 오류 문구 출력 */
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	/* 입력받은 key를 가진 노드를 찾아 삭제 */
	while(n != NULL && n != h) {
		if(n->key == key) {
			/* 첫 노드인 경우, deleteFirst함수 호출 */
			if(n == h->rlink) { 
				deleteFirst(h);
			} 
			/* 마지막 노드인 경우, deleteLast함수 호출 */
			else if (n->rlink == h){ 
				deleteLast(h);
			} else { 
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 해당 key를 찾지 못한 경우, 오류 문구 출력 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


