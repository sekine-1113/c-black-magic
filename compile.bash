#!/usr/bin/bash

mkdir -p bin
rm -rf bin/*

for file in `ls src`; do
    gcc src/${file} -o bin/${file:0:-2}
done
