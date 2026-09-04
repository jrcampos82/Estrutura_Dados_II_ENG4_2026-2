/* ============================================================================
 *  avl_aluno.c - IMPLEMENTACAO da arvore AVL  (ATIVIDADE)
 *  Estrutura de Dados 2 - IFMS
 *
 *  Nome: ______________________________________  Turma: _______
 *
 *  ---------------------------------------------------------------------------
 *  O QUE FAZER
 *
 *  Procure por  TODO  neste arquivo. Sao cinco funcoes para escrever, nesta
 *  ordem sugerida (cada uma prepara a seguinte):
 *
 *      TODO 1 - liberar          (recursao simples, para aquecer)
 *      TODO 2 - rotacaoDireita
 *      TODO 3 - rotacaoEsquerda
 *      TODO 4 - inserir
 *      TODO 5 - remover
 *
 *  Todo o resto ja esta pronto: alturas, fator de balanceamento, busca,
 *  impressao e a funcao rebalancear(), que decide qual rotacao aplicar.
 *
 *  ---------------------------------------------------------------------------
 *  COMO TESTAR
 *
 *      make                  compila
 *      ./avl_aluno           executa o menu
 *
 *  (ou, de uma vez so:  make run)
 *
 *  O programa JA COMPILA E RODA antes de voce escrever qualquer coisa - so
 *  que sem fazer nada de util. Implemente uma funcao de cada vez e teste
 *  pelo menu: a opcao 3 (Imprimir) avisa se a arvore deixou de ser uma AVL
 *  valida, o que ajuda a encontrar erros.
 *
 *  DICA: as funcoes inserir e remover DEVOLVEM a nova raiz. Isso acontece
 *  porque uma rotacao pode trocar o no que estava no topo. Nunca esqueca de
 *  guardar o retorno:   raiz = inserir(raiz, valor);
 * ========================================================================== */

#include "avl_aluno.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char tipo[40];
  int chaveNo;
} InfoRotacao;

#define MAX_ROT_OP 64

static InfoRotacao rotacoesOperacao[MAX_ROT_OP];
static int qtdRotacoesOperacao = 0;

static int totalRotacoesEE = 0;
static int totalRotacoesDD = 0;
static int totalRotacoesED = 0;
static int totalRotacoesDE = 0;

/* ============================================================================
 *  FUNCOES JA PRONTAS - nao precisa mexer
 * ========================================================================== */

int maximo(int a, int b) { return (a > b) ? a : b; }

int altura(No *no) {
  if (no == NULL)
    return -1; /* arvore vazia tem altura -1 */
  return no->altura;
}

void atualizarAltura(No *no) {
  no->altura = 1 + maximo(altura(no->esq), altura(no->dir));
}

int fator(No *no) {
  if (no == NULL)
    return 0;
  return altura(no->esq) - altura(no->dir);
}

No *criarNo(int chave) {
  No *no = (No *)malloc(sizeof(No));
  if (no == NULL) {
    printf("Err: mem insuficiente!\n");
    exit(1);
  }
  // iniciar o no
  no->chave = chave;
  no->altura = 0;
  no->esq = NULL;
  no->dir = NULL;
  return no;
}

/* Decide qual rotacao aplicar quando um no fica desequilibrado.
 *
 * Os quatro casos:
 *      EE : fb > +1 e fb(filho esq) >= 0  -> rotacao simples a direita
 *      ED : fb > +1 e fb(filho esq) <  0  -> esquerda no filho, depois direita
 *      DD : fb < -1 e fb(filho dir) <= 0  -> rotacao simples a esquerda
 *      DE : fb < -1 e fb(filho dir) >  0  -> direita no filho, depois esquerda
 *
 * Repare que esta funcao NAO sabe girar ponteiros: ela apenas escolhe e chama
 * rotacaoDireita / rotacaoEsquerda. Por isso ela so vai funcionar depois que
 * voce escrever as duas (TODO 2 e TODO 3).
 *
 * DESAFIO EXTRA: apague o corpo desta funcao e reescreva sozinho. */
