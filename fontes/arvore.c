
//arvore binaria

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


//bloco usado em estruturas arvore binaria e balanceada
struct no{

	int valor;
	unsigned int altura;
	struct no* esquerda;
	struct no* direita;
	struct no* pai;
};


//cria nova estrutura
struct no* novo(int valor){

	struct no* novo;
	novo = (struct no*)malloc(sizeof(struct no));
	novo->valor = valor;
	novo->altura = 0;
	novo->esquerda = NULL;
	novo->direita = NULL;
	novo->pai = NULL;
	return novo;

}


unsigned int maximo(unsigned int x, unsigned int y){

	if (x > y)
		return x;
	else
		return y;


}



unsigned int modulo(unsigned int x, unsigned int y){
	
	if (x - y < 0){
		return -(x - y);
	}
	else
		return x - y;

}


unsigned int altura(struct no* no){

	if (no == NULL)
		return 0;		
	else
		return no->altura;
}

int valor(struct no* no){

	if (no == NULL)
		return 0;
	else
		return no->valor;

}


//busca aparentemente em arvore simples
struct no* busca(struct no* raiz, int valor){

	if (raiz == NULL){
		struct no* null = NULL;
		return null;
	}
	else if (raiz->valor == valor)
		return raiz;
	else if (raiz->valor > valor)
		return busca(raiz->esquerda, valor);
	else
		return busca(raiz->direita, valor);
}



void imprimir(struct no* raiz){

	if (raiz != NULL){
		printf("\nValor: %d - Altura: %d\nDireita: %d - Altura: %d\nEsquerda: %d - Altura: %d\n", valor(raiz), altura(raiz), valor(raiz->direita), altura(raiz->direita), valor(raiz->esquerda), altura(raiz->esquerda));

		imprimir(raiz->direita);
		imprimir(raiz->esquerda);
	}

}



void atualizarAlturaIndividual(struct no* raiz){

	if (raiz != NULL){
		unsigned int x, y;
		x = altura(raiz->esquerda);
		y = altura(raiz->direita);
		raiz->altura = maximo(x, y) + 1;
	}
}


int atualizarAltura(struct no* raiz){

	int x, y;

	if (raiz != NULL){
		x = atualizarAltura(raiz->esquerda);
		y = atualizarAltura(raiz->direita);
		raiz->altura = maximo(x, y) + 1;
		return raiz->altura;
	}
	else
		return 0;

}


void rotacaoADireita(struct no* elemento){

	struct no* p = elemento->pai;
	struct no* y = elemento->esquerda;
	struct no* b = (elemento->esquerda)->direita;

	y->pai = p;
	if (p != NULL){
		
		if (p->direita == elemento){
			p->direita = y;
			atualizarAlturaIndividual(p);
		}
		else{
			p->esquerda = y;
			atualizarAlturaIndividual(p);
		}
	}
	
	elemento->esquerda = b;
	y->direita = elemento;
	atualizarAlturaIndividual(y);
	elemento->pai = y;

	if (b != NULL){
		b->pai = elemento;
		atualizarAlturaIndividual(b);
	}
	atualizarAlturaIndividual(elemento);
}



void rotacaoAEsquerda(struct no* elemento){

	struct no* p = elemento->pai;
	struct no* y = elemento->direita;
	struct no* b = (elemento->direita)->esquerda;

	y->pai = p;
	if (p != NULL){
		
		if (p->esquerda == elemento){
			p->esquerda = y;
			atualizarAlturaIndividual(p);
		}
		else{
			p->direita = y;
			atualizarAlturaIndividual(p);
		}
	}
	
	elemento->direita = b;
	y->esquerda = elemento;
	atualizarAlturaIndividual(y);
	elemento->pai = y;

	if (b != NULL){
		b->pai = elemento;
		atualizarAlturaIndividual(b);
	}	
	atualizarAlturaIndividual(elemento);
}


void balancear(struct no* no, struct no** raiz){

	if (altura(no->direita) > altura(no->esquerda)){
		if (altura((no->direita)->esquerda) > altura((no->direita)->direita)){
			rotacaoADireita(no->direita);
		}
		rotacaoAEsquerda(no);
		if ((*raiz) == no)
			(*raiz) = no->pai;
		
	}

	else{
		if (altura((no->esquerda)->direita) > altura((no->esquerda)->esquerda)){
			rotacaoAEsquerda(no->esquerda);
		}
		rotacaoADireita(no);
		if ((*raiz) == no)
			(*raiz) = no->pai;
	} 
}



void verificacao(struct no* no, struct no** raiz){

	unsigned int he, hd;

	while (no != NULL) {

		he = altura(no->esquerda);
		hd = altura(no->direita);
		
		no->altura = maximo(he, hd) + 1;
		if (modulo(hd, he) > 1)
			balancear(no, &(*raiz));		
		no = no->pai;
	}
}



//inserir
void inserir(struct no** raiz, struct no* novo, struct no** raizVerdadeira){

	if ((*raiz) == NULL){
		(*raiz) = novo;
		verificacao(novo, &(*raizVerdadeira));
	}

	else if (valor(*raiz) > valor(novo)){
		novo->pai = (*raiz);
		inserir(&((*raiz)->esquerda), novo, &(*raizVerdadeira));
	}
	else{
		novo->pai = (*raiz);
		inserir(&((*raiz)->direita), novo, &(*raizVerdadeira));
	}
}



int main(){

	
	struct timeval t1, t2;
	FILE *arq;
	arq = fopen("tempoBuscaArvoreAVL_Pior.txt", "wt");

	//raiz da arvore
	struct no* raiz;
	
	int contador, contador2, contador3;
	for (contador = 100; contador < 10000; contador += 100){

		raiz = NULL;
		//raiz = (struct no*)malloc(sizeof(struct no));


		for (contador2 = 0; contador2 < contador; contador2++){
			inserir(&raiz, novo(rand() % (contador2 + 1)), &raiz);
			//pior caso
			//inserir(&raiz, novo(contador2 + 1), &raiz);

		}

		float media = 0.0;
		for (contador3 = 0; contador3 < 100; contador3++){

			//medindo o tempo da função
			gettimeofday(&t1, NULL);

			//casos:

			//medio
			//busca(raiz, rand() % (contador2 + 100));
			//melhor
			//busca(raiz, contador/2);
			//busca(raiz, 1);

			//pior
			busca(raiz, contador * 2);

			gettimeofday(&t2, NULL);
	
			media += (float)(((t2.tv_sec * 1000000.0 + t2.tv_usec) - (t1.tv_sec * 1000000.0 + t1.tv_usec)) / 1000000.0);

	
		}

		//escrevendo no arquivo
		fprintf(arq, "%.20lf%s", media / 100.0, "\n");

	}

	fclose(arq);

	return 0;
}






