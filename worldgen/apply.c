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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <inttypes.h>

#include "lambert.h"

static status_t
rextract(proj_t **aref)
{
	char           oc[0x800];
	ssize_t        cx = 0;
	ssize_t        cy = 0;
	int			   year = 0;

	memset(oc, 0x0, 0x800);
	if ((sscanf((*aref)->filename, "%zu-%zu-%d.jpg", &cx, &cy, &year)) != 0) {
		printf("%zu %zu %d", cx, cy, year);
		printf("ok");
	}
	return (Success);
}

status_t
applyign(const char *filename)
{
	proj_t *proj = NULL;
	char   *base = NULL;

	if ((proj=(proj_t*)malloc(sizeof(proj_t))) == NULL) {
		return (Failure);
	}
	if ((base=(char*)basename((char*)filename)) == NULL) {
		base = (char*)filename;
	}
	proj->filename = strdup(base);
	if (!rextract(&proj)) {
		free(proj);
		return (Failure);
	}
	return (Success);
}
