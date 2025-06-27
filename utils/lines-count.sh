#!/bin/sh
find -name "*.c" -or -name "*.s" -or -name "*.h" -or -name "*.ld" -or -name "*.mk" -or -name "makefile" -or -name "*.sh"| xargs wc -l