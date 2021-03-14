/*********************************************************************
*   Cody Park
*   CS315
*   Program hw5
*
*   Program to create huffman tree using little end up heap
**********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 20

typedef struct littleHeapNode // Little end up heap node
{ 
  struct littleHeapNode *left, *right;
  char character;
  int freq;
} NODE;

void init();
void insertIntoHeap(NODE *heap[], int *count, char character, int freq, NODE *left, NODE *right);
void insertionSort(NODE *heap[], int count);
NODE *removeFromHeap(NODE *heap[], int *count);
void removalSort(NODE *heap[], int count);
void swapHeapNodes(NODE *heap[], int child, int parent);
void buildHuffTree(NODE *heap[], int *count);
void preOrderTraverse(NODE *huffTree);
void inOrderTraverse(NODE *huffTree);

/***********************************************************************************/
int main() 
{
  NODE *heap[MAXLEN];

  init(heap);

  return 0;
}

/***********************************************************************************/
void init(NODE *heap[]) 
{
  char character;
  int freq, heapCount = 0;

  while (1) //while heap is still being filled
    {
      printf("\nEnter a character (enter a '$' to quit entering characters): ");
      scanf(" %c", &character);

      if (character == '$') 
        {
          break;
        }

      printf("  Enter '%c's frequency: ", character);
      scanf("%d", &freq);

      insertIntoHeap(heap, &heapCount, character, freq, NULL, NULL);
    }

  if (heapCount >= 1) 
    {
      buildHuffTree(heap, &heapCount);
      printf("\n\nThe nodes of the Huffman tree in In-order are:\n");
      inOrderTraverse(heap[heapCount]);
      printf("\n\nand in Pre-order are:\n");
      preOrderTraverse(heap[heapCount]);
      printf("\n\n");
    } 
  else 
    {
      printf("\n\nNothing was inserted (-_-)\n\n");
    }
}

/***********************************************************************************/
void insertIntoHeap(NODE *heap[], int *count, char character, int freq, NODE *left, NODE *right) // Insert into heap
{
  NODE *tmp = malloc(sizeof(NODE));

  tmp->character = character;
  tmp->freq = freq;
  tmp->left = left;
  tmp->right = right;

  ++(*count);
  heap[*count] = tmp;
  
  if ((*count) != 1) // Check if root has children
    { 
      insertionSort(heap, (*count));
    }
}

/***********************************************************************************/
void insertionSort(NODE *heap[], int count) // Fix heap value property after node insertion
{
  int left, right, parent = count / 2;

  while (parent != 0) 
    {
      left = parent * 2;
      right = left + 1;

      if ((left <= count) && (heap[left]->freq < heap[parent]->freq)) // If left child breaks the heap value property
        { 
          swapHeapNodes(heap, left, parent);
          parent /= 2;
        } 
      else if ((right <= count) && (heap[right]->freq < heap[parent]->freq)) // If right child breaks the heap value property
        { 
          swapHeapNodes(heap, right, parent);
          parent /= 2;
        } 
      else 
        {
          parent = 0;
        }
    }
}

/***********************************************************************************/
NODE *removeFromHeap(NODE *heap[], int *count) // Remove node from heap
{ 
  NODE *removedNode = heap[1];
  heap[1] = heap[*count];

  --(*count);
  removalSort(heap, *count);

  return removedNode;
}

/***********************************************************************************/
void removalSort(NODE *heap[], int count) // Fix heap value property after node removal
{ 
  int parent = 1;
  int left = 2;
  int right = 3;
  
  while (left <= count)
    { 
      if (right > count) 
        { 
          if (heap[left]->freq < heap[parent]->freq) 
            { 
              swapHeapNodes(heap, left, parent);
            } 
          
          parent = left;
        } 
      else if ((heap[right]->freq < heap[parent]->freq) || (heap[left]->freq < heap[parent]->freq)) // check if the left or right child breaks the heap value property
        { 
          if (heap[right]->freq < heap[left]->freq) 
            {
              swapHeapNodes(heap, right, parent);
              parent = right;
            } 
          else 
            {
              swapHeapNodes(heap, left, parent);
              parent = left;
            }
        } 
      else
        {
          break;
        }

      left = parent * 2;
      right = left + 1;
    }
}

/***********************************************************************************/
void swapHeapNodes(NODE *heap[], int child, int parent) 
{
  NODE *tmp = heap[child];
  heap[child] = heap[parent];
  heap[parent] = tmp;
}

/***********************************************************************************/
void buildHuffTree(NODE *heap[], int *count) // Build Huffman tree out of heap nodes
{ 
  int newFreq;

  while (*count > 1)
    {
      NODE *tmpLeft = removeFromHeap(heap, count);
      NODE *tmpRight = removeFromHeap(heap, count);

      newFreq = tmpLeft->freq + tmpRight->freq;
      insertIntoHeap(heap, count, '-', newFreq, tmpLeft, tmpRight);
    }
}

/***********************************************************************************/
void preOrderTraverse(NODE *huffTree) 
{
  if (huffTree == NULL) 
    {
      return;
    }
  
  printf("\n%c%5d", huffTree->character, huffTree->freq);
  preOrderTraverse(huffTree->left);
  preOrderTraverse(huffTree->right);
}

/***********************************************************************************/
void inOrderTraverse(NODE *huffTree) 
{
  if (huffTree != NULL) 
    {
      inOrderTraverse(huffTree->left);
      printf("\n%c%5d", huffTree->character, huffTree->freq);
      inOrderTraverse(huffTree->right);
    }
}






