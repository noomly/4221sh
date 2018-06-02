/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:55:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/06/02 04:49:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh_jobs.h"

t_list		*g_jobslst = NULL;

uint8_t		sh_job_put(int n)
{
	t_list		**tmp;
	t_list		**bak;
	t_jobctrl	*dat;
	uint8_t		ret;

	tmp = &g_jobslst;
	ret = FALSE;
	while (*tmp)
	{
		dat = (t_jobctrl*)(*tmp)->content;
		if (n < 1 || n == dat->j_idx)
		{
			ret = TRUE;
			ft_jobputnode(dat);
			if (dat->j_state == kJobStateTerminated)
			{
				bak = tmp;
				tmp = &(*tmp)->next;
				ft_lstdelone(bak, &ft_joblstdel);
				continue ;
			}
		}
		tmp = &(*tmp)->next;
	}
	return (ret);
}

t_list		*sh_job_lastest(void)
{
	t_list	*tmp;

	if (!(tmp = g_jobslst))
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_list		**sh_job_add(char *cmd, pid_t pid)
{
	t_jobctrl	*jdat;
	t_list		*node;
	t_list		**tmp;

	tmp = &g_jobslst;
	while (*tmp && (*tmp)->next)
		tmp = &(*tmp)->next;
	if (!(jdat = ft_memalloc(sizeof(t_jobctrl))))
		return (NULL);
	jdat->j_idx = (!*tmp) ? 1 : ((t_jobctrl*)(*tmp)->content)->j_idx;
	jdat->j_state = kJobStateRunning;
	jdat->j_cmd = ft_strdup(cmd);
	jdat->j_pid = pid;
	if (!(node = ft_lstnew(NULL, 0)))
	{
		free(jdat->j_cmd);
		free(jdat);
		return (NULL);
	}
	node->content = jdat;
	node->content_size = sizeof(t_jobctrl);
	tmp = (*tmp) ? &(*tmp)->next : tmp;
	*tmp = node;
	return (tmp);
}