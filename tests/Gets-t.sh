#!/bin/sh

test_gets () {
	ok_program "$1" 0 "$(cat data/$2_$3.ans)" ./echo ${unit} ${type} $3 < data/$2.in
}

run_tests () {
	test_gets "Input with no line breaks" no_newline 10
	test_gets "Single word with ending line break" single_word 10
	test_gets "Word that exactly fits into the buffer" exact_fit 10
	test_gets "Too short buffer" single_word 3
	test_gets "Multiple lines" multiple_lines 10
}

. "tap/libtap.sh"

plan 20

unit="ch"
type="A"
diag "Tests for StringCchGetsA"
run_tests

type="W"
diag "Tests for StringCchGetsW"
run_tests

unit="b"
type="A"
diag "Tests for StringCbGetsA"
run_tests

type="W"
diag "Tests for StringCbGetsW"
run_tests
