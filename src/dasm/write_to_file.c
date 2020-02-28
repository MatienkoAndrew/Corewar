/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenergy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 23:12:09 by nenergy           #+#    #+#             */
/*   Updated: 2020/02/26 23:12:11 by nenergy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dasm.h"

void		ft_write_func_2(t_state *state, int fd)
{
	char	*number;

	number = NULL;
	if (state->argv[1] == DIR_CODE)
	{
		write(fd, " %", ft_strlen(" %"));
		number = ft_itoa(state->f_argv[1]);
		write(fd, number, ft_strlen(number));
	}
	else if (state->argv[1] == REG_CODE)
	{
		write(fd, " r", ft_strlen(" r"));
		number = ft_itoa(state->f_argv[1]);
		write(fd, number, ft_strlen(number));
	}
	else if (state->argv[1] == IND_CODE)
	{
		write(fd, " ", ft_strlen(" "));
		number = ft_itoa(state->f_argv[1]);
		write(fd, number, ft_strlen(number));
	}
	free(number);
}

void		help_write_func(t_state *state, int fd, char *time, char *number)
{
	time = ft_strjoin(state->name, " %");
	write(fd, time, ft_strlen(time));
	number = ft_itoa(state->f_argv[0]);
	write(fd, number, ft_strlen(number));
	ft_strdel(&time);
	ft_strdel(&number);
}

void		ft_write_func_1(t_state *state, int fd)
{
	char	*time;
	char	*number;

	time = NULL;
	number = NULL;
	if (state->argv[0] == DIR_CODE)
		help_write_func(state, fd, time, number);
	else if (state->argv[0] == REG_CODE)
	{
		time = ft_strjoin(state->name, " r");
		write(fd, time, ft_strlen(time));
		number = ft_itoa(state->f_argv[0]);
		write(fd, number, ft_strlen(number));
	}
	else if (state->argv[0] == IND_CODE)
	{
		time = ft_strjoin(state->name, " ");
		write(fd, time, ft_strlen(time));
		number = ft_itoa(state->f_argv[0]);
		write(fd, number, ft_strlen(number));
	}
	ft_free_char(number, time);
}

void		ft_write(t_state *temp, int fd, char *filename)
{
	while (temp && temp->name != NULL)
	{
		ft_write_func_1(temp, fd);
		if (temp->argv[1] != (char)0)
		{
			write(fd, ",", 1);
			ft_write_func_2(temp, fd);
		}
		if (temp->argv[2] != 0)
		{
			write(fd, ",", 1);
			ft_write_func_3(temp, fd);
		}
		write(fd, "\n", ft_strlen("\n"));
		temp = temp->next;
	}
	write(1, "Writing output program to ", 26);
	write(1, filename, ft_strlen(filename));
	write(1, "\n", 1);
}

void		ft_write_nc(int fd, char *s1, char *s)
{
	char	*time;
	char	*time1;
	char	*time2;

	time = ft_strjoin(s1, " \"");
	time1 = ft_strjoin(time, s);
	time2 = ft_strjoin(time1, "\"\n");
	write(fd, time2, ft_strlen(time2));
	free(time);
	free(time1);
	free(time2);
}
