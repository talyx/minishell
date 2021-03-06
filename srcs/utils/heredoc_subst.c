#include "minishell.h"

static void	merge_nospace(t_list **tok, char **result)
{
	char	*merged;

	merged = tokens_merge(tok, 0);
	(*result) = str_enlarge((*result), merged);
	free(merged);
}

static char	*tokens_to_str(t_list **tokens)
{
	t_list		*tok;
	char		*result;

	tok = *tokens;
	result = ft_calloc(sizeof(char), 1);
	if (!tok)
		return (result);
	while (tok)
	{
		if (!(((t_word_desc *)tok->content)->flags & T_NOSPC))
		{
			result = str_enlarge(result, ((t_word_desc *)tok->content)->word);
			if (tok->next)
				result = str_enlarge(result, " ");
		}
		else
			merge_nospace(&tok, &result);
		if (!tok || !(tok->next))
			break ;
		tok = tok->next;
	}
	return (result);
}

char	*heredoc_subst(char *input, t_minishell *mini)
{
	t_list	**tokens;
	char	*result;

	if (!input)
		return (ft_strdup(""));
	tokens = wordsplit(input, 0, NULL);
	split_on_vars(tokens);
	vars_substitute(tokens, mini);
	result = tokens_to_str(tokens);
	word_list_free(tokens);
	free(tokens);
	return (result);
}
