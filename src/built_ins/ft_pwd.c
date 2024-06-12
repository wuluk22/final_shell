#include "../../includes/minishell.h"

int	ft_pwd(t_simple_cmds *cmd)
{
	char	*crt_wd;

	crt_wd = NULL;
	(void)cmd;
	crt_wd = getcwd(crt_wd, sizeof(size_t));
	printf("%s\n", crt_wd);

	return (0);
}