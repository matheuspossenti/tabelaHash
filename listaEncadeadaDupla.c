#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct elemento e lista
typedef struct sElemento
{
	struct sElemento * next;
	struct sElemento * prev;
	char dado[50];
} Elemento;

typedef struct sLista
{
	struct sElemento * head;
	struct sElemento * tail;
	struct sLista * next;
	struct sLista * prev;
	int chave;
	int size;
} Lista;

Elemento* alocaMemoriaElemento(char *dado);
Lista* alocaMemoriaLista(int chave);

void insereLista(Lista *lista, Elemento *pivo, char *dado);
void imprimeLista(Lista *lista);

Elemento* alocaMemoriaElemento(char *dado)
{
	Elemento *elemento = (Elemento*) malloc(sizeof(Elemento));

	strcpy(elemento->dado, dado);
	elemento->next = NULL;
	elemento->prev = NULL;

	return elemento;
}

Lista* alocaMemoriaLista(int chave)
{
	Lista *lista = (Lista*) malloc(sizeof(Lista));

	lista->next = NULL;
	lista->prev = NULL;
	lista->chave = chave;
	lista->size = 0;

	return lista;
}

void insereLista(Lista *lista, Elemento *pivo, char *dado)
{
	Elemento *novo = alocaMemoriaElemento(dado);

	if ((pivo == NULL) && (lista->size != 0))
	{
		novo->next = lista->head;
		novo->next->prev = novo;
		lista->head = novo;
	}
	else if (lista->size == 0)
	{
		lista->head = novo;
		lista->tail = novo;
	}
	else
	{
		novo->next = pivo->next;
		novo->prev = pivo;

		if (pivo->next == NULL)
		{
			lista->tail = novo;
		}
		else
		{
			pivo->next->prev = novo;
		}

		pivo->next = novo;
	}

	lista->size++;
}

Elemento* buscarElemento(Lista *lista, char *dado)
{
	Elemento *elemento = lista->head;

	while (elemento != NULL)
	{
		if (strcmp(elemento->dado, dado) == 0)
		{
			return elemento;
		}

		elemento = elemento->next;
	}

	return NULL;
}

void imprimeLista(Lista *lista)
{
	if (lista != NULL)
	{
		Elemento *elemento = lista->head;

		printf("Chave %d \n", lista->chave);
		while (elemento != NULL)
		{
			printf("-> %s\n", elemento->dado);
			elemento = elemento->next;
		}

		printf("\n");
	}
}