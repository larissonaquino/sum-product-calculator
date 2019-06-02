#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no No;

struct lista {
	int tam;
	No * ini, * fim;
};

struct no {
	int info;
	No * prox, * ant;
};

Lista * criar() {
	Lista * l = malloc(sizeof(Lista));	
	l->tam = 0;
	l->ini = malloc(sizeof(No));
	l->fim = malloc(sizeof(No));
	l->ini->ant = NULL;
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->fim->prox = NULL;
	return l;
}

void destruir(Lista * l) {
	if (l != NULL) {
		limpar(l);
		free(l->ini);
		free(l->fim);
		free(l);
	}
}

void limpar(Lista * l) {
	No * aux = l->ini->prox, * aux2;
	while(aux != l->fim) {
		aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->tam = 0;
}

int tamanho(Lista * l) {
	return l->tam;	
}

int esta_vazia(Lista * l) {
	return tamanho(l) == 0;	
}

int ler_pos(Lista * l, int p) {
	No * aux; int i, tam = tamanho(l);
	if (p < 0 || p >= tam) {
		printf("Posição inválida!\n");
		return -1;
	}
	if (p < tam/2) {
		for (aux = l->ini->prox, i=0; i < p; i++) {
			aux = aux->prox;
		}
	} else {
		for (aux = l->fim->ant, i=tam-1; i > p; i--) {
			aux = aux->ant;
		}
	}
	return aux->info;
}

int primeiro(Lista * l) {
	return ler_pos(l, 0);
	// return l->tam != 0 ? l->ini->prox->info : -1;
}

int ultimo(Lista * l) {
	return ler_pos(l, tamanho(l)-1);
	//return l->tam != 0 ? l->fim->ant->info : -1;
}

int buscar(Lista * l, int v) {
	int p = 0;
	No * aux =  l->ini->prox;
	while(aux != l->fim) {
		if (aux->info == v) {
			return p;
		}
		aux = aux->prox;
		p++;
	}
	return -1;
	/* 
	int i;
	for (i=0; i<tamanho(l); i++) {
		if (ler_pos(i) == v) {
			return i;
		}
	}
	return -1;
	*/	
}

void imprimir(Lista * l) {
	int i;
	printf("[ ");
	No * aux =  l->ini->prox;
	while(aux != l->fim) {
		printf("%d ", aux->info);
		aux = aux->prox;
	}
	printf("]\n");
}

void escrever_pos(Lista * l, int p, int v) {
	int i;
	No * aux;
	if (p < 0 || p >= tamanho(l)) {
		printf("Posição inválida!\n");
		return;
	}
	for (aux = l->ini->prox, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux->info = v;
}

void inserir_pos(Lista * l, int p, int v) {
	int i, tam = tamanho(l);
	No * aux, * aux2;
	if (p < 0 || p > tam) {
		printf("Posição inválida!\n");
		return;
	}	
	aux2 = malloc(sizeof(No));
	aux2->info = v;
	for (aux = l->ini, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux->prox->ant = aux2;
	aux2->prox = aux->prox;
	aux2->ant = aux;
	aux->prox = aux2;
	l->tam++;
}

void inserir_primeiro(Lista * l, int v) {
	//inserir_pos(l, 0, v);
	No * aux = malloc(sizeof(No));
	aux->info = v;
	aux->prox = l->ini->prox;
	aux->ant = l->ini;
	l->ini->prox = aux;
	aux->prox->ant = aux;
	l->tam++;
}


void inserir_ultimo(Lista * l, int v) {
	//inserir_pos(l, tamanho(l), v);
	No * aux = malloc(sizeof(No));
	aux->info = v;
	aux->prox = l->fim;
	aux->ant = l->fim->ant;
	l->fim->ant = aux;
	aux->ant->prox = aux;
	l->tam++;
}

int remover_pos(Lista * l, int p) {
	int i, v, tam = tamanho(l);
	No * aux = NULL, * aux2;
	if (p < 0 || p >= tam) {
		printf("Posição inválida!\n");
		return -1;
	}		
	for (aux = l->ini, i=0; i < p; i++) {
		aux = aux->prox;
	}	
	aux2 = aux->prox;
	aux->prox = aux2->prox;
	aux2->prox->ant = aux;
	v = aux2->info;
	free(aux2);
	l->tam--;
	return v;
}

int remover_primeiro(Lista * l) {
	//return remover_pos(l, 0);
	int v;
	No * aux;
	if (l->tam == 0) {
		printf("Lista vazia!\n");
		return -1;
	}		
	aux = l->ini->prox;
	l->ini->prox = aux->prox;
	aux->prox->ant = l->ini;
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}

int remover_ultimo(Lista * l) {
	//return remover_pos(l, tamanho(l)-1);	
	int i, v;
	No * aux;
	if (l->tam == 0) {
		printf("Lista vazia!\n");
		return -1;
	}		
	aux = l->fim->ant;
	l->fim->ant = aux->ant;
	aux->ant->prox = l->fim;
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}
//RETIRAR DE L2 E CONCATENAR EM L1
void concatenar(Lista * l1, Lista * l2) {
	l1->fim->ant->prox = l2->ini->prox;
	l2->ini->prox->ant = l1->fim->ant;
	l2->fim->ant->prox = l1->fim;
	l1->fim->ant = l2->fim->ant;
	l2->ini->prox = l2->fim;
	l2->fim->ant = l2->ini;
	l1->tam += l2->tam;
	l2->tam = 0;
}

void remover(Lista * l, int v) {
	int i, tam = tamanho(l);
	No * aux = l->ini->prox;
	while(aux != l->fim) {
		if (aux->info == v) {
			break;
		}
		aux = aux->prox;
	}
	if (aux == l->fim) {
		return;
	}
	aux->ant->prox = aux->prox;
	aux->prox->ant = aux->ant;
	free(aux);
	l->tam--;
}

void inverter(Lista * l) {
	int tam = tamanho(l), i, tmp;
	No * aux1 = l->ini->prox, 
	   * aux2 = l->fim->ant;
	for (i=0; i<tam/2; i++) {
		tmp = aux1->info;
		aux1->info = aux2->info;
		aux2->info = tmp;
		aux1 = aux1->prox;
		aux2 = aux2->ant;
	}
}

Lista * unir(Lista * l1, Lista * l2) {
	Lista * l3 = criar();
	No * aux = l1->ini->prox;
	while(aux != l1->fim) {
		No * aux2 = malloc(sizeof(No));
		aux2->info = aux->info;
		aux2->prox = l3->fim;
		aux2->ant = l3->fim->ant;
		l3->fim->ant = aux2;
		aux2->ant->prox = aux2;
		l3->tam++;
		aux = aux->prox;
	}
	aux = l2->ini->prox;
	while(aux != l2->fim) {
		No * aux3 = l3->ini->prox;
		while(aux3 != l3->fim) {
			if (aux3->info == aux->info) {
				break;
			}
			aux3 = aux3->prox;
		}
		if (aux3 == l3->fim) { //PERCORREU L3 E NÃO ACHOU
			No * aux2 = malloc(sizeof(No));
			aux2->info = aux->info;
			aux2->prox = l3->fim;
			aux2->ant = l3->fim->ant;
			l3->fim->ant = aux2;
			aux2->ant->prox = aux2;
			l3->tam++;
		}	
		aux = aux->prox;
	}
	return l3;
}
