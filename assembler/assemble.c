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
printdim(const char *fname)
{
	VipsImage *file = NULL;

	if (!(file = vips_image_new_from_file(fname, NULL))) {
		vips_error_exit( NULL );
	}
	printf("File: %s - Height:%d Width:%d\n", fname,
	  vips_image_get_height(file),
	  vips_image_get_width(file));
	g_object_unref(file);
}

int
main(int argc, char *argv[])
{
	if (VIPS_INIT(argv[0])) {
		vips_error_exit(NULL);
	}
	for (ssize_t i = 1; i < argc; i++) {
		printdim(argv[i]);
	}
	return 0;
}
