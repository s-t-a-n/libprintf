/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_flags.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 17:34:28 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:40:07 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	ft_handle_flag_zero(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | zero;
	return (ft_handle_flag_unspec_width(cvs));
}

t_bool	ft_handle_flag_hash(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | hash;
	return (ft_handle_flag_unspec_width(cvs));
}

t_bool	ft_handle_flag_apostroph(t_conv_specs *cvs)
{
	(*cvs->fstring)++;
	cvs->flag_directives = cvs->flag_directives | apostroph;
	return (ft_handle_flag_unspec_width(cvs));
}
