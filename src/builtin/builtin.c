#include "../../inc/builtin.h"

int	check_builtin(char *cmd)
{
	if (!ft_strcmp("pwd", cmd))
		return (cmd_pwd());
	return (0);
}