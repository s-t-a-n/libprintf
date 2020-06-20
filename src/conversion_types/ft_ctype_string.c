/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 22:48:57 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 22:48:58 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_handle_width(t_conv_specs *cvs, size_t strlen)
{
	char padder;

	padder = (cvs->flag_directives & zero
			&& !(cvs->flag_directives & left_align)) ? '0' : ' ';
	if ((size_t)cvs->precision < strlen)
		cvs->width -= (cvs->precision >= 0) ? cvs->precision : strlen;
	else
		cvs->width -= strlen;
	while (cvs->width > 0)
	{
		ft_printchar(padder, cvs->obuffer);
		cvs->width--;
	}
}

static t_bool	ft_print_ascii_str(t_conv_specs *cvs)
{
	char	*str;
	size_t	strlen;

	str = va_arg(*(cvs->args), char *);
	str = (!str) ? "(null)" : str;
	strlen = ft_strlen(str);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, strlen);
	if (cvs->precision == -1)
		ft_printstr(str, strlen, cvs->obuffer);
	else
		ft_printstr(str, cvs->precision, cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, strlen);
	return (noerr);
}

static t_bool	ft_print_unicode_str(t_conv_specs *cvs)
{
	wchar_t	*str;
	size_t	strlen;

	str = va_arg(*(cvs->args), wchar_t *);
	str = (!str) ? L"(null)" : str;
	strlen = ft_wcslen(str);
	if (!(cvs->flag_directives & left_align))
		ft_handle_width(cvs, strlen);
	if (cvs->precision == -1)
		ft_printwstr(str, strlen, cvs->obuffer);
	else
		ft_printwstr(str, cvs->precision, cvs->obuffer);
	if (cvs->flag_directives & left_align)
		ft_handle_width(cvs, strlen);
	return (noerr);
}

t_bool			ft_print_str_op(t_conv_specs *cvs)
{
	if (cvs->size == def && **(cvs->fstring) == 's')
		return (ft_print_ascii_str(cvs));
	else if (cvs->size == l || **(cvs->fstring) == 'S')
		return (ft_print_unicode_str(cvs));
	else
		return (err);
}
