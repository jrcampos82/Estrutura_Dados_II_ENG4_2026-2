# ============================================================================
#  Arvore AVL - ATIVIDADE
#  Estrutura de Dados 2 - IFMS
#
#     make          compila o programa
#     make run      compila e ja executa
#     make clean    apaga o executavel e os arquivos .o
#
#  Voce nao precisa alterar este arquivo.
# ============================================================================

CC     = gcc

# -Wall e -Wextra ligam avisos do compilador que ajudam a achar erros.
# -g inclui informacao de depuracao (para usar o gdb, se precisar).
CFLAGS = -Wall -Wextra -g
PROG   = avl_aluno
OBJS   = main_aluno.o avl_aluno.o

# Suporte a argumentos para 'make run' (ex: make run 15)
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

# Alvo principal: liga os dois .o e gera o executavel
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

# Cada .c vira um .o. Os dois dependem de avl_aluno.h: se o cabecalho mudar,
# os dois sao recompilados.
main_aluno.o: main_aluno.c avl_aluno.h
	$(CC) $(CFLAGS) -c main_aluno.c

avl_aluno.o: avl_aluno.c avl_aluno.h
	$(CC) $(CFLAGS) -c avl_aluno.c

run: $(PROG)
	./$(PROG)

clean:
	rm -f $(PROG) $(OBJS)

.PHONY: run clean
