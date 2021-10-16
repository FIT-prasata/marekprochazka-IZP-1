#include <stdio.h>
#include <stdlib.h>

void clear_string(char string[100]);
int str_len(char string[]);
int samestr(const char first_string[], const char second_string[]);
int *get_params(int argc, char const *argv[]);
int *check_level1(const char string[]);
int *check_level2(const char string[], const int PARAM);
int *check_level3(const char string[], const int PARAM);
int *check_level4(const char string[], const int PARAM);
void process_checks(const int LEVEL, const int PARAM, const int STATS);
int main(int argc, char const *argv[])
{

    int *parametrs = get_params(argc, argv);
    const int LEVEL = *parametrs;
    const int PARAM = *(parametrs + 1);
    const int STATS = *(parametrs + 2);
    printf("LEVEL %d \n", LEVEL);
    printf("PARAM %d \n", PARAM);
    printf("STATS %d \n", STATS);
    int character;
    char password_string[100];
    int character_place = 0;
    while ((character = getchar()) != EOF)
    {
        if (character == '\n')
        {
            character_place = 0;
            printf("%s\n", password_string);
            clear_string(password_string);
        }
        else
        {
            password_string[character_place] = character;
            character_place++;
        }
    }

    return 0;
}

void clear_string(char string[100])
{
    for (int i = 0; i < 100; i++)
    {
        if (string[i] == '\0')
        {
            break;
        }
        else
        {
            string[i] = '\0';
        }
    }
}

int str_len(char string[])
{
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++)
        count++;
    return count;
}

int samestr(const char first_string[], const char second_string[])
{
    int are_same = 1;
    for (int i = 0; first_string[i] != '\0' && second_string[i] != '\0'; i++)
    {
        if (first_string[i] != second_string[i])
        {
            are_same = 0;
            break;
        }
    }
    return are_same;
}

int *get_params(int argc, char const *argv[])
{
    static int output[3] = {0, 0, 0};

    for (int i = 1; i < argc; i++)
    {
        if (samestr(argv[i], "-l") == 1)
        {
            output[0] = atoi(argv[i + 1]);
        }
        else if (samestr(argv[i], "-p") == 1)
        {
            output[1] = atoi(argv[i + 1]);
        }
        else if (samestr(argv[i], "--stats") == 1)
        {
            output[2] = 1;
        }
    }
    if (output[0] != 0 && output[1] == 0)
    {
        output[1] = 1;
    }
    else if (output[0] == 0 && output[1] != 0)
    {
        output[0] = 1;
    }
    else if (output[0] == 0 && output[1] == 0)
    {
        output[0] = atoi(argv[1]);
        output[1] = atoi(argv[2]);
    }

    return output;
}

void process_checks(const int LEVEL, const int PARAM, const int STATS)
{
}