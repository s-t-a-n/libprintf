/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ctype_common_float.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 17:24:05 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 17:24:28 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_handle_space_instead_of_sign_and_hash_float(t_conv_specs *cvs,
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
