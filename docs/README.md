# Indexação baseada em hash

## Principais características

- Excelentes para **seleções de igualdade**;
- Usa uma **função hashing** que mapeia valores em um campo de pesquisa para um intervalo de **números de bucket**.
- **Não suportam pesquisas por intervalo**;
- São muito úteis em implementações de operações relacionais como junções (Maiores detalhes no capítulo 14 do livro Sistemas de Gerenciamento de
  Banco de Dados, Terceira Edição, de Ramakrishnan e Gehrke);
- **Buckets** serão compostos por entradas de dados (Descritas no capítulo 8 do livro Sistemas de Gerenciamento de
  Banco de Dados, Terceira Edição, de Ramakrishnan e Gehrke)

## Tipos

- **Hashing Estático**: Uma técnica que utiliza **páginas de overflow**, o que **afeta seu desempenho**;
- **Hashing Extensível**: Usa uma abordagem de **diretório** o qual suporta **inserções e exclusões**, resolvendo assim
  o problema com páginas de overflow;
- **Hashing Linear**: Não será abordado. Para mais detalhes veja a seção 11.3 do livro Sistemas de Gerenciamento de
  Banco de Dados, Terceira Edição, de Ramakrishnan e Gehrke.

## Operações

- **Pesquisa por entrada de dados**¹: Apricado a função hash em $h$, identificado o bucket a qual pertence.

Demais operações serão mais específicas de cada um dos tipos de hashing utilizados.

¹ Para que seja acelerada a pesquisa é possível manter as **entradas de dados ordenada pela chave de busca**.

## A função hash

Uma função que deve distribuir valores no domínio do campo de pesquisa uniformemente sobre uma coeleção de buckets.