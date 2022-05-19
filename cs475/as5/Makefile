CC = gcc -fopenmp -lm  src/main.c -o simdspeed.exe

ifeq ($(OS),Windows_NT)
REALCC = $(CC) -L./target/release/wintime.lib
else
REALCC = $(CC)
endif

e:
	@$(REALCC)

rusttime:
	@cargo build --release

clean:
	@rm simdspeed.exe

bench:
	@hyperfine  --show-output ./simdspeed.exe 2>/dev/null | rg "([0-9]+\.[0-9]{2})" -o | sort -rn | head -n 1

per_size:
	@echo "[" > size_test.json
	@for i in 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152; do \
		$(REALCC) -DARRAY_SIZE=$$i ;\
		./simdspeed.exe >> size_test.json;\
	done
	@echo "]" >> size_test.json

per_thread:
	@echo "[" > thread_test.json
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12; do \
		$(REALCC) -DARRAY_SIZE=262144 -DNUMT=$$i ;\
		./simdspeed.exe >> thread_test.json;\
	done
	@echo "]" >> thread_test.json

viz:
	python3 visualize.py tests.json
