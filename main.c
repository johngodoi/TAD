#include <stdio.h>
#include <stdlib.h>

typedef struct SCelula *TApontador;

typedef struct SCelula {
    int item;
    TApontador prox;
} TCelula;

typedef struct {
    TApontador primeiro, ultimo;
} TLista;

void TLista_Inicia(TLista *pLista);
int TLista_EhVazia(TLista *pLista);
int TLista_Insere(TLista *pLista, int x);
int TLista_Retiraprimeiro(TLista *pLista, int pX);
void TLista_Imprime(TLista *pLista);

void TLista_Inicia(TLista *pLista)
{
pLista->primeiro = NULL;
pLista->ultimo = pLista->primeiro;
}
/* Retorna se a lista esta vazia */
int TLista_EhVazia(TLista *pLista)
{
return (pLista->ultimo == NULL);
}

int TLista_Insere(TLista *pLista, int x)
{
if (TLista_EhVazia(pLista)) {
pLista->primeiro = (TApontador) malloc(sizeof(TCelula));
pLista->ultimo = pLista->primeiro;
}
else {
TApontador s = pLista->primeiro;
pLista->primeiro = (TApontador) malloc(sizeof(TCelula));
pLista->primeiro->prox=s;
}
pLista->primeiro->item = x;
return 1;
}

int TLista_Retiraprimeiro(TLista *pLista, int pX)
{
TApontador q;
if (TLista_EhVazia(pLista))
return 0;
q = pLista->primeiro;
pX = q->item;
pLista->primeiro = q->prox;
free(q);
if (pLista->primeiro == NULL)
pLista->ultimo = NULL;
return 1;
}

void TLista_Imprime(TLista *pLista)
{
TApontador p;
p = pLista->primeiro;
while (p != NULL) {
printf("%d\n", p->item);
p = p->prox;
}
}

int main(){
TLista* lista = (TLista*) malloc(sizeof(TLista));
TLista_Insere(lista, 50);
TLista_Insere(lista, 10);
TLista_Insere(lista, 20);
TLista_Insere(lista, 5);
TLista_Imprime(lista);
return 0;
}
