/*
 * Author: Tobias Patzl
 * simple implementation of the caesar cipher
 * 
 * The key is the number of the places the alphabet is shifted, to create the cipher alphabet
 * Each letter is replaced with the letter on the same index in the cipher alphabet
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void caesar(char *plain, char *cipher, char key);
void shift(char *in, char *out, int n);
void rmspaces(char *str);

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s message key \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *plain = argv[1];
    
    if (argc > 3)
        if (!strcmp(argv[3], "--remove-spaces"))
            rmspaces(plain);

    char cipher[strlen(plain)];
    char key = atoi(argv[2]);

    if (key > 26 || key < 1) {
        fprintf(stderr, "key has to be between 1 and 26\n");
        exit(EXIT_FAILURE);
    }

    caesar(plain, cipher, key);
    
    printf("%s\n", plain);
    printf("%s\n", cipher);
    exit(EXIT_SUCCESS);
}

void caesar(char *plain, char *cipher, char key)
{
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipherbet[26];
    size_t i;

    shift(alphabet, cipherbet, key);

    for (i = 0; plain[i] != '\0'; ++i) {
        if (isspace(plain[i]))
           cipher[i] = plain[i]; 
        else
            cipher[i] = cipherbet[toupper(plain[i]) - 'A'];
    }
    cipher[i] = '\0';
}

/* ring shift the string by n places and write the result to out */
void shift(char *in, char *out, int n)
{
    size_t i;
    size_t size = strlen(in);

    for (i = 0; in[i] != '\0'; ++i)
        out[i] = in[i+n >= size ? i+n - size : i+n];
    out[i] = '\0';
}

/* remove all blanks from a string */
void rmspaces(char *str)
{
    char *i = str, *j = str;
    while(*j != 0)
    {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
}
