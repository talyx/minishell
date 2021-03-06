#include "minishell.h"

char	*str_enlarge(char *orig, char *add)
{
	size_t	orig_len;
	size_t	add_len;
	char	*result;

	orig_len = ft_strlen(orig);
	add_len = ft_strlen(add);
	result = ft_calloc(orig_len + add_len + 1, sizeof(char));
	ft_strlcpy(result, orig, orig_len + 1);
	ft_strlcat(result, add, add_len + orig_len + 1);
	free(orig);
	return (result);
}

t_list	*get_commands(t_list **tokens, t_minishell *mini)
{
	t_command	*cmd;
	t_list		*commands;
	int			next_cmd;
	t_redirects	cmd_redirs;

	next_cmd = 1;
	commands = NULL;
	while (next_cmd && !(mini->parse_status))
	{
		cmd = malloc(sizeof(t_command));
		cmd_redirs = get_redir(*tokens, mini);
		cmd->red = cmd_redirs.redir;
		cmd->append = cmd_redirs.append;
		cmd->path = get_path(tokens);
		cmd->arg = get_args(tokens, cmd->path);
		cmd->pipe = get_pipe(tokens, mini);
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		next_cmd = cmd->pipe;
	}
	if (!mini->parse_status)
		validity_check(&commands, mini);
	return (commands);
}

int	parse(t_minishell *mini)
{
	t_list	**tokens;
	t_list	*head_token;

	mini->parse_status = 0;
	tokens = string_tokenize(mini);
	vars_substitute(tokens, mini);
	head_token = *tokens;
	mini->commands = get_commands(&head_token, mini);
	word_list_free(tokens);
	free(tokens);
	return (mini->parse_status);
}
