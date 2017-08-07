#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matvec.h"


int main(int argc, char * argv[]) {
	INIT_MATVEC;

	mat_t matAT = mat_make(size, size);
	mat_transform_rowstripes(size, size, MatVec_STRIPE_SIZE, matA, matAT);
	MatVec(size, matAT, vecB, vecC);
	free(matAT);

	DONE_MATVEC;
}
