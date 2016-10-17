
//lista encadeada

//Diferenciar pilha(LIFO - last in, first out) de 
// fila(FIFO - first in, first out)

//lista circular




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


//bloco para uma estrutura usada em uma lista simples
struct BlocoSimples{
	
	int valor;
	struct BlocoSimples* proximo;

};

//bloco para uma estrutura usada em uma lista duplamente encadeada
struct Bloco{

	int valor;
	struct Bloco* esquerda;
	struct Bloco* direita; 
};

//cria novo bloco para uma estrutura usada em uma lista simples
struct BlocoSimples* novoSimples(int valor){

	struct BlocoSimples* novo;
	novo = (struct BlocoSimples*)malloc(sizeof(struct BlocoSimples));
	novo->valor = valor;
	novo->proximo = NULL;
	return novo;
}


//cria novo bloco para uma estrutura usada em uma lista duplamente encadeada
struct Bloco* novo(int valor){

	struct Bloco* novo;
	novo = (struct Bloco*)malloc(sizeof(struct Bloco));
	novo->valor = valor;
	novo->esquerda = NULL;
	novo->direita = NULL;
	return novo;
}

//inserção para lista duplamente encadeada
//pilha
void inserir(struct Bloco** inicio, struct Bloco* novo){
	
	if ((*inicio) != NULL)
		(*inicio)->esquerda = novo;
	novo->direita = (*inicio);
	(*inicio) = novo;
}


//inserção para lista encadeada
//pilha
void inserirSimples(struct BlocoSimples** inicio, struct BlocoSimples* novo){
	
	novo->proximo = (*inicio);
	(*inicio) = novo;
}


//para lista duplamente encadeada
void inserirOrdenado(struct Bloco** inicio, struct Bloco* novo){
	
	if ((*inicio) == NULL)
		(*inicio) = novo;
	else{
		struct Bloco* b, *a = (*inicio);
		while(a != NULL && (a->valor < novo->valor)){
			b = a;
			a = a->direita;
		}
		if (a != NULL){
			a->esquerda = novo;
			novo->direita = a;
		}
		if (a == (*inicio))
			(*inicio) = novo;
		if (a == NULL || a != (*inicio)){
			novo->esquerda = b;
			b->direita = novo;
		}
	}
}

//fazer inserçao ordenada para lista simples



//imprimir elementos em lista duplamente encadeada
void imprimir(struct Bloco* inicio){

	struct Bloco* elemento = inicio;
	while(elemento != NULL){
		printf("\n%d", elemento->valor);
		elemento = elemento->direita;
	}
	printf("\n");
}


//imprimir elementos em lista simples
void imprimirSimples(struct BlocoSimples* inicio){

	struct BlocoSimples* elemento = inicio;
	while(elemento != NULL){
		printf("\n%d", elemento->valor);
		elemento = elemento->proximo;
	}
	printf("\n");

}


//remove elemento em lista duplamente encadeada
int remover(struct Bloco* inicio, int valor){

	struct Bloco* elemento = inicio;
	while(elemento != NULL){
		if (elemento->valor == valor){
			(*elemento->esquerda).direita = elemento->direita;
			(*elemento->direita).esquerda = elemento->esquerda;
			return 1;
		}
		
		else
			elemento = elemento->direita;
	}
	return 0;

}


//remove elemento em lista encadeada
int removerSimples(struct BlocoSimples* inicio, int valor){

	struct BlocoSimples* elemento = inicio;
	struct BlocoSimples* elementoAnterior = elemento;
	while(elemento != NULL){
		if (elemento->valor == valor){
			(*elementoAnterior).proximo = elemento->proximo;

			return 1;
		}
		
		else
			elementoAnterior = elemento;
			elemento = elemento->proximo;
	}
	return 0;

}



//busca para lista simples
struct BlocoSimples* buscaSimples(struct BlocoSimples* inicio, int valor){

	struct BlocoSimples* elemento = inicio;
	while(elemento != NULL){
		if (elemento->valor == valor)
			return elemento;
		elemento = elemento->proximo;
	}
	return elemento;
}

//busca para lista duplamente encadeada
struct Bloco* busca(struct Bloco* inicio, int valor){

	struct Bloco* elemento = inicio;
	while(elemento != NULL){
		if (elemento->valor == valor)
			return elemento;
		elemento = elemento->direita;
	}
	return elemento;
}


//fazer busca binaria para lista simples e duplamente encadeada



int main(){


	struct timeval t1, t2;
	FILE *arq;
	arq = fopen("tempoBuscaListaEncadeada_Medio.txt", "wt");

	//estrutura para lista encadeada
	struct BlocoSimples* inicio;
	//estrutura para lista duplamente encadeada
	//struct Bloco* inicio;
	
	
	int contador, contador2, contador3;
	for (contador = 100; contador < 10000; contador += 100){

		inicio = (struct BlocoSimples*)malloc(sizeof(struct BlocoSimples));
		//inicio = (struct Bloco*)malloc(sizeof(struct Bloco));


		for (contador2 = contador; contador2 > 0; contador2--){

			inserirSimples(&inicio, novoSimples(rand() % contador2));
			//inserir(&inicio, novo(contador2));

			//inserirOrdenado(&inicio, novo(contador2));
		}

		float media = 0.0;
		for (contador3 = 0; contador3 < 100; contador3++){	

			//medindo o tempo da função
			gettimeofday(&t1, NULL);

			//melhor caso
			//buscaSimples(inicio, 0);
			//pior caso
			//buscaSimples(inicio, contador * 2);
			//medio caso
			buscaSimples(inicio, rand() % (contador + 100));

			//busca(inicio, rand() % contador);

			gettimeofday(&t2, NULL);
	
			media += (float)(((t2.tv_sec * 1000000.0 + t2.tv_usec) - (t1.tv_sec * 1000000.0 + t1.tv_usec)) / 1000000.0);

	
		}

		//escrevendo no arquivo
		fprintf(arq, "%.20lf%s", media / 100.0, "\n");

	}

	fclose(arq);
	//imprimir(inicio);
	//imprimirSimples(inicio);
	

	return 0;
}




