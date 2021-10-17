#include <stdio.h>
#include <stdlib.h>

void remove_break(char string[100]);
int str_len(const char string[]);
int samestr(const char first_string[], const char second_string[]);
int *get_params(int argc, char const *argv[]);
int check_level1(const char string[]);
int check_level2(const char string[], const int PARAM);
int check_level3(const char string[], const int PARAM);
int check_level4(const char string[], const int PARAM);
void process_checks(const int LEVEL, const int PARAM, const int STATS);

int main(int argc, char const *argv[])
{

    int *parametrs = get_params(argc, argv);
    const int LEVEL = *parametrs;
    const int PARAM = *(parametrs + 1);
    const int STATS = *(parametrs + 2);
    process_checks(LEVEL, PARAM, STATS);
    return 0;
}

void remove_break(char string[100])
{
    for (int i = 0; i < 100; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}

int str_len(const char string[])
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

int check_level1(const char string[])
{
    int has_small_char = 0;
    int has_big_char = 0;

    for (int i = 0; i < str_len(string); i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            has_small_char = 1;
        }
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            has_big_char = 1;
        }
        if (has_small_char && has_big_char)
        {
            break;
        }
    }
    return has_small_char && has_big_char;
}

int check_level2(const char string[], const int PARAM)
{
    int has_small_char = 0;
    int has_big_char = 0;
    int has_number_char = 0;
    int has_special_char = 0;
    int count_groups = 0;

    for (int i = 0; i < str_len(string); i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z' && has_small_char == 0)
        {
            count_groups++;
            has_small_char = 1;
        }
        if (string[i] >= 'A' && string[i] <= 'Z' && has_big_char == 0)
        {
            count_groups++;
            has_big_char = 1;
        }
        if (string[i] >= '0' && string[i] <= '9' && has_number_char == 0)
        {
            count_groups++;
            has_number_char = 1;
        }
        if (
            (
                (string[i] >= 32 && string[i] <= 57) ||
                (string[i] >= 72 && string[i] <= 100) ||
                (string[i] >= 91 && string[i] <= 96) ||
                (string[i] >= 123 && string[i] <= 126)) &&
            has_special_char == 0)
        {
            count_groups++;
            has_special_char = 1;
        }
    }
    return count_groups >= PARAM ? 1 : 0;
}
int check_level3(const char string[], const int PARAM)
{
    int biggest_count = 0;
    int sub_count = 0;
    for (int i = 0; i < str_len(string); i++)
    {
        if (sub_count > biggest_count)
        {
            biggest_count = sub_count;
        }
        sub_count = 0;
        for (int j = i; j < str_len(string); j++)
        {
            if (string[i] == string[j])
            {
                sub_count++;
            }
            else
            {
                break;
            }
        }
    }
    return biggest_count < PARAM ? 1 : 0;
}
int check_level4(const char string[], const int PARAM);

void process_checks(const int LEVEL, const int PARAM, const int STATS)
{
    char password_string[100];
    int is_valid = 1;
    int count = 0;
    while (fgets(password_string, 100, stdin))
    {
        remove_break(password_string);
        is_valid = 1;
        if (LEVEL >= 1)
        {
            if (check_level1(password_string) != 1)
            {
                is_valid = 0;
            }
        }
        if (LEVEL >= 2)
        {
            if (check_level2(password_string, PARAM) != 1)
            {
                is_valid = 0;
            }
        }
        if (LEVEL >= 3)
        {
            if (check_level3(password_string, PARAM) != 1)
            {
                is_valid = 0;
            }
        }

        if (is_valid == 1)
        {
            printf("%s\n", password_string);
        }
        count++;
    }
    printf("%d", count);
}