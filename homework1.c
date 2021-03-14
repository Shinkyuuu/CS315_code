/*********************************************************************
*   Cody Park
*   CS315
*   Program hw1
*
*   Program to allow the user to create a numerically ordered linked list and delete items within it
**********************************************************************/
 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> //use booleans

typedef struct listItem 
{
    int value;
    struct listItem *next;
} item;

void addSortedItems(item **); 
void printItems(item *); 
void askToDeleteItems(item *); 
void deleteItem(item **, int); 

/***********************************************************************************/
int main() 
{
    item *start = NULL;

    addSortedItems(&start);
    printItems(start);
    askToDeleteItems(start);

    return 0;
}

/***********************************************************************************/
void addSortedItems(item **start) //Add Items in numerical order
{ 
  item *tmp, *traverse;

  while (true) 
    {
      traverse = (*start);
      tmp = malloc(sizeof(item));

      printf("Enter an integer ('0' to end): ");
      scanf("%d", &(tmp->value));

      if (tmp->value == 0) 
        {
            break;
        }

      if (((*start) == NULL) || ((*start)->value > tmp->value)) 
        {
          tmp->next = (*start);
          (*start) = tmp;
        } 
      else 
        {
          while ((traverse->next != NULL) && (traverse->next->value < tmp->value)) 
            {
              traverse = traverse->next;
            }

          tmp->next = traverse->next;
          traverse->next = tmp;
        }       
    }
} 

/***********************************************************************************/
void printItems(item *start) //Print linked list
{ 
  item *traverse = start;

  if (start != NULL) 
    {
      printf("OK, here's your list in numeric order: ");

      while (traverse->next != NULL) 
        {
          printf("%d -> ", traverse->value);
          traverse = traverse->next;
        }

      printf("%d\n", traverse->value);
    }   
}

/***********************************************************************************/
void askToDeleteItems(item *start) //Ask user for item to delete
{ 
  int itemToDelete; 

  while (true) 
    {
      if (start == NULL) 
        {
          printf("Your list is empty\n");
          break;
        }

      printf("What do you want to delete? ");
      scanf("%d", &itemToDelete);

      if (itemToDelete == 0) 
        {
          printf("Bye.\n");
          break;
        }

      deleteItem(&start, itemToDelete);
    }
}

/***********************************************************************************/
void deleteItem(item **start, int itemToDelete) //Delete list item
{ 
  item *itemDel = (*start), *delItemHldr;

  if ((*start)->value == itemToDelete) //Delete first item
    { 
      delItemHldr = itemDel;
      (*start) = (*start)->next;
      free(delItemHldr);
      printf("    ");
      printItems(*start);
    } 
  else 
    { 
      while ((itemDel->next != NULL) && (itemDel->next->value != itemToDelete)) 
        {
          itemDel = itemDel->next;
        }

      if (itemDel->next == NULL) //itemToDelete not in list
        { 
          printf("    Can't delete %d, it isn't in the list\n", itemToDelete);
        } 
      else //Delete non-first item
        { 
          delItemHldr = itemDel->next;
          itemDel->next = (itemDel->next)->next;
          free(delItemHldr);
          printItems(*start);
        }
    }
}
