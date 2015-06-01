TEX_CMD=pdflatex -halt-on-error
BIB_CMD=bibtex

all: morgol.pdf

m4.pdf: m4.tex ../inc/style.sty ../inc/bibliography.bib
	$(TEX_CMD) m4;
	$(BIB_CMD) m4;
	$(TEX_CMD) m4;

clean:
	rm -f m4.pdf *.aux *.log *.out *.bbl *.blg *.toc;
