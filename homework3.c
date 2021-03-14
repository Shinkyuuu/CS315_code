/*********************************************************************
*   Cody Park
*   CS315
*   Program hw3
*
*   Program to create a queue with a circular linked list with insertion and removal functionality
**********************************************************************/

#include <stdio.h>
#include<stdlib.h>

typedef struct listItem 
{
  char value;
  struct listItem *next;
} item;

void init(item **);
void insertItem(item **);
void removeItem(item **);

/***********************************************************************************/
int main() 
{
  item *head = NULL; //points to rear

  init(&head);
  return 0;
}

/***********************************************************************************/
void init(item **head) //Ask user for command
{
  char command;

  do 
  {
    printf("\nEnter \"i\" to insert a new element, \"r\" to remove an element, \"q\" to quit: ");
    scanf(" %c", &command);

    if (command == 'i') 
      {
        insertItem(head);
      } 
    else if (command == 'r') 
      {
        removeItem(head);
      }
  } 
  while (command != 'q');
}

/***********************************************************************************/
void insertItem(item **head) 
{
  item *tmp = malloc(sizeof(item));

  printf("\nEnter character to be enqueued (inserted): ");
  scanf(" %c", &(tmp->value));

  if ((*head) == NULL) //If queue empty
    { 
      tmp->next = tmp;
    } 
  else 
    {
      tmp->next = (*head)->next;
      (*head)->next = tmp;
    }

  (*head) = tmp;
}

/***********************************************************************************/
void removeItem(item **head) 
{
  if (*head == NULL) //If queue empty
    {
      printf("\nNothing to remove; the queue is empty.\n");
      return;
    }

  item *removedItem = (*head)->next;

  if ((*head)->next == (*head)) //If only 1 item in queue
    { 
      (*head) = NULL;
    } 
  else 
    {
      (*head)->next = ((*head)->next)->next;
    }

  printf("\nThe character removed was an \"%c\"\n", removedItem->value);
  free(removedItem);
}

