all : sum-nbo.c
	g++ -o sum-nbo sum-nbo.c

clean :
	rm *.bin
	rm sum-nbo
