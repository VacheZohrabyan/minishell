/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:03:06 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/02 12:56:34 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	change_dir(t_shell *shell, char *path)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;

	if (!shell || !path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	old_pwd = get_env_param(shell->env_list, "PWD", 1);
	if (old_pwd)
		set_env_param(shell->env_list, "OLDPWD", ft_strdup(old_pwd));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		new_pwd = ft_strdup(cwd);
		if (!new_pwd)
			return (1);
		set_env_param(shell->env_list, "PWD", new_pwd);
	}
	return (-1);
}

int	cmd_cd(t_shell *shell, t_command *command)
{
	char	*path;

	if (!command->argv[1] || ft_strcmp(command->argv[1],
			"~") == 0)
	{
		path = get_env_param(shell->env_list, "HOME", 1);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else if (ft_strcmp(command->argv[1], "-") == 0)
	{
		path = get_env_param(shell->env_list, "OLDPWD", 1);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		ft_putendl_fd(path, 1);
	}
	else
		path = command->argv[1];
	return (change_dir(shell, path));
}
