CC=gcc
LIBS=
OUT=psxmem

main: ./src/main.c
	mkdir -p ./build
	$(CC) ./src/cores/*.c ./src/*.c -o ./build/$(OUT) -DCORES_ON
	echo "PSXMem should now be compiled! You can run it using ./$(OUT) while in the build folder!"


debug: ./src/main.c
	mkdir -p ./build
	$(CC) ./src/cores/*.c ./src/*.c -o ./build/$(OUT) -DCORES_ON -DDEBUG_ON
	echo "PSXMem should now be compiled! You can run it using ./$(OUT) while in the build folder! DEBUG ON!"

coreless: ./src/main.c
	mkdir -p ./build
	$(CC) ./src/cores/*.c ./src/*.c -o ./build/$(OUT) 
	echo "PSXMem should now be compiled! You can run it using ./$(OUT) while in the build folder!"

