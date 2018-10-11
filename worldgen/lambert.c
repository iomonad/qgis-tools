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
#include <libgen.h>
#include <inttypes.h>

#include "lambert.h"

void __attribute__((constructor))
banner(void)
{
	printf("JPG to Worldfile generator - V%s\n\n", VERSION);
}

static void __attribute__((cold))
usage(const char *name)
{
	printf("Usage: %s <jpeg list>\n", name);
	exit(EXIT_FAILURE);
}

static ssize_t
lextype(proj_t **aref)
{
	if (*aref == NULL) {
		return (FAILURE);
	}
	if (ISREG((*aref)->filename)) {
		(*aref)->type = Regular;
	} else if (ISASTRIDE((*aref)->filename)) {
		(*aref)->type = Astride;
	} else {
		(*aref)->type = Invalid;
		return (FAILURE);
	}
	return (SUCCESS);
}

static ssize_t
rextract(proj_t **aref)
{
	if (!lextype(aref)) {
		return (FAILURE);
	}
	return (SUCCESS);
}

static ssize_t __attribute__((hot))
applyign(const char *filename)
{
	proj_t *proj = NULL;
	char   *base = NULL;

	if ((proj=(proj_t*)malloc(sizeof(proj_t))) == NULL) {
		return (FAILURE);
	}
	if ((base=(char*)basename((char*)filename)) == NULL) {
		base = (char*)filename;
	}
	proj->filename = strdup(base);
	if (rextract(&proj) == FAILURE) {
		free(proj);
		return (FAILURE);
	}
	return (SUCCESS);
}

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
