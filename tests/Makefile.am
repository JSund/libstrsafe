check_PROGRAMS = runtests echo \
		 StringCchCatA-t StringCchCatNA-t StringCchCopyA-t \
		 StringCchCopyNA-t StringCchLengthA-t StringCchPrintfA-t \
		 StringCchCatW-t StringCchCatNW-t StringCchCopyW-t \
		 StringCchCopyNW-t StringCchLengthW-t StringCchPrintfW-t \
		 StringCbCatA-t StringCbCatNA-t StringCbCopyA-t \
		 StringCbCopyNA-t StringCbLengthA-t StringCbPrintfA-t \
		 StringCbCatW-t StringCbCatNW-t StringCbCopyW-t \
		 StringCbCopyNW-t StringCbLengthW-t StringCbPrintfW-t \
		 StringCchCopyExA-t
check_LIBRARIES = tap/libtap.a
AM_CPPFLAGS = -I../src
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h tap/wide.c tap/wide.h
AM_LDFLAGS = ../src/libstrsafe.la tap/libtap.a
EXTRA_DIST = tap/libtap.sh Gets-t

check-local: $(check_PROGRAMS)
	./runtests TESTS
