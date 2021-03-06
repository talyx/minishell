#include "minishell.h"

void	validity_check(t_list **cmds_list, t_minishell *mini)
{
	t_command	*cmd;
	t_list		*li;

	li = *cmds_list;
	if (!li)
		return ;
	while (li)
	{
		cmd = li->content;
		if (!(cmd->path) && (!(cmd->red->in) && !(cmd->red->out)
				&& !(cmd->append->in) && !(cmd->append->out)) && cmd->pipe)
		{
			handle_error(ERR_P_UNEXP, "|");
			mini->parse_status = 2;
		}
		if (mini->parse_status)
			break ;
		li = li->next;
	}
}
