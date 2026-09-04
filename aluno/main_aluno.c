/* ============================================================================
 * https://github.com/jrcampos82/Estrutura_Dados_II_ENG4_2026-2
 *
 *  main_aluno.c - programa de teste da ATIVIDADE
 *  Estrutura de Dados 2 - IFMS
 *
 *  NAO E PRECISO ALTERAR ESTE ARQUIVO.
 *  Ele so serve para voce testar o que escreveu em avl_aluno.c.
 *
 *  Compilar:  make
 *  Executar:  ./avl_aluno      (ou apenas: make run)
 * ========================================================================== */

#include "avl_aluno.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>

/* Le um numero inteiro do teclado com seguranca.
 * Se o usuario digitar algo que nao e numero, limpa a entrada e devolve 0. */
int lerInteiro(int *destino) {
  if (scanf("%d", destino) == 1)
    return 1;

  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    /* descarta o resto da linha */
  }
  return 0;
}

void mostrarMenu(void) {
  printf("\n======= ARVORE AVL (atividade) =======\n");
  printf("  1 - Inserir\n");
  printf("  2 - Remover\n");
  printf("  3 - Imprimir\n");
  printf("  0 - Sair\n");
  printf("======================================\n");
  printf("Opcao: ");
}

No *opcaoInserir(No *raiz) {
  int valor;

  printf("Valor a inserir: ");
  if (!lerInteiro(&valor)) {
    printf("Valor invalido.\n");
    return raiz;
  }

  if (buscar(raiz, valor) != NULL) {
    printf("O valor %d ja esta na arvore.\n", valor);
    return raiz;
  }

  raiz = inserir(raiz, valor);

  /* Confere se a insercao realmente aconteceu. Enquanto o TODO 4 nao
   * estiver pronto, o aluno recebe um aviso claro em vez de uma mensagem
   * de sucesso que nao corresponde a verdade. */
  if (buscar(raiz, valor) != NULL)
    printf("Valor %d inserido.\n", valor);
  else
    printf("Nada aconteceu: a funcao inserir() ainda esta vazia (TODO 4).\n");

  return raiz;
}

No *opcaoRemover(No *raiz) {
  int valor;

  printf("Valor a remover: ");
  if (!lerInteiro(&valor)) {
    printf("Valor invalido.\n");
    return raiz;
  }

  if (buscar(raiz, valor) == NULL) {
    printf("O valor %d nao esta na arvore.\n", valor);
    return raiz;
  }

  raiz = remover(raiz, valor);

  /* Mesma ideia da insercao: confere se a remocao aconteceu de fato. */
  if (buscar(raiz, valor) == NULL)
    printf("Valor %d removido.\n", valor);
  else
    printf("Nada aconteceu: a funcao remover() ainda esta vazia (TODO 5).\n");

  return raiz;
}

void opcaoImprimir(No *raiz) {
  if (raiz == NULL) {
    printf("\nA arvore esta vazia.\n");
    return;
  }

  printf(
      "\n--- Arvore (deitada: raiz a esquerda, filho direito em cima) ---\n\n");
  imprimirArvore(raiz, 0);

  printf("\nEm ordem  (crescente): ");
  emOrdem(raiz);
  printf("\nPre-ordem (estrutura): ");
  preOrdem(raiz);

  printf("\n\nQuantidade de nos: %d\n", contarNos(raiz));
  printf("Altura da arvore : %d\n", altura(raiz));

  /* Conferencia automatica: avisa se a arvore deixou de ser uma AVL. */
  if (arvoreValida(raiz)) {
    printf("Verificacao      : OK, e uma AVL valida.\n");
  } else {
    printf("Verificacao      : ATENCAO! Isto nao e uma AVL valida.\n");
    printf("                   Confira as alturas, o balanceamento e a\n");
    printf("                   ordem das chaves nas suas funcoes.\n");
  }
}

int main(int argc, char *argv[]) {

  No *raiz = NULL; /* a arvore comeca vazia */
  int opcao;

  // tempo!

  if (argc > 1) {
    int n = atoi(argv[1]);
    srand((unsigned int)time(NULL));

    int faixa = (n * 5) > 100 ? n * 5 : 100;

    for (int i = 0; i < n; i++) {
      int val = rand() % faixa + 1;

      if (buscar(raiz, val) == NULL)
        raiz = inserir(raiz, val);
    }
  }

  // qtd rotacoes e quais
  // imprimir
  // remover por [x, y, z]

  printf("Arvore AVL - atividade de Estrutura de Dados 2\n");
  printf("(implemente os TODO de avl_aluno.c e teste por aqui)\n");

  do {
    mostrarMenu();

    if (!lerInteiro(&opcao)) {
      printf("\nEntrada invalida. Digite o numero de uma opcao.\n");
      continue;
    }

    switch (opcao) {

    case 1:
      raiz = opcaoInserir(raiz);
      break;

    case 2:
      raiz = opcaoRemover(raiz);
      break;

    case 3:
      opcaoImprimir(raiz);
      break;

    case 0:
      printf("\nEncerrando...\n");
      break;

    default:
      printf("\nOpcao invalida. Escolha 0, 1, 2 ou 3.\n");
      break;
    }

  } while (opcao != 0);

  liberar(raiz); /* devolve toda a memoria antes de sair */
  return 0;
}
