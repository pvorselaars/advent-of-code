solution.bin: solution.c
	cc -O3 -llpsolve55 -o $@ $< && ./$@
	hyperfine -N --warmup 100 ./$@
