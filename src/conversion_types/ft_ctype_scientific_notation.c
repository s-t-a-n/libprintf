/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_scientific_notation.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 18:20:31 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:14:01 by sverschu      ########   odam.nl         */
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

	cvs->flag_directives = ft_strchr(numstr, 'n')
		&& cvs->flag_directives & zero ? cvs->flag_directives ^ zero
		: cvs->flag_directives;
	cvs->width += (cvs->width == numstr_len && cvs->flag_directives & space);
	cvs->width -= (cvs->flag_directives & plus && numstr[0] != '-'
			&& !ft_strchr(numstr, 'a'));
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

static void		ft_handle_space_instead_of_sign_and_hash(t_conv_specs *cvs,
		char **numstr)
{
	char *tmp;

	if (cvs->precision == 0 && cvs->flag_directives & hash)
	{
		if (ft_strchr(*numstr, 'n'))
			return ;
		tmp = ft_strjoin(*numstr, ".");
		if (tmp)
		{
			free(*numstr);
			*numstr = tmp;
		}
	}
	if (cvs->flag_directives & space && **numstr != '-'
			&& !(cvs->flag_directives & plus) && !ft_strchr(*numstr, 'a'))
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
}

/*
** size L is not handled for floats because to handle long doubles accurately
** access to the math library is required (frexp, floor, pow)
*/

static t_bool	ft_handle_size(t_conv_specs *cvs, char **numstr)
{
	if (cvs->size == def)
		*numstr = ft_dtoa_sc(va_arg(*(cvs->args), double),
				(cvs->precision >= 0) ? cvs->precision : 6, NULL,
				**(cvs->fstring) == 'E');
	else if (cvs->size == L)
		return (err);
	else
		return (err);
	return (*numstr != NULL);
}

t_bool			ft_print_scnot_op(t_conv_specs *cvs)
{
	char	*numstr;
	int		numstr_len;

	if (!ft_handle_size(cvs, &numstr))
		return (err);
	if (cvs->flag_directives & left_align && cvs->flag_directives & zero)
		cvs->flag_directives = cvs->flag_directives ^ zero;
	ft_handle_space_instead_of_sign_and_hash(cvs, &numstr);
	numstr_len = ft_strlen(numstr);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, numstr, numstr_len);
	if (!(cvs->flag_directives & zero)
			|| cvs->width < numstr_len - (numstr[0] == '-'))
		ft_handle_sign(cvs, numstr);
	ft_printstr(numstr + (*numstr == '-'), numstr_len - (*numstr == '-'),
			cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, numstr, numstr_len);
	free(numstr);
	return (noerr);
}
