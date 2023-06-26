# Projeto Final Tabela Hash - Estrutura de Dados

Trabalho Final: Implementação de uma Tabela de Espalhamento (Tabela Hash)

## Execução
Pode-se usar um compilador online de C, recomenda-se usar o [Replit](https://replit.com/), mas também pode-se compilar utilizando o gcc e executando o arquivo gerado como administrador.

```bash
gcc -o tabelaHash tabelaHash.c 
```

## Relatório

### Introdução

Neste trabalho, foi necessário implementar uma tabela de espalhamento, também conhecida como tabela hash, com tratamento de colisão. A tabela hash é uma estrutura de dados que permite o armazenamento eficiente de elementos com base em suas chaves. O tratamento de colisão se faz necessário quando dois ou mais elementos são mapeados para a mesma posição na tabela. Neste relatório, será apresentada a metodologia utilizada para resolver esse problema, desde a escolha da função de hash até a análise da distribuição dos elementos pela tabela.

### Escolha da Função de Hash

A primeira etapa foi escolher uma função de hash adequada para distribuir os elementos uniformemente na tabela. Existem várias opções de funções de hash, como a função modular, função multiplicativa, entre outras. No presente trabalho, optou-se pela função de hash modular. Nessa função, a chave é convertida em um valor numérico e é calculada a soma dos valores ASCII dos caracteres do nome.

```c
int hash(char *dado)
{
	int i, chave = 0;
	for (i = 0; i < strlen(dado); i++)
	{
		chave += dado[i] * 7;
	}
	return (chave % M);
}
```

### Implementação da Tabela Hash

Com a função de hash definida, foi necessário implementar a estrutura da tabela hash. Definimos o tamanho da tabela como 53, uma vez que a quantidade de chaves seria igual a 53. Optamos por utilizar uma lista encadeada dupla para lidar com as colisões. Cada posição da tabela contém um ponteiro para o primeiro elemento da lista encadeada correspondente. Além disso, cada elemento da lista possui ponteiros para o próximo e para o elemento anterior.

### Tratamento de colisões

O tratamento de colisão foi implementado através do encadeamento separado. Quando ocorre uma colisão, ou seja, quando dois elementos são mapeados para a mesma posição da tabela, os elementos são inseridos sequencialmente na lista duplamente encadeada correspondente àquela posição. Dessa forma, é possível armazenar múltiplos elementos na mesma posição sem perder informações.


### Análise da Tabela Hash

Após a implementação da tabela hash, foi realizada uma análise para verificar se a hipótese do hashing uniforme foi alcançada. A hipótese do hashing uniforme estabelece que cada chave tem a mesma probabilidade de ser mapeada para qualquer posição da tabela. Para avaliar isso, foi gerado um histograma de frequência das chaves da tabela.

![image](https://github.com/matheuspossenti/tabelaHash/assets/84344863/5e505621-d596-4f67-8eb5-951ede88931b)


O histograma de frequência permite visualizar a distribuição dos elementos pelas posições da tabela hash. Um histograma adequado apresentaria uma distribuição uniforme, indicando que os elementos estão espalhados de forma igualmente aleatória pelas posições da tabela. Por outro lado, um histograma desigual indicaria colisões e uma distribuição não uniforme dos elementos.

### Conclusão

A metodologia utilizada para implementar a tabela hash com tratamento de colisão envolveu a escolha da função de hash, a implementação da estrutura da tabela com lista encadeada dupla e o tratamento de colisão através do encadeamento. A análise da tabela foi realizada através do histograma de frequência, que permitiu avaliar a distribuição dos elementos. Com base na análise do histograma, podemos concluir que a hipótese do hashing uniforme foi alcançada, uma vez que a distribuição dos elementos foi uniforme nas posições da tabela hash.

Essa metodologia permitiu a implementação de uma tabela hash eficiente, com tratamento de colisão adequado. No entanto, é importante ressaltar que a escolha da função de hash, o tamanho da tabela e a estratégia de tratamento de colisão podem variar dependendo das características dos dados e dos requisitos específicos do problema.
