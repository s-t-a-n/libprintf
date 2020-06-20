/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 16:17:00 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 23:31:25 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool		ft_print_ascii_char(t_conv_specs *cvs)
{
	cvs->width -= 1;
	while (!(cvs->flag_directives & left_align) && cvs->width > 0)
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
	ft_printchar(va_arg(*(cvs->args), int), cvs->obuffer);
	while (cvs->width > 0)
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
	return (noerr);
}

/*
**	wchar_t is currently unstable : https://www.gnu.org/software/
**		libunistring/manual/html_node/The-wchar_005ft-mess.html
*/

t_bool		ft_print_unicode_char(t_conv_specs *cvs)
{
	wint_t wc;

	wc = va_arg(*(cvs->args), wint_t);
	if (wc > WCHAR_MAX)
		return (err);
	cvs->width -= ft_wclen(wc);
	while (!(cvs->flag_directives & left_align) && cvs->width > 0)
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
	ft_printwchar(wc, cvs->obuffer);
	while (cvs->width > 0)
	{
		ft_printchar(' ', cvs->obuffer);
		cvs->width--;
	}
	return (noerr);
}

t_bool		ft_print_char_op(t_conv_specs *cvs)
{
	if (cvs->size == def && **(cvs->fstring) == 'c')
		return (ft_print_ascii_char(cvs));
	else if (cvs->size == l || **(cvs->fstring) == 'C')
		return (ft_print_unicode_char(cvs));
	else
		return (err);
}
