SHELL = /bin/sh

Zork: source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++
zork : source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++
zork_sample: source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++
	@./Zork XML_Samples/sample.txt.xml

zork_creature: source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++
	./Zork XML_Samples/creaturesample.xml

zork_trigger: source/*.cpp
	@g++ source/*.cpp -o Zork -static-libstdc++
	./Zork XML_Samples/triggersample.xml


clean:
	@rm Zork
