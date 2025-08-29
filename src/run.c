#include "../inc/include.h"

void	run(t_shell *shell)
{
	if (shell->command->next == NULL)
	{
		if (!check_builtin(shell))
			// printf("Zhenya\n");
			;
		else
			printf("Vache\n");
	}
	else
		printf("open process");
}