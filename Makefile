CC:=gcc

OUTPUTFILE=DaihonCompiler

.PHONY: build debug install

build:
	mkdir -p build
	$(CC) -o build/DaihonCompiler main.c

debug:
	mkdir -p debug
	$(CC) -g -DDEBUG -o debug/dhnc-debug main.c
	debug/dhnc-debug -o debug/debug-result.html -f TakaoGothic -r en-US -t "dhnc debug" sample.dhn

install: build/DaihonCompiler
	mkdir -p ${HOME}/.local/bin
	cp -u build/DaihonCompiler ${HOME}/.local/bin/.