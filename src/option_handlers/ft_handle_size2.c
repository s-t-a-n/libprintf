/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_size2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:42:20 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:47:50 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	ft_handle_size_l_float(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		cvs->size = L;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}
