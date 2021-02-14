/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_snprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 21:26:24 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:51:11 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int                 ft_snprintf(char *str, size_t size, const char *format_string, ...)
{
	va_list args;
	int rvalue;

	va_start(args, format_string);
	rvalue = ft_vsnprintf(str, size, format_string, args);
	va_end(args);
	return (rvalue);
}
