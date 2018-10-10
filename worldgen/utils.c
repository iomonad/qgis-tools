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
#include <stdlib.h>

#include "world.h"

void
banner(void)
{
	printf("JPG to Worldfile generator - V%s\n\n", VERSION);
}

void
usage(const char *name)
{
	printf("Usage: %s <jpeg list>\n", name);
	exit(EXIT_FAILURE);
}
