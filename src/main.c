#include "../inc/minishell.h"
#include "../inc/parser.h"

int main(int argc, char** argv, char** env )
{
    if (argc != 1 || !argv)
        return (0);
    t_env* str_env;
    char* buffer;
    str_env = init_env(env);
    while (1)
    {
        buffer = readline("minishell -> ");
        if (*buffer == '\0') break;
        init_token(buffer);
    }
    free_init_str_env(str_env);
}