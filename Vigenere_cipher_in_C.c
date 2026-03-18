#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_OF_SYMBOLS 29
#define CONTENT_FILE 20000
#define MAX_KEYS 50
#define MAX_KEY_LENGTH 50
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

int file_read(char path[], char buffer[], int size){
    FILE *pF = fopen(path, "r");
    char temp_buffer[CONTENT_FILE]; /*to append temporarily to hold lines?*/

    if (pF == NULL)
    {
        printf("Unable to open file!\n");
        return 0;
    }

    buffer[0] = '\0';
    while (fgets(temp_buffer, sizeof(temp_buffer), pF) != NULL)
    {
        temp_buffer[strcspn(temp_buffer, "\n")] = '\0';
        if (strlen(buffer) + strlen(temp_buffer) + 1 > size) {
            fclose(pF);
            printf("cant continue reading, buffer will overflow!!!\n");
            return 0;
        }
        strcat(buffer, temp_buffer);
    }
    fclose(pF);
    return 1;
}

int key_read(char path[], char keys[][MAX_KEY_LENGTH], int max_keys) {
FILE *fptr;
fptr = fopen(path, "r");

if(fptr == NULL) {
    printf("Not able to open the file.");
    return 0;
}

char Content_of_file[CONTENT_FILE];
char *token;
int i = 0;

while (fgets(Content_of_file, CONTENT_FILE, fptr) != NULL) {
    Content_of_file[strcspn(Content_of_file, "\n")] = '\0';

    token = strtok(Content_of_file, ",");
    while(token != NULL) {
        if ( i >=max_keys) {
            fclose(fptr);
            return i;
        }

        strcpy(keys[i], token);
        i++;
        token = strtok(NULL, ",");
    }

}

fclose(fptr);
return i;
}

int create_file_results(char path[], char original_text[], char key[], char result_output[]) {
    FILE *pF = fopen(path, "w");

    if (pF == NULL) {
        printf("Unable to create the file.\n");
        return 0;
    }

    fprintf(pF, "original:\n%s\n\n", original_text);
    fprintf(pF, "Key:\n%s\n\n", key);
    fprintf(pF, "Coded//Decoded:\n%s\n", result_output);

    fclose(pF);
    return 1;
}


int main() {
char file_path[CONTENT_FILE];
char choice_prompt[10];
char cipher_ask[CONTENT_FILE];
char output[CONTENT_FILE];
char keys[MAX_KEYS][MAX_KEY_LENGTH];
char results_buffer[MAX_KEYS][CONTENT_FILE];
char key_file_path[CONTENT_FILE];
char output_save_choice[32];
int key_count = 0;
printf("Type: Cipher \\ Decipher\n");
if (input_read(choice_prompt, sizeof(choice_prompt))) {
    /* this is the big one*/
    for ( int i = 0; i < strlen(choice_prompt); i++ ) {
        choice_prompt[i] = tolower(choice_prompt[i]);
    }
    if ( strcmp(choice_prompt, "cipher") == 0) {
        printf("Ready to Cipher, please provide path to file:\n");
       if (input_read(file_path, sizeof(file_path))) {
        if (!file_read(file_path, cipher_ask, sizeof(cipher_ask) )) {
            return 1;
        }
        printf("Please provide path to Keys file:\n");
        if (input_read(key_file_path, sizeof(key_file_path))) {
            int key_count = key_read(key_file_path, keys, MAX_KEYS);
            if (key_count == 0) {
                return 1;
            }
            for ( int i = 0; i < key_count; i++) {
                if (!key_val(keys[i])) {
                    printf("key is not made of valid numbers...\n");
                    return 1;
                }
                int key_length = strlen(keys[i]);
                int text_length = strlen(cipher_ask);
                for (int j = 0; j < text_length; j++) {
                    int key_pos = j % key_length;
                    int shift = keys[i][key_pos] - '0';
                    output[j] = cipher(cipher_ask[j], shift);
                }
                output[text_length] = '\0';
                strcpy(results_buffer[i], output);
                printf("\nResult %d\n", i + 1);
                printf("Key: %s\n", keys[i]);
                printf("%s\n", results_buffer[i]);
            }
        }
        printf("\nWhich output do you want to save?\n");
        if (input_read(output_save_choice, sizeof(output_save_choice))) {
            int chosen_number = atoi(output_save_choice);
            key_count = key_read(key_file_path, keys, MAX_KEYS);
            if ( chosen_number < 1 || chosen_number > key_count) {
                printf("Input is not in results range\n");
                return 1;
            }

            int true_index = chosen_number -1;
            char save_path[CONTENT_FILE];
            printf("Please enter output file path, or just the name of the file, to create it in the same folder the program is in\n");
            if (!input_read(save_path, sizeof(save_path))) {
                printf("Path not valid.\n");
                return 1;
            }
            printf("Chosen key: %s\n", keys[true_index]);
            printf("Chosen output:\n%s\n", results_buffer[true_index]);
            if (!create_file_results(save_path, cipher_ask, keys[true_index], results_buffer[true_index])) {
                printf("creating file failed.\n");
                return 1;
            }
            printf("Result was saved successfully.\n");
        }

    }
 } else if (strcmp(choice_prompt, "decipher") == 0) {  
                printf("Ready to Decipher, Please provide file path:\n");
                if (input_read(file_path, sizeof(file_path))) {
                    if (!file_read(file_path, cipher_ask, sizeof(cipher_ask))){
                        return 1;
                    }
                printf("Please provide a Path to a Key file:\n");
                if (input_read(key_file_path, sizeof(key_file_path))) {
                    int key_count = key_read(key_file_path, keys, MAX_KEYS);
                    if (key_count == 0) {
                        return 1;
                        } 
                    for ( int i = 0; i < key_count; i++) {
                        if (!key_val(keys[i])) {
                        printf("key is not made of valid numbers...\n");
                        return 1;
                        }
                        int key_length = strlen(keys[i]);
                        int text_length = strlen(cipher_ask);
                        for (int j = 0; j < text_length; j++) {
                            int key_pos = j % key_length;
                            int shift = keys[i][key_pos] - '0';
                            output[j] = decipher(cipher_ask[j], shift);
                            }
                        output[text_length] = '\0';
                        strcpy(results_buffer[i], output);
                        printf("\nResult %d\n", i + 1);
                        printf("Key: %s\n", keys[i]);
                        printf("%s\n", results_buffer[i]);
                        }
                printf("\nWhich output do you want to save?\n");
                if (input_read(output_save_choice, sizeof(output_save_choice))) {
                    int chosen_number = atoi(output_save_choice);
                    key_count = key_read(key_file_path, keys, MAX_KEYS);
                    if ( chosen_number < 1 || chosen_number > key_count) {
                        printf("Input is not in results range\n");
                        return 1;
                    }

                    int true_index = chosen_number -1;
                    char save_path[CONTENT_FILE];
                    printf("Please enter output file path, or just the name of the file, to create it in the same folder the program is in\n");
                    if (!input_read(save_path, sizeof(save_path))) {
                        printf("Path not valid.\n");
                        return 1;
                    }
                    printf("Chosen key: %s\n", keys[true_index]);
                    printf("Chosen output:\n%s\n", results_buffer[true_index]);
                    if (!create_file_results(save_path, cipher_ask, keys[true_index], results_buffer[true_index])) {
                        printf("creating file failed.\n");
                        return 1;
                    }
                    printf("Result was saved successfully.\n");
                }
            } 
        } else {
                printf("input must be cipher or decipher.");
                return 1;
                }
              
            }
        }
}
