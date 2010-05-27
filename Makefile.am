SUBDIRS = src . tests
ACLOCAL_AMFLAGS = -I /usr/share/aclocal
check_PROGRAMS = tests/runtests tests/StringCChLengthA-t
tests_runtests_CPPFLAGS = -DSOURCE='"$(abs_top_srcdir)/tests"' \
						  -DBUILD='"$(abs_top_srcdir)/tests"'
check_LIBRARIES = tests/tap/libtap.a
tests_tap_libtap_a_CPPFLAGS = -I$(abs_top_srcdir)/tests
tests_tap_libtap_a_SOURCES = tests/tap/basic.c tests/tap/basic.h

check-local: $(check_PROGRAMS)
	cd tests && ./runtests $(abs_top_srcdir)/tests/TESTS
