#include "minishell.h"

char	**lst_to_char(t_list **env)
{
	char	**ret;
	char	*line;
	t_list	*tmp;
	int		len;
	int		j;

	j = 0;
	tmp = (*env)->next;
	len = ft_lstsize(tmp);
	ret = malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		line = tmp->content;
		ret[j++] = ft_substr(line, 0, ft_strlen(line));
		tmp = tmp->next;
	}
	ret[j] = NULL;
	return (ret);
}

int	check_dir(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (127);
}

int	run_cmd(char *path, char **arg, t_minishell *mini)
{
	char	**envp;
	int		exit_status;
	int		pid;

	envp = lst_to_char(mini->env);
	pid = fork();
	if (pid == 0)
	{
		execve(path, arg, envp);
		exit_status = check_dir(path);
		exit(exit_status);
	}
	else
		waitpid(pid, &exit_status, 0);
	ft_split_clear(envp);
	return (WEXITSTATUS(exit_status));
}

int	run_bins(t_minishell *mini, t_command *comm)
{
	char	**all_path;
	char	*path;
	char	*env;
	int		i;

	path = NULL;
	i = 0;
	env = get_env_param(mini->env, "PATH");
	if (!env)
		return (run_cmd(comm->path, comm->arg, mini));
	all_path = ft_split(env, ':');
	while (all_path[i] && path == NULL)
		path = get_need_path(all_path[i++], comm->path);
	if (path)
		i = run_cmd(path, comm->arg, mini);
	else
		i = run_cmd(comm->path, comm->arg, mini);
	ft_split_clear(all_path);
	free(path);
	return (i);
}
