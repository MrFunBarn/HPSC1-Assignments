CC=mpicc
flagGCC= -Wall -lm
flagIntel= -Wall
out=hw6

# all assumes gcc compiler wich needs -lm flag.
all:
	$(CC) $(flagGCC) BellBrandon_HW6.c -o $(out)

# Don't want the -lm flag on the intel complier for Sampede/Comet. Uses it's
# own optomised math library. 
intel:
	$(CC) $(flagIntel) BellBrandon_HW6.c -o $(out)
clean:
	rm $(out) 
