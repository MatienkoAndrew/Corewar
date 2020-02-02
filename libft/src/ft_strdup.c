/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:28:13 by fgeruss           #+#    #+#             */
/*   Updated: 2019/04/07 22:28:14 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//char	*ft_strdup(const char *s1)
//{
//	size_t	i;
//	char	*result;
//
//	if ((result = ft_strnew(ft_strlen(s1))))
//	{
//		i = 0;
//		while (s1[i])
//		{
//			result[i] = s1[i];
//			i++;
//		}
//		result[i] = '\0';
//	}
//	return (result);
//}

char	*ft_strdup(const char *s)
{
	char	*array;
	size_t	i;

	i = 0;
	array = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (array == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
