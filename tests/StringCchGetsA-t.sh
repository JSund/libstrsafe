#!/bin/sh

. "tap/libtap.sh"

plan 5

test_gets () {
	ok_program "$1" 0 "$(cat data/$2_$3.ans)" ./echo ch A $3 < data/$2.in
}

test_gets "Input with no line breaks" no_newline 10
test_gets "Single word with ending line break" single_word 10
test_gets "Word that exactly fits into the buffer" exact_fit 10
test_gets "Too short buffer" single_word 3
test_gets "Multiple lines" multiple_lines 10
