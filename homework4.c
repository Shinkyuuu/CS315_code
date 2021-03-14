/*********************************************************************
*   Cody Park
*   CS315
*   Program hw4
*
*   Program to create a binary tree with insertion, searching, and pre\in-order traversal functions
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLEN 10

typedef struct treeNode 
{
  char key, value[MAXLEN];
  struct treeNode *left, *right;
} NODE;

typedef struct stackItem 
{
  struct treeNode *value;
  struct stackItem *next;
} ITEM;

void init(NODE **, ITEM **);
void insertNode(NODE **);
void insertTraversal(NODE **, NODE *);
void findNode(NODE *);
void findTraversal(NODE *, char);
void inOrderTraversal(NODE *, ITEM **);
void preOrderTraversal(NODE *, ITEM **);
void push(NODE *, ITEM **);
NODE *pop(ITEM **);

/***********************************************************************************/
int main() 
{
  NODE *treeRoot = NULL;
  ITEM *stackTop = NULL;

  init(&treeRoot, &stackTop);

  return 0;
}

/***********************************************************************************/
void init(NODE **treeRoot, ITEM **stackTop) //Ask user for command
{
  char command;
    
  do 
    {
      printf("\n\nEnter choice (lower case is also acceptable) --- (I)nsert, (F)ind, (Q)uit: ");
      scanf (" %c", &command);
      command = tolower(command);

      if (command == 'i') 
        {
          insertNode(treeRoot);
          preOrderTraversal((*treeRoot), stackTop);
          inOrderTraversal((*treeRoot), stackTop);
        } 
      else if (command == 'f') 
        {
          findNode(*treeRoot);
        }
    } while (command != 'q');
}

/***********************************************************************************/
void insertNode(NODE **treeRoot) 
{ 
  NODE *tmp = malloc(sizeof(NODE));

  printf("\nEnter new node's key value: ");
  scanf(" %c", &(tmp->key));
  printf("\nEnter a string of up to 10 characters for '%c's data: ", tmp->key);
  scanf(" %s", tmp->value);
  tmp->left = NULL;
  tmp->right = NULL;
  
  insertTraversal(treeRoot, tmp);
}

/***********************************************************************************/
void insertTraversal(NODE **treeRoot, NODE *tmp) //Search for spot to insert node
{
  if ((*treeRoot) == NULL) 
    {
      (*treeRoot) = tmp;
    } 
  else if ((*treeRoot)->key > tmp->key) 
    {
      insertTraversal(&((*treeRoot)->left), tmp);
    } 
  else 
    {
      insertTraversal(&((*treeRoot)->right), tmp);
    }

  return;
}

/***********************************************************************************/
void findNode(NODE *treeRoot) 
{
  char searchKey;

  printf("\nEnter the search key: ");
  scanf(" %c", &searchKey);
  findTraversal(treeRoot, searchKey);
}

/***********************************************************************************/
void findTraversal(NODE *treeRoot, char searchKey) //Search for Node with matching key
{
  if (treeRoot == NULL) 
    {
      printf("\n  '%c' is not in the tree", searchKey);
    } 
  else if (treeRoot->key == searchKey) 
    {
      printf("\n  Found the string \"%s\" there.", treeRoot->value);
    } 
  else if (treeRoot->key > searchKey) 
    {
      findTraversal(treeRoot->left, searchKey);
    } 
  else 
    {
      findTraversal(treeRoot->right, searchKey);
    }

  return;
}

/***********************************************************************************/
void preOrderTraversal(NODE *treeRoot, ITEM **stackTop) 
{
  int done = 0;
  NODE *trvPtr = treeRoot;

  printf("\n  Pre-order traversal is: ");
  while (!done) 
    {
      while (trvPtr != NULL) 
        {
          printf("%c ", trvPtr->key);
          if (trvPtr->left != NULL) 
            {
              push(trvPtr, stackTop);
              trvPtr = trvPtr->left;
            } 
          else 
            {
              trvPtr = trvPtr->right;
            }
        }

      if ((*stackTop) == NULL) 
        {
          done = 1;
        } 
      else 
        {
          trvPtr = pop(stackTop)->right;
        }
    }
}

/***********************************************************************************/
void inOrderTraversal(NODE *treeRoot, ITEM **stackTop) 
{
  int done = 0;
  NODE *trvPtr = treeRoot;

  printf("\n  Inorder traversal is: ");
  while (!done) 
    {
      while (trvPtr != NULL) 
        {
          if (trvPtr->left != NULL) 
            {
              push(trvPtr, stackTop);
              trvPtr = trvPtr->left;
            } 
          else 
            {
              printf("%c ", trvPtr->key);
              trvPtr = trvPtr->right;
            }
        }

      if ((*stackTop) == NULL) 
        {
          done = 1;
        } 
      else 
        {
          trvPtr = pop(stackTop);
          printf("%c ", trvPtr->key);
          trvPtr = trvPtr->right;
        }
    }
}

/***********************************************************************************/
void push(NODE *value, ITEM **stackTop) 
{
  ITEM *tmp = malloc(sizeof(ITEM));
  tmp->value = value;
  tmp->next = (*stackTop);

  (*stackTop) = tmp;
}

/***********************************************************************************/
NODE * pop(ITEM **stackTop) 
{
  NODE *tmp = (*stackTop)->value;
  (*stackTop) = ((*stackTop)->next);
  
  return tmp;
}
