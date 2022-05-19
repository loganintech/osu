CC = /usr/local/cuda-10.0/bin/nvcc -O3 src/montecarloTemplate.cu -o monte.o

build:
	$(CC)

clean:
	rm a.out

bench:
	echo "[" > trial_records$$b.json
	for b in 16 32 64 128; do \
		for t in 16384 32768 65536 131072 262144 524288 1048576; do \
			$(CC) -DNUMTRIALS=$$t -DBLOCKSIZE=$$b;\
			./monte.o | rg "\{.*\}," -o >> trial_records.json ; \
		done \
	done
	echo "]" >> records.json

