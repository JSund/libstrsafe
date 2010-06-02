check_PROGRAMS = runtests \
		 StringCchCatA-t StringCchCatNA-t StringCchCopyA-t \
		 StringCchCopyNA-t StringCchLengthA-t \
		 StringCchCatW-t StringCchCatNW-t StringCchCopyW-t \
		 StringCchCopyNW-t StringCchLengthW-t \
		 StringCbCatW-t StringCbCatNW-t StringCbCopyW-t \
		 StringCbCopyNW-t StringCbLengthW-t 
check_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
AM_LDFLAGS = ../src/libstrsafe.la tap/libtap.a

check-local: $(check_PROGRAMS)
	./runtests TESTS
