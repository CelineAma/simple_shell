#!/bin/bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 ../*.c -o hsh
valgrind ./hsh
rm hsh