/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_signed_dec.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 17:08:23 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 23:43:42 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_handle_width(t_conv_specs *cvs, char *numstr, int numstr_len)
{
	char	padder;

	cvs->width -= (cvs->precision > numstr_len - (numstr[0] == '-')) ?
		(cvs->precision - (numstr_len - (numstr[0] == '-'))) : 0;
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-'
			&& cvs->precision != 0) ? 1 : 0;
	cvs->width -= (cvs->flag_directives & apostroph)
		? numstr_len / 3 : 0;
	padder = (cvs->precision == -1 && cvs->flag_directives & zero
			&& !(cvs->flag_directives & left_align)) ? '0' : ' ';
	if (cvs->precision == -1 && cvs->flag_directives & zero
			&& !(cvs->flag_directives & left_align))
		ft_handle_sign_dec(cvs, numstr);
	while (cvs->width > numstr_len)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static t_bool	ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def
			&& (**(cvs->fstring) == 'i' || **(cvs->fstring) == 'd'))
		*numstr = ft_ltoa_base(va_arg(*(cvs->args), int), 10, false);
	else if (cvs->size == h)
		*numstr = ft_itoa((short int)va_arg(*(cvs->args), int));
	else if (cvs->size == hh)
		*numstr = ft_itoa((char)va_arg(*(cvs->args), int));
	else if (cvs->size == l || **(cvs->fstring) == 'I'
			|| **(cvs->fstring) == 'D')
		*numstr = ft_ltoa_base(va_arg(*(cvs->args), long), 10, false);
	else if (cvs->size == ll)
		*numstr = ft_lltoa_base(va_arg(*(cvs->args), long long), 10, false);
	else
		return (err);
	return (*numstr != NULL);
}

static void		ft_handle_space_instead_of_sign(t_conv_specs *cvs,
				char *numstr)
{
	if (cvs->flag_directives & space
			&& numstr[0] != '-'
			&& !(cvs->flag_directives & plus))
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
}

t_bool			ft_print_signed_dec_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	numstr_len = ft_strlen(numstr);
	ft_handle_space_instead_of_sign(cvs, numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	ft_handle_precision_dec(cvs, numstr, numstr_len);
	if (cvs->flag_directives & apostroph)
		ft_handle_apostroph_flag_dec(cvs->obuffer, numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'));
	else if (numstr[0] == '0' && cvs->precision == 0 && cvs->width > 0
			&& !(cvs->flag_directives & plus))
		ft_printchar(' ', cvs->obuffer);
	else if (!(numstr[0] == '0' && cvs->precision == 0))
		ft_printstr(numstr + (*numstr == '-'),
				numstr_len - (*numstr == '-'), cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
