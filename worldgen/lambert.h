#ifndef LAMBERT_1_H
#define LAMBERT_1_H

#include <inttypes.h>

/*
 * Les planches IGC sont dans la
 * projection Lambert 1, puisque
 * la grille d’assemblage n’est pas courbe.
 */

#define HYPOTHETIC_ORIG_X = 0x8EAD0
#define HYPOTHETIC_ORIG_Y = 0x117D70

#define PANE_OFFSET_X     = 0x258
#define PANE_OFFSET_Y     = -0x190

#define CALCX(column) = ((HYPOTHETIC_ORIG_X + PANE_OFFSET_X) * column)
#define CALCY(line)   = ((HYPOTHETIC_ORIG_Y + PANE_OFFSET_Y) * line)

typedef enum status_e {
	Success = 0,
	Failure
} status_t;

typedef struct proj_s{
	char *filename;
	uintmax_t cx;
	uintmax_t cy;
	enum type {
		Regular = 0,
		Astride
	} type;
} proj_t;

#define RE_EXTRACTOR = "^([^-]*)-([^-]*)-.*$"

status_t applyign(const char *filename);

#endif /* LAMBERT_1_H */
