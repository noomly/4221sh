/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_bltncmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echojnow <echojnow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:35:25 by echojnow          #+#    #+#             */
/*   Updated: 2018/07/27 00:04:50 by echojnow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			remaining_fields_size(char **line_split)
{
	int	new_size;

	new_size = 0;
	while (*line_split)
	{
		if (new_size == 0)
			new_size += ft_strlen(*line_split);
		else
			new_size += ft_strlen(*line_split) + 1;
		line_split++;
	}
	return (new_size);
}

void		remaining_fields(int remaining, char *var_name, char **line_split)
{
	int		new_size;
	char	*new;
	char	*tmp;

	if (!remaining)
		return ;
	new_size = remaining_fields_size(line_split);
	new = ft_strnew(new_size);
	new[new_size] = '\0';
	tmp = NULL;
	ft_strcat(new, *(line_split++));
	while (*line_split)
	{
		tmp = ft_strapp(" ", *line_split);
		ft_strcat(new, tmp);
		free(tmp);
		line_split++;
	}
	set_lvar(var_name, new);
	free(new);
}

void		remaining_args(int remaining, char **args)
{
	if (!remaining)
		return ;
	while (*args)
		set_lvar(*(args++), "");
}

char		*get_line(t_rl_opts *opts, int nl_escaped)
{
	char		*line;
	char		*final;

	line = NULL;
	final = NULL;
	ft_readline(&line, nl_escaped > 0 ? "> " : NULL, opts, NULL);
	if (!line)
		return (NULL);
	if (nl_escaped > -1 && line[ft_strlen(line) - 1] == '\\')
	{
		final = ft_strapp(line, get_line(opts, 1));
		free(line);
	}
	else
		return (line);
	return (final);
}

int			exec_read(t_rl_opts *opts, char **args, int dont_escape)
{
	char	*line;
	char	**line_split;
	int		line_split_len;
	int		i;

	line = get_line(opts, 0 - dont_escape);
	if (!line)
	{
		remaining_args(1, args);
		return (0);
	}
	line_split = ft_readsplit(line, ' ', dont_escape);
	line_split_len = ft_ntsarr_len(line_split);
	i = 0;
	while (line_split[i] && args[i] && args[i + 1])
	{
		set_lvar(args[i], line_split[i]);
		i++;
	}
	remaining_args(ft_ntsarr_len(args) > i, &args[i]);
	remaining_fields(ft_ntsarr_len(line_split) > i, args[i], &line_split[i]);
	free(line);
	ft_ntsarr_free(&line_split);
	return (0);
}

char	**argv_pop(int argc, char **argv, int pops)
{
	char	**new;
	int		i;
	int		j;

	new = (char**)malloc(sizeof(char*) * (argc - pops + 1));
	new[argc - pops] = NULL;
	i = pops;
	j = 0;
	while (i < argc)
	{
		new[j] = argv[i];
		i++;
		j++;
	}

	return (new);
}

int		read_bltn(int ac, char **av)
{
	char		**new_av;
	t_rl_opts	opts;
	int			dont_escape;

	dont_escape = 0;
	if (ac > 1 && ft_strcmp(av[1], "-r") == 0)
		dont_escape = 1;
	new_av = argv_pop(ac, av, 1  + dont_escape);
	if (ft_ntsarr_len(new_av) > 0)
		exec_read(&opts, new_av, dont_escape);
	else
		ft_putendl_fd("read: usage: [-r] vars...", STDERR_FILENO);
	free(new_av);
	return (0);
}

/* int			manage_backslashes(char **line) */
/* { */
/* 	char	*tmp; */
/* 	char	*new; */
/* 	int		i; */
/* 	int		nl_escaped; */

/* 	new = NULL; */
/* 	i = -1; */
/* 	nl_escaped = 0; */
/* 	while ((*line)[++i]) */
/* 	{ */
/* 		if ((*line)[i] == '\\' && (*line)[i + 1] && (*line)[i + 1] == '\\') */
/* 			tmp = ft_strappc(new, (*line)[i++]); */
/* 		if ((*line)[i] == '\\' && !(*line)[i + 1]) */
/* 		{ */
/* 			nl_escaped = 1; */
/* 			break ; */
/* 		} */
/* 		else */
/* 			tmp = ft_strappc(new, (*line)[i]); */
/* 		free(new); */
/* 		new = tmp; */
/* 	} */
/* 	ft_strdel(line); */
/* 	*line = new; */
/* 	return (nl_escaped); */
/* } */
