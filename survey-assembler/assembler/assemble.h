#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <sys/queue.h>

typedef struct Sdim {
	long long height;
	long long width;
} Dim;

typedef struct Tile {
	Dim dim;
	VipsImage *aref;

	SLIST_ENTRY(Tile) next;
} Tile;

#define DEFAULT_OUT "vips-out.jpg"
#define APPLYOFFSETS(ref, tile) ref.height += tile->dim.height;\
	                            ref.width  += tile->dim.width

SLIST_HEAD( , Tile) head;

#endif /* ASSEMBLE_H */
