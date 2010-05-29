check_PROGRAMS = runtests StringCbCatA-t StringCbCatNA-t\
		 StringCbCopyA-t StringCbCopyNA-t StringCbLengthA-t\
		 StringCchCatA-t StringCchCatNA-t StringCchCopyA-t\
		 StringCchCopyNA-t StringCchLengthA-t 
check_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
AM_LDFLAGS = ../src/libstrsafe.la tap/libtap.a

check-local: $(check_PROGRAMS)
	./runtests TESTS
