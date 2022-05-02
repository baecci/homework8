#include<stdio.h>
#include<stdlib.h>

/* ��� ���� ����ü */
typedef struct Node {
	int key;             //����� ������
	struct Node* llink;  //�Ĺ渮��Ʈ�� ����Ű�� ��ũ
	struct Node* rlink;  //���渮��Ʈ�� ����Ű�� ��ũ
} listNode;

/* �Լ� ����Ʈ */
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
	listNode* headnode=NULL;  //������ ���� 

	do{
		printf("  ------------------- [����] [2021041081] -----------------  \n");
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
			/* ������ �޸� �Ҵ� �Լ� ȣ�� */
			initialize(&headnode);  
			break;
		case 'p': case 'P':
			/* ��� ����Ʈ ��� �Լ� ȣ�� */
			printList(headnode);
			break;
		case 'i': case 'I':
			/* ����Ʈ�� ��� ���� �Լ� ȣ�� */
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			/* key�� ���� ��� ���� �Լ� ȣ�� */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			/* ����Ʈ ������ ���� ���� �Լ� ȣ�� */
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			/* ������ ��� ���� �Լ� ȣ�� */
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			/* ����Ʈ ù ���� ���� �Լ� ȣ�� */
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			/* ù ��� ���� �Լ� ȣ�� */
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			/* ����Ʈ ��ũ�� �������� �ϴ� �Լ� ȣ�� */
			invertList(headnode);
			break;
		case 'q': case 'Q':
			/* ����Ʈ�� ��� �޸𸮸� ���� */
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

	/* headnode�� ������ �ƴϸ�, freeList�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headnode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}


int freeList(listNode* h){

	/* ����Ʈ�� headnode���̶�� headnode �޸𸮸� ���� */
	if(h->rlink == h)
	{
		free(h);
		return 1;
	}

	/* headnode���� ����Ʈ ������ ��ü �޸� ���� */
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

	/* headnode�� �����̶�� ���� ��� */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;  //headnode�� rlink �ּҸ� p�� ����

	/* p�� rlink�� �������� NULL�� ���ö����� ��� ��� */
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* headnode�� llink, node, rlink �ּ� ��� */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	/* ��� ������ llink, node, rlink �ּ� ��� */
	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



int insertLast(listNode* h, int key) {

	/* headnode�� �����̸� �Լ� ���� */
	if (h == NULL) return -1;

	/* ������ ��� �޸� �Ҵ� �� ��� ����ü ������� ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* ��� ����Ʈ�� headnode �ۿ� ���ٸ� ù ���� ���� */
	if (h->rlink == h) 
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} 
	/* �ƴϸ� ������ ���� ���� */
	else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}



int deleteLast(listNode* h) {

	/* headnode�� ������ ����Ű�ų� ����Ű�� �ٸ� ��尡 ���ٸ� ���� ���� ��� */
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	/* headnode�� llink�� ����Ű�� �ּҸ� ���� */
	listNode* nodetoremove = h->llink;

	/* llink ���� */
	nodetoremove->llink->rlink = h; 
	h->llink = nodetoremove->llink;

	/* ��� ������ ���� �ӽ� ��� �޸� ���� */
	free(nodetoremove);

	return 1;
}



int insertFirst(listNode* h, int key) {

	/* ������ ��� �޸� �Ҵ� �� ��� ����ü ������� ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* ������ ���� �ֺ��� ��� ���� ���� */
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}



int deleteFirst(listNode* h) {

	/* headnode�� ������ ����Ű�ų� ����Ű�� �ٸ� ��尡 ���ٸ� ���� ���� ��� */
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	/* link ���� */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;

}



int invertList(listNode* h) {

	/* headnode�� ������ ����Ű�ų� ����Ű�� �ٸ� ��尡 ���ٸ� ���� ���� ��� */
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	/* ����Ʈ ��ũ ������ ���� �ӽó�� ���� */
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	/* ��ũ ���� ��ġ */
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

	/* headnode�� �����̸� �Լ� ���� */
	if(h == NULL) return -1;

	/* ������ ��� �޸� �Ҵ� �� ��� ����ü ������� ���� */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* ��� ����Ʈ�� headnode �ۿ� ���ٸ� insertFirst�Լ� ȣ�� */
	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	/* �Է¹��� key�̰ų�, ���� ū ���� ���� ��� �տ� ���ο� ��� ���� */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			if(n == h->rlink) {  //�� �տ� ��带 �����ϴ� case
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

	/* ��� key�� �Է¹��� key���� ���� ���, insertLast�Լ� ȣ�� */
	insertLast(h, key);
	return 0;
}



int deleteNode(listNode* h, int key) {

	/* headnode�� ������ ����Ű�ų� ����Ű�� �ٸ� ��尡 ���ٸ� ���� ���� ��� */
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	/* �Է¹��� key�� ���� ��带 ã�� ���� */
	while(n != NULL && n != h) {
		if(n->key == key) {
			/* ù ����� ���, deleteFirst�Լ� ȣ�� */
			if(n == h->rlink) { 
				deleteFirst(h);
			} 
			/* ������ ����� ���, deleteLast�Լ� ȣ�� */
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

	/* �ش� key�� ã�� ���� ���, ���� ���� ��� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


