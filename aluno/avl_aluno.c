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

/* ============================================================================
 *  FUNCOES JA PRONTAS - nao precisa mexer
 * ========================================================================== */

int maximo(int a, int b)
{
    // implementar aqui
    return 0;
}

int altura(No *no)
{
    if (no == NULL)
        return -1;                /* arvore vazia tem altura -1 */
    return no->altura;
}

void atualizarAltura(No *no)
{
    no->altura = 1 + maximo(altura(no->esq), altura(no->dir));
}

int fator(No *no)
{
    // calcular a altura
    return 0;
}

No *criarNo(int chave)
{
    // critar NO
    return NULL;
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
No *rebalancear(No *no)
{
    atualizarAltura(no);

    int fb = fator(no);

    if (fb > 1) {                                /* pesado a esquerda */
        if (fator(no->esq) < 0)                  /* caso ED */
            no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);               /* casos EE e ED */
    }

    if (fb < -1) {                               /* pesado a direita */
        if (fator(no->dir) > 0)                  /* caso DE */
            no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);              /* casos DD e DE */
    }

    return no;                                   /* ja estava equilibrado */
}

No *menorNo(No *no)
{
    while (no != NULL && no->esq != NULL)
        no = no->esq;
    return no;
}

No *buscar(No *raiz, int chave)
{
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

int contarNos(No *raiz)
{
    if (raiz == NULL)
        return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

void imprimirArvore(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;

    imprimirArvore(raiz->dir, nivel + 1);        /* direita em cima */

    int i;
    for (i = 0; i < nivel; i++)
        printf("        ");
    printf("%d (h=%d, fb=%d)\n", raiz->chave, raiz->altura, fator(raiz));

    imprimirArvore(raiz->esq, nivel + 1);        /* esquerda embaixo */
}

void emOrdem(No *raiz)
{
    if (raiz == NULL)
        return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
}

void preOrdem(No *raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

/* Confere as tres regras de uma AVL de uma vez so. Devolve a altura da
 * subarvore, ou -2 para avisar que encontrou um problema. */
static int validarRec(No *no, int temMin, int min, int temMax, int max)
{
    if (no == NULL)
        return -1;

    /* regra 1: ordenacao da arvore de busca */
    if (temMin && no->chave <= min) return -2;
    if (temMax && no->chave >= max) return -2;

    int he = validarRec(no->esq, temMin, min, 1, no->chave);
    if (he == -2) return -2;

    int hd = validarRec(no->dir, 1, no->chave, temMax, max);
    if (hd == -2) return -2;

    /* regra 2: o campo altura precisa estar correto */
    if (no->altura != 1 + maximo(he, hd)) return -2;

    /* regra 3: o balanceamento nao pode passar de 1 */
    int fb = he - hd;
    if (fb < -1 || fb > 1) return -2;

    return no->altura;
}

int arvoreValida(No *raiz)
{
    return validarRec(raiz, 0, 0, 0, 0) != -2;
}

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
void liberar(No *raiz)
{
    (void) raiz;    /* apague esta linha quando implementar */

    /* escreva sua implementacao aqui */
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
No *rotacaoDireita(No *y)
{
    /* escreva sua implementacao aqui */

    return y;       /* provisorio, para o programa compilar: troque pelo certo */
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
No *rotacaoEsquerda(No *x)
{
    /* escreva sua implementacao aqui */

    return x;       /* provisorio, para o programa compilar: troque pelo certo */
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
No *inserir(No *raiz, int chave)
{
    (void) chave;   /* apague esta linha quando implementar */

    /* escreva sua implementacao aqui */

    return raiz;    /* provisorio, para o programa compilar */
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
No *remover(No *raiz, int chave)
{
    (void) chave;   /* apague esta linha quando implementar */

    /* escreva sua implementacao aqui */

    return raiz;    /* provisorio, para o programa compilar */
}
