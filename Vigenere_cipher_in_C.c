#include <stdio.h>
#include <string.h>

#define NUMBER_OF_SYMBOLS 29
#define CONTENT_FILE 300
#define MAX_KEYS 50
#define MAX_KEY_LENGTH 50
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
FILE *fptr;
fptr = fopen("keys.txt", "r");

if(fptr == NULL) {
    printf("Not able to open the file.");
    return 1;
}

char Content_of_file[CONTENT_FILE];
char *token;
int i = 0;
char keys[MAX_KEYS][MAX_KEY_LENGTH];

while (fgets(Content_of_file, CONTENT_FILE, fptr) != NULL) {
    Content_of_file[strcspn(Content_of_file, "\n")] = '\0';

    token = strtok(Content_of_file, ",");
    while(token != NULL) {
        strcpy(keys[i], token);
        i++;
        token = strtok(NULL, ",");
    }

}

fclose(fptr);

for (int j = 0; j < i; j++) {
    printf("[%s]\n", keys[j]);
    }

char text[] = "attack at dawn";
char output[CONTENT_FILE];
int text_length = strlen(text);
int key_length = strlen(keys[0]);
for (int i = 0; i < text_length; i++) {
    int key_pos = i % key_length;
    int shift = keys[0][key_pos] - '0';
    output[i] = cipher(text[i], shift);
}
output[text_length] = '\0';
printf("%s\n", output);






}