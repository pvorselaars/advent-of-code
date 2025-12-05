solution.bin: solution.c
	cc -g -o $@ $< && ./$@
