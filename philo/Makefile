# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jevan-de <jevan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/27 11:47:23 by jevan-de      #+#    #+#                  #
#    Updated: 2021/10/27 11:47:23 by jevan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =				philo

CFLAGS =			-Wall -Werror -Wextra -fsanitize=address

LIBS =				-lpthread

INCLUDES =			includes

SRC_DIR = 			srcs

SRCS =				main.c \
					utils/ft_atoi.c \
					utils/ft_atol.c \
					utils/ft_isdigit.c \
					utils/ft_strlen.c \
					utils/is_valid_number.c \
					utils/destroy_objs.c \
					utils/parse_args.c \
					utils/get_time_ms.c \
					utils/safe_write_msg.c \
					philo/philo_destroy.c \
					philo/philo_new.c \
					philo/philo_run.c \
					philo/philo_monitor.c \
					philo/philo_eat.c \
					philo/philo_think.c \
					philo/philo_sleep.c \
					fork/fork_destroy.c \
					fork/fork_new.c \
					config/config_destroy.c \
					config/config_init.c \
					config/config_init_forks.c \
					config/config_init_philos.c

OBJS =				$(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

UNAME_S =			$(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	P = 			\x1b[35m
	B = 			\x1b[34m
	Y = 			\x1b[33m
	G = 			\x1b[32m
	R = 			\x1b[31m
	W = 			\x1b[0m
else ifeq ($(UNAME_S), Linux)
	P = 			\033[35m
	B = 			\033[34m
	Y = 			\033[33m
	G = 			\033[32m
	R = 			\033[31m
	W = 			\033[0m
endif

define ASCII

$P██████╗ $B██╗  ██╗$Y██╗$G██╗     $R ██████╗ $W███████╗$P ██████╗ $B██████╗ $Y██╗  ██╗$G███████╗$R██████╗ $W███████╗
$P██╔══██╗$B██║  ██║$Y██║$G██║     $R██╔═══██╗$W██╔════╝$P██╔═══██╗$B██╔══██╗$Y██║  ██║$G██╔════╝$R██╔══██╗$W██╔════╝
$P██████╔╝$B███████║$Y██║$G██║     $R██║   ██║$W███████╗$P██║   ██║$B██████╔╝$Y███████║$G█████╗  $R██████╔╝$W███████╗
$P██╔═══╝ $B██╔══██║$Y██║$G██║     $R██║   ██║$W╚════██║$P██║   ██║$B██╔═══╝ $Y██╔══██║$G██╔══╝  $R██╔══██╗$W╚════██║
$P██║     $B██║  ██║$Y██║$G███████╗$R╚██████╔╝$W███████║$P╚██████╔╝$B██║     $Y██║  ██║$G███████╗$R██║  ██║$W███████║
$P╚═╝     $B╚═╝  ╚═╝$Y╚═╝$G╚══════╝$R ╚═════╝ $W╚══════╝$P ╚═════╝ $B╚═╝     $Y╚═╝  ╚═╝$G╚══════╝$R╚═╝  ╚═╝$W╚══════╝
$W                             -- created by jevan-de --

endef
export ASCII

all: ascii $(NAME)

ascii:
	@printf "$$ASCII\n"

$(NAME): $(OBJS)
	@$(CC) -I$(INCLUDES) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@printf "\n[$(G)INFO$(W)]: Finished building program $(NAME)\n"

%.o: %.c
	@printf "[$(G)INFO$(W)]: Creating object file %-33.33s\r" $@
	@$(CC) -I$(INCLUDES) -c $(CFLAGS) -o $@ $<

clean:
	@echo "[$(G)INFO$(W)]: Cleaning object files ..."
	@rm -f $(OBJS)

fclean: clean
	@echo "[$(G)INFO$(W)]: Cleaning program files $(NAME)..."
	@rm -f $(NAME)

re: fclean all
