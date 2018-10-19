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
#include <vips/vips.h>

#include "assemble.h"

static void
getdim(const char *fname, Dim *dim)
{
	VipsImage *file = NULL;

	if (!(file = vips_image_new_from_file(fname, NULL))) {
		vips_error_exit( NULL );
	}
	printf("File: %.40s - Height:%.7d Width:%.7d\n", fname,
	  vips_image_get_height(file),
	  vips_image_get_width(file));
	dim->width += vips_image_get_height(file);
	dim->height += vips_image_get_width(file);
	g_object_unref(file);
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
	printf("\nTotal Stuff: %lld x %lld\n", dim.height, dim.width);
	return 0;
}
