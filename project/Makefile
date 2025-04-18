all:
	(cd timerLib && make install)
	(cd source && make)

load:
	(cd timerLib && make install)
	(cd source && make load)

clean:
	(cd source && rm *.o *.elf)
	(rm -rf h lib)
