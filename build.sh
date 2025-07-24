#!/bin/bash

rm -rf ./target/objs/* ./target/lib/*
mkdir -p ./target/objs ./target/lib
gcc -include src/types.H -include src/errno.H -include src/syscall.H -include src/misc.H -Wno-builtin-declaration-mismatch -fPIC -fvisibility=hidden -c src/errno.c -o ./target/objs/errno.o
gcc -include src/types.H -include src/errno.H -include src/syscall.H -include src/misc.H -Wno-builtin-declaration-mismatch -fPIC -fvisibility=hidden -c src/misc.c -o ./target/objs/misc.o
gcc -include src/types.H -include src/errno.H -include src/syscall.H -include src/misc.H -Wno-builtin-declaration-mismatch -fPIC -fvisibility=hidden -c src/syscall.c -o ./target/objs/syscall.o
gcc -shared -nostdlib -ffreestanding -fvisibility=hidden -o ./target/lib/libfamcore.so ./target/objs/*.o
