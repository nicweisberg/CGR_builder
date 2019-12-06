#include <stdlib.h>
#include <stdio.h>


struct test_t{
char reason[32];
int size;
char sequence[1024];
int testing;
char file[32];
};

typedef struct test_t test;

test tests[] = {

{"Scale too small", 16, "<<<actg", 1, ""},
{"edge case for scale", 31, "<<<actg", 1, ""},
{"edge case for scale", 33, "<<<actg", 1, ""},
{"edge case for scale", 4095, "<<<actg", 1, ""},
{"edge case for scale", 4097, "<<<actg", 1, ""},
{"Scale too big", 8192, "<<<actg", 1, ""},
{"not power of 2", 48, "<<<actg", 1, ""},
{"edge case for power of 2", 63, "<<<actg", 1, ""},
{"edge case for power of 2", 129, "<<<actg", 1, ""},
{"blank", 32, "<<< ' '", 1, ""},
{"single a", 32, "<<<a", 1, ""},
{"single c", 32, "<<<c", 1, ""},
{"single t", 32, "<<<t", 1, ""},
{"single g", 32, "<<<g", 1, ""},
{"simple example", 32, "<<<actgactg", 1, ""},
{"simple example with caps", 32, "<<<actgACTG", 1, ""},
{"non-allowable characters", 32, "<<<l2jb;h+k", 1, ""},
{"corner a", 32, "<<<aaaaaaaaaa", 1, ""},
{"corner c", 32, "<<<cccccccccc", 1, ""},
{"corner t", 32, "<<<tttttttttt", 1, ""},
{"corner g", 32, "<<<gggggggggg", 1, ""},
{"reading from text file", 32, "<testText_1.txt", 1, ""},
{"writing to pbm file", 32, "<<< ' '", 0, "> testPBM_1.pbm"},
{"writing to pbm file", 32, "<<<actgactgactgactgactgactg", 0, "> testPBM_2.pbm"},
{"writing to pbm file", 64, "<<<actgactgactgactgactgactgactgactgactg", 0, "> testPBM_3.pbm"},
{"writing to pbm file", 128, "<<<actgactgactgactgactgactgactgactgactgactgactgactgactgactgactg", 0, "> testPBM_4.pbm"},
{"writing to pbm file", 256, "<<<actgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactgactg", 0, "> testPBM_5.pbm"},
{"large size: 512", 512, "<testText_2.txt", 0, "> testPBM_6.pbm"},
{"large size: 1024", 1024, "<testText_3.txt", 0, "> testPBM_7.pbm"},
{"large size: 2048", 2048, "<testText_4.txt", 0, "> testPBM_8.pbm"},
{"large size: 4096", 4096, "<testText_5.txt", 0, "> testPBM_9.pbm"}




		};

char command[2048];

int main(){

	int numTests = sizeof(tests)/sizeof(tests[0]);
	for (int i = 0; i < numTests; i++){
		printf("Testing for: %s\n", tests[i].reason);
		sprintf(command, "./cgr %d %d %s %s", tests[i].size, tests[i].testing, tests[i].sequence, tests[i].file);
		printf("%s\n", command);
		system(command);
	}
}
