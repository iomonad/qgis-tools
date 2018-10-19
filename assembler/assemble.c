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

int
main(int argc, char *argv[])
{
	if (VIPS_INIT(argv[0]) || argc < 2) {
		vips_error_exit(NULL);
	}
    return 0;
}
