/* ============================================================================
 *  avl_aluno.h - INTERFACE da arvore AVL  (ATIVIDADE)
 *  Estrutura de Dados 2 - IFMS
 *
 *  NAO E PRECISO ALTERAR ESTE ARQUIVO.
 *  Ele diz O QUE cada funcao faz; voce vai escrever o COMO em avl_aluno.c.
 *
 *  Cinco funcoes estao vazias esperando por voce:
 *
 *      1. liberar           (comece por esta)
 *      2. rotacaoDireita
 *      3. rotacaoEsquerda
 *      4. inserir
 *      5. remover
 *
 *  Todas as outras ja estao prontas e podem ser usadas a vontade.
 * ========================================================================== */

#ifndef AVL_ALUNO_H        /* protecao contra inclusao repetida deste arquivo */
#define AVL_ALUNO_H

/* ============================================================================
 *  ESTRUTURA
 * ========================================================================== */

/* Cada no guarda a propria altura, para que o balanceamento possa ser
 * verificado em tempo constante.
 *
 * Convencao de altura usada em toda a atividade:
 *      arvore vazia (NULL) .... altura -1
 *      folha .................. altura  0
 */
typedef struct No {
    int         chave;
    int         altura;
    struct No  *esq;
    struct No  *dir;
} No;

/* ============================================================================
 *  PARTE 1 - VOCE VAI IMPLEMENTAR ESTAS
 * ========================================================================== */

/* Insere a chave e devolve a nova raiz da subarvore.
 * Chaves repetidas devem ser ignoradas.
 *
 * ATENCAO: devolve a NOVA raiz porque, depois de uma rotacao, o no do topo
 * pode ter mudado. Quem chama deve escrever  raiz = inserir(raiz, valor); */
No *inserir(No *raiz, int chave);

/* Remove a chave e devolve a nova raiz da subarvore.
 * Se a chave nao existir, a arvore fica como estava. */
No *remover(No *raiz, int chave);

/* Libera a memoria de todos os nos da arvore. */
void liberar(No *raiz);

/* Rotacao simples a direita sobre y. Devolve a nova raiz da subarvore.
 *
 *        y                x
 *       / \              / \
 *      x   C    ==>     A   y
 *     / \                  / \
 *    A   B                B   C
 */
No *rotacaoDireita(No *y);

/* Rotacao simples a esquerda sobre x. Devolve a nova raiz da subarvore.
 *
 *      x                  y
 *     / \                / \
 *    A   y     ==>      x   C
 *       / \            / \
 *      B   C          A   B
 */
No *rotacaoEsquerda(No *x);

/* ============================================================================
 *  PARTE 2 - JA PRONTAS, PODE USAR
 * ========================================================================== */

/* Devolve o maior entre dois inteiros. */
int maximo(int a, int b);

/* Altura de um no: -1 se for NULL, 0 se for folha. */
int altura(No *no);

/* Recalcula a altura de um no a partir da altura dos filhos.
 * Chame sempre que os filhos de um no mudarem. */
void atualizarAltura(No *no);

/* Fator de balanceamento = altura(esq) - altura(dir).
 *      0, +1 ou -1  -> no equilibrado
 *      > +1         -> pesado para a esquerda, precisa rotacionar
 *      < -1         -> pesado para a direita,  precisa rotacionar
 */
int fator(No *no);

/* Cria um no novo, ja como folha (altura 0), com os dois filhos NULL. */
No *criarNo(int chave);

/* Aplica a rotacao adequada quando o no esta desequilibrado.
 * Devolve a raiz da subarvore, que pode ter mudado.
 * Use esta funcao no final de inserir e de remover. */
No *rebalancear(No *no);

/* Devolve o no de menor chave de uma subarvore (o mais a esquerda).
 * Util na remocao de um no que tem dois filhos. */
No *menorNo(No *no);

/* Procura a chave. Devolve o no encontrado, ou NULL se ela nao existir. */
No *buscar(No *raiz, int chave);

/* Quantidade de nos da arvore. */
int contarNos(No *raiz);

/* Desenha a arvore DEITADA: a raiz fica na margem esquerda, o filho direito
 * aparece acima e o esquerdo abaixo. Comece a chamada com nivel = 0. */
void imprimirArvore(No *raiz, int nivel);

/* Percurso em ordem (esquerda, raiz, direita): sai em ordem crescente. */
void emOrdem(No *raiz);

/* Percurso em pre-ordem (raiz, esquerda, direita): mostra a estrutura. */
void preOrdem(No *raiz);

/* Verifica se a arvore respeita as regras da AVL: ordenacao correta,
 * alturas corretas e |fator| <= 1 em todo no.
 * Use para conferir seu trabalho - devolve 1 se estiver tudo certo. */
int arvoreValida(No *raiz);

#endif /* AVL_ALUNO_H */

/* Estatisticas */
static void registrarRotacao(const char *tipo, int chaveNo);

// print est.
void exibirEstatisticasRotacoes(void);
