/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:01:31 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/10 18:01:44 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	free_in_assem(t_asm *assem, t_metka *temp_m, t_link *temp_l)
{
	while (assem->metka)
	{
		while (assem->metka->link)
		{
			temp_l = assem->metka->link->next;
			free(assem->metka->link);
			assem->metka->link = NULL;
			assem->metka->link = temp_l;
		}
		ft_strdel(&assem->metka->name);
		temp_m = assem->metka->next;
		free(assem->metka);
		assem->metka = NULL;
		assem->metka = temp_m;
	}
}

void	freeer(t_asm *assem)
{
	t_cont		*temp;
	t_metka		*temp_m;
	t_link		*temp_l;

	ft_strdel(&assem->name);
	ft_strdel(&assem->comment);
	ft_strdel(&assem->b_code);
	temp = assem->content;
	while (assem->content)
	{
		ft_strdel(&assem->content->content);
		temp = assem->content->next;
		free(assem->content);
		assem->content = NULL;
		assem->content = temp;
	}
	temp_m = NULL;
	temp_l = NULL;
	free_in_assem(assem, temp_m, temp_l);
	free(assem);
}
