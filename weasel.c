#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COPY_COUNT 100
#define MUTATE_CHANCE 5

char*
genseq(int len, int alphc, char alphv[])
{
	int i;
	char *seq = (char*) malloc((len + 1) * sizeof(char));

	for (i = 0; i < len; i++)
		seq[i] = alphv[rand() % alphc];

	return seq;
}

void
modseq(char **seq, int alphc, char alphv[], float chance)
{
	int i, j;

	for (i = 0; (*seq)[i] != '\0'; i++) {
		if (rand() % 100 < chance) {
			j = rand() % alphc;

			/* Same char?? Get the next one */
			if ((*seq)[i] == alphv[j])
				j = (j + 1) % alphc;

			(*seq)[i] = alphv[j];
		}
	}
}

int
seqcmp(char *seq, char *target)
{
	int s;

	for (s = 0; *seq != '\0' && *target != '\0'; seq++, target++)
		s += *seq == *target;

	return s;
}

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

