# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luicasad <luicasad@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 13:07:33 by luicasad          #+#    #+#              #
#    Updated: 2025/10/26 00:59:03 by luicasad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                 COLORS                                       #
# ============================================================================ #
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED			=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82m
DARK_YELLOW		=	\033[38;5;143m
# ============================================================================ #
#                                 TARGETS                                      #
# ============================================================================ #

TARGET			= identify
SRCDIR			= ./
OBJDIR 			= ./obj/

REQUIRED_DIRS	= $(OBJDIR)
# ============================================================================ #
#                               COMPILER SETUP                                 #
# ============================================================================ #
CC 				= c++ -std=c++98
CC 				= clang++ -std=c++98
WRNFL			= -Wall -Wextra -Werror -Wshadow #-fsanitize=address
DBGFL			= #-g3  -pg
CFLGS			= $(DBGFL) $(WRNFL) -c 
#HEADS			= -I$(INCDIR)
LFLGS 			= #-fsanitize=address

HEADERS		=	Base.hpp \
				A.hpp \
				B.hpp \
				C.hpp \
				identify.hpp

SRCS_TARGET	= 	main.cpp \
			Base.cpp \
			A.cpp \
			B.cpp \
			C.cpp \
			identify.cpp


FILE_TARGET = $(addprefix $(SRCDIR_TARGET), $(SRCS_TARGET))
OBJS_TARGET = $(addprefix $(OBJDIR), $(SRCS_TARGET:.cpp=.o))
DEPE_TARGET = $(addprefix $(OBJDIR), $(SRCS_TARGET:.cpp=.d))

$(info tests  $(FILE_TARGET))
$(info object  $(OBJS_TARGET))
$(info patha $(DEPE_TARGET))

# ============================================================================ #
#                                 RULES                                        #
# ============================================================================ #
all: makedirs $(TARGET)
-include $(DEPE_TARGET)

# .......................... directories creation ............................ #
makedirs:
	$(shell for d in $(REQUIRED_DIRS); \
 				do \
 					[ -d $$d ] || mkdir -p $$d; \
 				done)
 
# ....................... dependencies construction .......................... #
#for each c file create its dependency file 
#READ GNU make  manual 4.14 Generating Prerequisites Automatically.
#READ GNU gcc manuel 3.13 Options controlling the preprocessor.
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) $(HEADS) -MM $< > $@.$$$$ ; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$

# .......................... targets construction ............................ #
$(TARGET): Makefile  $(OBJS_TARGET) $(HEADERS)
	@echo "$(GREEN)========== GATHERING $(TARGET) OBJECTS =============$(DEF_COLOR)"
	$(CC) $(LFLGS) $(OBJS_TARGET) -o $@ $(LLIBS) $(FRAMEWORKS)

# .......................... objects construction ............................ #
$(OBJDIR)%.o: $(SRCDIR_TARGET)%.cpp 
	@echo "$(GREEN)========== COMPILING $(TARGET) FILES ===============$(DEF_COLOR)"
	$(CC) $(CFLGS) $< -o $@   

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)


clean:
	rm -f $(TARGET)
	rm -rf $(OBJDIR)
	
fclean: clean
	rm -f $(TARGET)
	rm -rf $(OBJDIR)

re: fclean all

run:
	./$(TARGET)

profile:
	valgrind --tool=callgrind ./$(TARGET)
	callgrind_annotate

leaks:
	valgrind -s --error-limit=no --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all bonus test clean fclean re rebonus norma profile leaks
