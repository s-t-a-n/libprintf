/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 16:14:47 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/04 23:01:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** higher dependencies
*/
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_output.h"

/*
** ft_printf.c
*/
int					ft_printf(const char *format_string, ...);

/*
** ft_dprintf.c
*/
int					ft_dprintf(int fd, const char *format_string, ...);

/*
** ft_vdprintf.c
*/
int					ft_vdprintf(int fd, const char *format_string, va_list args);
/*
** flag directives
*/
typedef enum		e_flag_dirs
{
	left_align = 1,
	plus = 2,
	zero = 4,
	space = 8,
	hash = 16,
	apostroph = 32
}					t_flag_dirs;

/*
** conversion sizes
*/
typedef enum		e_size
{
	def,
	hh,
	h,
	l,
	ll,
	j,
	L,
	t,
	z
}					t_size;

/*
** conversion specifications
*/
typedef struct		s_conv_specs
{
	int				width;
	int				precision;
	t_size			size;
	unsigned char	flag_directives;
	va_list			*args;
	t_output_buffer *obuffer;
	char			**fstring;
}					t_conv_specs;

/*
** ft_conversion.c
*/
t_bool				ft_run_conversion(t_conv_specs *cvs);
void				ft_set_conv_specs_defaults(t_conv_specs *cvs,
						t_output_buffer *obuffer, va_list *args,
						char **format_string);
t_conv_specs		*ft_initialize_conv_specs(t_output_buffer *obuffer,
						va_list *args, char **format_string);

/*
** ft_handle_flags.c
*/
t_bool				ft_handle_flag_unspec_width(t_conv_specs *cvs);
t_bool				ft_handle_flag_precision(t_conv_specs *cvs);
t_bool				ft_handle_flag_minus(t_conv_specs *cvs);
t_bool				ft_handle_flag_plus(t_conv_specs *cvs);
t_bool				ft_handle_flag_space(t_conv_specs *cvs);
t_bool				ft_handle_flag_zero(t_conv_specs *cvs);
t_bool				ft_handle_flag_hash(t_conv_specs *cvs);
t_bool				ft_handle_flag_apostroph(t_conv_specs *cvs);

/*
** ft_handle_size.c
*/
t_bool				ft_handle_size_h(t_conv_specs *cvs);
t_bool				ft_handle_size_l(t_conv_specs *cvs);
t_bool				ft_handle_size_j(t_conv_specs *cvs);
t_bool				ft_handle_size_z(t_conv_specs *cvs);
t_bool				ft_handle_size_t(t_conv_specs *cvs);
t_bool				ft_handle_size_l_float(t_conv_specs *cvs);

/*
** ft_func_router.c
*/
typedef t_bool		(*t_route_func)(t_conv_specs *);

t_route_func		ft_func_route_flags(char c);
t_route_func		ft_func_route_size(char c);
t_route_func		ft_func_route_type(char c);

/*
** ft_ctype_common_dec.c
*/
void				ft_handle_apostroph_flag_dec(t_output_buffer *obuffer,
						char *numstr, int numstr_len);
void				ft_handle_precision_dec(t_conv_specs *cvs,
						char *numstr, int numstr_len);
void				ft_handle_sign_dec(t_conv_specs *cvs, char *numstr);

/*
** ft_ctype_signed_dec.c
*/
t_bool				ft_print_signed_dec_op(t_conv_specs *cvs);

/*
** ft_ctype_unsigned_dec.c
*/
t_bool				ft_print_unsigned_dec_op(t_conv_specs *cvs);

/*
** ft_ctype_pointer.c
*/
t_bool				ft_print_ptraddr_op(t_conv_specs *cvs);

/*
** ft_ctype_hexadecimal_x.c
*/
t_bool				ft_print_hexadecimal_x_op(t_conv_specs *cvs);

/*
**	ft_ctype_hexadecimal_uppercase_x.c
*/
t_bool				ft_print_hexadecimal_uppercase_x_op(t_conv_specs *cvs);

/*
** ft_ctype_octal.c
*/
t_bool				ft_print_octal_op(t_conv_specs *cvs);

/*
** ft_ctype_char.c
*/
t_bool				ft_print_char_op(t_conv_specs *cvs);

/*
** ft_ctype_string.c
*/
t_bool				ft_print_str_op(t_conv_specs *cvs);

/*
** ft_ctype_percentage.c
*/
t_bool				ft_print_percentage_op(t_conv_specs *cvs);

/*
** ft_ctype_common_float.c
*/
void				ft_handle_space_instead_of_sign_and_hash_float(
						t_conv_specs *cvs, char **numstr);

/*
** ft_ctype_float.c
*/
t_bool				ft_print_float_op(t_conv_specs *cvs);

/*
** ft_ctype_scientific_notation.c
*/

t_bool				ft_print_scnot_op(t_conv_specs *cvs);

/*
** ft_ctype_scientific_notation_or_full_float.c
*/
t_bool				ft_print_scnot_float_shortest_op(t_conv_specs *cvs);

/*
** ft_ctype_chars_printed.c
*/
t_bool				ft_print_output_count_op(t_conv_specs *cvs);

#endif
