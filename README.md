Here's how to run the program
1. Install jgraph: sudo apt install jgraph
2. Call make (this will compile the source code and provide 5 examples)
3. Run on your own using the following commands:
    ./finance [post-tax income] [monthly house/rent payment] [total debt] [monthy debt payment] [monthly food] [monthly insurance] [monthy transport] [monthly savings/invesments] [other monthly payments]
    jgraph -P < tmp.txt | ps2pdf - > tmp.pdf
4. Call make clean to remove executable and all txt/pdf files from the current directory 