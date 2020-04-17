AS_TARGET  = assemble
ACFLAGS    = $(shell pkg-config vips --cflags --libs)
AS_FOLDER  = assembler/
AS_SF      = assemble.c
AS_SOURCES = $(addprefix $(AS_FOLDER), $(AS_SF))

assembler:
	$(CC) $(CFLAGS) $(ACFLAGS) $(AS_SOURCES) -o $(AS_TARGET)
	$(STRIPER) $(STRIPC) $(AS_TARGET)
