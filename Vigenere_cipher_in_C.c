#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER_OF_SYMBOLS 29
#define CONTENT_FILE 300
const char alphabet[NUMBER_OF_SYMBOLS] ={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '@', '.', ' '};

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

char decipher(char c, int shift) {
    int is_index = -1;
    int new_index = 0;
    for (int k = 0; k < NUMBER_OF_SYMBOLS; k++){
        if (alphabet[k] == c) {
            is_index = k;
            break;
        }
    }
    if (is_index == -1) {
        printf("character not found...\n");
        return c;
    }

    new_index = (is_index - shift + NUMBER_OF_SYMBOLS) % NUMBER_OF_SYMBOLS;
    return alphabet[new_index];
}

int input_read(char buffer[], int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        /*checking for bof*/
        if (strchr(buffer, '\n') == NULL) {
            int ch;
            while((ch=getchar()) != '\n' && ch !=EOF) {}
            }

        if (buffer[0] == '\n') {
            printf("Please Enter Something.\n");
            return 0;
            }
            buffer[strcspn(buffer, "\n")] =  '\0';
            return 1;
        }
    return 0;
}

int key_val(char key[]){
    int key_length = strlen(key);
    for (int i = 0; i < key_length; i++){
        if (key[i] < '0' || key[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int main() {

char choice_prompt[10];
char cipher_ask[CONTENT_FILE];
char output[CONTENT_FILE];
printf("Type: cipher \\ Decipher\n");
if (input_read(choice_prompt, sizeof(choice_prompt))) {
char key_ask[CONTENT_FILE];
    /* this is the big one*/
    for ( int i = 0; i < strlen(choice_prompt); i++ ) {
        choice_prompt[i] = tolower(choice_prompt[i]);
    }
    if ( strcmp(choice_prompt, "cipher") == 0) {
        printf("Ready to Cipher:\n");
       if (input_read(cipher_ask, sizeof(cipher_ask))) {
    printf("Please provide Key:\n");
    if (input_read(key_ask, sizeof(key_ask))) {
        int key_length = strlen(key_ask);
        if (!key_val(key_ask)) {
            printf("You entered an Invalid character, please enter numbers between 0-9\n");
            return 1;
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
        } else if (strcmp(choice_prompt, "decipher") == 0) {
                printf("Ready to Decipher:\n");
                if (input_read(cipher_ask, sizeof(cipher_ask))) {
                printf("Please provide a Key:\n");
                if (input_read(key_ask, sizeof(key_ask))) {
                    int key_length = strlen(key_ask);
                    if (!key_val(key_ask)){
                        printf("You entered an Invalid character, please enter numbers between 0-9\n");
                        return 1;
                    }
                int text_length = strlen(cipher_ask);
                for (int i = 0; i < text_length; i++) {
                    int key_pos = i % key_length;
                    int shift = key_ask[key_pos] - '0';
                    output[i] = decipher(cipher_ask[i], shift);
                    }
                output[text_length] = '\0';
                printf("%s\n", output);
                }       
            }
        }else 
            printf("input must be cipher or decipher.");
            return 1;
    }
}