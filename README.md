# Estrutura de Dados II — ENG4 — 2026/2

Repositório da disciplina de **Estrutura de Dados II**, turma ENG4, segundo
semestre de 2026 — IFMS (Instituto Federal de Mato Grosso do Sul).

## Para que serve este repositório

Aqui são compartilhados os **materiais das aulas** e os **exercícios
pré-preenchidos** da disciplina.

Os exercícios chegam com o esqueleto pronto: a estrutura de dados, as funções
auxiliares e um programa de teste com menu já estão implementados. Você escreve
as partes marcadas com `TODO` — que são exatamente os algoritmos estudados em
aula. Assim o tempo é gasto no que interessa (o algoritmo), e não em montar
menu, leitura de teclado ou impressão.

A cada tópico do semestre, uma nova pasta é publicada aqui.

## Ementa

| # | Tópico |
|---|--------|
| 1 | Árvores |
| 2 | Árvores AVL |
| 3 | Árvores Rubro-Negras |
| 4 | Árvores B |
| 5 | Árvores B* |
| 6 | Tabelas Hash |

## Conteúdo disponível

| Pasta | Conteúdo | Situação |
|-------|----------|----------|
| [`aluno/`](aluno) | Árvores AVL — inserção, remoção, rotações e liberação de memória | disponível |

As demais pastas serão publicadas conforme o semestre avançar.

## Como usar

```bash
git clone https://github.com/jrcampos82/Estrutura_Dados_II_ENG4_2026-2.git
cd Estrutura_Dados_II_ENG4_2026-2/aluno

make        # compila
./avl_aluno # executa
```

Ou, de uma vez só:

```bash
make run
```

O programa abre um menu com as opções de **inserir**, **remover** e
**imprimir**. Ele compila e roda desde o primeiro momento, mesmo antes de você
escrever qualquer coisa — só que ainda sem fazer nada de útil. Implemente uma
função de cada vez e vá testando pelo menu.

### Dica

A opção **3 (Imprimir)** desenha a árvore com a altura (`h`) e o fator de
balanceamento (`fb`) de cada nó, e ainda avisa automaticamente se a árvore
deixou de ser uma AVL válida:

```
        30 (h=0, fb=0)
20 (h=1, fb=0)
        10 (h=0, fb=0)

Verificacao      : OK, e uma AVL valida.
```

Use isso para conferir seu trabalho sem precisar esperar a correção.

## Requisitos

- Compilador C (`gcc` ou `clang`)
- `make`

**Linux:** `sudo apt install build-essential`

**macOS:** `xcode-select --install`

**Windows:** instale o [MSYS2](https://www.msys2.org) e, no terminal
*MSYS2 MinGW 64-bit*, execute:

```bash
pacman -S mingw-w64-x86_64-gcc make git
```

No Windows, use o terminal do MSYS2 ou o Git Bash para rodar o `make` — o
`cmd.exe` e o PowerShell não entendem os comandos usados pelo Makefile.

## Entrega dos exercícios

Siga as orientações passadas em aula. Antes de entregar, confira se:

- [ ] o programa **compila sem erros** (`make` não pode falhar);
- [ ] o programa **compila sem avisos** (nenhuma mensagem de *warning*);
- [ ] a opção 3 do menu diz **"OK, e uma AVL valida"** depois de várias
      inserções e remoções;
- [ ] seu **nome e turma** estão preenchidos no cabeçalho do arquivo.

---

*IFMS — Estrutura de Dados II — ENG4 — 2026/2*
