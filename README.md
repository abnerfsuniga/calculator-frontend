# Calculator frontend

O objetivo desta tarefa é implementar um frontend. Mais precisamente, o objetivo é implementar as
três fases de análise e um motor de execução.

1. Implemente o analisador léxico, utilizando a ferramenta flex.
2. Implemente o analisador sintático, utilizando a ferramenta bison.
3. Implemente o analisador semântico.
4. Implemente o motor de execução.

### Linguagem

A linguagem é composta por:
1. palavras reservadas: print
2. identificadores: nome de variáveis
3. números inteiros
4. números reais
5. símbolos: ( ) + - * / ^ , =1


Portanto o programa é composto por uma lista contendo expressões matemáticas e atribuições.

Exemplo 1:
```
a = (4-6) * 7 ^ 8
print a
```
Exemplo 2:
```
a = 10
b = 10,5
c = a + b
print c
```
Exemplo 3:
```
print 5*(5+7)
```
Exemplo 4:
```
5
```
Exemplo 5:
```
7 + 9
```
Todos estes exemplos são válidos.

### Considerações
1. Sua gramática deve considerar precedência de operadores.
2. Seu motor de execução deve processar a árvore sintática abstrata.
3. A saída da sua implementação é o resultado do processamento da árvore.
4. Seu frontend deve emitir erros de forma precisa, indicando linha e coluna além da descrição do
erro.
5. A entrada de seu programa é um arquivo.

### Exemplo de execução
```
./calculator -i <caminho_codigo> -d -a <arquivo_arvore>
```

**Observação**: a gramática atualmente **não** suporta linhas em branco entre as instruções
