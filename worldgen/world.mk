WORLD_DIR    = worldgen/
WORLD_FILES  = world.c utils.c
WORLDCFLAGS  = -I./$(WORLD_DIR)
WORLD_SRC    = $(addprefix $(WORLD_DIR), $(WORLD_FILES))
WORLD_TARGET = world

world:
	$(CC) $(CFLAGS) $(WORLDCFLAGS) $(WORLD_SRC) -o $(WORLD_TARGET)
	$(STRIPER) $(STRIPC) $(WORLD_TARGET)
