/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzohraby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:56:36 by vzohraby          #+#    #+#             */
/*   Updated: 2025/09/25 14:43:22 by vzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	absolute_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.'))
		return (1);
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

char	*find_command_path(t_env *env, char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*full_path;

	path_env = "";
	if (!cmd)
		return (NULL);
	if (absolute_path(cmd))
		return (ft_strdup(cmd));
	path_env = get_env_param(env, "PATH", 1);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = join_path(paths, cmd);
	free_split(paths);
	return (full_path);
}
