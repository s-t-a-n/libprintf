/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_unsigned_dec.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 17:09:00 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/05 00:08:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_handle_width(t_conv_specs *cvs, char *numstr,
						int numstr_len)
{
	char	padder;

	cvs->width -= (cvs->precision > numstr_len - (numstr[0] == '-')) ?
		(cvs->precision - (numstr_len - (numstr[0] == '-'))) : 0;
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-') ? 1 : 0;
	cvs->width -= (cvs->flag_directives & apostroph) ? numstr_len / 3 : 0;
	padder = (cvs->precision == -1 && cvs->flag_directives & zero) ? '0' : ' ';
	if (cvs->width >= numstr_len - (numstr[0] == '-') && cvs->precision == -1
			&& cvs->flag_directives & zero)
		ft_handle_sign_dec(cvs, numstr);
	while (cvs->width > numstr_len)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static t_bool		ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def && **(cvs->fstring) == 'u')
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned int), 10, FALSE);
	else if (cvs->size == h)
		*numstr = ft_ultoa_base((unsigned short int)va_arg(*(cvs->args),
					unsigned int), 10, FALSE);
	else if (cvs->size == hh)
		*numstr = ft_ultoa_base((unsigned char)va_arg(*(cvs->args),
					unsigned int), 10, FALSE);
	else if (cvs->size == l || **(cvs->fstring) == 'U')
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned long), 10, FALSE);
	else if (cvs->size == ll)
		*numstr = ft_ulltoa_base(va_arg(*(cvs->args), unsigned long long),
				10, FALSE);
	else
		return (err);
	return (*numstr != NULL);
}

t_bool				ft_print_unsigned_dec_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	ft_handle_precision_dec(cvs, numstr, numstr_len);
	if (cvs->flag_directives & apostroph)
		ft_handle_apostroph_flag_dec(cvs->obuffer, numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'));
	else if (numstr[0] == '0' && cvs->precision == 0 && cvs->width > 0)
		ft_printchar(' ', cvs->obuffer);
	else if (!(numstr[0] == '0' && cvs->precision == 0))
		ft_printstr(numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'), cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
