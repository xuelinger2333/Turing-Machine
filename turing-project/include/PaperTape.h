#ifndef PAPERTAPE_H
#define PAPERTAPE_H
#include<iostream>
#include<vector>
using namespace std;
class PaperTape
{
    public:
        PaperTape();
        virtual ~PaperTape();
        void set_input(string input);

        char get_char_at_pivot();
        int get_pivot();
        pair<int, int> get_tape_range();
        vector<char> get_tape_char();

        void change_pivot(char tar);
        void change_dir(char d);
        void refresh_head_tail();
    protected:
        vector<char> tape;
        vector<char> r_tape;
        int pivot;
        int head;
        int tail;

    private:
};

#endif // PAPERTAPE_H
