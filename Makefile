#-------------EXECUTABLE--------------#

NAME = cub3d
BONUS = cub3d_bonus

#---------------LIBFT-----------------#

LIBFT = libft

#-------------INCLUDES----------------#

INCLUDES = includes
BONUS_INCLUDES = includes/bonus

#-------------SOURCES-----------------#

SOURCES_DIR = sources
SOURCES_MAIN = main.c

SOURCES_PARSING_DIR = sources/parsing
SOURCES_PARSING = cleaning.c error.c flood_fill.c \
	parse_colors_utils.c parse_colors.c parse_map_utils.c \
	parse_map.c parse_texture.c parse_utils.c \

SOURCES_EXEC_DIR = sources/execute
SOURCES_EXEC = mlx_key.c moving.c init_textures.c \
	exit.c mlx_utils.c render.c \
	game_loop.c game_loop_utils.c init.c

#---------------BONUS-----------------#

BONUS_SOURCES_DIR = sources/bonus
BONUS_SOURCES_MAIN = bonus_main.c

BONUS_SOURCES_PARSING_DIR = sources/bonus/parsing
BONUS_SOURCES_PARSING = bonus_cleaning.c bonus_error.c \
	bonus_flood_fill.c bonus_parse_map_utils.c bonus_parse_map.c \
	bonus_parse_texture.c bonus_parse_utils.c \

BONUS_SOURCES_EXEC_DIR = sources/bonus
BONUS_SOURCES_EXEC = bonus_mlx_keys.c bonus_moving.c bonus_init_textures.c \
	bonus_exit.c bonus_mlx_utils.c bonus_render.c \
	bonus_game_loop.c bonus_game_utils.c bonus_init.c \
	bonus_minimap.c bonus_moving2.c bonus_rotate.c \
	bonus_sprite.c

#-------------OBJECTS-----------------#

OBJECTSDIR = ./.objects
BOBJECTSDIR = ./.bonus_objects
OBJECTS_MAIN = $(addprefix $(OBJECTSDIR)/, $(SOURCES_MAIN:.c=.o))
OBJECTS_PARSING = $(addprefix $(OBJECTSDIR)/, $(SOURCES_PARSING:.c=.o))
OBJECTS_EXEC = $(addprefix $(OBJECTSDIR)/, $(SOURCES_EXEC:.c=.o))
OBJECTS = $(OBJECTS_MAIN) $(OBJECTS_PARSING) $(OBJECTS_EXEC)

BONUS_OBJECTS_MAIN = $(addprefix $(BOBJECTSDIR)/, $(BONUS_SOURCES_MAIN:.c=.o))
BONUS_OBJECTS_PARSING = $(addprefix $(BOBJECTSDIR)/, $(BONUS_SOURCES_PARSING:.c=.o))
BONUS_OBJECTS_EXEC = $(addprefix $(BOBJECTSDIR)/, $(BONUS_SOURCES_EXEC:.c=.o))
BOBJECTS = $(BONUS_OBJECTS_MAIN) $(BONUS_OBJECTS_PARSING) $(BONUS_OBJECTS_EXEC)

#-------------FLAGS-------------------#

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = -lmlx -lXext -lX11 -lXfixes -lm -g3 -O3

#------------COLORS-------------------#

COLOUR_GREEN = '\033[0;32m'
COLOUR_RED = '\033[0;31m'
COLOUR_BLUE = '\033[0;34m'
END_COLOUR = '\033[0m'
BOLD = '\033[1m'
COLOUR_ORANGE = '\033[38;5;208m'

#------------CODE---------------------#


all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJECTS)
	@echo " "
	@echo $(BOLD)$(COLOUR_ORANGE)"----Compiling Cub3D files now-----"$(END_COLOUR)
	@make --no-print-directory -C $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJECTS) -I.$(INCLUDES) -L./$(LIBFT) -lft
	@echo $(BOLD)$(COLOUR_GREEN)"🎉 Made Cub3D game successfully!🎉"$(END_COLOUR)
	@echo " "

$(BONUS): $(BOBJECTS)
	@echo " "
	@echo $(BOLD)$(COLOUR_ORANGE)"----Compiling Cub3D bonus files now-----"$(END_COLOUR)
	@make --no-print-directory -C $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(BONUS) $(BOBJECTS) -I.$(BONUS_INCLUDES) -L./$(LIBFT) -lft
	@echo $(BOLD)$(COLOUR_GREEN)"🎉   Made Cub3D game successfully!    🎉"$(END_COLOUR)
	@echo " "

$(OBJECTSDIR):
	@mkdir -p $(OBJECTSDIR)

$(OBJECTSDIR)/%.o:$(SOURCES_DIR)/%.c | $(OBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTSDIR)/%.o:$(SOURCES_PARSING_DIR)/%.c | $(OBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTSDIR)/%.o:$(SOURCES_EXEC_DIR)/%.c | $(OBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BOBJECTSDIR):
	@mkdir -p $(BOBJECTSDIR)

$(BOBJECTSDIR)/%.o:$(BONUS_SOURCES_DIR)/%.c | $(BOBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BOBJECTSDIR)/%.o: $(BONUS_SOURCES_PARSING_DIR)/%.c | $(BOBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BOBJECTSDIR)/%.o: $(BONUS_SOURCES_EXEC_DIR)/%.c | $(BOBJECTSDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --no-print-directory clean -C $(LIBFT)
	@rm -rf $(OBJECTSDIR) $(BOBJECTSDIR)
	@echo " "
	@echo 🗑$(COLOUR_RED)" Removed all objects files."$(END_COLOUR)🗑
	@echo " "

fclean:
	@make --no-print-directory fclean -C $(LIBFT)
	@rm -rf $(NAME) $(OBJECTSDIR) $(BOBJECTSDIR) $(BONUS)
	@echo " "
	@echo 🗑$(COLOUR_RED)" Removed everything."$(END_COLOUR)🗑
	@echo " "

re: fclean all

reb: fclean bonus

.PHONY: all bonus clean fclean re reb
