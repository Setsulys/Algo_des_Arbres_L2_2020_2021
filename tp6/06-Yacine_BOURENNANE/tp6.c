#include <stdio.h>
#include <stdlib.h>

typedef struct unionfind
{
	int taille; /* Taille des tableaux */
	int *pere; /* Tableau des peres */
	int *rang; /* Tableau des rangs */
	unsigned nb_appels;
} unionfind_t;

unionfond_t* initialisation(int N)
{
	unionfind_t* partition;
	int i;

	if ((partition = (unionfind_t *) malloc(sizeof(unionfond_t))) == NULL)
		return NULL;

	if ((partition->pere = (int *) malloc((N + 5) * sizeof(int))) == NULL)
		return NULL;

	if ((partition->pere = (int *) malloc((N + 5) * sizeof(int))) == NULL)
		return NULL;

	for (i = 0; i < N; i++)
	{
		partition->pere[i] = i;
		partition->rang[i] = 1;		
	}

	partition->taille = N;
	partition->nb_appels = 0;

	return partition;
}

int trouve_naif(unionfind_t* partition, int x)
{
	partition->nb_appels++;
	if (x == partition->pere[x])
		return x;

	return trouve_naif(partition, partition->pere[x]);
}

void fusion_naive(unionfind_t* partition, int x, int y)
{
	int representant_x, representant_y;
	
	representant_x = trouve_naif(partition, x);
	representant_y = trouve_naif(partition, y);

	if (representant_x != representant_y)
	{
		partition->nb_appels++;
		partition->pere[representant_y] = x;
	}
}

int trouve_compresse(unionfind_t* partition, int x)
{
	partition->nb_appels++;
	if (x != partition->pere[x])
		partition->pere[x] = trouve_compresse(partition, partition->pere[x]);

	return partition->pere[x];
}

void fusion_rang(unionfind_t* partition, int x, int y)
{
	int representant_x, representant_y;
	
	representant_x = trouve_compresse(partition, x);
	representant_y = trouve_compresse(partition, y);

	if (representant_x != representant_y)
	{
		if (partition->rang[representant_x] >= partition->rang[representant_y])
		{
			partition->nb_appels++;
			partition->pere[representant_y] = x;
			
			if (partition->rang[representant_x] < partition->rang[representant_y] + (x == representant_x ? 1 : 2))
			{
				partition->rang[representant_x] = partition->rang[representant_y] + (x == representant_x ? 1 : 2);
				partition->rang[representant_y] = '?';
			}
		}
		else
		{
			partition->nb_appels++;
			partition->pere[representant_x] = y;
			
			if (partition->rang[representant_y] < partition->rang[representant_x] + (y == representant_y ? 1 : 2))
			{
				partition->rang[representant_y] = partition->rang[representant_x] + (y == representant_y ? 1 : 2);
				partition->rang[representant_y] = '?';
			}
		}
	}
}

int main(void)
{
	unionfond_t P;

	return 0;
}