#include <stdio.h>
#include <string.h>

#define NUMBER_OF_SYMBOLS 29
#define CONTENT_FILE 300
const char alphabet[NUMBER_OF_SYMBOLS] ={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '@', '.', ' '};


/*Cyphering function*/

char cipher(char c, int shift) {
    int is_index = -1;
    int new_index = 0;
    for (int j = 0; j < NUMBER_OF_SYMBOLS; j++){
        if (alphabet[j] == c) {
            is_index = j;
            break;
        }
    }
    if (is_index == -1) {
    printf("character not found...\n");
    return c;
    }

    new_index = (is_index + shift) % NUMBER_OF_SYMBOLS;
    return alphabet[new_index];
}

int main() {

char cipher_ask[CONTENT_FILE];
char key_ask[CONTENT_FILE];
char output[CONTENT_FILE];

printf("Ready to Cipher:\n");
if (fgets(cipher_ask, sizeof(cipher_ask),stdin) != NULL) {
    /*check for buffer overflow*/
    if (strchr(cipher_ask, '\n') == NULL) {
    int ch;
    while((ch =getchar()) != '\n' && ch != EOF) {}
    }
    if (cipher_ask[0] == '\n') {
        printf("you must enter something!");
        return 1;
}
cipher_ask[strcspn(cipher_ask, "\n")] = '\0';

printf("Please provide Key:\n");
if (fgets(key_ask, sizeof(key_ask),stdin) != NULL) {
    /*check for buffer overflow*/
    if (strchr(key_ask, '\n') == NULL) {
    int ch;
    while((ch =getchar()) != '\n' && ch != EOF) {}
        }
    if (key_ask[0] == '\n') {
        printf("you must enter something!");
        return 1;
        }
    key_ask[strcspn(key_ask, "\n")] = '\0';

        int key_length = strlen(key_ask);
    for(int i = 0; i < key_length; i++) {
        if (key_ask[i] < '0' || key_ask[i] > '9')
        {
            printf("You entered an invalid character. please enter numbers between 0-9.");
            return 1;
        }
        
    }



    int text_length = strlen(cipher_ask);
    for (int i = 0; i < text_length; i++) {
        int key_pos = i % key_length;
        int shift = key_ask[key_pos] - '0';
        output[i] = cipher(cipher_ask[i], shift);
    }
    output[text_length] = '\0';
    printf("%s\n", output);
        }
    }
}