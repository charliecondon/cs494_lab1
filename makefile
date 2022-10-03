EXECUTABLES = finance

CFLAGS ?= -Wall -Wextra

all: $(EXECUTABLES) run

clean:
	rm -f finance *.pdf *.txt

finance: src/finance.cpp
	g++ $(CFLAGS) -o finance src/finance.cpp

run:
	./finance 100000 3333 10000 833 833 666 1333 416 916	
	jgraph -P < tmp.txt | ps2pdf - > tmp1.pdf
	./finance 100000 1190 10000 1190 1190 1190 1190 1190 1190
	jgraph -P < tmp.txt | ps2pdf - > tmp2.pdf	
	./finance 50000 694 0 0 694 694 694 694 694
	jgraph -P < tmp.txt | ps2pdf - > tmp3.pdf
	./finance 350000 10000 20000 500 2000 1000 5000 8000 2666
	jgraph -P < tmp.txt | ps2pdf - > tmp4.pdf
	./finance 400000 33333 10000 0 0 0 0 0 0
	jgraph -P < tmp.txt | ps2pdf - > tmp5.pdf
