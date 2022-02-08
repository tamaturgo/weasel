#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "weasel.h"

int
main()
{
	char alphv[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ",
		 *target = "METHINKS IT IS LIKE A WEASEL",
		 *seq,
		 *copies[COPY_COUNT];
	int alphc = strlen(alphv),
		len = strlen(target),
		done = 0,
		bsti, bstv,
		val, i, loop;

	/* Initialize */

	srand(time(NULL));

	seq = genseq(len, alphc, alphv);

	for (i = 0; i < COPY_COUNT; i++)
		copies[i] = (char*) malloc((len + 1) * sizeof(char));

	/* Real work */
	
	for (loop = 1; !done; loop++) {
		bstv = 0;
		bsti = 0;

		for (i = 0; i < COPY_COUNT; i++) {
			strcpy(copies[i], seq);
			modseq(copies + i, alphc, alphv, MUTATE_CHANCE);

			/* Compare the current copy */
			val = seqcmp(copies[i], target);

			if (val > bstv) {
				bstv = val;
				bsti = i;
			}
		}

		strcpy(seq, copies[bsti]);
		done = len == bstv;

		printf("%s - %d - %d#\n", seq, len - bstv, loop);
	}

	return 0;
}

