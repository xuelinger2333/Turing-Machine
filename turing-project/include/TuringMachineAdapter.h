#ifndef TURINGMACHINEADAPTER_H
#define TURINGMACHINEADAPTER_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <stdio.h>
#include <errno.h>
#include "TuringMachine.h"
using namespace std;


class TuringMachineAdapter
{
    public:
        TuringMachineAdapter();
        virtual ~TuringMachineAdapter();
        bool process_line(string buff);
        bool process_input(string buff);
        bool check_tm_valid();
        void initialize_tm();
        void run(bool v);
        void print_result(bool v);
        void check_turing_completeness();
        string state;

    protected:
        TuringMachine* tm;

        string input;

        int s_length;
        int g_length;
        set<string> q;
        set<char> s;
        set<char> g;
        string q0;
        char b;
        set<string> f;
        int n;

        map<string, vector<string> > delta_functions_map;
        bool accepted;
        bool error;
        int error_pos;
    private:
};

#endif // TURINGMACHINEADAPTER_H
