/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_func_router.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 15:12:29 by sverschu      #+#    #+#                 */
/*   Updated: 2020/01/05 16:48:13 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Kudoos to Liewe Gutter : (https://github.com/lgutter) for teaching me how to
** properly initialize a static jumptable
*/

t_route_func	ft_func_route_flags(char c)
{
	static const t_route_func route_flags_table[128] = {
		['.'] = &ft_handle_flag_precision,
		['-'] = &ft_handle_flag_minus,
		['+'] = &ft_handle_flag_plus,
		[' '] = &ft_handle_flag_space,
		['0'] = &ft_handle_flag_zero,
		['#'] = &ft_handle_flag_hash,
		['\''] = &ft_handle_flag_apostroph
	};

	return (ft_isascii(c) ? route_flags_table[(int)c] : NULL);
}

t_route_func	ft_func_route_size(char c)
{
	static const t_route_func route_size_table[128] = {
		['h'] = &ft_handle_size_h,
		['l'] = &ft_handle_size_l,
		['j'] = &ft_handle_size_j,
		['L'] = &ft_handle_size_l_float,
		['t'] = &ft_handle_size_t,
		['z'] = &ft_handle_size_z
	};

	return (ft_isascii(c) ? route_size_table[(int)c] : NULL);
}

t_route_func	ft_func_route_type(char c)
{
	static const t_route_func route_type_table[128] = {
		['c'] = &ft_print_char_op,
		['C'] = &ft_print_char_op,
		['s'] = &ft_print_str_op,
		['S'] = &ft_print_str_op,
		['i'] = &ft_print_signed_dec_op,
		['d'] = &ft_print_signed_dec_op,
		['D'] = &ft_print_signed_dec_op,
		['u'] = &ft_print_unsigned_dec_op,
		['U'] = &ft_print_unsigned_dec_op,
		['p'] = &ft_print_ptraddr_op,
		['x'] = &ft_print_hexadecimal_x_op,
		['X'] = &ft_print_hexadecimal_uppercase_x_op,
		['o'] = &ft_print_octal_op,
		['%'] = &ft_print_percentage_op,
		['f'] = &ft_print_float_op,
		['F'] = &ft_print_float_op,
		['e'] = &ft_print_scnot_op,
		['E'] = &ft_print_scnot_op,
		['g'] = &ft_print_scnot_float_shortest_op,
		['G'] = &ft_print_scnot_float_shortest_op,
		['n'] = &ft_print_output_count_op
	};

	return (ft_isascii(c) ? route_type_table[(int)c] : NULL);
}

/*
** strijders die het van Norminette verloren hebben:
** ['O'] = &ft_print_octal_op,
*/
