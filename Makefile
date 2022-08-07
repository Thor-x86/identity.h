HAS_PHP := $(shell command -v php 2> /dev/null)

ifndef MAX_ITERATION
export MAX_ITERATION := 64
endif

ifndef PREFIX
export PREFIX := /usr/local
endif

ifndef VERSION
export VERSION := unreleased
endif

all: clean prepare main.h.php define.h.php undefine.h.php

main.h.php:
	php -f ./src/main.h.php > ./out/include/identity.h

define.h.php:
	php -f ./src/define.h.php > ./out/include/identity/define.h

undefine.h.php:
	php -f ./src/undefine.h.php > ./out/include/identity/undefine.h

prepare:
ifndef HAS_PHP
	$(error Please install PHP first)
	exit 2
endif
	mkdir -p ./out && \
	mkdir -p ./out/include && \
	mkdir -p ./out/include/identity

clean:
	rm -rf out

test:
	${CC} test/main.c -I ./out/include -o out/test && out/test

install: uninstall
	mkdir -p ${PREFIX} && \
	mkdir -p ${PREFIX}/include && \
	cp -vr out/include/identity ${PREFIX}/include/identity && \
	cp -v out/include/identity.h ${PREFIX}/include/identity.h

uninstall:
	rm -vrf ${PREFIX}/include/identity && \
	rm -vf ${PREFIX}/include/identity.h

deploy:
	cd out && \
	tar -czvf identity-${VERSION}.tar.gz include

.PHONY: all prepare clean test install uninstall