#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   //Valido en filas
   for (int filas = 0; filas < 9; filas++)
   {
      int arreglo[10] = {0};

      for (int columnas = 0; columnas < 9; columnas++)
      {
         int casilla = n -> sudo[filas][columnas];

         if (casilla != 0)
         {
            if (arreglo[casilla] == 0)
               arreglo[casilla] = 1;
            else
               return 0;
         }
      }
   }

   //Valido en columnas
   for (int filas = 0; filas < 9; filas++)
   {
      int arreglo [10] = {0};
      for  (int columnas = 0; columnas < 9; columnas++)
      {
         int cColumnas = n -> sudo[columnas][filas];

         if (cColumnas != 0)
         {
            if (arreglo[cColumnas] == 0)
               arreglo[cColumnas] = 1;
            else
               return 0;
         }
      }
   }

   //Valido en submatrices
   for (int i = 0; i < 3; i++)
   {
      int arreglo[10] = {0};
      for (int j = 0; j < 9; j++)
      {
         int fila = 3 * (i/3) + (j/3);
         int columna = 3 * (i%3) + (j%3);
         
         int matriz = n -> sudo[fila][columna];
         if (matriz != 0)
         {
            if (arreglo[matriz] == 0)
               arreglo[matriz] = 1;
            else
               return 0;
         }
      }
   }

   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list = createList();
   
   int fila, columna;
   for (fila = 0; fila < 9; fila++)
   {
      int num = 1;
      for (columna = 0; columna < 9; columna++)
      {
         if (n -> sudo[fila][columna] == 0) //si esta vacio
         {
            for (num = 1; num <= 9; num++)
            {
               n -> sudo[fila][columna] = num;
               
               if (is_valid(n))     //si el numero no se repite
               {
                  Node* adyacente = copy(n);
                  pushBack(list, adyacente);
               }
            }
            n -> sudo[fila][columna] = 0;
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n)
{
   for (int filas = 0; filas < 9; filas++)
   {
      for (int columnas = 0; columnas < 9; columnas++)
      {
         if (n -> sudo[filas][columnas] == 0) return 0;
      }
   }
      
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack* S = createStack();
   if (S == NULL) return NULL;
   
   push(S, initial);
   while (get_size(S) != 0)
   {
      Node* nodo = top(S);
      pop(S);

      if (is_final(nodo)) return nodo;
      
      List* list = get_adj_nodes(nodo);
      Node* primero = first(list);
      while (list != NULL)
      {
         push(S, primero);
         primero = next(list);
      }

      free(nodo);
   }
   
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/