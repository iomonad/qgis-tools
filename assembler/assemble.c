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

static void __attribute__ ((destructor))
cleanup(void)
{
		Tile *p = NULL;

		while (!SLIST_EMPTY(&head))
		{
				p = SLIST_FIRST(&head);
				SLIST_REMOVE_HEAD(&head, next);
				g_object_unref(p->aref);
				free(p);
		}
		printf("Cleaned up, exiting ...\n");
}

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

static Dim __attribute__ ((const))
finalsize(void)
{
		Dim  final = {0x0, 0x0};
		Tile *p;

		SLIST_FOREACH(p, &head, next) {
				APPLYOFFSETS(final, p);
		}
		assert((final.height * final.width) > 0x7F7A60);
		return (final);
}

static VipsImage* __attribute__ ((hot))
		populate(const char *outfile)
{
		Tile *p  = NULL;
		Dim size = finalsize(), offsets = {0x0, 0x0};

		SLIST_FOREACH(p, &head, next) {
				printf("Got dimensions %llu - %llu\n",
					   p->dim.height, p->dim.width);
				APPLYOFFSETS(offsets, p);
		}
		printf("Writing to outfile: %s with dimension: %lld - %lld\n",
			   outfile, size.height, size.width);
		return (NULL);
}

int
main(int argc, char *argv[])
{
		VipsImage *output = NULL;

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
		if (!(output = populate(DEFAULT_OUT))) {
				vips_error_exit(NULL);
		}
		return (EXIT_SUCCESS);
}
