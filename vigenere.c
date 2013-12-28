/* 
 * Author: Tobias Patzl
 * simple implementation of the Vigenere cipher [1]
 *
 * The Vigenere square contains all 26 Caesar ciphers.
 * The plaintext message is encrypted with some of them.
 * A keyword is used to determine which Caesar cipher should be used for each letter.
 * The characters of the keyword are repeated to match the length of the plaintext message, so that 
 * there is one letter of the keyword for each letter of the plaintext message.
 * Each letter is ciphered with the Caesar cipher that starts with the corresponding letter from the keyword.
 *
 * [1] https://en.wikipedia.org/wiki/Vigenere_cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void encrypt(char *plain, char *cipher, char *keyword);
void decrypt(char *cipher, char *plain, char *keyword);
void rmspaces(char *str);
void repeat(char *word, char *rword, int n);
void strtoupper(char *str);
size_t strindex(char *str, char c);

char vigsquare[26][27] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "BCDEFGHIJKLMNOPQRSTUVWXYZA",
    "CDEFGHIJKLMNOPQRSTUVWXYZAB",
    "DEFGHIJKLMNOPQRSTUVWXYZABC",
    "EFGHIJKLMNOPQRSTUVWXYZABCD",
    "FGHIJKLMNOPQRSTUVWXYZABCDE",
    "GHIJKLMNOPQRSTUVWXYZABCDEF",
    "HIJKLMNOPQRSTUVWXYZABCDEFG",
    "IJKLMNOPQRSTUVWXYZABCDEFGH",
    "JKLMNOPQRSTUVWXYZABCDEFGHI",
    "KLMNOPQRSTUVWXYZABCDEFGHIJ",
    "LMNOPQRSTUVWXYZABCDEFGHIJK",
    "MNOPQRSTUVWXYZABCDEFGHIJKL",
    "NOPQRSTUVWXYZABCDEFGHIJKLM",
    "OPQRSTUVWXYZABCDEFGHIJKLMN",
    "PQRSTUVWXYZABCDEFGHIJKLMNO",
    "QRSTUVWXYZABCDEFGHIJKLMNOP",
    "RSTUVWXYZABCDEFGHIJKLMNOPQ",
    "STUVWXYZABCDEFGHIJKLMNOPQR",
    "TUVWXYZABCDEFGHIJKLMNOPQRS",
    "UVWXYZABCDEFGHIJKLMNOPQRST",
    "VWXYZABCDEFGHIJKLMNOPQRSTU",
    "WXYZABCDEFGHIJKLMNOPQRSTUV",
    "XYZABCDEFGHIJKLMNOPQRSTUVW",
    "YZABCDEFGHIJKLMNOPQRSTUVWX",
    "ZABCDEFGHIJKLMNOPQRSTUVWXY", 
};

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "usage: %s mode message keyword [--remove-spaces]\n", argv[0]);
        fprintf(stderr, "    where mode is either encrypt or decrypt\n");
        exit(EXIT_FAILURE);
    }

    char *in = argv[2];
    if (argc > 4)
        if (!strcmp(argv[4], "--remove-spaces"))
            rmspaces(in);

    char out[strlen(in)];
    char *keyword = argv[3];

    printf("%s\n", in);

    if (!strcmp(argv[1], "encrypt"))
        encrypt(in, out, keyword);
    else if (!strcmp(argv[1], "decrypt"))
        decrypt(in, out, keyword);
    else {
        fprintf(stderr, "unrecognized mode: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("%s\n", out);

    exit(EXIT_SUCCESS);
}

void encrypt(char *plain, char *cipher, char *keyword)
{
    int len = strlen(plain);
    char rkeyword[len]; 
    size_t i;

    strtoupper(plain);
    repeat(keyword, rkeyword, len); 
    strtoupper(rkeyword);

    for (i = 0; i < len; ++i) {
        if(isspace(plain[i]))
            cipher[i] = plain[i];
        else
            cipher[i] = vigsquare[rkeyword[i] - 'A'][plain[i] - 'A'];
    }
    cipher[i] = '\0';
}

void decrypt(char *cipher, char *plain, char *keyword)
{
    int len = strlen(cipher);
    char rkeyword[len]; 
    size_t i;
    int index;

    strtoupper(cipher);
    repeat(keyword, rkeyword, len); 
    strtoupper(rkeyword);

    for (i = 0; i < len; ++i) {
        if (isspace(cipher[i]))
            plain[i] = cipher[i];
        else { 
            index = strindex(vigsquare[rkeyword[i] - 'A'], cipher[i]);
            plain[i] = vigsquare[0][index];
        }
    }
    plain[i] = '\0';
}

/* repeat:  repeat the character sequence of word into rword until the length of rword is n */
void repeat(char *word, char *rword, int n)
{
     size_t wordlen = strlen(word);
     size_t i;
     size_t j = 0; /* holds the index of the next free char in the repeated word */

     for (i = 0; j != n ; ++i)
     {
         if (i == wordlen)
             i = 0;
         rword[j++] = word[i];
         rword[j] = '\0';
     }
}

/* rmspaces: remove all blanks from a string */
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

/* strtoupper: make all characters of the string str uppercase */
void strtoupper(char *str)
{
    while (*str != '\0') {
        *str = toupper((unsigned char)*str);
        *str++;
    }
}

/* strindex: return the index of the first occurance of the character c in the string str */
size_t strindex(char *str, char c)
{
    size_t i;
    for (i = 0; str[i] != '\0'; ++i)
        if (str[i] == c)
            return i;
    return -1;
}

