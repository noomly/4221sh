/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:30:47 by kdumarai          #+#    #+#             */
/*   Updated: 2018/05/05 17:33:41 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BP_H
# define BP_H

t_btree	*parse_tokens(t_list *tokens);
void	lstdelf(void *data, size_t datsize);
void	astputelem(void *data, size_t datsize);

#endif
