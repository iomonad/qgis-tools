/*
 *
 * Full resolution assembler
 * for IGC's topology.
 *
 * (c) 2018 iomonad <clement@trosa.io>
 *
 * See LICENSE file.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vips/vips.h>

#include "assemble.h"

static void
prepare(Tile *tile, const char * const fname)
{
	tile->aref = NULL;

	if (!(tile->aref = vips_image_new_from_file(fname, NULL))) {
		vips_error_exit( NULL );
	}
	tile->dim.height = vips_image_get_height(tile->aref);
	tile->dim.width  = vips_image_get_width(tile->aref);
}

static VipsImage*
populate(const char *outfile)
{
	printf("Writing to outfile: %s\n", outfile);
	return NULL;
}

int
main(int argc, char *argv[])
{
	SLIST_INIT(&head);

	if (VIPS_INIT(argv[0])) {
		vips_error_exit(NULL);
	}
	for (ssize_t i = 1; i < argc; i++) {
		Tile *tile = NULL;

		if (!(tile = (Tile*)malloc(sizeof(Tile)))) {
			vips_error_exit( NULL );
		}
		prepare(tile, argv[i]);
		SLIST_INSERT_HEAD(&head, tile, next);
	}
	populate(DEFAULT_OUT);
	return 0;
}
