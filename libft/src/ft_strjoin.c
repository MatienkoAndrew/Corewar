/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asusan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:14:44 by asusan            #+#    #+#             */
/*   Updated: 2019/04/19 23:07:52 by asusan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char 	*start;

	if (!s1 && !s2)
		return (NULL);
	if (!(ptr = (char*)malloc((s1 ? ft_strlen(s1) : 0)
			+ (s2 ? ft_strlen(s2) : 0) + 1)))
		return (NULL);
	start = ptr;
	if (s1)
		while (*s1)
			*ptr++ = *s1++;
	if (s2)
		while (*s2)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (start);
}
