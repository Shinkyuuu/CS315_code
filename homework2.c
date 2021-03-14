/*********************************************************************
*   Cody Park
*   CS315
*   Program hw2
*
*   Program to create a queue within an array with insertion and deletion functionality
**********************************************************************/

#include<stdio.h>
#define MAXSIZE 5

void init();
void insertInt(int *, int *, int[]);
void removeInt(int *, int *, int[]);

/***********************************************************************************/
int main() 
{
  init();

  return 0;
}

/***********************************************************************************/
void init() //Ask user for command
{ 
  int arrayQueue[MAXSIZE];
  int rear = 0, front = 0, queueLen = 0;
  char command;

 do 
  {
    printf("\nWhat do you want to do? [i for insert, r for remove, q for quit] ");
    scanf(" %c", &command);

    if (command == 'i') 
      {
        insertInt(&rear, &queueLen, arrayQueue);
      } 
    else if (command == 'r')
      {
        removeInt(&front, &queueLen, arrayQueue);
      }
    
  } while (command != 'q');
}

/***********************************************************************************/
void insertInt(int *rear, int *queueLen, int arrayQueue[]) //Insert integer into queue
{ 
  int num;

  printf("Enter an integer to be inserted into the queue: ");
  scanf("%d", &num);

  if ((*queueLen) == MAXSIZE) //Queue is full
    { 
      printf("Can't insert, the array is full\n");

      return;
    }

  arrayQueue[(*rear)] = num;
  (*rear) = (((*rear)+1) % MAXSIZE);
  (*queueLen)++;
}

/***********************************************************************************/
void removeInt(int *front, int *queueLen, int arrayQueue[]) //Remove integer from queue
{ 
  if ((*queueLen) == 0) //Queue is empty
    { 
      printf("Cannot remove, the queue is empty\n");

      return;
    }

  printf("%d removed from the queue\n", arrayQueue[(*front)]);
  (*front) = (((*front)+1) % MAXSIZE);
  (*queueLen)--;
}