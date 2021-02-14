cmake_minimum_required(VERSION 3.11)
project(printf)
add_library(printf STATIC
src/ft_printf.c
src/conversion_types/ft_ctype_common_dec.c
src/conversion_types/ft_ctype_hexadecimal_uppercase_x.c
src/conversion_types/ft_ctype_signed_dec.c
src/conversion_types/ft_ctype_output_count.c
src/conversion_types/ft_ctype_string.c
src/conversion_types/ft_ctype_percentage.c
src/conversion_types/ft_ctype_octal.c
src/conversion_types/ft_ctype_common_float.c
src/conversion_types/ft_ctype_hexadecimal_x.c
src/conversion_types/ft_ctype_unsigned_dec.c
src/conversion_types/ft_ctype_pointer.c
src/conversion_types/ft_ctype_float.c
src/conversion_types/ft_ctype_scientific_notation_or_full_float.c
src/conversion_types/ft_ctype_scientific_notation.c
src/conversion_types/ft_ctype_char.c
src/output/ft_output2.c
src/output/ft_output1.c
src/ft_output2.c
src/option_handlers/ft_handle_flags2.c
src/option_handlers/ft_handle_flags1.c
src/option_handlers/ft_handle_size2.c
src/option_handlers/ft_handle_size1.c
src/ft_func_router.c
)
target_include_directories(printf
PUBLIC
	inc
PRIVATE
	lib/libft/inc
)
target_compile_options(printf PRIVATE
${CMAKE_C_FLAGS}
-Wall -Wextra -Werror -std=c99 -pedantic
)
target_link_libraries(printf PRIVATE
ft)
