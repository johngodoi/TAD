#include <stdio.h>
#include "TLista.h"
#include "SparseMatrix.h"

void useList();

void useSparseMatrix();

int main(){
    //useList();
    useSparseMatrix();

    return 0;
}

void useSparseMatrix() {
    SparseMatrixPointer sparseMatrix = initialize(4, 4);

    insert(sparseMatrix,0,0,50);
    insert(sparseMatrix,1,0,10);
    insert(sparseMatrix,1,2,20);
    insert(sparseMatrix,3,0,-30);
    insert(sparseMatrix,3,2,-60);
    insert(sparseMatrix,3,3,5);
    removeOn(sparseMatrix,1,2);
    insert(sparseMatrix,1,2,20);

    print(sparseMatrix);
}

void useList() {
    TLista* lista = (TLista*) malloc(sizeof(TLista));
    TLista_Insere(lista, 50);
    TLista_Insere(lista, 10);
    TLista_Insere(lista, 20);
    TLista_Insere(lista, 5);
    TLista_Imprime(lista);
}
