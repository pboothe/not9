.PHONY: all clean

all: article.pdf basic basicnopause basicreorder notr notrcount genetic
clean:
	rm -f *.aux *.log *.bbl *.blg article.pdf basic basicnopause basicreorder notr notrcount *.pyc

basic: basic.cpp
	g++ -o $@ -O3 $<
basicnopause: basicnopause.cpp
	g++ -o $@ -O3 $<
basicreorder: basicreorder.cpp
	g++ -o $@ -O3 $<
genetic: genetic.cpp
	g++ -o $@ -O3 $<

article.pdf: *.tex bibliography.bib
	pdflatex article
	bibtex article
	pdflatex article
	pdflatex article


GENETICDATA=geneticdata/1.dat geneticdata/2.dat geneticdata/3.dat geneticdata/4.dat geneticdata/5.dat geneticdata/6.dat geneticdata/7.dat geneticdata/8.dat geneticdata/9.dat

geneticdata/%.dat: genetic
	./genetic | tee $@

genedata: $(GENETICDATA)

SEQDATAFILES=seqdata/0-5.dat seqdata/5-10.dat seqdata/10-15.dat seqdata/15-20.dat seqdata/20-25.dat seqdata/25-30.dat seqdata/30-35.dat seqdata/35-40.dat seqdata/40-45.dat seqdata/45-50.dat
INTDATAFILES=intdata/0-5.dat intdata/5-10.dat intdata/10-15.dat intdata/15-20.dat intdata/20-25.dat intdata/25-30.dat intdata/30-35.dat intdata/35-40.dat intdata/40-45.dat intdata/45-50.dat

#$(SEQDATAFILES) have been removed due to irrelevance
data:  $(INTDATAFILES) genedata

notr: notr.cpp
	g++ -o $@ -O3 $<

seqdata/%.dat: notr
	./notr `echo $* | sed -e 's/-.*/0000/'` `echo $* | sed -e 's/.*-\(.*\)/\10000/'`> $@

notrcount: notrcount.cpp
	g++ -o $@ -O3 $<

intdata/%.dat: notrcount
	./notrcount `echo $* | sed -e 's/-.*/0000/'` `echo $* | sed -e 's/.*-\(.*\)/\10000/'`> $@
