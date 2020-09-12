#!/usr/bin/env bash

target="/tmp/dll"
configScript="$PWD/configure"

if [ "$1" ]
then
    target="$1"
fi

mkdir -p "$target/build" "$target/install/share"
echo -e 'CPPFLAGS=-DDEBUG\nCFLAGS="${CFLAGS} -std=c11 -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2"' > "$target/install/share/config.site"
cd "$target/build"
$configScript --prefix="$target/install"
