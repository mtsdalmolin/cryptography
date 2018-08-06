#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void trocaCaracter(char* a, char* b )
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void ordenaChave(char* chave)
{
	for (unsigned int i = 0; i < strlen(chave) - 1; i++)
		for (unsigned int j = i + 1; j < strlen(chave); j++)
			if (chave[i] > chave[j])
				trocaCaracter(&chave[i], &chave[j]);
}

void zeraString(char* mensagemCodificada, char* mensagemFinal)
{
	for (int i = 0; i < 200; ++i)
	{
		mensagemCodificada[i] = 0;
		mensagemFinal[i] = 0;
	}
}

void tiraEspacos(char* mensagemCodificada, char* mensagemBase)
{
	for (int i = 0, j = 0; i < strlen(mensagemBase); i++)
		if (mensagemBase[i] != ' ')
		{
			mensagemCodificada[j] = mensagemBase[i];
			j++;
		}
}

void codificaMsg(char* mensagemBase, char* mensagemCodificada, char* tabelaBase, char* tabelaCodificacao)
{
	for (int i = 0; i < strlen(mensagemBase); i++)
		for (int j = 0; j < 26; j++)
			if (tolower(mensagemCodificada[i]) == tabelaBase[j])
				mensagemCodificada[i] = tabelaCodificacao[j];
}

void tabelaChaveMsg(int linhasMatriz, int colunasMatriz, char* chave, char** matriz, char* mensagemCodificada, char* tabelaBase)
{
	for (int i = 0, k = 0; i < linhasMatriz; ++i)
	{
		for (int j = 0; j < colunasMatriz; ++j)
		{
			if (!i)
				matriz[i][j] = chave[j];
			else if (k >= strlen(mensagemCodificada))
				matriz[i][j] = tabelaBase[rand() % 26];
			else
			{
				matriz[i][j] = mensagemCodificada[k];
				++k;
			}
		}
	}
}

int main()
{
	int linhasMatriz;
	int colunasMatriz;
	char tabelaBase[26] =        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char tabelaCodificacao[26] = {'8', 'F', 'H', 'G', '3', 'l', '1', 'L', 'E', 'I', 'w', 'o', 'M', 'x', '6', 'Q', 'P', 'b', 'V', '9', 'a', 'Z', 'S', 'D', 'j', 'r'};
	char mensagemBase[200];
	char mensagemCodificada[200];
	char mensagemFinal[200];
	char chave[20];
	char chaveOrdenada[20];
	char** matriz;

	srand(time(NULL));

	zeraString(mensagemCodificada, mensagemBase);

	printf("Digite a mensagem.\n");
	gets(mensagemBase);

	printf("Digite a chave.\n");
	gets(chave);

	tiraEspacos(mensagemCodificada, mensagemBase);

	if (strlen(mensagemCodificada) % strlen(chave) == 0)
	{
		linhasMatriz = strlen(mensagemCodificada) / strlen(chave) + 1;
		colunasMatriz = strlen(chave);
		matriz = (char**) malloc(linhasMatriz * sizeof(char*));

		for (int i = 0; i < linhasMatriz; ++i)
			matriz[i] = (char*) malloc(colunasMatriz * sizeof(char));
	} else {
		linhasMatriz = strlen(mensagemCodificada) / strlen(chave) + 2;
		colunasMatriz = strlen(chave);
		matriz = (char**) malloc(linhasMatriz * sizeof(char*));

		for (int i = 0; i < linhasMatriz; ++i)
			matriz[i] = (char*) malloc(colunasMatriz * sizeof(char));
	}

	// transposição de colunas com chave
	tabelaChaveMsg(linhasMatriz, colunasMatriz, chave, matriz, mensagemCodificada, tabelaBase);

	printf("\n---Tabela---\n");
	for (int i = 0; i < linhasMatriz; ++i)
	{
		for (int j = 0; j < colunasMatriz; ++j)
		{
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}

	// chama a função de substituição homófona
	codificaMsg(mensagemBase, mensagemCodificada, tabelaBase, tabelaCodificacao);

	strcpy(chaveOrdenada, chave);
	ordenaChave(chaveOrdenada);

	// pega as colunas da tabela gerada
	for (int i = 0, k = 0; i < strlen(chaveOrdenada); ++i)
	{
		for (int j = 0; j < colunasMatriz; ++j)
		{
			if (chaveOrdenada[i] == matriz[0][j])
				for (int l = 0; l < linhasMatriz; ++l)
				{
					mensagemCodificada[k] = matriz[l][j];
					++k;
				}
		}
	}

	// separa a msg em partes de 5
	for (int i = 0, j = 0, k = 0; i < strlen(mensagemCodificada); ++i, ++k)
	{
		if (j == 5)
		{
			mensagemFinal[k] = ' ';
			j = 0;
			--i;
		} else {
			mensagemFinal[k] = mensagemCodificada[i];
			++j;
		}
	}

	printf("\nMensagem Base:\n\t%s\n", mensagemBase);
	printf("Chave:\n\t%s\n", chave);
	printf("Mensagem Final:\n\t%s\n", mensagemFinal);

	return 0;
}