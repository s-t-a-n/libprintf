/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_float1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:54:36 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:26:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_handle_sign(t_conv_specs *cvs, char *numstr)
{
	if ((cvs->flag_directives & plus) && *numstr != '-'
			&& !ft_strnstr(numstr, "nan", 5))
		ft_printchar('+', cvs->obuffer);
	if (*numstr == '-')
		ft_printchar('-', cvs->obuffer);
}

static void		ft_handle_width(t_conv_specs *cvs, char *numstr, int numstr_len)
{
	char	padder;

	cvs->flag_directives = ft_strchr(numstr, 'n') && cvs->flag_directives
		& zero ? cvs->flag_directives ^ zero : cvs->flag_directives;
	cvs->width += (cvs->width == numstr_len && cvs->flag_directives & space);
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-'
			&& !ft_strchr(numstr, 'a')) ? 1 : 0;
	padder = (cvs->flag_directives & zero) ? '0' : ' ';
	if (cvs->width >= numstr_len - (numstr[0] == '-')
			&& cvs->flag_directives & zero
			&& !(cvs->flag_directives & left_align))
		ft_handle_sign(cvs, numstr);
	while (cvs->width > numstr_len)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static t_bool	ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def)
		*numstr = ft_ldtoa(va_arg(*(cvs->args), double),
				(cvs->precision >= 0) ? cvs->precision : 6);
	else if (cvs->size == L)
		*numstr = ft_ldtoa(va_arg(*(cvs->args), long double),
				(cvs->precision >= 0) ? cvs->precision : 6);
	else
		return (err);
	return (*numstr != NULL);
}

t_bool			ft_print_float_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	if (cvs->flag_directives & left_align && cvs->flag_directives & zero)
		cvs->flag_directives = cvs->flag_directives ^ zero;
	ft_handle_space_instead_of_sign_and_hash_float(cvs, &numstr);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	if (!(cvs->flag_directives & zero) || cvs->width <
			numstr_len - (numstr[0] == '-'))
		ft_handle_sign(cvs, numstr);
	ft_printstr(numstr + (*numstr == '-'), numstr_len
			- (*numstr == '-'), cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
