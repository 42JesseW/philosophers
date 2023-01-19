NAME			= philo

INCLUDE_DIR		= includes

CFLAGS			= -Wall -Werror -Wextra

CLIBS			= -lpthread

SOURCE_FILES	= main.c \
				  parse_options.c \
				  philosopher.c \
				  table.c \
				  watcher.c \
				  write.c \
				  eat.c \
				  sleep.c \
				  utils/atoi.c \
				  utils/atol.c \
				  utils/isdigit.c \
				  utils/strlen.c \
				  utils/time.c

OBJECT_FILES	= $(SOURCE_FILES:.c=.o)

UNAME_S 		= $(shell uname -s)

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

$(NAME): $(OBJECT_FILES)
	@$(CC) $(OBJECT_FILES) -o $@ $(CFLAGS) $(CLIBS) -I $(INCLUDE_DIR)

%.o: %.c
	@if $(CC) -I$(INCLUDE_DIR) -c $(CFLAGS) -o $@ $<; then \
		printf "[$(G)INFO$(W)]: Successfully created object file %-33.33s\r" $@; \
	else \
	  	printf "[$(R)ERROR$(W)]: Failed to create object file %-33.33s\n" $@; \
	fi

clean:
	@rm -f $(OBJECT_FILES)

fclean: clean
	@rm -f $(philo) $(NAME)

re: fclean all

test:
	norminette
