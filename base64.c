#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char DICT[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

void encode(char input[], char* encoded) {
    int pad, len, temp, last_in, j;
    char result[200];
    last_in = 0;
    pad = 0;
    len = strlen(input);
    j = 0;
    for(int i = 0; i < len; i++){
        temp = 0;
        if(last_in != 0){
            temp += ((last_in) & ((3 << (2 * (pad - 1))) | 2)) << (6 - (2 * pad));
            printf("%x\n", (last_in & ((3 << (2 * (pad - 1))) | 3)));
            printf("%x\n", temp);
            printf("%x\n", (int)input[i] >> (2 * (pad + 1)));
        }
        pad++;
        temp += (int)input[i] >> (2 * pad);
        result[j] = DICT[temp];
        j++;
        if(pad == 3){
            result[j] = DICT[(int)input[i] & 63];
            j++;
            last_in = 0;
            pad = 0;
        }else{
            last_in = (int)input[i];
        }
    }

    if(last_in != 0){
        temp = (last_in & ((3 << (2 * (pad - 1))) | 3)) << (6 - (2 * pad));
        result[j] = DICT[temp];
        j++;
        result[j] = '=';
        j++;
        if(pad == 1){
            result[j] = '=';
            j++;
        }
    }
    result[j] = '\0';
    strncpy(encoded, result, 199);
}

int main() {
    char input[100];
    puts("input: ");
    scanf("%99s", input);
    char encoded[200];
    encode(input, encoded);
    printf("\nencoded: %s", encoded);
    return 0;
}