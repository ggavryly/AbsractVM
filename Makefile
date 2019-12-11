.PHONY: all, clean, fclean, re.
NAME = AVM

INC = -I ./include/

SRCS_NAME = src/AVM.cpp \
			src/Command.cpp \
			src/ErrorHandling.cpp \
			src/main.cpp \
			src/Parser.cpp

SRCO_NAME = $(SRCS_NAME:.cpp=.o)

all: $(NAME)

$(NAME):
	@clang++ -std="c++14" $(SRCS_NAME) $(INC) -o $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all