solution.bin: solution.c
	cc -O3 -o $@ $< && ./$@
	hyperfine -N --warmup 100 ./$@
