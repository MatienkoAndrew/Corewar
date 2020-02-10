/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_asm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:00:04 by fgeruss           #+#    #+#             */
/*   Updated: 2020/01/23 21:00:12 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_asm(char **line, char **str)
{
	char	*res;

	if ((res = ft_strjoin(*line, *str)) == NULL)
		error("Not allocated memory");
	ft_strdel(line);
	ft_strdel(str);
	return (res);
}
