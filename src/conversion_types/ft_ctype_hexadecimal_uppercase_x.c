/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_hexadecimal_uppercase_x.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 22:49:53 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 22:49:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_handle_width(t_conv_specs *cvs, char *numstr, int numstr_len)
{
	char	padder;

	cvs->width -= (cvs->precision > numstr_len - (numstr[0] == '-')) ?
		(cvs->precision - (numstr_len - (numstr[0] == '-'))) : 0;
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-') ? 1 : 0;
	cvs->width -= (cvs->flag_directives & hash && numstr[0] != '0') ? 2 : 0;
	padder = (cvs->precision == -1 && cvs->flag_directives & zero) ? '0' : ' ';
	if (cvs->precision == -1 && cvs->flag_directives & hash
			&& cvs->flag_directives & zero && numstr[0] != '0')
		ft_printstr("0X", 2, cvs->obuffer);
	while (cvs->width > numstr_len)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static void		ft_handle_precision(t_conv_specs *cvs,
					char *numstr, int numstr_len)
{
	int		precision;

	precision = cvs->precision;
	if ((cvs->precision >= 0 || !(cvs->flag_directives & zero))
			&& cvs->flag_directives & hash && numstr[0] != '0')
		ft_printstr("0X", 2, cvs->obuffer);
	while (precision + (numstr[0] == '-') > numstr_len)
	{
		ft_printchar('0', cvs->obuffer);
		precision--;
	}
}

static t_bool	ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def)
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned int), 16, TRUE);
	else if (cvs->size == h)
		*numstr = ft_ultoa_base((unsigned short int)va_arg(*(cvs->args),
					unsigned int), 16, TRUE);
	else if (cvs->size == hh)
		*numstr = ft_ultoa_base((unsigned char)va_arg(*(cvs->args),
					unsigned int), 16, TRUE);
	else if (cvs->size == l)
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned long), 16, TRUE);
	else if (cvs->size == ll)
		*numstr = ft_ulltoa_base(va_arg(*(cvs->args), unsigned long long),
				16, TRUE);
	else
		return (err);
	return (*numstr != NULL);
}

t_bool			ft_print_hexadecimal_uppercase_x_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	ft_handle_precision(cvs, numstr, numstr_len);
	if (numstr[0] == '0' && cvs->precision == 0 && cvs->width > 0)
		ft_printchar(' ', cvs->obuffer);
	else if (!(numstr[0] == '0' && cvs->precision == 0))
		ft_printstr(numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'), cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
