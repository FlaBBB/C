#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToHex(int decimal, char *hexadecimal) {
    if(decimal == 0){
        sprintf(hexadecimal, "00");
        return;
    }

    int remainder, quotient;
    int i = 0;
    char hex[100];

    quotient = decimal;
    while(quotient < 0){
        quotient += 0x100;
    }

    while (quotient > 0) {
        remainder = quotient % 16;

        if (remainder < 10)
            hex[i] = remainder + '0';
        else
            hex[i] = remainder + 'A' - 10; 

        quotient = quotient / 16;
        i++;
    }

    int j = 0;
    for(int k = i % 2; k > 0; k--){
        hexadecimal[j++] = '0';
    }

    for (int k = i - 1; k >= 0; k--)
        hexadecimal[j++] = hex[k];

    hexadecimal[j] = '\0';
}

char *decode(char input[])
{
    char temp[3];
    int input_length = strlen(input);
    int output_length = input_length / 2;

    char *result = malloc(output_length + 1);

    int last = 0;

    int j = 0;
    for (int i = 0; i < input_length; i += 2)
    {
        strncpy(temp, input + i, 2);
        last += strtol(temp, NULL, 16);
        result[j++] = (char)(last % 0x100);
    }

    result[j] = '\0';

    return result;
}

char *encode(char input[])
{
    int length_input = strlen(input);
    char *result = malloc((length_input * 2) + 1);
    result[0] = '\0';

    int last = 0;
    for (int i = 0; i < length_input; i++)
    {
        char temp[100];
        decimalToHex((int)input[i] - last, temp);
        last = (int)input[i];
        strncat(result, temp, 2);
        free(temp);
    }

    return result;
}

int main()
{
    char *input;
    input = malloc(1024 * sizeof(char));

    printf("Give me input, I will encode it: ");
    scanf("%s", input);
    // printf("%d\n", strlen(input));

    printf("output: %s\n\n", encode(input));
    free(input);

    input = malloc(1024 * sizeof(char));
    
    printf("Give me input again, Now i will decode it: ");
    scanf("%s", input);
    
    printf("output: %s\n", decode(input));
    free(input);
}