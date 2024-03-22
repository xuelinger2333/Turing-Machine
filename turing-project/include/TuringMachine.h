#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H
#include<iostream>
#include <string>
#include <vector>
#include <sstream>
#include "PaperTape.h"
#include <iomanip>
using namespace std;
class TuringMachine
{
    public:
        TuringMachine();
        TuringMachine(int n, string input);
        bool step_next(string delta);
        void refresh_present_vec();
        void print_tape_info();
        string get_result();
        virtual ~TuringMachine();

    protected:
        int tape_num;
        PaperTape* machine;
        char* present_vec;

    private:
};

#endif // TURINGMACHINE_H
