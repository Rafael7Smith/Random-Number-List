// Rafael Smith, Ra761089
// ENG3211-17summer c002
// Mid-Term Part 2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Linked list called myList
struct myStruct
{
  int data;
  struct myStruct *next;
} *myList;

// Declare the used functions
void FirstElements(), addnum(), findnum();
void display(), remnum(), minmaxran(), numdub(); 
int menu();

int main()    
{
  int cont;
  char quit[1];
  time_t t;
  // Random Gen seed
  srand((unsigned) time(&t));
  
  myList = malloc(sizeof(struct myStruct)); /* allocates memory for first element */
  FirstElements();
  
  do {
    /*Menu function */
    menu();
  
    // Quitting the program  
    printf("\n\n");
    printf("Please choose one of the following options:\nReturn to Main Menu?  Y\nQuit the program: Q\n");
    scanf(" %c", quit);
    if((quit[0] == 'Y') || (quit[0] == 'y'))
    {
      printf("Returning to main menu.\n");
      cont = 1;
      printf("\n\n");
    } else if ((quit[0] == 'Q') || (quit[0] == 'q')) {
      printf("Quitting the program\n\n");
      cont = 0;
    } else {
      printf("I'm sorry there was an error, returning to main menu\n");
      cont = 1;
    }
  } while(cont == 1 );
  
  return 0;
}

//Initialize first 100 elements
void FirstElements()
{
  printf("Initializing the first 100 random numbers....\n");
  addnum(100, myList);
  printf("\n");
}

//Print menu
int menu()
{
  //Declare struct, will have to pass that to the functions
  int choice, x;
  char q[0];
  struct myStruct *ptr, *parptr;
  
  printf("MyList number database management.\n\n");
  printf("Main Menu: Please enter the number of your selection.\n");
  printf("1: Add more random numbers to your list.\n");
  printf("2: Remove a specific number from your list.\n");
  printf("3: Print the minimum, maximum, and range of your list.\n");
  printf("4: Print the number of times a number has occured.\n");
  printf("5: Double all numbers in your list.\n");
  printf("6: Display your list.\n");
  printf("7: Quit the program.\n");
  scanf(" %d", &choice);
  
  switch(choice)
  {
    case 1:
      printf("Add random numbers to your list.\nPlease enter how many random numbers you'd like.\n");
      scanf(" %d", &x);
      printf("Adding %d numbers to your list.\n", x);
      // find end of myList structure 
      ptr = myList;
      while(ptr->next != NULL) {
        ptr = ptr->next;
      }
      // at this point ptr is NULL and therefore is at the end of our list
      // if you want to add zero numbers, you are already done
      if (x > 0) {
        ptr->next = malloc(sizeof(struct myStruct)); /* allocates memory for element */
        addnum(x, ptr->next); //adds the data to structure, repeats if needed
      }
      printf("Done.\n");
      break;
    case 2:
      printf("Remove a specific number from your list.\n");
      printf("Please enter which number you would like to delete\n");
      scanf(" %d", &x);
      remnum(x);
      printf("Done.\n");
      break;
    case 3:
      printf("Printing minimum, maximum, and range of your list.\n");
      minmaxran();
      printf("Done.\n");
      break;
    case 4:
      printf("Which number would you like to find?\n");
      scanf(" %d", &x);
      findnum(x);
      printf("Done.\n");
      break;
    case 5:
      printf("Doubling all the numbers in your list.\n");
      numdub();
      printf("Done.\n");
      break;
    case 6:
      printf("Displaying all the numbers in your list.\n");
      display();
      printf("Done.\n");
      break;
    case 7:
      break;
    default:
      printf("I'm sorry, there has been an error.  Returning to menu.\n\n");
      break;
  }
  
}

//add random numbers to myList
void addnum(int a, struct myStruct *ptr)
{
  int r,i;
  struct myStruct *next;
  
  
  /*Generate and assign the new number to data */
  r = 100 + rand() % 901;
  ptr->data = r;
 
  for(i=0; i<a - 1; i++)
  {
    ptr->next = malloc(sizeof(struct myStruct)); /* allocates memory for first element */
    r = 100 + rand() % 901;
    next = ptr->next;
    next->data =r;
    ptr = next;
  }
  /* at end make sure that the last element pointer to the next structure is set to null */
  ptr->next = NULL;
  printf("Made %d new numbers for your list.\n\n", a);
}

//remove specific number from myList
void remnum(int b)
{
  struct myStruct *ptr, *parptr;
  
  
  ptr = myList;
  parptr = ptr;
  while(ptr != NULL) 
  {
    if(ptr->data == b){
      if(myList == ptr) {
        myList = ptr->next;
        free(ptr);
        ptr = myList; /* reset list so we can contine looking for occrence */
      } else {
          if (ptr->next == NULL) {
              parptr->next = NULL;
          } else {
              parptr->next = ptr->next;
          }
          free(ptr);
          ptr = parptr; /* reset to parent so we can continue looking thru rest of list */
      }
    }
    parptr = ptr; /* save parent/ current node just in case */
    ptr = ptr->next; /* point to next node */
  }
}

//show min, max, and range of myList
void minmaxran(void)
{
  struct myStruct *ptr;
  int max,min,range;
  
  ptr = myList;
  max = ptr->data;
  min = ptr->data;
  while(ptr != NULL){ //once we reach the end, stop
    if(ptr->data < min) {
      min = ptr->data;  //found a new low? save it
    }
    if(ptr->data > max) {
      max = ptr->data; //found a new high, save it
    }
    
    ptr = ptr->next;  //onto the next block
  }
  printf("Minimum: %d\n", min);
  printf("Maximum: %d\n", max);
  printf("Range: %d\n", (max-min));
}

//Show specific number and amount 
void findnum(int c)
{
  struct myStruct *ptr;
  int count;
  
  ptr = myList;
  count = 0;
  printf("starting check\n");
  while(ptr != NULL) 
  {
    if(ptr->data == c){
      count++; /*add one tick */
    }
    ptr = ptr->next; /* point to next node */
  }
  printf("The number %d, occurs %d times.\n", c,count);
  
}

//double all numbers in myList
void numdub()
{
  struct myStruct *ptr;
  int x;
  
  ptr = myList;
  while(ptr != NULL){
    x = ptr->data; //take what we found
    ptr->data = x*2; //double it and save it back in the same place
    ptr = ptr->next; //onto the next block
  }
}

//display all numbers in myList
void display(void)
{
  struct myStruct *ptr;
  int i;
  
  i = 0;
  ptr = myList;
  while(ptr != NULL){
    printf("Element %d: value is: %d\n", i++, ptr->data);
    ptr = ptr->next;
  }
  
}

