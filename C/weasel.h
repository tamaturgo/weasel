#ifndef WEASEL_H

#define WEASEL_H
#define COPY_COUNT 100
#define MUTATE_CHANCE 5

char *genseq(int len, int alphc, char alphv[]);

void modseq(char **seq, int alphc, char alphv[], float chance);

int seqcmp(char *seq, char *target);

int *seqcmpa(char *seq, int len, char *target);

#endif
