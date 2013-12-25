#include <stdio.h>
#include <string.h>
#include <ctype.h>

void atbash(char* plain, char* cipher);

int main(int argc, char *argv[])
{
    if (argc != 2)  {
        fprintf(stderr, "usage: %s \"text to encrypt\"\n", argv[0]);
        return 1;
    }
    char* plain = argv[1];
    char cipher[strlen(plain)];

    atbash(plain, cipher);

    printf("%s\n", plain);
    printf("%s\n", cipher);

    return 0;
}

void atbash(char* plain, char* cipher)
{
    size_t i;
    int dist;

    for (i = 0; plain[i] != '\0' ; ++i)
    {
        if (isspace(plain[i]))
            cipher[i] = plain[i];
        else {
            dist = toupper(plain[i]) - 'A';
            cipher[i] = 'Z' - dist;
        }
    }
    cipher[i] = '\0';
}
