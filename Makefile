solution.bin: solution.c
	cc -g -o $@ $< && ./$@
	hyperfine -N --warmup 100 ./$@
