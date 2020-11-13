/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_common_dec.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 17:07:11 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:08:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_handle_sign_dec(t_conv_specs *cvs, char *numstr)
{
	if ((cvs->flag_directives & plus) && *numstr != '-')
		ft_printchar('+', cvs->obuffer);
	if (*numstr == '-')
		ft_printchar('-', cvs->obuffer);
}

void		ft_handle_apostroph_flag_dec(t_output_buffer *obuffer,
				char *numstr, int numstr_len)
{
	t_bool	first_digit;

	first_digit = TRUE;
	while (*numstr)
	{
		if (!first_digit && numstr_len % 3 == 0)
			ft_printchar(',', obuffer);
		ft_printchar(*numstr, obuffer);
		numstr++;
		numstr_len--;
		first_digit = FALSE;
	}
}

void		ft_handle_precision_dec(t_conv_specs *cvs,
				char *numstr, int numstr_len)
{
	int		precision;

	precision = cvs->precision;
	if (numstr[0] == '-')
		cvs->precision -= (cvs->flag_directives & apostroph) ?
			(numstr_len / 3) - 1 : 0;
	else
		cvs->precision -= (cvs->flag_directives & apostroph) ?
			(numstr_len / 3) : 0;
	if (cvs->precision >= 0 || !(cvs->flag_directives & zero))
		ft_handle_sign_dec(cvs, numstr);
	while (precision + (numstr[0] == '-') > numstr_len)
	{
		ft_printchar('0', cvs->obuffer);
		precision--;
	}
}
