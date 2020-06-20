/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_pointer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 21:36:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:00:37 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_handle_sign(t_conv_specs *cvs, char *numstr)
{
	if ((cvs->flag_directives & plus) && *numstr != '-')
		ft_printchar('+', cvs->obuffer);
	if (*numstr == '-')
		ft_printchar('-', cvs->obuffer);
}

static void	ft_handle_width(t_conv_specs *cvs, char *numstr, int numstr_len)
{
	char	padder;

	cvs->width -= 2;
	cvs->width -= (cvs->precision > numstr_len - (numstr[0] == '-')) ?
		(cvs->precision - (numstr_len - (numstr[0] == '-'))) : 0;
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-') ? 1 : 0;
	padder = (cvs->precision == -1 && cvs->flag_directives & zero) ? '0' : ' ';
	if (cvs->width >= numstr_len - (numstr[0] == '-') && cvs->precision == -1
			&& cvs->flag_directives & zero)
		ft_handle_sign(cvs, numstr);
	while (cvs->width + (numstr[0] == '0' && cvs->precision == 0
				&& cvs->width > 0) > numstr_len)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static void	ft_handle_precision(t_conv_specs *cvs,
					char *numstr, int numstr_len)
{
	int		precision;

	ft_printstr("0x", 2, cvs->obuffer);
	precision = cvs->precision;
	if (cvs->precision >= 0 || !(cvs->flag_directives & zero))
		ft_handle_sign(cvs, numstr);
	while (precision + (numstr[0] == '-') > numstr_len)
	{
		ft_printchar('0', cvs->obuffer);
		precision--;
	}
}

t_bool		ft_print_ptraddr_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	numstr = ft_ultoa_base((unsigned long)va_arg(*(cvs->args), void *),
			16, false);
	if (!numstr)
		return (err);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	ft_handle_precision(cvs, numstr, numstr_len);
	if (numstr[0] == '0' && cvs->precision == 0 && cvs->width > 0
			&& numstr_len > 1)
		ft_printchar(' ', cvs->obuffer);
	else if (!(numstr[0] == '0' && cvs->precision == 0))
		ft_printstr(numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'), cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
