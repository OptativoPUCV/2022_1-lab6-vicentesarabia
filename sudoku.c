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

int is_valid(Node* n){
  for (int i = 0; i < 9; i++){
    int f[10] = {0};
    for (int j = 0; j < 9; j++)
    {
      if (f[n->sudo[i][j]])
        return 0;

      if (f[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0)
        f[n->sudo[i][j]] = 1;
    }
  }

  for (int i = 0; i < 9; i++){ 
    int colum[10] = {0};
    for (int j = 0; j < 9; j++)
    {
      if (colum[n->sudo[j][i]] != 0)
        return 0;

      if (colum[n->sudo[j][i]] == 0 && n->sudo[j][i] != 0)
        colum[n->sudo[j][i]] = 1;
    }
  }
  for (int aux = 0; aux < 9; aux++)
  {
    int auxmatriz[10] = {0};
    int k=aux,p; 
    for(p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      if (auxmatriz[n->sudo[i][j]] != 0)
        return 0;
      if(!auxmatriz[n->sudo[i][j]] && n->sudo[i][j])
        auxmatriz[n->sudo[i][j]] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){ 
    List* list=createList();
    Node* nodoAux;
    int filavacia, columnavacia;
    int flag_vacia = 0; 
    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          filavacia = i;
          columnavacia = j;
          flag_vacia = 1;
          break;
        }
      }
      if(flag_vacia == 1)
        break;
    }
    if(flag_vacia == 0)
        return list;
    for (int i = 1; i < 10; i++)
    {
      nodoAux = copy(n);
      nodoAux->sudo[filavacia][columnavacia] = i;
      if(is_valid(nodoAux))
        pushBack(list, nodoAux);
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
          if(n->sudo[i][j] == 0) return 0;
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* vari = createStack();
  push(vari, initial);

  while(get_size(vari) != 0)
  {
    Node* aux = top(vari);
    pop(vari);

    if(is_final(aux))
        return aux;

    List* list = get_adj_nodes(aux);

    Node* auxList = first(list);

    while(auxList)
    {
      push(vari, auxList);
      auxList = next(list);
    }
    free(aux);
    (*cont)++;
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