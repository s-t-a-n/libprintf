/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_octal.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/05 00:07:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/05 00:07:39 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_handle_hash_flag(t_conv_specs *cvs)
{
	ft_printchar('0', cvs->obuffer);
}

static void		ft_handle_width(t_conv_specs *cvs, char *numstr, int numstr_len)
{
	char	padder;

	cvs->width -= (cvs->precision > numstr_len) ?
		(cvs->precision - numstr_len) : 0;
	cvs->width -= (cvs->flag_directives & hash
			&& (cvs->precision > -1 || !(cvs->flag_directives & zero))
			&& cvs->precision <= numstr_len && numstr[0] != '0') ? 1 : 0;
	padder = (cvs->precision == -1 && cvs->flag_directives & zero) ? '0' : ' ';
	if (cvs->flag_directives & hash && cvs->flag_directives & zero
			&& cvs->precision == -1 && cvs->width <= numstr_len
			&& numstr[0] != '0')
	{
		ft_handle_hash_flag(cvs);
		cvs->width--;
	}
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
	if (cvs->flag_directives & hash
			&& (cvs->precision > -1 || !(cvs->flag_directives & zero))
			&& cvs->precision <= numstr_len && numstr[0] != '0')
		ft_handle_hash_flag(cvs);
	while (precision > numstr_len)
	{
		ft_printchar('0', cvs->obuffer);
		precision--;
	}
}

static t_bool	ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def && **(cvs->fstring) == 'o')
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned int), 8, FALSE);
	else if (cvs->size == h)
		*numstr = ft_ultoa_base((unsigned short int)va_arg(*(cvs->args),
					unsigned int), 8, FALSE);
	else if (cvs->size == hh)
		*numstr = ft_ultoa_base((unsigned char)va_arg(*(cvs->args),
					unsigned int), 8, FALSE);
	else if (cvs->size == l || **(cvs->fstring) == 'O')
		*numstr = ft_ultoa_base(va_arg(*(cvs->args), unsigned long), 8, FALSE);
	else if (cvs->size == ll)
		*numstr = ft_ulltoa_base(va_arg(*(cvs->args), unsigned long long),
				8, FALSE);
	else
		return (err);
	return (*numstr != NULL);
}

t_bool			ft_print_octal_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	ft_handle_precision(cvs, numstr, numstr_len);
	if (cvs->precision == 0 && ft_strncmp(numstr, "0", 2) == 0
			&& cvs->width > 0)
		ft_printchar(cvs->flag_directives & hash
				? '0' : ' ', cvs->obuffer);
	else if (!(cvs->precision == 0 && ft_strncmp(numstr, "0", 2) == 0
				&& !(cvs->flag_directives & hash)))
		ft_printstr(numstr, numstr_len, cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
