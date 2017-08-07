#include <MaxSLiCInterface.h>
#include "Maxfiles.h"

#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matvec.h"


int main(int argc, char * argv[]) {
	INIT_MATVEC;

	MatVec(size, matA, vecB, vecC);

	DONE_MATVEC;
}
