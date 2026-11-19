CC:=gcc
INSTALL_DIR:=/usr/local/bin

BUILDFILE=dhnc

.PHONY: build debug install

build:
	mkdir -p build
	$(CC) -o build/$(BUILDFILE) main.c

debug:
	mkdir -p debug
	$(CC) -g -DDEBUG -o debug/dhnc-debug main.c
	debug/dhnc-debug -f TakaoGothic -r en-US sample.dhn | tee debug/debug-result.html

install: build/$(BUILDFILE)
	cp -u build/$(BUILDFILE) $(INSTALL_DIR)/.