#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 DIRECTORY"
    exit 1
fi
directory="$1"
mkdir -p "$directory"
mkdir -p "$directory"/a
mkdir -p "$directory"/a/c/d
mkdir -p "$directory"/e/c
mkdir -p "$directory"/e/d
man printf > "$directory"/a/file1.txt
man ls > "$directory"/a/file2.txt

cp /bin/bash "$directory"/e/c/bash_copy

cp /lib/x86_64-linux-gnu/libc.so.6 "$directory"/e/d/libc.so.6_copy

chmod 777 "$directory"/*
chmod 777 "$directory"/a/*
chmod 777 "$directory"/e/c/*



