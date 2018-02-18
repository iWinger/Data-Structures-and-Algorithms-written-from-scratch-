#include <stdio.h> 
#include <stdbool.h> 
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
  };
/* make sure each element is the head so that every bucket can have a linked list full of values */
struct Hash {
  struct Node *head;
};

int size = 10000;
struct Hash *hashTable = NULL;
bool duplicate(int num) {
  /* find if theres a duplicate in the bucket/linked list */
  int hIndex = num % size;
  struct Node *trav = hashTable[hIndex].head;
  if (trav == NULL) {
    return false;
  }
  while (trav != NULL) {
    if ((*trav).value == num) {
      return true;
    }
    trav = trav->next;
  }
  return false;
}

/* num is essentially the key itself, simple hash function */
void insert(int num) {
  /* check if theres a duplicate first, and if there is, dont insert the number
  if there is we can insert on head, and if its occupied, put it in the linked list */
  if (duplicate(num) == true) {
    printf("%s\n", "duplicate");
    return;
  }

  struct Node *insNode;
  insNode = (struct Node* ) malloc(sizeof(struct Node));
  insNode->value = num;
  insNode->next = NULL;

  int hIndex = num % size;
  if (hashTable[hIndex].head == NULL) {
    hashTable[hIndex].head = insNode;
    printf("%s\n", "inserted");
    return;
  }
  insNode->next = hashTable[hIndex].head;
  hashTable[hIndex].head = insNode;
  printf("%s\n", "inserted");
}

void search(int num) {
  /* search for the number in each bucket by traversing linked-list style */
  bool presence = false;
  /* this is the hash function */
  int hIndex = num % size;
  struct Node *temp = hashTable[hIndex].head;
  if (temp == NULL) {
    printf("%s\n", "absent");
    return;
  }
  while (temp != NULL) {
    if ((*temp).value == num) {
      presence = true;
      printf("%s\n", "present");
    }
    temp = temp->next;
  }
  if (presence == false) {
    printf("%s\n", "absent");
  }
}
int main(int argc, char **argv) {
  FILE *fp = fopen(argv[1], "r");
  char buf[1000];

  /*assign memory to 10000 elements, or like an array to hashtable */
  hashTable = (struct Hash* ) calloc(size, sizeof(struct Hash));
  if (fp == 0) {
    printf("%s", "error");
    return 1;
  }
  while (fgets(buf, 1000, fp) != NULL) {
    int num;
    char insdel;
    sscanf(buf, "%c %d", &insdel, &num);
    if (insdel == 'i') {
      insert(num);
    } else if (insdel == 's') {
      search(num);
    }
  }
  fclose(fp);
  return 0;
}
