#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 256
#define TABLE_SIZE 11

struct student;
typedef struct student* Position;
typedef struct student* List;
struct hashT;
typedef struct hashT* hashTab;

typedef struct student {
	char name[MAX];
	char lastName[MAX];
	int mat;
	Position next;
}_student;

typedef struct hashT {
	List* hashList;
}_hashTable;

unsigned int hash(char[MAX]);
hashTab initTable();
void add(hashTab, Position);
void addSorted(hashTab, int, Position);
void print(hashTab);
int search(hashTab, char[MAX], char[MAX]);

int main() {

	hashTab ht = initTable();
	char c = '\0';
	Position p = NULL;

	while (toupper(c) != 'N') {
		p = NULL;
		printf("Unesite ime, prezime i maticni broj studenta.\n");
		scanf("%s %s %d", p->name, p->lastName, &p->mat);
		add(ht, p);

		printf("Zelite li dodati jos jedan clan (Y \ N) \n");
		scanf(" %c", &c);
		while (toupper(c) != 'Y' || toupper(c) != 'N') {
			printf("Nepoznata opcija!\n");
			scanf(" %c", &c);
		}
	}
	
	c = '\0';
	char temp1[MAX];
	char temp2[MAX];
	int num = 0;
	printf("Zelite li pronaci neki clan? (Y \ N)\n");
	scanf(" %c", &c);
	while (toupper(c) != 'Y' || toupper(c) != 'N') {
		printf("Nepoznata opcija!\n");
		scanf(" %c", &c);
	}

	while (toupper(c) != 'N') {
		printf("Upisite ime i prezime zeljenog studenta\n");
		scanf("%s %s", temp1, temp2);
		
		if (num = search(ht, temp1, temp2))
			printf("Maticni broj studenta %s %s je: %d", temp1, temp2, num);

		else
			printf("Nema trazenog studenta.\n");
		
		printf("Zelite li pronaci novog clana? (Y \ N)\n");
		scanf(" %c", &c);

		while (toupper(c) != 'Y' || toupper(c) != 'N') {
			printf("Nepoznata opcija!\n");
			scanf(" %c", &c);
		}
	}

	printf("Zelite li ispisati tablicu (Y \ N)");
	scanf(" %c", &c);
	while (toupper(c) != 'Y' || toupper(c) != 'N') {
		printf("Nepoznata opcija!\n");
		scanf(" %c", &c);
	}
	if (toupper(c) == 'Y')
		print(ht);

	return 0;
}

unsigned int hash(char lastName[MAX]) {
	
	unsigned int value = 0;
	unsigned int i = 0;

	for (i = 0; i < 4; i++)
		value += lastName[i];

	value = value % 11;

	return value;
}

hashTab initTable() {

	hashTab H = NULL;
	int i = 0;

	H = (hashTab)malloc(sizeof(_hashTable));
	if (H == NULL) {
		printf("Greska pri alokaciji za tablicu!\n");
		return;
	}

	H->hashList = (List*)malloc(sizeof(List) * TABLE_SIZE);

	for (i = 0; i < TABLE_SIZE; i++)
		H->hashList[i] = NULL;

	return H;
}

void add(hashTab H, Position p) {
	unsigned int key = hash(p->lastName);

	if (H->hashList[key] == NULL)
		H->hashList[key] = p;

	else
		addSorted(H, key, p);
}

void addSorted(hashTab H, int key, Position p) {

	Position temp = H->hashList[key];
	while (temp->next != NULL && temp->lastName[0] < p->lastName[0])
		temp = temp->next;

	p->next = temp->next;
	temp->next = p;
}

void print(hashTab H) {
	Position temp = NULL;
	int i = 0;

	for (i = 0; i < TABLE_SIZE; i++) {
		temp = H->hashList[i];
		printf("%d --> %s %s %d(%u)", temp->name, temp->lastName, temp->mat, hash(temp->lastName));
		if(temp->next != NULL)
			while (temp != NULL) {
				printf(", %s %s %d(%u)", temp->name, temp->lastName, temp->mat, hash(temp->lastName));
				temp = temp->next;
			}
		printf("\n");
	}
}

int search(hashTab H, char temp1[MAX], char temp2[MAX]) {
	Position p = H->hashList[0];
	int i = 0;

	while (p != NULL || (!strcmp(p->name, temp1) && !strcmp(p->lastName, temp2))) {
		if(p->next != NULL)
			while (p->next != NULL || (!strcmp(p->name, temp1) && !strcmp(p->lastName, temp2))) {
				p = p->next;
			}
		i++;
		p = H->hashList[i];
	}

	if (p != NULL)
		return p->mat;
	
	return 0;
}