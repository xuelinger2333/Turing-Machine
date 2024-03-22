# Turing-Machine
A command line tool of a simulated turing machine written in C++  
**Language:**  C++  
**Env:** Linux Terminal   
**Description:** 
Run turing in the command line, pass in the file name and input string of the Turing machine program as parameters.  
The program will output running results, showing whether the Turing machine program accepts the string, and the content of first paper tape when the Turing machine stops.  
**Examples:**  
```
$ turing --help   
usage: turing [-v|--verbose] [-h|--help] <tm> <input>

$ turing palindrome_detector.tm 100010001  
(ACCEPTED) true

$ turing palindrome_detector.tm 10001000  
(UNACCEPTED) false

$ turing palindrome_detector.tm 100A1A001  
illegal input string

$ turing palindrome_detector.tm 10x101  
illegal input string
```
