#include "common/common.h"
#include "common/timer.h"
#include "common/matrix.h"
#include "common/matvec.h"


int main(int argc, char * argv[]) {
	INIT_MATVEC

	mul_matvec(size, size, matA, vecB, vecC);

	DONE_MATVEC
}
