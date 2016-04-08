#include <stdio.h>
#include "TLista.h"

int main(){
TLista* lista = (TLista*) malloc(sizeof(TLista));
TLista_Insere(lista, 50);
TLista_Insere(lista, 10);
TLista_Insere(lista, 20);
TLista_Insere(lista, 5);
TLista_Imprime(lista);
return 0;
}
