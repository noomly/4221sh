/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:14:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/04/28 10:01:17 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BL_H
# define BL_H

# include "libft.h"

typedef enum	e_lexstate
{
	kLexStateUndefined,
	kLexStateGeneral,
	kLexStateDQuote
}				t_lexstate;

typedef enum	e_charstate
{
	kCharStateNull,
	kCharStateGeneral,
	kCharStateSpace,
	kCharStateDQuote
}				t_charstate;

typedef struct	s_lexdat
{
	t_list		**ret;
	t_lexstate	curr_state;
	char		**currtokstr;
	char		c;
}				t_lexdat;

typedef struct	s_equi
{
	int		nb;
	int		(*act)(void *);
	void	*data;
}				t_equi;

t_list			*lex_line(char *line);

void			add_token(t_list **tokens, char *s);

int				add_to_curr(void *data);
int				add_token_to_ret(void *data);
int				switch_to_dquote(void *data);
int				switch_to_general(void *data);
int				ft_swcmp(void *p1, void *p2);

#endif
