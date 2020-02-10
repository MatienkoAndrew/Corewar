/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeruss <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:00:07 by fgeruss           #+#    #+#             */
/*   Updated: 2020/02/02 13:00:22 by fgeruss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

void	new_filename(char **filename, int *fd)
{
	char	*new_file;

	if (!(new_file = ft_strsub(*filename, 0, ft_strlen(*filename) - 2)))
		error(MEMORY);
	if (!(*filename = ft_strjoin(new_file, ".cor")))
		error(MEMORY);
	ft_strdel(&new_file);
	if ((*fd = open(*filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		error("\nFile hasn't created\n");
}
