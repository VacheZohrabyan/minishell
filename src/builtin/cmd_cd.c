/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaleksan <zaleksan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:22:45 by zaleksan          #+#    #+#             */
/*   Updated: 2025/09/11 16:24:27 by zaleksan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/builtin.h"

// int	change_dir(t_shell *shell, char *path)
// {
// 	char	cwd[PATH_MAX];
// 	char	*old_pwd;
// 	char	*new_pwd;

// 	if (!shell || !path)
// 		return (1);
// 	if (chdir(path) == -1)
// 	{
// 		perror("minishell: cd");
// 		shell->env_list->exit_code = 1;
// 		return (1);
// 	}
// 	new_pwd = NULL;
// 	old_pwd = get_env_param(shell->env_list, "PWD", 1);
// 	if (old_pwd)
// 		set_env_param(shell->env_list, "OLDPWD", ft_strdup(old_pwd));
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		new_pwd = ft_strdup(cwd);
// 		if (!new_pwd)
// 			return (shell->env_list->exit_code = 1, 1);
// 		set_env_param(shell->env_list, "PWD", new_pwd);
// 	}
// 	else
// 	{
// 		ft_putendl_fd("cd: error retrieving current directory:
// getcwd: cannot access parent directories:
// No such file or directory",
// 						2);
// 		set_env_param(shell->env_list, "PWD", ft_strjoin_gnl(ft_strdup(old_pwd),
// 				path));
// 	}
// 	return (0);
// }

// int	cmd_cd(t_shell *shell, t_command *command)
// {
// 	char	*path;

// 	if (!ft_strcmp(command->argv[0], "cd.."))
// 	{
// 		ft_putendl_fd("cd..: command not found", 2);
// 		shell->env_list->exit_code = 1;
// 		return (1);
// 	}
// 	if (command->argv[2])
// 	{
// 		ft_putendl_fd("minishell: cd: too many arguments", 2);
// 		shell->env_list->exit_code = 1;
// 		return (1);
// 	}
// 	if (!command->argv[1] || ft_strcmp(command->argv[1], "~") == 0)
// 	{
// 		path = get_env_param(shell->env_list, "HOME", 1);
// 		if (!path)
// 		{
// 			ft_putendl_fd("minishell: cd: HOME not set", 2);
// 			shell->env_list->exit_code = 1;
// 			return (1);
// 		}
// 	}
// 	else if (ft_strcmp(command->argv[1], "-") == 0)
// 	{
// 		path = get_env_param(shell->env_list, "OLDPWD", 1);
// 		if (!path)
// 		{
// 			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
// 			shell->env_list->exit_code = 1;
// 			return (1);
// 		}
// 		ft_putendl_fd(path, 1);
// 	}
// 	else
// 		path = command->argv[1];
// 	shell->env_list->exit_code = 0;
// 	return (change_dir(shell, path));
// }

#include "../../inc/builtin.h"

static void	update_pwd_vars(t_shell *shell, char *old_pwd, char *path)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (old_pwd)
		set_env_param(shell->env_list, "OLDPWD", ft_strdup(old_pwd));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		new_pwd = ft_strdup(cwd);
		if (!new_pwd)
			shell->env_list->exit_code = 1;
		else
			set_env_param(shell->env_list, "PWD", new_pwd);
	}
	else
	{
		ft_putendl_fd("cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory", 2);
		set_env_param(shell->env_list, "PWD", ft_strjoin_gnl(ft_strdup(old_pwd),
				path));
	}
}

int	change_dir(t_shell *shell, char *path)
{
	char	*old_pwd;

	if (!shell || !path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		shell->env_list->exit_code = 1;
		return (1);
	}
	old_pwd = get_env_param(shell->env_list, "PWD", 1);
	update_pwd_vars(shell, old_pwd, path);
	return (0);
}

static char	*resolve_path(t_shell *shell, t_command *cmd)
{
	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
	{
		if (!get_env_param(shell->env_list, "HOME", 1))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			shell->env_list->exit_code = 1;
			return (NULL);
		}
		return (get_env_param(shell->env_list, "HOME", 1));
	}
	if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		if (!get_env_param(shell->env_list, "OLDPWD", 1))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			shell->env_list->exit_code = 1;
			return (NULL);
		}
		ft_putendl_fd(get_env_param(shell->env_list, "OLDPWD", 1), 1);
		return (get_env_param(shell->env_list, "OLDPWD", 1));
	}
	return (cmd->argv[1]);
}

int	cmd_cd(t_shell *shell, t_command *cmd)
{
	char	*path;

	if (!ft_strcmp(cmd->argv[0], "cd.."))
	{
		ft_putendl_fd("cd..: command not found", 2);
		shell->env_list->exit_code = 1;
		return (1);
	}
	if (cmd->argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		shell->env_list->exit_code = 1;
		return (1);
	}
	path = resolve_path(shell, cmd);
	if (!path)
		return (1);
	shell->env_list->exit_code = 0;
	return (change_dir(shell, path));
}
