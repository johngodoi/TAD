//#include "TFila.h"
#include <stdlib.h>

typedef struct {
int x, y;
} TPosicao;
typedef TPosicao TItem;
typedef int **TLabirinto;
typedef int TChave;
//typedef struct {
//TChave Chave;
/* outros componentes */
//} TItem;

typedef struct SCelula *TApontador;
typedef struct SCelula {
TPosicao Item;
TApontador Prox;
} TCelula;

typedef struct {
TApontador Frente, Tras;
} TFila;

void TFila_Inicia(TFila *pFila)
{
pFila->Frente = (TApontador) malloc(sizeof(TCelula));
pFila->Tras = pFila->Frente;
pFila->Frente->Prox = NULL;
}
/* Retorna se a fila esta vazia */
int TFila_EhVazia(TFila *pFila)
{
return (pFila->Frente == pFila->Tras);
}

/* Enfileira um item na parte de tras da fila */
int TFila_Enfileira(TFila *pFila, TPosicao x)
{
pFila->Tras->Prox = (TApontador) malloc(sizeof(TCelula));
pFila->Tras = pFila->Tras->Prox;
pFila->Tras->Item = x;
pFila->Tras->Prox = NULL;
return 1;
}

/* Desenfileira o item da frente da fila */
int TFila_Desenfileira(TFila *pFila, TPosicao *pX)
{
TApontador pAux;
if (TFila_EhVazia(pFila))
return 0;
pAux = pFila->Frente;
pFila->Frente = pAux->Prox;
*pX = pAux->Prox->Item;
free(pAux);
return 1;
}
void LimpaLabirinto(TLabirinto A, int m, int n)
{
/* Coloca -2 em todas as posições livre,
significando que nenhuma delas está marcada. */
int i, j;
for (i=0; i<m; i++)
for (j=0; j<n; j++)
if (A[i][j] != -1)
A[i][j] = -2;
}

void MarcaVizinhos(TLabirinto A, TFila *pFila, TPosicao p)
{ /* Marca cada um dos vizinhos da posição p que ainda
é livre com um a mais que o rótulo da posição p. */
TPosicao aux;
/* Se a posição é livre e não está marcada,
marca e insere no fim da fila. */
if (A[p.x+1][p.y] == -2)
{ A[p.x+1][p.y] = A[p.x][p.y] + 1; aux.x = p.x+1; aux.y = p.y;
TFila_Enfileira(pFila, aux); }
if (A[p.x-1][p.y] == -2)
{ A[p.x-1][p.y] = A[p.x][p.y] + 1; aux.x = p.x-1; aux.y = p.y;
TFila_Enfileira(pFila, aux); }
if (A[p.x][p.y+1] == -2)
{ A[p.x][p.y+1] = A[p.x][p.y] + 1; aux.x = p.x; aux.y = p.y+1;
TFila_Enfileira(pFila, aux); }
if (A[p.x][p.y-1] == -2)
{ A[p.x][p.y-1] = A[p.x][p.y] + 1; aux.x = p.x; aux.y = p.y-1;
TFila_Enfileira(pFila, aux); }
}
void MarcaLabirinto(TLabirinto A, int m, int n, TPosicao p)
{
/* Marca o labirinto com a distância mínima para
chegar a cada posição a partir da posição p
*/
TFila Fila;
TPosicao q;
TFila_Inicia(&Fila);
LimpaLabirinto(A, m, n);
/* Começa da posição p */
A[p.x][p.y] = 0;
TFila_Enfileira(&Fila, p);

while (!TFila_EhVazia(&Fila)) {
TFila_Desenfileira(&Fila, &q);
MarcaVizinhos(A, &Fila, q);
}
}
TPosicao Anterior(TLabirinto A, TPosicao p)
{
TPosicao aux;
if (A[p.x+1][p.y] == A[p.x][p.y] - 1)
{ aux.x = p.x+1; aux.y = p.y; }
else if (A[p.x-1][p.y] == A[p.x][p.y] - 1)
{ aux.x = p.x-1; aux.y = p.y; }
else if (A[p.x][p.y+1] == A[p.x][p.y] - 1)
{ aux.x = p.x; aux.y = p.y+1; }
else if (A[p.x][p.y-1] == A[p.x][p.y] - 1)
{ aux.x = p.x; aux.y = p.y-1; }
return (aux);
}

void DeterminaCaminho(TLabirinto A, int m, int n, TPosicao p)
{
/* Dado um labirinto marcado com as distâncias mínimas a partir
de uma posição inicial (determinada por ter distância mínima
zero), determina o caminho mínino de p à posição inicial */
TPosicao q;

if (A[p.x][p.y] == -2)
printf("Não há caminho.\n");
else {
q = p;
printf("Caminho:\n");
while (A[q.x][q.y] != 0) {
printf("(%d,%d)\n", q.x, q.y);
q = Anterior(A, q);
}
printf("(%d,%d)\n\n", q.x, q.y);
}
}
