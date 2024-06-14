/*
 * Projekt: Linked list
 * Autor: Lukáš Pachta
 * Datum: 13. 6. 2024
 */

//#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>  // pro praci s textovymi retezci
// #include <stdbool.h> // pro praci s typem bool a konstantami true a false
// #include <ctype.h>   // isalpha, isspace, islower, isupper, ...
// #include <math.h>    // funkce z matematicke knihovny
// #include <float.h>   // konstanty pro racionalni typy DBL_MAX, DBL_DIG, ...
// #include <limits.h>  // konstanty pro celociselne typy INT_MAX, INT_MIN, ...
// #include <time.h>    // funkce time a dalsi pro praci s casem

# define MAX_ARR_SIZE 255

typedef struct LINK_NODE LINK_NODE;

struct LINK_NODE
{
  float data;
  LINK_NODE* next;
};

typedef struct 
{
  int listLength;
  int expectedLength;
  struct LINK_NODE* first;
}NODE_HEADER;
 


/// @brief Vytvori linked list.
/// @param in 
/// @param arr 
/// @param n 
/// @param pN 
void makeArrayFromStream(FILE * in, float arr[], int n, int *pN){
  fscanf(in, "%i", & n);
  *pN = n;
  if(n > 0 && n < MAX_ARR_SIZE){
    for(int i = 0; i < n; i++){
      fscanf(in, "%f", & arr[i]);
    }

    printf("Pole bylo nacteno uspesne.\n\n");
  } else {
    printf("Pole nebylo nacteno.");
    if(n < MAX_ARR_SIZE){
      printf(" Je moc male.\n\n");
    }
  }
  
}

/// @brief Vytiskne pole.
/// @param arr 
/// @param n 
void printArray(float arr[], int n){
  for(int i = 0; i < n; i++){
    printf("%.1f, ", arr[i]);
  }
  printf("\n\n");
}

/// @brief Vytvori header listu.
/// @param header 
/// @param n 
void makeHeader(NODE_HEADER* header, int n){
  //NODE_HEADER* newNode = (NODE_HEADER*)malloc(sizeof(NODE_HEADER));

  header->first = NULL;
  header->expectedLength = n;
  header->listLength = 1;
  /*
  newNode->expectedLength = n;
  newNode->listLength = 1;
  *header = newNode;
  */
}

/// @brief Vypise do konzole linked list.
/// @param header 
void printLinkedList(NODE_HEADER* header){
  LINK_NODE* tempNode = NULL;
  printf("__ length: %i, next: %i __\n\n", header->listLength, header->first);
  if(header->first != NULL){
    tempNode = header->first;
    printf("data: %.1f\nnext: %i\n\n", tempNode->data, tempNode->next);
    while(tempNode->next != NULL){
      tempNode = tempNode->next;
      printf("data: %.1f\nnext: %i\n\n", tempNode->data, tempNode->next);
    }
  }
}

/// @brief Prida jeden prvek na konec linked listu.
/// @param header 
/// @param data 
void addNode(NODE_HEADER* header, float data){
  LINK_NODE* newNode = (LINK_NODE*)malloc(sizeof(LINK_NODE));
  if(header->first == NULL){
    header->first = newNode;
    newNode->data = data;
    newNode->next = NULL;
    header->listLength++;
  } else {
    LINK_NODE* currentNode = header->first;
    while(currentNode->next != NULL){
      //printf("%i, %i\n\n", currentNode->data, currentNode->next);
      currentNode = currentNode->next;
    }
    //printf("%i, %i\n\n", currentNode->data, currentNode->next);
    currentNode->next = newNode;
    newNode->data = data;
    newNode->next = NULL;
    header->listLength++;

  }

}

/// @brief Vytvori linked list z pole floatu.
/// @param header 
/// @param arr 
/// @param n 
void makeLinkedListFromArray(NODE_HEADER* header, float arr[], int n){
  makeHeader(header, n);
  for(int i = 0; i < n; i++){
    addNode(header, arr[i]);
  }
}


//int main(int argc, char *argv[])  // pro parametry prikazoveho radku
int main(void)
{
  FILE * in = fopen("file1.txt", "r");
  if(in == NULL){printf("Soubor nebyl nacten.\n"); return EXIT_FAILURE;}
  float arr[MAX_ARR_SIZE];
  int n;

  makeArrayFromStream(in, arr, n, &n);

  printArray(arr, n);
  NODE_HEADER* header = (NODE_HEADER*)malloc(sizeof(NODE_HEADER));

  makeLinkedListFromArray(header, arr, n);
  printLinkedList(header);


  
  return 0;
}
