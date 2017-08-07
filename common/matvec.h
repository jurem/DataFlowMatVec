#ifndef MATVEC_H
#define MATVEC_H


#include <getopt.h>


// show help
int help_flag = 0;

/* tracing
	0 - prints only n, sum of result, correctness, realtime, cputime
	1 - prints input, output, final result
*/
int trace = 0;

// seed for random numbers
int seed = 0;

// number of rows / columns. Matrix size is size * size
size_t size = 64;

// elements of matrix are in -range  to +range interval
float range = 100.0;


void help(const char * cmd) {
    printf("Usage: %s [filename]\n", cmd);
    printf("\nOptions:\n");
    printf("  -h, --help\n\tPrint short help\n");
    printf("  -t, --trace\n\tTrace level: 0,1,2\n");
    printf("  -s, --seed\n\tSeed for random numbers\n");
    printf("  -n, --size\n\tSize n of matrix\n");
    printf("  -r, --range\n\tRange of elements\n");
};


struct option options[] = {
	{ "help",	required_argument, 0, 'h' },
	{ "trace",	required_argument, 0, 't' },
	{ "seed",	required_argument, 0, 's' },
	{ "size",	required_argument, 0, 'n' },
	{ "range",	required_argument, 0, 'r' },
	{ 0, 0, 0, 0 }
};

#define SHORTOPT "ht:n:r:s:"


void parse_args(int argc, char * argv[]) {
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;

		switch (opt) {
			case 'h':
				help_flag = 1;
				break;
			case 't':
				trace = atoi(optarg);
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'n':
				size = atoi(optarg);
				break;
			case 'r':
				range = atoi(optarg);
				break;
			case '?':
				error(1, "Invalid option '%c'", optopt);
			default:
				abort();
		}
	}
	if (help_flag) {
		help(argv[0]);
		exit(0);
	}
}


void trace_inputs(size_t n, mat_t mat, vec_t vec) {
	if (trace < 2) return;
	printf("\nInput matrix\n");
	mat_print(n, n, mat);
	printf("\nInput vector\n");
	vec_print(n, vec);
}


void trace_outputs(size_t n, vec_t out) {
	if (trace < 2) return;
	printf("\nOutput vector\n");
	vec_print(n, out);
}


int check_outputs(size_t n, mat_t mat, vec_t vec, vec_t out) {
	float *expected = vec_make(n);
	mul_matvec(n, n, mat, vec, expected);
	int status = vec_check(n, out, expected, trace >= 1);
	free(expected);
	return status;
}


#define INIT_MATVEC \
	if (trace > 0) printf("Init ... \n"); \
	if (argc > 1) parse_args(argc, argv); \
	rand_init(seed); \
\
	if (trace > 0) printf("Generating inputs ... \n"); \
	mat_t matA = mat_make(size, size); \
	mat_t vecB = vec_make(size); \
	mat_t vecC = vec_make(size); \
\
	mat_rand(size, size, matA, range); \
	vec_rand(size, vecB, range); \
\
	trace_inputs(size, matA, vecB); \
\
	if (trace > 0) printf("Benchmarking ... \n"); \
	timing_t timer1; \
	timer_start(&timer1);
//	for (int _c = 0; _c < count; _c++) {


#define DONE_MATVEC \
	timer_stop(&timer1); \
\
	trace_outputs(size, vecC); \
\
	if (trace > 0) printf("Checking the results ... \n"); \
	float sum = vec_sumall(size, vecC); \
	char* status = check_outputs(size, matA, vecB, vecC) ? "ok" : "err"; \
	printf("%ld %f %s %ld %ld\n", size, sum, status, timer1.realtime, timer1.cputime); \
\
	if (trace > 0) printf("Done ... \n"); \
	free(matA); \
	free(vecB); \
	free(vecC); \
\
	return 0;


#endif
