#!/usr/bin/env bash

target="/tmp/dll"
configScript="$PWD/configure"

if [ "$1" ]
then
    target="$1"
fi

mkdir -p "$target/build" "$target/install/share"
cat > "$target/install/share/config.site" <<EOF
CPPFLAGS=-DDEBUG
CFLAGS="\${CFLAGS} -std=c11 -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2"
CXXFLAGS="\${CXXFLAGS} -g -Wall -Wextra -Werror -Og -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast"
EOF

cd "$target/build"
$configScript --prefix="$target/install"
