#!/usr/bin/env bash

target="/tmp/dll"
configScript="$PWD/configure"
configSiteFile="$target/install/share/config.site"
buildDir="$target/dish"

if [ "$1" ]
then
    target="$1"
fi

mkdir -p "$buildDir" "$target/install/share"

cd "$buildDir"

if [ ! -s $configSiteFile ]; then
    cat > "$configSiteFile" <<EOF
CPPFLAGS=-DDEBUG
CFLAGS="\${CFLAGS} -std=c11 -Wall -Wextra -Wshadow -Wcast-align -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2"
CXXFLAGS="\${CXXFLAGS} -g -Wall -Wextra -Werror -Og -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast"
EOF
fi

$configScript --prefix="$target/install"
