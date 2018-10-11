/*
 *
 * Image to WorldFile generator, a six line
 * plain text sidecar file used by geographic
 * information systems (GIS) to georeference
 * raster map images.
 *
 * (c) 2018 iomonad - <clement@trosa.io>
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
#include "utils.h"
#include "lambert.h"

int
main(int argc, char *argv[])
{
	if (argc <= 1) {
		usage(argv[0]);
	}
	for (ssize_t i = 0x1; i < argc; i++) {
		if (!(applyign(argv[i]))) {
			dprintf(2, "Error while processing: %s\n", argv[i]);
		}
	}
	return (EXIT_SUCCESS);
}
