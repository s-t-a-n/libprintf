/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_size1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 14:42:16 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:47:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	ft_handle_size_h(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		if (*(*(cvs->fstring)) == 'h')
		{
			(*(cvs->fstring))++;
			cvs->size = hh;
		}
		else
			cvs->size = h;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}

t_bool	ft_handle_size_l(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		if (*(*(cvs->fstring)) == 'l')
		{
			(*(cvs->fstring))++;
			cvs->size = ll;
		}
		else
			cvs->size = l;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}

t_bool	ft_handle_size_j(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		cvs->size = j;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}

t_bool	ft_handle_size_z(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		cvs->size = z;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}

t_bool	ft_handle_size_t(t_conv_specs *cvs)
{
	if (cvs->size == def)
	{
		(*(cvs->fstring))++;
		cvs->size = t;
		return (noerr);
	}
	(*(cvs->fstring))++;
	return (err);
}
