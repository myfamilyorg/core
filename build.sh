#!/bin/bash

CC=gcc
CFLAGS="-fPIC \
	-Wno-builtin-declaration-mismatch \
	-fvisibility=hidden \
	-DSTATIC=static"
LDFLAGS="-shared -nostdlib -ffreestanding -fvisibility=hidden"
rm -rf ./target/objs/* ./target/lib/*
mkdir -p ./target/objs ./target/lib

COMMAND="${CC} ${CFLAGS} \
        -include src/types.H \
	-include src/syscall.H \
	-include src/misc.H \
        -c src/types.c -o ./target/objs/types.o"
echo ${COMMAND};
${COMMAND} || exit -1;

COMMAND="${CC} ${CFLAGS} \
	-include src/types.H \
	-include src/errno.H \
	-include src/syscall.H \
	-include src/misc.H \
	-c src/errno.c -o ./target/objs/errno.o"
echo ${COMMAND};
${COMMAND} || exit -1;

COMMAND="${CC} ${CFLAGS} \
	-include src/types.H \
	-include src/misc.H \
	-c src/misc.c -o ./target/objs/misc.o"
echo ${COMMAND};
${COMMAND} || exit -1;

COMMAND="${CC} ${CFLAGS} \
        -include src/types.H \
        -include src/errno.H \
        -include src/syscall.H \
        -include src/misc.H \
	-include src/init.H \
        -c src/init.c -o ./target/objs/init.o"
echo ${COMMAND};
${COMMAND} || exit -1;


COMMAND="${CC} ${CFLAGS} \
	-include src/types.H \
	-include src/errno.H \
	-include src/syscall.H \
	-include src/misc.H \
	-include src/init.H \
        -c src/syscall.c -o ./target/objs/syscall.o"
echo ${COMMAND};
${COMMAND} || exit -1;

COMMAND="${CC} ${LDFLAGS} -o ./target/lib/libfamcore.so ./target/objs/*.o"
echo ${COMMAND};
${COMMAND} || exit -1;
