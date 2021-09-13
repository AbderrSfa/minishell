
#include "exec.h"

void here(char *limiter)
{
	int i;
	int fd;
	char *line;

	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		line = readline(">");
		i = strncmp(line, limiter, ft_strlen(limiter) + 1);
		if (i == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);	
}

void heredoc(t_list *cmds)
{
	t_list 	*red;
	t_redir	*rec;
	t_cmd	*cmd;
	
	while (cmds)
	{
		cmd = cmds->content;
		red = cmd->redir;
		while (red != NULL)
		{
			rec = red->content;
			if (rec->type == 'H')
				here(rec->file);
			red = red->next;
		}
		cmds = cmds->next;
	}
}

