#include <stdlib.h>
#include "weasel.h"

char*
genseq(int len, int alphc, char alphv[])
{
	int i;
	char *seq = (char*) malloc((len + 1) * sizeof(char));

	for (i = 0; i < len; i++)
		seq[i] = alphv[rand() % alphc];

	seq[len] = '\0';

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

int*
seqcmpa(char *seq, int len, char *target)
{
	int i,
		*a = (int*) malloc(len * sizeof(int));

	for (i = 0; i < len; i++)
		a[i] = seq[i] == target[i];

	return a;
}

