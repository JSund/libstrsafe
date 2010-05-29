check_PROGRAMS = runtests StringCchLengthA-t
check_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
AM_LDFLAGS = -I ../src/libstrsafe.la

check-local: $(check_PROGRAMS)
	./runtests TESTS
