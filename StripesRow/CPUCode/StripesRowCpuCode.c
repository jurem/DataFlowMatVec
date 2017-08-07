#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matvec.h"


void mat_transform_rowstripes_pipes(int n, int m, int s, int p, float * src, float * dst) {
	int d = 0;
	for (int i = 0; i < n; i += s)
		for (int j = 0; j < m / p; j++)
			for (int k = 0; k < s; k++)
				for (int l = 0; l < p; l++)
					dst[d++] = src[(i + k) * m + (j * p + l)];
}


int main(int argc, char * argv[]) {
	INIT_MATVEC;

	mat_t matAT = mat_make(size, size);
	mat_transform_rowstripes_pipes(size, size, MatVec_STRIPE_SIZE, MatVec_PIPE_COUNT, matA, matAT);
	MatVec(size, matAT, vecB, vecC);
	free(matAT);

	DONE_MATVEC;
}

