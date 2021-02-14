/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_output.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 18:46:35 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 23:01:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OUTPUT_H
# define FT_OUTPUT_H

# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

/*
** output buffer (+ft_output.c)
*/
# ifndef O_BUF_SIZE
#  define O_BUF_SIZE 1000
# endif

typedef struct		s_output_buffer
{
	unsigned char	store[O_BUF_SIZE + 1];
	unsigned int	index;
	int				output_ctr;
	int				fd;
}					t_output_buffer;

int					ft_finalize_obuffer(t_output_buffer *obuffer);
int					ft_finalize_obuffer_tostr(t_output_buffer *obuffer, char *buf, size_t buflen);
t_output_buffer		*ft_initialize_obuffer(int fd);

void				ft_printstr(char *str, size_t len,
						t_output_buffer *obuffer);
void				ft_printchar(char c, t_output_buffer *obuffer);
void				ft_printwchar(wint_t c, t_output_buffer *obuffer);
void				ft_printwstr(wchar_t *str, size_t len,
						t_output_buffer *obuffer);

#endif
