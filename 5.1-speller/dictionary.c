// Implementa a funcionalidade de um dicionário

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Representa um nó numa tabela hash
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Número de baldes na tabela hash
#define N 26

// Tabela Hash
node *table[N];

int dict_size = 0;

// Retorna verdadeiro se a palavra está no dicionário, senão falso
bool check(const char *word)
{
    int hash_value = hash(word);
    node *p = table[hash_value];

    while (p != NULL)
    {
        if (strcasecmp(word, p->word) == 0)
        {
            return true;
        }

        p = p->next;
    }
    return false;
}

// Faz o hash da palavra para um número
unsigned int hash(const char *word)
{
    /* Algoritmo djb2 por Dan Bernstring */
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Carga do dicionário na memória, retornando verdadeiro se bem sucedido, senão falso
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);

        int hash_value = hash(word);

        n->next = table[hash_value];
        table[hash_value] = n;
        dict_size++;
    }

    fclose(dict);
    return true;
}

// Devolve o número de palavras no dicionário se carregadas, ou 0 se ainda não carregadas
unsigned int size(void)
{
    if (dict_size > 0)
    {
        return dict_size;
    }
    return 0;
}

// Descarrega o dicionário da memória, retornando verdadeiro se bem sucedido, senão falso
bool unload(void)
{
    for(int i=0;i<N;i++)
    {
        node *tmp1=table[i];
        while(tmp1!=NULL)
        {
            node *tmp2 = tmp1;
            tmp1 = tmp1 -> next;
            free(tmp2);
        }
   }
    return true;
}
