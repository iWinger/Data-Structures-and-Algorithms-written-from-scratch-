#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
  struct bstNode {
    int data;
    struct bstNode *right;
    struct bstNode *left;
  };
/* define the global variables here */
struct bstNode *root = NULL;
struct bstNode *temp = NULL;
void insert(num) {
  /* prototype */
  bool search(int a);
  struct bstNode *current;
  /* allocate memory to new node, and initialize the pointers to NULL */
  current = (struct bstNode* ) malloc(sizeof(struct bstNode));
  ( *current).data = num;
  current->right = NULL;
  current->left = NULL;
  /*if bst list is empty */
  if (root == NULL) {
    root = current;
    root->left = NULL;
    root->right = NULL;
    printf("%s\n", "inserted");
  } else {
    /* use search function to see if there is any number in the bst tree already. If so, do not insert the duplicated number */
    if (search(num)) {
      printf("%s\n", "duplicate");
      return;
    }
    struct bstNode *temp = root;
    while (temp != NULL) {
      if (current-> data < temp->data) {
        if (temp->left == NULL) {
          temp->left = current;
          printf("%s\n", "inserted");
          break;
        } else
          temp = temp->left;
      } else {
        if (temp->right == NULL) {
          temp->right = current;
          printf("%s\n", "inserted");
          break;
        } else
          temp = temp->right;
      }
    }
  }
}

bool search(num) {
  bool presence = false;
  struct bstNode *temp2 = root;
  /* same principles as insertion, in terms of looping through the BST tree but just finding the number */
  while (temp2 != NULL) {
    if (num < temp2->data) {
      if (num == temp2->data) {
        presence = true;
        break;
      } else {
        temp2 = temp2->left;
      }
    } else {
      if (num == temp2->data) {
        presence = true;
        break;
      } else {
        temp2 = temp2->right;
      }
    }
  }
  return presence;
}

int findMinValue(struct bstNode *ptr, int num) {
  /* what this function does is when deleting a node with 2 children, find the element to replace by 
  placing a left or right pointer. Then goes to the closest element in terms of value to the node being deleted */
  struct bstNode *trav = ptr;
  int minElement = 0;
  if (num < trav->data) {
    struct bstNode *travLeft = trav->left;
    while (travLeft->right != NULL) {
      travLeft = travLeft->right;
    }
    minElement = travLeft->data;
    travLeft = NULL;
    return minElement;
  } else {
    struct bstNode *travRight = trav->right;
    while (travRight->left != NULL) {
      travRight = travRight->left;
    }
    minElement = travRight->data;
    travRight = NULL;
    return minElement;
  }
  /* min element not found */
  return minElement;
}

void printbstNode(struct bstNode *head) {
  struct bstNode *temp3 = head;
  if (head == NULL) {
    printf("%s", "");
    return;
  }
  printf("(");
  printbstNode(head->left);
  printf("%d", temp3->data);
  printbstNode(head->right);
  printf(")");
}

void delete(struct bstNode *root, int num) {
  struct bstNode *tmp = root;
  struct bstNode *prev = NULL;
  /* if there is no node to be deleted then do not continue with deletion */
  if (search(num) == false) {
    printf("%s\n", "absent");
    return;
  }
  /* if there is only root node */
  if (root != NULL && root->left == NULL && root->right == NULL) {
    root = NULL;
    free(root);
    printf("%s\n", "deleted");
    return;
  }

  while (tmp != NULL) {
    if (num < tmp->data) {

      if (num == tmp->data) {
        /* delete left leaf node............. */
        if (tmp->left == NULL && tmp->right == NULL) {
          tmp = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        }
        /* node with one child */
        else if (tmp->right != NULL && tmp->left == NULL) {
          prev->left = tmp->right;
          tmp = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        } else if (tmp->left != NULL && tmp->right == NULL) {
          if (num == root->data) {
            tmp->left = NULL;
            return;
          }
          prev->right = tmp->left;
          tmp = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        }
        /* node with two children */
        else if (tmp->left != NULL && tmp->right != NULL) {
          int input = findMinValue(tmp, (tmp->data));
          tmp->data = input;
          printf("%s\n", "deleted");
          return;
        }
      }
      /*............................*/
      else {
        prev = tmp;
        tmp = tmp->left;
      }
    } else {
      if (num == tmp->data) {
        /*delete right tree  leaf node.....................*/
        if (tmp->left == NULL && tmp->right == NULL) {
          prev->right = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        }
        /* soon-to-be deleted node with one child */
        else if (tmp->right != NULL && tmp->left == NULL) {
          if (num == root->data) {
            tmp->right = NULL;
            return;
          }
          prev->left = tmp->right;
          tmp = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        } else if (tmp->left != NULL && tmp->right == NULL) {
          prev->right = tmp->left;
          tmp = NULL;
          free(tmp);
          printf("%s\n", "deleted");
          return;
        }
        /* soon-to-be-deleted node with two children  */
        else if (tmp->left != NULL && tmp->right != NULL) {
          int numb = findMinValue(tmp, (tmp->data));
          tmp->data = numb;
          printf("%s\n", "deleted");
        }
      } else {
        prev = tmp;
        tmp = tmp->right;
      }

    }
  }
}
int main(int argc, char *argv[]) {
  FILE *fp = fopen(argv[1], "r");
  char buf[100];

  if(fp == 0) {
    printf("%s", "error");
    return 1;
  }
  while (fgets(buf, 100, fp) != NULL) {
    int num;
    char insdel;
    sscanf(buf, "%c %d", & insdel, & num);
    /* read in text file and see if its insertion, deletion, print, or search */
    if (insdel == 'i') {
      insert(num);
    } else if (insdel == 's') {
      if (search(num))
        printf("%s\n", "present");
      else
        printf("%s\n", "absent");
    } else if (insdel == 'p') {
      printbstNode(root);
      printf("\n");
    } else if (insdel == 'd') {
      delete(root, num);
    }
  }
  fclose(fp);
  return 0;
}
