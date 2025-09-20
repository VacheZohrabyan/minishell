/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:46:55 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/20 15:43:27 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
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
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
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

int	cmd_exit(t_shell *shell, t_command *command)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!command->argv[1])
	{
		free_shell(shell);
		exit(g_exit_status);
	}
	if (is_non_numeric(command->argv[1]) || !ft_atol(command->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_shell(shell);
		exit(2);
	}
	if (command->argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = ft_atoi(command->argv[1]) % 256;
	exit(g_exit_status);
}