No *rebalancear(No *no) {
  atualizarAltura(no);

  int fb = fator(no);

  if (fb > 1) {             /* pesado a esquerda */
    if (fator(no->esq) < 0) /* caso ED */
      no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no); /* casos EE e ED */
  }

  if (fb < -1) {            /* pesado a direita */
    if (fator(no->dir) > 0) /* caso DE */
      no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no); /* casos DD e DE */
  }

  return no; /* ja estava equilibrado */
}

No *menorNo(No *no) {
  while (no != NULL && no->esq != NULL)
    no = no->esq;
  return no;
}

No *buscar(No *raiz, int chave) {
  while (raiz != NULL) {
    if (chave == raiz->chave)
      return raiz;
    if (chave < raiz->chave)
      raiz = raiz->esq;
    else
      raiz = raiz->dir;
  }
  return NULL;
}

int contarNos(No *raiz) {
  if (raiz == NULL)
    return 0;
  return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

void exibirEstatisticasRotacoes(void) {
  printf("\n=== Estatisticas Acumuladas de Rotacoes ===\n");
  printf("  Simples a Direita (EE) : %d\n", totalRotacoesEE);
  printf("  Simples a Esquerda (DD): %d\n", totalRotacoesDD);
  printf("  Dupla a Direita (ED)   : %d\n", totalRotacoesED);
  printf("  Dupla a Esquerda (DE)  : %d\n", totalRotacoesDE);
  // printf("  Total de rotacoes      : %d\n", obterTotalRotacoes());
  printf("===========================================\n");
}

/* Funcao auxiliar recursiva para desenhar a arvore com linhas de conexao
 * (ramos). Desenha a arvore deitada: filho direito acima (┌──), filho esquerdo
 * abaixo (└──). */
static void imprimirArvoreRec(No *raiz, char *prefixo, int eEsquerdo,
                              int eRaiz) {
  if (raiz == NULL)
    return;

  char novoPrefixo[512];

  /* 1. Subarvore direita (aparece acima no terminal) */
  if (raiz->dir != NULL) {
    if (eRaiz) {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s    ", prefixo);
    } else if (eEsquerdo) {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s│   ", prefixo);
    } else {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s    ", prefixo);
    }
    imprimirArvoreRec(raiz->dir, novoPrefixo, 0, 0);

    /* Linha conectora vertical para o filho direito (espacamento) */
    printf("%s│\n", novoPrefixo);
  }

  /* 2. No atual */
  printf("%s", prefixo);
  if (!eRaiz) {
    if (eEsquerdo) {
      printf("└── ");
    } else {
      printf("┌── ");
    }
  }
  printf("%d (h=%d, fb=%d)\n", raiz->chave, raiz->altura, fator(raiz));

  /* 3. Subarvore esquerda (aparece abaixo no terminal) */
  if (raiz->esq != NULL) {
    if (eRaiz) {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s    ", prefixo);
    } else if (eEsquerdo) {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s    ", prefixo);
    } else {
      snprintf(novoPrefixo, sizeof(novoPrefixo), "%s│   ", prefixo);
    }

    /* Linha conectora vertical para o filho esquerdo (espacamento) */
    printf("%s│\n", novoPrefixo);

    imprimirArvoreRec(raiz->esq, novoPrefixo, 1, 0);
  }
}

void imprimirArvore(No *raiz, int nivel) {
  if (raiz == NULL)
    return;

  char prefixoInicial[512] = "";
  int i;
  for (i = 0; i < nivel && i < 50; i++) {
    strcat(prefixoInicial, "    ");
  }

  imprimirArvoreRec(raiz, prefixoInicial, 0, 1);
}

void emOrdem(No *raiz) {
  if (raiz == NULL)
    return;
  emOrdem(raiz->esq);
  printf("%d ", raiz->chave);
  emOrdem(raiz->dir);
}

void preOrdem(No *raiz) {
  if (raiz == NULL)
    return;
  printf("%d ", raiz->chave);
  preOrdem(raiz->esq);
  preOrdem(raiz->dir);
}

/* Confere as tres regras de uma AVL de uma vez so. Devolve a altura da
 * subarvore, ou -2 para avisar que encontrou um problema. */
static int validarRec(No *no, int temMin, int min, int temMax, int max) {
  if (no == NULL)
    return -1;

  /* regra 1: ordenacao da arvore de busca */
  if (temMin && no->chave <= min)
    return -2;
  if (temMax && no->chave >= max)
    return -2;

  int he = validarRec(no->esq, temMin, min, 1, no->chave);
  if (he == -2)
    return -2;

  int hd = validarRec(no->dir, 1, no->chave, temMax, max);
  if (hd == -2)
    return -2;

  /* regra 2: o campo altura precisa estar correto */
  if (no->altura != 1 + maximo(he, hd))
    return -2;

  /* regra 3: o balanceamento nao pode passar de 1 */
  int fb = he - hd;
  if (fb < -1 || fb > 1)
    return -2;

  return no->altura;
}

int arvoreValida(No *raiz) { return validarRec(raiz, 0, 0, 0, 0) != -2; }

/* ############################################################################
 * ############################################################################
 *
 *                      A PARTIR DAQUI E COM VOCE
 *
 * ############################################################################
 * ########################################################################## */

/* ============================================================================
 *  TODO 1 - liberar
 *
 *  Libere a memoria de TODOS os nos da arvore.
 *
 *  Passos:
 *    1. se raiz for NULL, nao ha nada a fazer: apenas retorne
 *    2. libere a subarvore da esquerda (chamada recursiva)
 *    3. libere a subarvore da direita  (chamada recursiva)
 *    4. use free() para liberar o proprio no
 *
 *  CUIDADO com a ordem: os filhos precisam ser liberados ANTES do pai.
 *  Se voce liberar o pai primeiro, perde o endereco dos filhos e a memoria
 *  deles fica perdida (vazamento).
 *
 *  Este e o percurso em POS-ORDEM: esquerda, direita, raiz.
 * ========================================================================== */
void liberar(No *raiz) {
  if (raiz == NULL)
    return;
  liberar(raiz->esq);
  liberar(raiz->dir);
  free(raiz);
}

/* ============================================================================
 *  TODO 2 - rotacaoDireita
 *
 *  Aplique a rotacao simples a direita sobre o no y e devolva a nova raiz
 *  da subarvore.
 *
 *        y                x
 *       / \              / \
 *      x   C    ==>     A   y
 *     / \                  / \
 *    A   B                B   C
 *
 *  Passos:
 *    1. guarde  x = filho ESQUERDO de y
 *    2. guarde  B = filho DIREITO de x     (a subarvore que vai mudar de pai)
 *    3. faca o filho direito de x apontar para y
 *    4. faca o filho esquerdo de y apontar para B
 *    5. atualize a altura de y e DEPOIS a de x
 *       (nessa ordem: y agora esta abaixo de x, entao a altura dele precisa
 *        estar correta antes de x ser recalculado)
 *    6. devolva x, que passou a ser a raiz desta subarvore
 *
 *  Repare que a ordem das chaves nao muda: A < x < B < y < C antes e depois.
 *  A rotacao muda a FORMA da arvore, nunca a ORDEM.
 * ========================================================================== */
No *rotacaoDireita(No *y) {
  No *x = y->esq;
  No *B = x->dir;

  // rotacao
  x->dir = y;
  y->esq = B;

  // atualizar
  atualizarAltura(y);
  atualizarAltura(x);

  return x;
}

/* ============================================================================
 *  TODO 3 - rotacaoEsquerda
 *
 *  E o espelho do TODO 2. Aplique a rotacao simples a esquerda sobre x.
 *
 *      x                  y
 *     / \                / \
 *    A   y     ==>      x   C
 *       / \            / \
 *      B   C          A   B
 *
 *  Passos:
 *    1. guarde  y = filho DIREITO de x
 *    2. guarde  B = filho ESQUERDO de y
 *    3. faca o filho esquerdo de y apontar para x
 *    4. faca o filho direito de x apontar para B
 *    5. atualize a altura de x e DEPOIS a de y
 *    6. devolva y
 *
 *  DICA: pegue o seu TODO 2 e troque "esq" por "dir" em todo lugar.
 * ========================================================================== */
No *rotacaoEsquerda(No *x) {
  No *y = x->dir;
  No *B = y->esq;

  // rotacao
  y->esq = x;
  x->dir = B;

  // atualizar
  atualizarAltura(x);
  atualizarAltura(y);

  return y; /* provisorio, para o programa compilar: troque pelo certo */
}

/* ============================================================================
 *  TODO 4 - inserir
 *
 *  Insira a chave na posicao correta e devolva a nova raiz da subarvore.
 *
 *  Passos:
 *    1. se raiz for NULL, chegamos ao lugar certo:
 *       devolva criarNo(chave)
 *    2. se a chave for MENOR que a do no atual:
 *       raiz->esq = inserir(raiz->esq, chave);
 *    3. se a chave for MAIOR:
 *       raiz->dir = inserir(raiz->dir, chave);
 *    4. se for IGUAL, a chave ja existe: devolva raiz sem alterar nada
 *    5. antes de devolver, chame  return rebalancear(raiz);
 *
 *  O passo 5 e o que transforma uma arvore binaria de busca comum em AVL.
 *  Como ele acontece na VOLTA da recursao, o ajuste sobe da folha ate a raiz,
 *  corrigindo o primeiro no que ficou desequilibrado.
 * ========================================================================== */
No *inserir(No *raiz, int chave) {
  if (raiz == NULL)
    return criarNo(chave);

  if (chave < raiz->chave)
    raiz->esq = inserir(raiz->esq, chave);
  else if (chave > raiz->chave)
    raiz->dir = inserir(raiz->dir, chave);
  else
    return raiz;

  return rebalancear(raiz);
}

/* ============================================================================
 *  TODO 5 - remover
 *
 *  Remova a chave e devolva a nova raiz da subarvore.
 *  Se a chave nao existir, a arvore deve continuar igual.
 *
 *  Primeiro ACHE o no, como na insercao:
 *    1. se raiz for NULL, a chave nao existe: devolva NULL
 *    2. se a chave for MENOR:  raiz->esq = remover(raiz->esq, chave);
 *    3. se a chave for MAIOR:  raiz->dir = remover(raiz->dir, chave);
 *
 *  Quando ACHAR o no (chave igual), ha tres situacoes:
 *
 *    CASO 1 - o no nao tem filhos
 *    CASO 2 - o no tem apenas um filho
 *      Os dois casos se resolvem do mesmo jeito: guarde o filho que existe
 *      (ou NULL, se nao houver nenhum), libere o no com free() e devolva
 *      esse filho. Ele sobe e ocupa o lugar do pai.
 *
 *    CASO 3 - o no tem os dois filhos
 *      Nao da para puxar nenhum dos dois para cima, porque cada um tem sua
 *      propria subarvore. Entao:
 *        a) encontre o SUCESSOR com  menorNo(raiz->dir)
 *           (a menor chave da subarvore direita)
 *        b) copie a chave do sucessor para o no atual
 *        c) remova o sucessor da subarvore direita, chamando remover()
 *           de novo: raiz->dir = remover(raiz->dir, chave_do_sucessor);
 *      O sucessor nunca tem filho a esquerda (ele e o menor), entao essa
 *      segunda remocao sempre cai no CASO 1 ou 2 - nao entra em laco.
 *
 *  4. no final, antes de devolver, chame  return rebalancear(raiz);
 *
 *  ATENCAO: na remocao, uma unica rotacao pode nao ser suficiente. Por isso
 *  o rebalancear() precisa ser chamado na volta de TODOS os niveis - e nao
 *  so no primeiro no corrigido, como acontece na insercao.
 * ========================================================================== */
No *remover(No *raiz, int chave) {
  /* 1. Caso base: chave não encontrada */
  if (raiz == NULL)
    return NULL;

  /* 2. Busca recursiva */
  if (chave < raiz->chave) {
    raiz->esq = remover(raiz->esq, chave);
  } else if (chave > raiz->chave) {
    raiz->dir = remover(raiz->dir, chave);
  } else {

    // /* 3. Encontrou o nó */  fira code
    if (raiz->esq == NULL || raiz->dir == NULL) {
      No *filho = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
      free(raiz);
      return filho;
    }

    // dois filhos
    No *sucessor = menorNo(raiz->dir);
    raiz->chave = sucessor->chave;
    raiz->dir = remover(raiz->dir, sucessor->chave);
  }
  return rebalancear(raiz);
}
//  40, 20, 60, 10, 30, 50, 70
