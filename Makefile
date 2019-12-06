
.PHONY: clean

all: cgr runtests

CGR_OBJECT = cgr.o cgr_plot.o cgr_aux.o
CFLAGS = -Wall -Wextra -c
LDFLAGS = -Wall -Wextra -lnetpbm -o

cgr_aux.o: cgr_aux.c cgr_aux.h cgr_plot.h
	gcc $(CFLAGS) cgr_aux.c

cgr_plot.o: cgr_plot.c cgr_aux.h cgr_plot.h cgr.h
	gcc $(CFLAGS) cgr_plot.c

cgr.o: cgr.c cgr.h cgr_plot.h cgr_aux.h
	gcc $(CFLAGS) cgr.c

cgr: $(CGR_OBJECT)
	gcc $(CGR_OBJECT) $(LDFLAGS) cgr

runtests:
	gcc -Wall -Wextra test_cgr.c -o runtests

clean:
	rm -f *.o
	rm -f *.pbm
	rm -f cgr
	rm -f runtests
	rm -f testLogs.txt
