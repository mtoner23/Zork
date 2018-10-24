Zork: source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++

clean:
	@rm Zork