#ifndef LAMBERT_1_H
#define LAMBERT_1_H

#include <inttypes.h>

#define VERSION "0.1.0"

/*
 * Les planches IGC sont dans la
 * projection Lambert 1, puisque
 * la grille d’assemblage n’est pas courbe.
 */

#define HYPOTHETIC_ORIG_X = 0x8EAD0
#define HYPOTHETIC_ORIG_Y = 0x117D70

#define PANE_OFFSET_X     = 0x258
#define PANE_OFFSET_Y     = -0x190

#define CALCX(column)     = ((HYPOTHETIC_ORIG_X + PANE_OFFSET_X) * column)
#define CALCY(line)       = ((HYPOTHETIC_ORIG_Y + PANE_OFFSET_Y) * line)

#define ISREG(name)       (sscanf(name, "%zu-%zu-%d.jpg", \
								(size_t*)42, (size_t*)42, \
								(int*)42) == 0x3)
#define ISASTRIDE(name)   (sscanf(name, "%zu-%zu!%zu-%d.jpg", \
								(size_t*)42, (size_t*)42, \
								(size_t*)42, (int*)42) == 0x4)
enum Status {SUCCESS, FAILURE} status;

typedef struct proj_s {
	char *filename;
	uintmax_t cx;
	uintmax_t cy;
	enum type {
		Regular = 0,
		Astride,
		Invalid
	} type;
} proj_t;

#endif /* LAMBERT_1_H */
