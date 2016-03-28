RNAME=report

all: q3 report

q1:
	@g++ -Wall -Wextra main.cpp sorters.cpp -o 567HW1 -O3
q3:
	@g++ -Wall -Wextra q3.cpp sorters.cpp classifiers.cpp -o 567HW1 -O3

report : $(RNAME).pdf

%.pdf: %.tex %.bib
	@pdflatex $<
	@bibtex $(RNAME).aux
	@pdflatex $<
	@pdflatex $<

clean:
	@rm -rf *.aux *.log *.pdf *.blg *.bbl *.out *.toc
