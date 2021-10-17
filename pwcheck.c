#include <stdio.h>
#include <stdlib.h>

void remove_break(char string[102]);
int str_len(const char string[]);
int str_same(const char first_string[], const char second_string[]);
int str_isnum(const char string[]);
const char *str_strip(const char string[], int start, int end);
int *get_params(int argc, char const *argv[]);
int validate_input(const int LEVEL,const int PARAM, int argc, char const *argv[]);
int check_level1(const char string[]);
int check_level2(const char string[], const int PARAM);
int check_level3(const char string[], const int PARAM);
int check_level4(const char string[], const int PARAM);
int process_checks(const int LEVEL, const int PARAM, const int STATS);

int main(int argc, char const *argv[])
{
    int *parametrs = get_params(argc, argv);
    const int LEVEL = *parametrs;
    const int PARAM = *(parametrs + 1);
    const int STATS = *(parametrs + 2);
    if (validate_input(LEVEL,PARAM, argc, argv) == 1)
    {
        
        return process_checks(LEVEL, PARAM, STATS);
    }
    return 1;
}

void remove_break(char string[102])
{
    for (int i = 0; i < 102; i++)
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

int str_same(const char *first_string, const char *second_string)
{
    int are_same = 1;

    // Iterate a loop till the end
    // of both the strings
    while (*first_string != '\0' || *second_string != '\0')
    {
        if (*first_string == *second_string)
        {
            first_string++;
            second_string++;
        }

        // If two characters are not same
        // print the difference and exit
        else if ((*first_string == '\0' && *second_string != '\0') || (*first_string != '\0' && *second_string == '\0') || *first_string != *second_string)
        {
            are_same = 0;
            break;
        }
    }

    // If two strings are exactly same
    return are_same;
}
int str_isnum(const char string[])
{
    int is_num = 1;
    for (int i = 0; i < str_len(string); i++)
    {
        if (string[i] < '0' || string[i] > '9')
        {
            is_num = 0;
        }
    }
    return is_num;
}

int *get_params(int argc, char const *argv[])
{
    static int output[3] = {0, 0, 0};

    for (int i = 1; i < argc; i++)
    {
        if (str_same(argv[i], "-l") == 1)
        {
            output[0] = atoi(argv[i + 1]);
        }
        else if (str_same(argv[i], "-p") == 1)
        {
            output[1] = atoi(argv[i + 1]);
        }
        else if (str_same(argv[i], "--stats") == 1)
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

int validate_input(const int LEVEL,const int PARAM, int argc, char const *argv[])
{
    int validated = 1;
    int num_arg_count = 0;
    if (LEVEL > 4 || LEVEL < 1)
    {
        validated = 0;
        fprintf(stderr, "Invalid LEVEL param '%d'\n", LEVEL);
    }
        if (PARAM < 1)
    {
        validated = 0;
        fprintf(stderr, "Invalid PARAM param '%d'\n", PARAM);
    }
    if (argc > 6)
    {
        validated = 0;
        fprintf(stderr, "Too many params\n");
    }
    if (argc < 3)
    {
        validated = 0;
        fprintf(stderr, "Not enough params\n");
    }
    for (int i = 1; i < argc; i++)
    {
        if (str_isnum(argv[i]) == 1)
        {
            num_arg_count++;
        }
        if (((str_isnum(argv[i])) ||
             (str_same(argv[i], "-l")) ||
             (str_same(argv[i], "-p")) ||
             (str_same(argv[i], "--stats"))) != 1)
        {
            validated = 0;
            fprintf(stderr, "Invalid param: %s\n", argv[i]);
        }
    }
    if (num_arg_count > 2 || num_arg_count < 2)
    {
        validated = 0;
        fprintf(stderr, "Invalid count of numeric params: %d\n", num_arg_count);
    }

    return validated;
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
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            if (has_small_char != 1)
            {
                count_groups++;
            }
            has_small_char = 1;
            continue;
        }
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            if (has_big_char != 1)
            {
                count_groups++;
            }
            has_big_char = 1;
            continue;
        }
        if (string[i] >= '0' && string[i] <= '9' && has_number_char == 0)
        {
            if (has_number_char != 1)
            {
                count_groups++;
            }
            has_number_char = 1;
            continue;
        }
        if ((string[i] >= 32 && string[i] <= 126) == 1 && has_special_char == 0)
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
int check_level4(const char string[], const int PARAM)
{
    char substring[102] = "";
    char comparison_string[102] = "";
    int is_ok = 1;
    for (int i = 0; i < str_len(string); i++)
    {

        // construct substring
        for (int j = 0; j < PARAM; j++)
        {
            substring[j] = string[i + j];
        }
        for (int k = i + 1; k < str_len(string); k++)
        {

            // construct comparison
            for (int l = 0; l < PARAM; l++)
            {
                comparison_string[l] = string[k + l];
            }
            if (str_same(substring, comparison_string) == 1)
            {
                is_ok = 0;
                break;
            }
        }
    }
    return is_ok;
}

int process_checks(const int LEVEL, const int PARAM, const int STATS)
{
    char password_string[102];
    int is_valid = 1;
    int count = 0;
    int is_error = 0;
    while (fgets(password_string, 102, stdin))
    {
        if (password_string[str_len(password_string)-1] != '\n') {
            fprintf(stderr, "Too big bro");
            is_error = 1;
            break;
        }
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
        if (LEVEL >= 4)
        {
            if (check_level4(password_string, PARAM) != 1)
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
    return is_error;
}