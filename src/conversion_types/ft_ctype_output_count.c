/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_output_count.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 21:17:21 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/22 21:22:43 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool		ft_print_output_count_op(t_conv_specs *cvs)
{
	int	*iptr;

	iptr = va_arg(*(cvs->args), int *);
	if (iptr)
	{
		*iptr = cvs->obuffer->output_ctr + cvs->obuffer->index;
		return (noerr);
	}
	return (err);
}
