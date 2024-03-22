#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <fstream>
#include "TuringMachineAdapter.h"
using namespace std;

TuringMachineAdapter turingMachineAdapter = TuringMachineAdapter();
void get_file(string path)
{
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		fprintf(stderr, "file not found\n");
        exit(22);
	}
	string buff;
	while (getline(fin, buff))
	{
		bool process_flag = turingMachineAdapter.process_line(buff);
		if (process_flag == false){
            fprintf(stderr, "invalid input\n");
            exit(23);
		}
	}
	fin.close();
}

void get_input(string input)
{
    turingMachineAdapter.process_input(input);
}

struct option long_options[] = {
    { "help", no_argument, NULL, 'h' },
    { "verbose", no_argument, NULL, 'v' },
    { 0, 0, 0, 0 },
};

int main(int argc, char* argv[]){
    if(argc == 1){
        return 1;
    }
    int opt;
    bool verbose_mode = false;
    bool has_arg = false;
    while ((opt = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch (opt) {
        case 'h':
            printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
            has_arg = true;
            break;
        case 'v':
            verbose_mode = true;
            break;

        }
    }
    if (argv[optind] != nullptr ){
        get_file(argv[optind]);
        if (argv[optind + 1] != nullptr)
        get_input(argv[optind + 1]);
    }
    else{
        if (has_arg == false){
            fprintf(stderr, "syntax error\n");
            exit(21);
        }else{
        return 0;
    }
    }
    turingMachineAdapter.initialize_tm();
    turingMachineAdapter.check_turing_completeness();
    turingMachineAdapter.run(verbose_mode);
    turingMachineAdapter.print_result(verbose_mode);

    return 0;
}
