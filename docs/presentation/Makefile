MAKEFLAGS += k  #Keep going when some targets can't be made

FILE := document

JOB := document

DIAGRAM_SRCS := $(wildcard diagrams/*.drawio)
DIAGRAM_OBJS := $(patsubst %.drawio,%.pdf,$(DIAGRAM_SRCS))

DIAGRAM_DOC_SRCS := $(wildcard ../documentation/diagrams/*.drawio)
DIAGRAM_DOC_OBJS := $(patsubst %.drawio,%.pdf,$(DIAGRAM_DOC_SRCS))

ANIMATION_SRCS := $(wildcard animations/*.gif)
ANIMATION_OBJS := $(patsubst %.gif,%.png,$(ANIMATION_SRCS))

all: build clean_temps

build: diagrams diagrams_doc animations tex1 bib tex2

tex1:
	pdflatex -jobname ${JOB} ${FILE} --shell-escape # shell-escape: need for inkscape to convert SVG to PDF

tex2:
	pdflatex -jobname ${JOB} ${FILE} --shell-escape # shell-escape: need for inkscape to convert SVG to PDF
	pdflatex -jobname ${JOB} ${FILE} --shell-escape # shell-escape: need for inkscape to convert SVG to PDF

bib:
	bibtex ${JOB}

diagrams: $(DIAGRAM_OBJS)

diagrams/%.pdf: diagrams/%.drawio
	draw.io --crop -x -o $@ $<

diagrams_doc: $(DIAGRAM_DOC_OBJS)

../documentation/diagrams/%.pdf: ../documentation/diagrams/%.drawio
	draw.io --crop -x -o $@ $<

animations: $(ANIMATION_OBJS)

animations/%.png: animations/%.gif
	 magick convert -coalesce $< $@

clean: clean_temps
	rm -f *.pdf
	rm -f diagrams/*.pdf
	rm -f animations/*.png
	rm -f -r svg-inkscape/

clean_temps:
	rm -f *.acn
	rm -f *.acr
	rm -f *.alg
	rm -f *.aux
	rm -f *.bbl
	rm -f *.blg
	rm -f *.dvi
	rm -f *.equ
	rm -f *.glg
	rm -f *.glo
	rm -f *.gls
	rm -f *.gz
	rm -f *.ist
	rm -f *.lof
	rm -f *.log
	rm -f *.lol
	rm -f *.lot
	rm -f *.out
	rm -f *.toc
	rm -f *.nav
	rm -f *.snm
	rm -f *.fls
	rm -f *.fdb_latexmk
