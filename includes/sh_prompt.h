/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:21:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/12 01:55:10 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PROMPT_H
# define SH_PROMPT_H

/*
** prompt
*/

char	*get_prompt_from_str(char *s);

/*
** prompt utilities
*/

int		add_username(char **dest);
int		add_hostname(char **dest);
int		add_pwd(char **dest, int all);

#endif
