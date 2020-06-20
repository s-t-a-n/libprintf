/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_flags1.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:39:09 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:39:26 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	ft_handle_flag_unspec_width(t_conv_specs *cvs)
{
	if (**(cvs->fstring) == '*')
	{
		(*(cvs->fstring))++;
		cvs->width = va_arg(*(cvs->args), int);
		if (cvs->width < 0)
		{
			cvs->width *= -1;
			cvs->flag_directives |= left_align;
		}
	}
	else if (**(cvs->fstring) != '0' && ft_isdigit(**(cvs->fstring)))
	{
		cvs->width = ft_atoi(*cvs->fstring);
		while (ft_isdigit(**cvs->fstring))
			(*(cvs->fstring))++;
	}
	return (noerr);
}

t_bool	ft_handle_flag_precision(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	if (**cvs->fstring == '*')
	{
		(*cvs->fstring)++;
		cvs->precision = va_arg(*(cvs->args), int);
	}
	else
	{
		cvs->precision = ft_atoi(*cvs->fstring);
		while (ft_isdigit(**cvs->fstring))
			(*cvs->fstring)++;
	}
	return (noerr);
}

t_bool	ft_handle_flag_minus(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | left_align;
	return (ft_handle_flag_unspec_width(cvs));
}

t_bool	ft_handle_flag_plus(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | plus;
	return (ft_handle_flag_unspec_width(cvs));
}

t_bool	ft_handle_flag_space(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | space;
	return (ft_handle_flag_unspec_width(cvs));
}
