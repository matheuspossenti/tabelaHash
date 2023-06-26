#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaEncadeadaDupla.c"
#define M 53

// Struct da tabela
typedef struct sTabela
{
	struct sLista * head;
	struct sLista * tail;
	int chave;
	int size;
} Tabela;

// Prototipação
Tabela* alocaMemoriaTabela();

// Prototipação tabela
Lista* buscarLista(Tabela *tabela, int chave);
void removeElementoDaLista(Tabela *tabela, char *dado);
void insereTabela(Tabela *tabela, Lista *pivo, char *dado);
void removerListaDaTabela(Tabela *tabela, Lista *lista);
void imprimeTabela(Tabela *tabela);
int contaTotalNomes(Tabela *tabela);
int contaTotalNomesLista(Lista *lista, char *dado);
void insereNome(Tabela *tabela, char *dado);
void insereArquivo(Tabela *tabela);
int pesquisaNome(Tabela *tabela, char *dado);

// Prototipação Quicksort
void swap(Elemento *A, Elemento *B);
Elemento* particiona(Lista *lista, Elemento *left, Elemento *pivo);
void quickSort(Lista *lista, Elemento *left, Elemento *right, int i);

// Alocação de memoria da tabela
Tabela* alocaMemoriaTabela()
{
	Tabela *tabela = (Tabela*) malloc(sizeof(Tabela));

	tabela->head = NULL;
	tabela->tail = NULL;
	tabela->size = 0;

	return tabela;
}

// Hash a partir da soma do ASCII de cada letra
int hash(char *dado)
{
	int i, chave = 0;
	for (i = 0; i < strlen(dado); i++)
	{
		chave += dado[i] * 7;
	}

	return (chave % M);
}

void insereTabela(Tabela *tabela, Lista *pivo, char *dado)
{
	int chave = hash(dado);
	Lista *lista = buscarLista(tabela, chave);

	if (lista == NULL)
	{
		lista = alocaMemoriaLista(chave);

		if ((pivo == NULL) && (tabela->size != 0))
		{
			lista->next = tabela->head;
			lista->next->prev = lista;
			tabela->head = lista;
		}
		else if (tabela->size == 0)
		{
			tabela->head = lista;
			tabela->tail = lista;
		}
		else
		{
			lista->next = pivo->next;
			lista->prev = pivo;

			if (pivo->next == NULL)
			{
				tabela->tail = lista;
			}
			else
			{
				pivo->next->prev = lista;
			}

			pivo->next = lista;
		}

		tabela->size++;
	}

	insereLista(lista, lista->tail, dado);
}

void removeElementoDaLista(Tabela *tabela, char *dado)
{
	int chave = hash(dado);

	Lista *lista = buscarLista(tabela, chave);
	Elemento *elemento = buscarElemento(lista, dado);

	if ((lista != NULL) && (elemento != NULL))
	{
		if ((elemento != NULL) && (lista->size != 0))
		{
			if (elemento == lista->head)
			{
				lista->head = elemento->next;
				if (lista->head == NULL)
				{
					lista->tail = NULL;
				}
				else
				{
					elemento->next->prev = NULL;
				}
			}
			else
			{
				elemento->prev->next = elemento->next;
				if (elemento->next == NULL)
				{
					lista->tail = elemento->prev;
				}
				else
				{
					elemento->next->prev = elemento->prev;
				}
			}

			free(elemento);
			lista->size--;

			if (lista->size == 0)
			{
				removerListaDaTabela(tabela, lista);
			}
		}
	}
}

void removerListaDaTabela(Tabela *tabela, Lista *lista)
{
	if ((lista != NULL) && (tabela->size != 0))
	{
		if (lista == tabela->head)
		{
			tabela->head = lista->next;

			if (tabela->head == NULL)
			{
				tabela->tail = NULL;
			}
			else
			{
				lista->next->prev = NULL;
			}
		}
		else
		{
			lista->prev->next = lista->next;

			if (lista->next == NULL)
			{
				tabela->tail = lista->prev;
			}
			else
			{
				lista->next->prev = lista->prev;
			}
		}

		free(lista);
		tabela->size--;
	}
}

Lista* buscarLista(Tabela *tabela, int chave)
{
	Lista *lista = tabela->head;

	while (lista != NULL)
	{
		if (lista->chave == chave)
		{
			return lista;
		}

		lista = lista->next;
	}

	return NULL;
}

// Inserção dos nomes do arquivo nomes.txt
void insereArquivo(Tabela *tabela)
{
	FILE * file;
	char nome[50];

	file = fopen("nomes.txt", "r");

	while (fgets(nome, 50, file) != NULL)
	{
		strcpy(nome, strtok(nome, "\n"));
		insereNome(tabela, nome);
	}
}

void insereNome(Tabela *tabela, char *dado)
{
	int chave = hash(dado);
	Lista *lista = buscarLista(tabela, chave);
	insereTabela(tabela, lista, dado);
}

void imprimeTabela(Tabela *tabela)
{
	Lista *lista = tabela->head;

	while (lista != NULL)
	{
		imprimeLista(lista);
		lista = lista->next;
	}
}

