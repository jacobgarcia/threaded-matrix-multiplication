all:	multiplication

FileIO.o:	FileIO.c
		gcc -c FileIO.c

MatrixFunctions.o:	MatrixFunctions.c
			gcc -c MatrixFunctions.c

multiplication:		FileIO.o MatrixFunctions.o MultiplicateMatrices.c
			gcc FileIO.o MatrixFunctions.o MultiplicateMatrices.c -o multiplication

clean:
		rm multiplication *.o
