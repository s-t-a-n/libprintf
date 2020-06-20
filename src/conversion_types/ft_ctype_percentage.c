/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_percentage.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 18:15:24 by sverschu      #+#    #+#                 */
/*   Updated: 2019/12/29 18:15:31 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool		ft_print_percentage_op(t_conv_specs *cvs)
{
	char padder;

	padder = (cvs->flag_directives & zero
			&& !(cvs->flag_directives & left_align)) ? '0' : ' ';
	cvs->width -= 1;
	while (!(cvs->flag_directives & left_align) && cvs->width > 0)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
	ft_printchar('%', cvs->obuffer);
	while (cvs->width > 0)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
	return (noerr);
}
