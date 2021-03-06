#include "minishell.h"

void	redir_error_dup(char *redir_op, t_minishell *mini)
{
	if (redir_op)
	{
		handle_error(ERR_P_UNEXP, redir_op);
		mini->parse_status = 2;
	}
}

int	redir_error_missing(char *filename, t_minishell *mini)
{
	if (!filename || !(*filename))
	{
		handle_error(ERR_P_MISSING, "redirect argument");
		mini->parse_status = 2;
		return (1);
	}
	else
		return (0);
}
