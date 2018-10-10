/*
 *
 * Image to WorldFile generator, a six line
 * plain text sidecar file used by geographic
 * information systems (GIS) to georeference
 * raster map images.
 *
 * (c) iomonad - <clement@trosa.io>
 *
 * This is a part of the IGC toolkit
 * (https://github.com/iomonad/igc)
 * Licensed under MIT license.
 *
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "world.h"

void
banner(void)
{
	printf("JPG to Worldfile generator - V%s\n\n", VERSION);
}

int
main(int argc, char *argv[])
{
	for (ssize_t i = 0x1; i < argc; i++) {
		if (write(0x0, argv[i], strlen(argv[i])) < 0 ||
			write(0x0, "\n", 0x1) < 0) {
			perror(argv[i]);
		}
	}
	return (EXIT_SUCCESS);
}
