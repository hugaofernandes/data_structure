

//tabela hash (tabela de inspersão)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>



struct list{

	int valor;
	struct list* proximo;

};

struct hash{

	struct list** vetor;
	unsigned int tamanho;
	unsigned int elementos;
};


struct list* novo(int valor){

	struct list* novo;
	novo = (struct list*)malloc(sizeof(struct list));
	novo->valor = valor;
	novo->proximo = NULL;
	return novo;
}


void inserir(struct hash* hash, struct list** inicio, struct list* novo){
	
	novo->proximo = (*inicio);
	(*inicio) = novo;
	(*hash).elementos += 1;

}


void imprimir(struct list** inicio, int tamanho){

	int i;
	struct list* elemento;
	for (i = 0; i < tamanho; i++){
		struct list* elemento = inicio[i];
		while(elemento != NULL){
			printf("\n%d", elemento->valor);
			elemento = elemento->proximo;
		}
	}
	printf("\n");
}


struct list* busca(struct list** inicio, int valor, int tamanho){

	int i;
	struct list* elemento;
	for (i = 0; i < tamanho; i++){
		elemento = inicio[valor % tamanho];
		while(elemento != NULL){
			if (elemento->valor == valor)
				return elemento;		
			elemento = elemento->proximo;
		}
		elemento = NULL;
		return elemento;
	}
	elemento = NULL;
	return elemento;
}


struct hash* rehashing(struct hash** estrutura){

	struct hash* inicio;
	inicio = malloc(sizeof(struct hash));
	(*inicio).vetor = malloc(((*estrutura)->tamanho * 2) * sizeof(struct list*));
	(*inicio).tamanho = (*estrutura)->tamanho * 2;
	(*inicio).elementos = 0;

	int i;
	for (i = 0; i < (*estrutura)->elementos; i++){
		inserir(inicio, &(*inicio).vetor[(i % (*inicio).tamanho) % (*inicio).tamanho], novo(i % (*inicio).tamanho));
	}
	
	return inicio;
}


int main(){
	
	struct timeval t1, t2;
	FILE *arq;
	arq = fopen("tempoBuscaTabelaHash_Medio.txt", "wt");

	struct hash* inicio;
	int contador, contador2, contador3;

	for (contador = 100; contador < 10000; contador += 100){

		inicio = malloc(sizeof(struct hash));
		(*inicio).vetor = malloc(contador * sizeof(struct list*));
		(*inicio).tamanho = contador;
		(*inicio).elementos = 0;

		//inserindo
		for (contador2 = 0; contador2 < (contador + 10); contador2++){
			inserir(inicio, &(*inicio).vetor[(contador2 % (*inicio).tamanho) % (*inicio).tamanho], novo(contador2 % (*inicio).tamanho));

			if ((*inicio).elementos > (*inicio).tamanho){
				inicio = rehashing(&inicio);
			}
		}


		float media = 0.0;
		for (contador3 = 0; contador3 < 100; contador3++){

			//medindo o tempo da função
			gettimeofday(&t1, NULL);

			busca((*inicio).vetor, rand() % ((*inicio).tamanho + 100), (*inicio).tamanho);

			gettimeofday(&t2, NULL);
	
			media += (float)(((t2.tv_sec * 1000000.0 + t2.tv_usec) - (t1.tv_sec * 1000000.0 + t1.tv_usec)) / 1000000.0);
		
		}

		//escrevendo no arquivo
		fprintf(arq, "%.20lf%s", media / 100.0, "\n");

	}


	fclose(arq);
	return 0;
	
}




