#include "PaperTape.h"

PaperTape::PaperTape()
{
    //ctor
    pivot = 0;
    head = 0;
    tail = 0;
    r_tape.push_back('_');
    tape.push_back('_');
}

PaperTape::~PaperTape()
{
    //dtor
}

void PaperTape::set_input(string input){
    pivot = 0;
    head = 0;
    tail = input.size() - 1;
    for (int i = 0; i < input.length(); i++){
        if (i < tape.size())
            tape[i] = input[i];
        else
            tape.push_back(input[i]);
    }
}

void PaperTape::refresh_head_tail(){
    head = min(head, pivot);
    tail = max(tail, pivot);
    while(head < pivot){
        if (head < 0){
            if (r_tape[head * -1] == '_'){
                head++;
            }else{
            break;
            }
        }
        else {
            if (tape[head] == '_'){
                head++;
            }else{
            break;
            }
        }
    }
    while(tail > pivot){
        if (tail >= 0){
            if (tape[tail] == '_'){
                tail--;
            }else{
            break;
            }
        }
        else{
            if (r_tape[tail * -1] == '_'){
                tail--;
            }else{
            break;
            }
        }
    }
}

pair<int, int> PaperTape::get_tape_range(){
    pair<int, int> res;
    head = min(head, pivot);
    tail = max(tail, pivot);
    res.first = head;
    res.second = tail;
    return res;
}

int PaperTape::get_pivot(){
    return pivot;
}

char PaperTape::get_char_at_pivot(){
    if (pivot >= 0){
        if (tape.size() - 1 < pivot){
            while(tape.size() - 1 < pivot){
                tape.push_back('_');
            }
            return tape[pivot];
        }
        else{
            return tape[pivot];
        }
    }
    else{
        int rp = pivot * -1;
        if (r_tape.size() - 1 < rp){
            while(r_tape.size() - 1 < rp){
                r_tape.push_back('_');
            }
            return r_tape[rp];
        }
        else{
            return r_tape[rp];
        }
    }
}

vector<char> PaperTape::get_tape_char(){
    vector<char> res;
    if (pivot >= 0){
        if (tape.size() - 1 < pivot){
            while(tape.size() - 1 < pivot){
                tape.push_back('_');
            }
        }
    }
    else{
        int rp = pivot * -1;
        if (r_tape.size() - 1 < rp){
            while(r_tape.size() - 1 < rp){
                r_tape.push_back('_');
            }
        }
    }
    head = min(head, pivot);
    tail = max(tail, pivot);
    if (head < 0){
        if (tail <= -1)
            for (int i = head * -1; i >= tail * -1; i--){
                res.push_back(r_tape[i]);
            }
        else
            for (int i = head * -1; i >= 1; i--){
            res.push_back(r_tape[i]);
            }
    }
    if (tail >= 0){
        if (head >= 0)
            for (int i = head; i <= tail; i++){
                res.push_back(tape[i]);
            }
        else
            for (int i = 0; i <= tail; i++){
                res.push_back(tape[i]);
            }
    }
    return res;
}

void PaperTape::change_pivot(char target){
    if (pivot >= 0){
        if (tape.size() - 1 < pivot){
            while(tape.size() - 1 < pivot){
                tape.push_back('_');
            }
            tape[pivot] = target;
        }
        else{
            tape[pivot] = target;
        }
    }
    else{
        int rp = pivot * -1;
        if (r_tape.size() - 1 < rp){
            while(r_tape.size() - 1 < rp){
                r_tape.push_back('_');
            }
            r_tape[rp] = target;
        }
        else{
            r_tape[rp] = target;
        }
    }
    head = min(head, pivot);
    tail = max(tail, pivot);
}

void PaperTape::change_dir(char d){
    if (d == 'l'){
        pivot -= 1;
    }else{
        if (d == 'r'){
            pivot += 1;
        }
    }
}



