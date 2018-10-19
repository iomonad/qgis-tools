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
getdim(const char *fname, Dim *dim)
{
	VipsImage *file = NULL;

	if (!(file = vips_image_new_from_file(fname, NULL))) {
		vips_error_exit( NULL );
	}
	dim->width += vips_image_get_height(file);
	dim->height += vips_image_get_width(file);
	g_object_unref(file);
}

static void
populate(Dim *dim, const char *target)
{
	VipsImage *outfile = NULL;

	if (vips_embed(NULL, &outfile, 0, 0, dim->width,
		dim->height, NULL)) {
		vips_error_exit(NULL);
	}
	if (vips_image_write_to_file(outfile, target, NULL)) {
		vips_error_exit(NULL);
	}
}

int
main(int argc, char *argv[])
{
	static Dim dim = {0x0, 0x0};

	if (VIPS_INIT(argv[0])) {
		vips_error_exit(NULL);
	}
	for (ssize_t i = 1; i < argc; i++) {
		getdim(argv[i], &dim);
	}
	assert(dim.height != 0 && dim.width != 0);
	populate(&dim, DEFAULT_OUT);
	printf("\nGeneration tile: %lld x %lld\n", dim.height, dim.width);
	return 0;
}
