# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/04 23:06:10 by sverschu      #+#    #+#                  #
#    Updated: 2020/06/19 17:40:29 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

# directories
SRC_D = src
OBJ_D = obj
INC_D = inc
LIB_D = lib

# C source and header files
SRC =	$(SRC_D)/ft_func_router												\
		$(SRC_D)/ft_printf													\
		$(SRC_D)/output/ft_output1											\
		$(SRC_D)/output/ft_output2											\
		$(SRC_D)/conversion_types/ft_ctype_char								\
		$(SRC_D)/conversion_types/ft_ctype_hexadecimal_uppercase_x			\
		$(SRC_D)/conversion_types/ft_ctype_hexadecimal_x					\
		$(SRC_D)/conversion_types/ft_ctype_octal							\
		$(SRC_D)/conversion_types/ft_ctype_output_count						\
		$(SRC_D)/conversion_types/ft_ctype_percentage						\
		$(SRC_D)/conversion_types/ft_ctype_pointer							\
		$(SRC_D)/conversion_types/ft_ctype_common_float						\
		$(SRC_D)/conversion_types/ft_ctype_float							\
		$(SRC_D)/conversion_types/ft_ctype_scientific_notation				\
		$(SRC_D)/conversion_types/ft_ctype_scientific_notation_or_full_float\
		$(SRC_D)/conversion_types/ft_ctype_common_dec						\
		$(SRC_D)/conversion_types/ft_ctype_signed_dec						\
		$(SRC_D)/conversion_types/ft_ctype_unsigned_dec						\
		$(SRC_D)/conversion_types/ft_ctype_string							\
		$(SRC_D)/option_handlers/ft_handle_flags1							\
		$(SRC_D)/option_handlers/ft_handle_flags2							\
		$(SRC_D)/option_handlers/ft_handle_size1							\
		$(SRC_D)/option_handlers/ft_handle_size2

SRC := $(SRC:%=%.c)

INC =	$(INC_D)/ft_output.h												\
		$(INC_D)/ft_printf.h												\
		$(LIB_D)/libft/inc/ft_std.h											\
		$(LIB_D)/libft/inc/libft.h
OBJ :=	$(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

LIBFT = $(LIB_D)/libft/libft.a

# outputting
CC_LOG=./.cc.log
CC_ERROR=./.cc.error

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

ECHO=printf
CAT=cat

# compiler and linker
CC = clang
LD = ar

# compile flags
CC_FLAGS = -Werror -Wextra -Wall
LD_FLAGS = -rcs

# debugging and optimization flags
CC_OPT_FLAGS = -O3													\
			   -march=native

ifeq ($(ASAN),1)
	CC_FLAGS += -fsanitize=address										\
				-fno-optimize-sibling-calls
	LD_FLAGS +=
	DEBUG = 1
endif

ifeq ($(DEBUG),1)
	CC_FLAGS += -g 														\
				-O0														\
				-fno-omit-frame-pointer									\
				-fstack-protector-all									\
				-DDEBUG
	LD_FLAGS +=
else
	CC_FLAGS += $(CC_OPT_FLAGS)
	LD_FLAGS +=
endif

# make commands
all: $(NAME)


$(NAME): $(OBJ_D) $(OBJ) $(INC) $(LIBFT)
	@$(ECHO) "Linking $(NAME)..."
	@$(LD) $(LD_FLAGS) $(NAME) $(OBJ) 2>$(CC_LOG) || touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(OBJ_D):
	@mkdir -p $(OBJ_D)
	@mkdir -p $(OBJ_D)/output
	@mkdir -p $(OBJ_D)/conversion_types
	@mkdir -p $(OBJ_D)/option_handlers

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_D)/libft/inc -c $< -o $@ 2>$(CC_LOG) \
		|| touch $(CC_ERROR)
	@if test -e $(CC_ERROR); then											\
		$(ECHO) "$(ERROR_STRING)\n" && $(CAT) $(CC_LOG);					\
	elif test -s $(CC_LOG); then											\
		$(ECHO) "$(WARN_STRING)\n" && $(CAT) $(CC_LOG);						\
	else																	\
		$(ECHO) "$(OK_STRING)\n";											\
	fi
	@$(RM) -f $(CC_LOG) $(CC_ERROR)

$(LIBFT):
	@make -C $(LIB_D)/libft

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_D)
	@make -C $(LIB_D)/libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus
	@make -C $(LIB_D)/libft fclean

bonus: $(NAME)
	@touch bonus

re: fclean all

.PHONY = all clean fclean re bonus
