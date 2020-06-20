/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_output2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 22:51:51 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 22:52:32 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_output.h"

void	ft_printwstr(wchar_t *str, size_t len, t_output_buffer *obuffer)
{
	while (len > 0 && *str)
	{
		ft_printwchar(*str, obuffer);
		str++;
		len--;
	}
}
