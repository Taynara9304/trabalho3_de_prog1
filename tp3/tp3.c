/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */
struct racional *lerRacional() {
  long numerador;
  long denominador;

  scanf("%ld", &numerador);
  scanf("%ld", &denominador);

  return cria_r(numerador, denominador);
}

void lerVetor(struct racional **vetor, int n) {
  for (int i = 0; i < n; i++) {
    vetor[i] = lerRacional();
  }  
};

void imprimirVetor(struct racional **vetor, int n) {
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      printf(" ");
    }
    
    imprime_r(vetor[i]);
  }

  printf("\n");
}

void eliminarElementosInvalidos(struct racional **ponteiroVetor, int *ponteiroN) {
  int i = 0;
  int final = *ponteiroN;

  while (i < final) {
    if (!valido_r(ponteiroVetor[i])) {
      free(ponteiroVetor[i]);
      final--;
      ponteiroVetor[i] = ponteiroVetor[final];
    } else {
      i++;
    }
  }

  *ponteiroN = final;
}

void troca(struct racional **ponteiroVetor, int j) {
  struct racional *aux;

  aux = ponteiroVetor[j];
  ponteiroVetor[j] = ponteiroVetor[j+1];
  ponteiroVetor[j+1] = aux;
}

// Método bubble sort
void ordenarVetor(struct racional **ponteiroVetor, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n-1; j++) {
      if(compara_r(ponteiroVetor[j], ponteiroVetor[j+1]) == 1) {
        troca(ponteiroVetor, j);
      }
    }
  }
}

struct racional *somarElementosDoVetor(struct racional **ponteiroVetor, int n) {
    struct racional *acumulador = cria_r(0, 1);
    if (!acumulador)
        return NULL;

    for (int i = 0; i < n; i++) {
        soma_r(acumulador, ponteiroVetor[i], acumulador);
    }

    return acumulador;
}

void lerTamanho(int *n) {
  scanf("%d", n);
}

/* programa principal */
int main ()
{
  int n;
  struct racional **vetor, *soma;

  lerTamanho(&n);

  if (n < 0 || n > 100)
    return 1;

  vetor = malloc(n * sizeof(vetor));

  lerVetor(vetor, n);

  printf("VETOR = ");
  imprimirVetor(vetor, n);

  eliminarElementosInvalidos(vetor, &n);

  printf("VETOR = ");
  imprimirVetor(vetor, n);

  ordenarVetor(vetor, n);

  printf("VETOR = ");
  imprimirVetor(vetor, n);

  soma = somarElementosDoVetor(vetor, n);

  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");

  for (int i = 0; i < n; i++) {
    free(vetor[i]);
    vetor[i] = NULL;
  }

  printf("VETOR = ");
  imprimirVetor(vetor, n);

  free(vetor);
  free(soma);

  return 0;
}

/*
leia um valor n tal que 0 < n < 100 - OK
aloque dinamicamente um vetor com n ponteiros para números racionais - OK
preencha o vetor com n números racionais lidos da entrada - OK
(leia o numerador e o denominador de cada racional)
imprima "VETOR = " e os racionais apontados pelo vetor - OK
elimine do vetor os racionais inválidos - OK
imprima "VETOR = " e o vetor resultante - OK
ordene o vetor em ordem crescente - OK
imprima "VETOR = " e os racionais apontados pelo vetor - OK
calcule a soma dos racionais apontados pelo vetor - OK
imprima "SOMA = " e a soma calculada acima - OK
libere os racionais apontados pelo vetor - OK
imprima "VETOR = " e os racionais apontados pelo vetor
libere o vetor de ponteiros
libere o espaço utilizado para fazer o cálculo da soma
retorne 0
*/