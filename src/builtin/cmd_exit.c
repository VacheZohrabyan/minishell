/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:55 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/11 17:00:25 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		digit;
	int		i;

	result = 0;
	sign = 1;
	digit = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (0);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}

int	is_non_numeric(char *status)
{
	int	i;

	i = 0;
	if (!status || status[0] == '\0')
		return (1);
	if (status[0] == '+' || status[0] == '-')
		i++;
	if (status[i] == '\0')
		return (1);
	while (status[i])
	{
		if (!ft_isdigit((unsigned char)status[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_argument(t_command *command, char *err_msg)
{
	if (is_non_numeric(command->argv[1]) || !ft_atol(command->argv[1]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(err_msg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(command->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		// free all here
		return (0);
	}
	return (1);
}

int	cmd_exit(t_shell *shell, t_command *command)
{
	long	val;

	val = 0;
	ft_putendl_fd("exit", 1);
	if (!command->argv[1])
		exit(shell->env_list->exit_code);
	if (command->argv[2] && !is_non_numeric(command->argv[1]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->env_list->exit_code = 1;
		return (1);
	}
	else if (check_argument(command, "exit"))
		exit (255);
	shell->env_list->exit_code = (unsigned char)val;
	// free shell/env here
	exit(shell->env_list->exit_code);
}
