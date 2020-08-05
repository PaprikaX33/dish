#!/bin/sh

echo 'calling aclocal'
aclocal
echo 'calling autoconf'
autoconf
echo 'calling automake'
automake --add-missing
