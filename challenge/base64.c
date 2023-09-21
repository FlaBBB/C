#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char DICT[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

char *base64_encode(char input[], size_t input_length, size_t *output_length)
{
    int pad, temp, last_input, j;
    last_input = 0;
    pad = 0;
    j = 0;

    *output_length = ((input_length + 2) / 3) * 4;
    char *result = malloc(*output_length + 1);
    if (result == NULL)
    {
        printf("Failed to allocate memory for result.\n");
        return NULL;
    }

    for (int i = 0; i < input_length; i++)
    {
        temp = 0;

        if (last_input != 0)
        {
            temp += (last_input & ((3 << (2 * (pad - 1))) | 3)) << (6 - (2 * pad));
        }

        pad++;
        temp += (int)input[i] >> (2 * pad);
        result[j++] = DICT[temp];

        if (pad == 3)
        {
            result[j++] = DICT[(int)input[i] & 63];
            last_input = 0;
            pad = 0;
        }
        else
        {
            last_input = (int)input[i];
        }
    }

    if (last_input != 0)
    {
        temp = (last_input & ((3 << (2 * (pad - 1))) | 3)) << (6 - (2 * pad));
        result[j++] = DICT[temp];
        result[j++] = '=';
        if (pad == 1)
        {
            result[j++] = '=';
        }
    }
    
    result[*output_length - 1] = '\0';

    return result;
}

char *base64_url_encode(char input[], size_t input_length, size_t *output_length)
{
    char *result = base64_encode(input, input_length, output_length);

    for (int i = 0; i < *output_length; i++)
    {
        if (result[i] == '+')
        {
            result[i] = '-';
        }
        else if (result[i] == '/')
        {
            result[i] = '_';
        }
        else if (result[i] == '=')
        {
            result[i] = '\0';
            *output_length = i;
            break;
        }
    }

    return result;
}

char *base64_filename_encode(char input[], size_t input_length, size_t *output_length)
{
    char *result = base64_encode(input, input_length, output_length);

    for (int i = 0; i < *output_length; i++)
    {
        if (result[i] == '/')
        {
            result[i] = '-';
        }
    }

    return result;
}

int main()
{
    size_t output_length = 0;
    char *input;
    input = malloc(1024 * sizeof(char));

    printf("input: ");
    scanf("%s", input);

    char *encoded = base64_encode(input, strlen(input), &output_length);
    printf("encoded: %s", encoded);

    free(input);
    free(encoded);

    return 0;
}