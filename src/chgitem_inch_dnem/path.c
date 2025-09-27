/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:56:36 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/27 11:34:07 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	absolute_path(int *status, char *cmd)
{
	if (cmd[0] == '/')
		return (*status = 2, 1);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (*status = 1, 1);
	return (0);
}

static char	*join_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_env *env, char *cmd, int *status)
{
	char	**paths;
	char	*path_env;
	char	*full_path;

	path_env = "";
	*status = 0;
	if (!cmd)
		return (NULL);
	if (absolute_path(status, cmd))
		return (ft_strdup(cmd));
	path_env = get_env_param(env, "PATH", 1);
	if (!path_env)
		return (*status = 1, cmd);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = join_path(paths, cmd);
	if (!full_path)
		return (free_split(paths), ft_strdup(cmd));
	free_split(paths);
	return (full_path);
}
