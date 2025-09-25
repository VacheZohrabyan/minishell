/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:20:34 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/25 16:58:11 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

int			g_exit_status = 0;

static void	init_minishell(t_shell **shell, char **env)
{
	*shell = init_shell(env);
	init_shell_history(*shell);
	shlvl(*shell);
}

static void	handle_empty_input(t_shell *shell)
{
	if (shell->buffer[0] == '\0')
	{
		free(shell->buffer);
		shell->buffer = NULL;
	}
}

static int	process_input(t_shell *shell)
{
	record_history(shell, shell->buffer);
	shell->token = lexical(shell);
	if (!shell->token)
		return (0);
	if (parsing(&(shell->command), shell->token) == -1)
	{
		token_node_free(&shell->token);
		free_command(&(shell->command));
		return (-1);
	}
	run(shell);
	token_node_free(&shell->token);
	free_command(&(shell->command));
	return (0);
}

static int	shell_loop(struct termios orig_term,
		struct termios new_term, t_shell *shell)
{
	enable_raw_mode(&orig_term, &new_term);
	while (1)
	{
		disable_raw_mode(&orig_term);
		signal(SIGINT, handle_sigcat);
		signal(SIGQUIT, SIG_IGN);
		// sig();
		shell->buffer = readline("minishell> ");
		if (!shell->buffer)
		{
			printf("exit\n");
			break ;
		}
		if (shell->buffer[0] == '\0')
		{
			handle_empty_input(shell);
			continue ;
		}
		if (process_input(shell) == -1)
			break ;
		free(shell->buffer);
		shell->buffer = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell			*shell;
	struct termios	orig_term;
	struct termios	new_term;

	if (argc != 1 || !argv[0])
		return (0);
	init_minishell(&shell, env);
	shell_loop(orig_term, new_term, shell);
	close_shell_history(shell);
	free_shell(shell);
	return (0);
}