int pesquisaNome(Tabela *tabela, char *dado)
{
	int chave = hash(dado);
	Lista *lista = buscarLista(tabela, chave);
	int cont = 0;

	if (lista != NULL)
	{
		cont = contaTotalNomesLista(lista, dado);
	}

	if (cont > 0)
	{
		return cont;
	}

	return -1;
}

int contaTotalNomesLista(Lista *lista, char *dado)
{
	Elemento *elemento = lista->head;
	int cont = 0;

	while (elemento != NULL)
	{
		if (strcmp(elemento->dado, dado) == 0)
		{
			cont++;
		}

		elemento = elemento->next;
	}

	return cont;
}

int contaTotalNomes(Tabela *tabela)
{
	Lista *lista = tabela->head;
	int qtdNomes = 0;

	while (lista != NULL)
	{
		qtdNomes += lista->size;
		lista = lista->next;
	}

	return qtdNomes;
}

//Quicksort
void swap(Elemento *A, Elemento *B)
{
	char temp[30];
	strcpy(temp, A->dado);
	strcpy(A->dado, B->dado);
	strcpy(B->dado, temp);
}

Elemento *particiona(Lista *lista, Elemento *left, Elemento *pivo)
{
	Elemento *aux = left->prev;

	for (Elemento *i = left; i != pivo; i = i->next)
	{
		if (strcmp(i->dado, pivo->dado) < 0)
		{
			if (aux)
			{
				aux = aux->next;
			}
			else
			{
				aux = left;
			}

			swap(aux, i);
		}
	}

	if (aux)
	{
		aux = aux->next;
	}
	else
	{
		aux = left;
	}

	swap(aux, pivo);

	return aux;
}

void quickSort(Lista *lista, Elemento *left, Elemento *right, int i)
{
	if (right != NULL && left != NULL && left != right && left != right->next)
	{
		Elemento *pivo = particiona(lista, left, right);

		quickSort(lista, left, pivo->prev, i + 1);
		quickSort(lista, pivo->next, right, i + 1);
	}
}

//Main
int main()
{
	Tabela *tabela = alocaMemoriaTabela();
	Lista * lista;
	int opcao, chave, flag = 0;
	char nome[50];

	do {
		printf("\n----- Menu de Opções -----\n");
        printf("\n1 - Inserir nomes do arquivo\n");
        printf("2 - Inserir nome\n");
        printf("3 - Remover nome\n");
        printf("4 - Pesquisar nome\n");
        printf("5 - Imprimir lista\n");
        printf("6 - Imprimir tabela\n");
        printf("7 - Quantidade de nomes na lista\n");
        printf("8 - Quantidade de nomes na tabela\n");
        printf("9 - Quicksort lista\n");
        printf("10 - Quicksort tabela\n");
        printf("0 - Sair\n");

		printf("Opcao: ");
		scanf("%d", &opcao);

		system("clear");
		switch (opcao)
		{
			case 1:
				insereArquivo(tabela);

				break;
			case 2:
				printf("\nQual o nome a ser adicionado ?\n");
				scanf("%s", nome);

				insereNome(tabela, nome);

				break;
			case 3:
				printf("\nQual o nome a ser removido ? \n");
				scanf("%s", nome);

				removeElementoDaLista(tabela, nome);

				break;
			case 4:
				printf("\nColoque o nome a ser buscado: ");
				scanf("%s", nome);

				int busca = pesquisaNome(tabela, nome);

				if (busca > 0)
				{
					printf("\n O nome %s foi encontrado(s) %d na lista", nome, busca);
				}
				else
				{
					printf("\n%s nao encontrado(a)", nome);
				}

				break;
			case 5:
				printf("\nQual a chave ? ");
				scanf("%d", &chave);

				lista = buscarLista(tabela, chave);

				if (lista == NULL)
				{
					printf("Nenhuma lista criada com essa chave");
				}
				else
				{
					imprimeLista(lista);
				}

				break;
			case 6:
				imprimeTabela(tabela);

				break;
			case 7:
				printf("\nColoque a chave da lista: ");
				scanf("%d", &chave);

				lista = buscarLista(tabela, chave);
				if (lista == NULL)
				{
					printf("Nenhuma lista criada com essa chave");
				}
				else
				{
					printf("\nQuantidade de nomes na lista %d: %d\n", chave, lista->size);
				}

				break;
			case 8:
				printf("\nQuantidade de nomes na tabela: %d\n", contaTotalNomes(tabela));

				break;
			case 9:
				printf("\nColoque a chave da lista: ");
				scanf("%d", &chave);

				lista = buscarLista(tabela, chave);
				if (lista == NULL)
				{
					printf("Nenhuma lista criada com essa chave");
				}
				else
				{
					quickSort(lista, lista->head, lista->tail, 0);
				}

				break;
			case 10:
				lista = tabela->head;
				for (int i = 0; i < tabela->size; i++)
				{
					lista = buscarLista(tabela, lista->chave);
					quickSort(lista, lista->head, lista->tail, 0);

					lista = lista->next;
				}

				break;
			default:
				flag += 1;

				break;
		}
	} while (flag == 0);

	free(lista);
	free(tabela);

	return 0;
}
