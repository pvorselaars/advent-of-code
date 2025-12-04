solution: main.c
	cc -o solution main.c -g && ./solution

bench: bench.c
	cc -o bench bench.c
	hyperfine -N --warmup 100 ./bench
