check_PROGRAMS = runtests echo \
				 StringCchCatA-t StringCchCatW-t \
				 StringCbCatA-t StringCbCatW-t \
				 StringCchCatExA-t StringCchCatExW-t \
				 StringCbCatExA-t StringCbCatExW-t \
				 StringCchCatNA-t StringCchCatNW-t \
				 StringCbCatNA-t StringCbCatNW-t \
				 StringCchCatNExA-t StringCchCatNExW-t \
				 StringCbCatNExA-t StringCbCatNExW-t \
				 StringCchCopyA-t StringCchCopyW-t \
				 StringCbCopyA-t StringCbCopyW-t \
				 StringCchCopyExA-t StringCchCopyExW-t \
				 StringCbCopyExA-t StringCbCopyExW-t \
				 StringCchCopyNA-t StringCchCopyNW-t \
				 StringCbCopyNA-t StringCbCopyNW-t \
				 StringCchCopyNExA-t StringCchCopyNExW-t \
				 StringCbCopyNExA-t StringCbCopyNExW-t \
				 StringCchGetsExA-t StringCchGetsExW-t \
				 StringCbGetsExA-t StringCbGetsExW-t \
				 StringCchPrintfA-t StringCchPrintfW-t \
				 StringCbPrintfA-t StringCbPrintfW-t \
				 StringCchPrintfExA-t StringCchPrintfExW-t \
				 StringCbPrintfExA-t StringCbPrintfExW-t \
				 StringCchLengthA-t StringCchLengthW-t \
				 StringCbLengthA-t StringCbLengthW-t
check_LIBRARIES = tap/libtap.a
AM_CPPFLAGS = -I../src
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h tap/wide.c tap/wide.h
AM_LDFLAGS = ../src/libstrsafe.la tap/libtap.a
EXTRA_DIST = tap/libtap.sh TESTS \
			 StringCchGetsA-t StringCchGetsW-t \
			 StringCbGetsA-t StringCbGetsW-t \
			 data/*.in data/*.ans

check-local: $(check_PROGRAMS)
	./runtests TESTS
