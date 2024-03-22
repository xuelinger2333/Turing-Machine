#include "TuringMachine.h"
TuringMachine::TuringMachine(){

}
TuringMachine::TuringMachine(int n, string input){
    tape_num = n;
    machine = new PaperTape[n];
    machine[0].set_input(input);
    present_vec = new char[n];
}

TuringMachine::~TuringMachine()
{
    //dtor
    delete[] machine;
    machine = nullptr;
    delete[] present_vec;
    present_vec = nullptr;
}

bool TuringMachine::step_next(string delta){
    std::vector<std::string> stringArray;
    std::istringstream iss(delta);
    std::string item;
    while (iss >> item) {
        stringArray.push_back(item);
    }
    string expected_input = stringArray[1];
    string target_output = stringArray[2];
    string target_dir = stringArray[3];
    for (int i = 0; i < expected_input.length(); i++){
        if (expected_input[i] != '*'){
            if (expected_input[i] != present_vec[i]){
                return false;
            }
        }
    }
    //SUCCESS MATCH!!
    for (int i = 0; i < target_output.length(); i++){
        if (target_output[i] != '*'){
            machine[i].change_pivot(target_output[i]);
        }
    }
    for (int i = 0; i < target_dir.length(); i++){
        if (target_dir[i] != '*'){
            machine[i].change_dir(target_dir[i]);
        }
    }
    return true;
}

void TuringMachine::refresh_present_vec(){
    for (int i = 0; i < tape_num; i++){
        present_vec[i] = machine[i].get_char_at_pivot();
    }
}
void TuringMachine::print_tape_info(){
    for (int i = 0; i < tape_num; i++){
        machine[i].refresh_head_tail();
        int pivot = machine[i].get_pivot();
        pair<int, int> ht = machine[i].get_tape_range();
        vector<char> t = machine[i].get_tape_char();
        cout<<"Index"<<i<<" : ";
        vector<int> input_space;
        for (int j = ht.first; j <= ht.second; j++){
            int t_j = abs(j);
            if (t_j < 10)
                input_space.push_back(2);
            if (t_j >= 10 && t_j < 100)
                input_space.push_back(3);
            if (t_j >= 100)
                input_space.push_back(4);
                cout<<std::left<<setw(input_space[input_space.size() - 1])<<abs(j);
        }
        cout<<endl;
        cout<<"Tape"<<i<<"  : ";
        for (int k = 0; k < t.size(); k++){
            cout<<std::left<<setw(input_space[k])<<t[k];
        }
        cout<<endl;
        cout<<"Head"<<i<<"  : ";
        for (int j = ht.first; j <= ht.second; j++){
            if (pivot == j){
                cout<<std::left<<setw(input_space[j - ht.first])<<'^';
            }
            else{
                cout<<std::left<<setw(input_space[j - ht.first])<< " ";
            }
        }
        cout<<endl;
    }
}

string TuringMachine::get_result(){
    machine[0].refresh_head_tail();
    vector<char> t0= machine[0].get_tape_char();
    string res = "";
    bool str_flag = false;
    for (int i = 0; i < t0.size(); i++){
        if (t0[i] != '_' || str_flag == true){
            str_flag = true;
            res += t0[i];
        }
    }
    while(res[res.size() - 1] == '_')
        res.pop_back();
    return res;
}
