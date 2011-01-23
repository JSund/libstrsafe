SOURCES = libstrsafe.tex abstract.tex buffer-overflows.tex legacy-code.tex \
		  using-strsafe.tex

all: libstrsafe.pdf

libstrsafe.pdf: $(SOURCES)
	pdflatex libstrsafe.tex
	pdflatex libstrsafe.tex
	rm -f *.aux *.log *.out *.toc

clean:
	rm -f libstrsafe.pdf

.PHONY: clean
