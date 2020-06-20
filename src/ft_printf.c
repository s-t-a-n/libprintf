/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 21:26:24 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/03 14:51:11 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv_specs	*ft_initialize_conv_specs(t_output_buffer *obuffer,
					va_list *args, char **format_string)
{
	t_conv_specs *cvs;

	cvs = malloc(sizeof(t_conv_specs));
	if (cvs)
	{
		cvs->width = 0;
		cvs->precision = -1;
		cvs->size = def;
		cvs->flag_directives = 0;
		cvs->args = args;
		cvs->obuffer = obuffer;
		cvs->fstring = format_string;
	}
	return (cvs);
}

static t_bool	ft_handle_conv_format(char **format_string,
					t_output_buffer *obuffer, va_list *args)
{
	int				iserror;
	t_conv_specs	*cvs;

	cvs = ft_initialize_conv_specs(obuffer, args, format_string);
	if (!cvs)
		return (err);
	iserror = 0;
	if (**(cvs->fstring) != '0' && (ft_isdigit(**(cvs->fstring))
				|| **(cvs->fstring) == '*'))
		iserror += ft_handle_flag_unspec_width(cvs);
	while (**(cvs->fstring) && ft_func_route_flags(**(cvs->fstring)))
		iserror += ft_func_route_flags(**(cvs->fstring))(cvs);
	while (**(cvs->fstring) && ft_func_route_size(**(cvs->fstring)))
		iserror += ft_func_route_size(**(cvs->fstring))(cvs);
	if (**(cvs->fstring) && ft_func_route_type(**(cvs->fstring)))
	{
		iserror += ft_func_route_type(**(cvs->fstring))(cvs);
		(*(cvs->fstring))++;
	}
	free(cvs);
	return (iserror > 0);
}

static void		ft_handle_conv_error(const char *format_string,
					t_output_buffer *obuffer)
{
	const char *format_string_orig = format_string;

	while (*format_string != '%')
		format_string--;
	while (format_string != format_string_orig)
	{
		ft_printchar(*format_string, obuffer);
		format_string++;
	}
}

int				ft_printf(const char *format_string, ...)
{
	t_output_buffer	*obuffer;
	va_list			args;

	obuffer = ft_initialize_obuffer(STDOUT);
	if (!obuffer)
		return (0);
	va_start(args, format_string);
	while (*format_string)
	{
		if (*format_string == '%')
		{
			format_string++;
			if (!ft_handle_conv_format((char **)&format_string, obuffer, &args))
				ft_handle_conv_error(format_string, obuffer);
		}
		else
		{
			ft_printchar(*format_string, obuffer);
			format_string++;
		}
	}
	va_end(args);
	return (ft_finalize_obuffer(obuffer));
}
