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

SLIST_HEAD( , Tile) head;

#endif /* ASSEMBLE_H */
