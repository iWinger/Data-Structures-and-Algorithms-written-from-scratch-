#include <stdio.h> 
#include <stdlib.h>

int x = 0;
int counti = 0;
int countd = 0;

/* create a datatype that has this information, an integer and a pointer */
struct Node {
  int data;
  struct Node *next;
};

struct Node *head = NULL;
struct Node *temp = NULL;
void insert(int n) {
  /* allocate memory for the node, and insert it one after another */
  struct Node *current;
  current = (struct Node*) malloc(sizeof(struct Node));
  (*current).data = n;
  current->next = NULL;
  /*if list is empty*/
  if (head == NULL) {
    head = current;
    temp = current;
    return;
  }
  temp->next = current;
  temp = temp->next;

}
void delete(int n) {
  struct Node *prev1 = NULL;
  struct Node *temp1 = head;
  /* if the head of the list is null, delete by changing head to the next node */
  if (temp1 != NULL && (*temp1).data == n) {
    head = temp1->next;
    return;
  }
  /* deletion works for any node besides the head by discarding the pointer to the soon-to be deleted node */
  while (temp1 != NULL) {
    if ((*temp1).data == n) {
      prev1->next = temp1->next;
    }

    prev1 = temp1;
    temp1 = temp1->next;
  }

}

void swap(int *a, int *b) {
  /* integer swap using pointers */
  int temp = *a; 
  *a = *b; 
  *b = temp;
}

void sort(int input[]) {
  /* sort the numbers inputted because it's hard to do that while using linked lists */
  int z;
  int y;
  for (z = counti - 1; z > 0; z--) {
    for (y = counti - 1; y > 0; y--) {
      if (input[y] < input[y - 1]) {
        swap( & input[y], & input[y - 1]);
      }
    }
  }
}

void deleteDupNode(struct Node *link) {
  struct Node *temp2 = link;
  struct Node *storeNext;
  /*if list is empty */
  if (temp2 == NULL)
    return;
  /*traverse the list until last and because we sorted the list already
  the duplicate should be next to each other, and we will delete that*/
  while (temp2->next != NULL) {
    if ((*temp2).data == (*temp2->next).data) {
      storeNext = temp2->next->next;
      free(temp2->next);
      temp2->next = storeNext;
    } else {
      temp2 = temp2->next;
    }
  }
}
void printNode(struct Node *link) {
    while (link != NULL) {
      printf("%d ", (*link).data);
      link = link->next;
    }
  }
  /*free the memory */
void freeList(struct Node *first) {
  struct Node *sub;
  while (first != NULL) {
    sub = first;
    first = first->next;
    free(sub);
  }
}

int main(int argc, char **argv) {
  /*storing arrays of integers and chars to help with sorting and swapping methods */
  int arri[50];
  int arr2[50];
  char arrc[50];
  char arrd[50];
  FILE *fp = fopen(argv[1], "r");
  char buf[1000];
  int p;
  int u;
  if (fp == 0) {
    printf("%s", "error");
    exit(0);
  }

  while (fgets(buf, 1000, fp) != NULL) {
    int num;
    char insdel;
    /* put the num and the char into different arrays in the same indices */
    sscanf(buf, "%c %d", &insdel, &num);
    if (insdel == 'i') {
      arri[counti] = num;
      arrc[counti] = insdel;
      counti++;
    } else if (insdel == 'd') {
      arr2[countd] = num;
      arrd[countd] = insdel;
      countd++;

    }
  }
  sort(arri);
  fclose(fp);
  /* get the instruction to insert or delete with the num */
  for (p = 0; p < counti; p++) {
    if (arrc[p] == 'i') {
      insert(arri[p]);
    }
  }
  for (u = 0; u < countd; u++) {
    if (arrd[u] == 'd') {
      delete(arr2[u]);
    }
  }
  /* print length of linked list on first line, then on second line, print the actual linked list */
  printf("%d", (counti - countd));
  printf("\n");
  deleteDupNode(head);
  printNode(head);
  freeList(head);
  return 0;
}
