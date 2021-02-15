/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_output.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 22:52:09 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 23:30:33 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include "libft.h"
#include "ft_output.h"

void			ft_printchar(char c, t_output_buffer *obuffer)
{
	if (obuffer->index >= O_BUF_SIZE)
	{
		write(obuffer->fd, obuffer->store, O_BUF_SIZE);
		obuffer->index = 0;
		obuffer->output_ctr += O_BUF_SIZE;
	}
	obuffer->store[obuffer->index] = c;
	obuffer->index++;
}

/*
** see ft_putwchar_fd.c in libft for documentation
*/

void			ft_printwchar(wint_t c, t_output_buffer *obuffer)
{
	if (c > WCHAR_MAX)
		return ;
	if (c <= 0x7F)
		ft_printchar(c, obuffer);
	else if (c <= 0x7FF)
	{
		ft_printchar((c >> 0x6) + 0xC0, obuffer);
		ft_printchar((c & 0x3F) + 0x80, obuffer);
	}
	else if (c <= 0xFFFF)
	{
		ft_printchar((c >> 0xC) + 0xE0, obuffer);
		ft_printchar(((c >> 0x6) & 0x3F) + 0x80, obuffer);
		ft_printchar((c & 0x3F) + 0x80, obuffer);
	}
	else if (c <= 0x10FFFF)
	{
		ft_printchar((c >> 0x12) + 0xF0, obuffer);
		ft_printchar(((c >> 0xc) & 0x3F) + 0x80, obuffer);
		ft_printchar(((c >> 0x6) & 0x3F) + 0x80, obuffer);
		ft_printchar((c & 0x3F) + 0x80, obuffer);
	}
}

void			ft_printstr(char *str, size_t len, t_output_buffer *obuffer)
{
	while (len > 0 && *str)
	{
		if (obuffer->index >= O_BUF_SIZE)
		{
			write(obuffer->fd, obuffer->store, O_BUF_SIZE);
			obuffer->index = 0;
			obuffer->output_ctr += O_BUF_SIZE;
		}
		obuffer->store[obuffer->index] = *str;
		obuffer->index++;
		str++;
		len--;
	}
}

t_output_buffer	*ft_initialize_obuffer(int fd)
{
	t_output_buffer *obuffer;

	obuffer = malloc(sizeof(t_output_buffer));
	if (obuffer)
	{
		obuffer->index = 0;
		obuffer->output_ctr = 0;
		obuffer->fd = fd;
	}
	return (obuffer);
}

int				ft_finalize_obuffer(t_output_buffer *obuffer)
{
	int total_output;

	total_output = obuffer->output_ctr + obuffer->index;
	write(obuffer->fd, obuffer->store, obuffer->index);
	free(obuffer);
	return (total_output);
}

int				ft_finalize_obuffer_tostr(t_output_buffer *obuffer, char *buf, size_t buflen)
{
	int total_output;
	const size_t obuffer_end = (obuffer->index >= buflen) ? buflen - 1 : obuffer->index;

	assert(buflen > 0);
	total_output = obuffer->output_ctr + obuffer->index;
	ft_memmove(buf, (char *)obuffer->store, obuffer_end);
	buf[obuffer_end] = '\0';
	free(obuffer);
	return (total_output);
}
