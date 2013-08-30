TEX_CMD=pdflatex -halt-on-error
BIB_CMD=bibtex

all: morgol.pdf

morgol.pdf: morgol.tex ../inc/style.sty ../inc/bibliography.bib
	$(TEX_CMD) morgol;
	$(BIB_CMD) morgol;
	$(TEX_CMD) morgol;	

clean:
	rm -f morgol.pdf *.aux *.log *.out *.bbl *.blg *.toc;
