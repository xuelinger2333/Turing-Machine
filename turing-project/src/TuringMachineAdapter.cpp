#include "TuringMachineAdapter.h"

TuringMachineAdapter::TuringMachineAdapter()
{
    //ctor
    accepted = false;
    error = false;
    error_pos = -1;
    input = "";
}

TuringMachineAdapter::~TuringMachineAdapter()
{
    //dtor
    delete tm;
    tm = nullptr;
}
bool check_char(char a){
    if (a <= 'z'&&a >='a'||a <= 'Z' && a >='A'||a>=48 && a<=57 ||a == '_')
        return true;
    else
        return false;
}
void TuringMachineAdapter::check_turing_completeness(){
    //CHECK Q
    for(set<string>::iterator it = q.begin(); it != q.end(); it++) {
        for (int j = 0; j < (*it).length(); j++){
            if (check_char((*it)[j]) == false){
                fprintf(stderr, "syntax error\n");
                exit(20);
          //      error = true;
                return;
            }
        }
    }
    //CHECK S
    char er_s[7] = {' ', ',', ';', '{', '}', '*', '_'};
    for (int i = 0; i < 7; i++){
        if (s.find(er_s[i]) != s.end()){
            fprintf(stderr, "syntax error\n");
            exit(20);
         //   error = true;
            return;
        }
    }
    //CHECK G
    char er_g[6] = {' ', ',', ';', '{', '}', '*'};
    for (int i = 0; i < 6; i++){
        if (g.find(er_g[i]) != g.end()){
            fprintf(stderr, "syntax error\n");
            exit(20);
           // error = true;
            return;
        }
    }
    //CHECK B
    if (b != '_'){
        fprintf(stderr, "syntax error\n");
        exit(20);
        //error = true;
        return;
    }
    //CHECK INPUT
    for (int i = 0; i < input.length(); i++){
        if (s.find(input[i]) == s.end()){
            error_pos = i;
            error = true;
            return;
        }
    }
}
vector<string> split(const string& strs,  const char& delim) {
	vector<string> res;
	if (strs == "") return res;
	stringstream sstr(strs);
	string token;
	while (getline(sstr, token, delim))
	{
		res.push_back(token);
	}

	return res;
}
bool TuringMachineAdapter::process_input(string buff){
    input = buff;
    return true;
}
bool TuringMachineAdapter::process_line(string buff){
    if (buff[0] == ';' || buff == "")
        return true;
    if (buff[0] == '#'){
        vector<string> res1;
        switch (int(buff[1])){
        case int('Q'):
            buff = buff.substr(6);
            buff.pop_back();
            res1 = split(buff, ',');
            for (int i = 0; i < res1.size(); i++){
                q.insert(res1[i]);
            }
            break;
        case int('S'):
            buff = buff.substr(6);
            buff.pop_back();
            res1 = split(buff, ',');
            s_length = res1.size();
            for (int i = 0; i < res1.size(); i++){
                s.insert(res1[i][0]);
            }
            break;
        case int('G'):
            buff = buff.substr(6);
            buff.pop_back();
            res1 = split(buff, ',');
            g_length = res1.size();
            for (int i = 0; i < res1.size(); i++){
                g.insert(res1[i][0]);
            }
            break;
        case int('B'):
            b = buff[5];
            break;
        case int('F'):
            buff = buff.substr(6);
            buff.pop_back();
            res1 = split(buff, ',');
            for (int i = 0; i < res1.size(); i++){
                f.insert(res1[i]);
            }
            break;
        case int('N'):
            buff = buff.substr(5);
            n = atoi(buff.c_str());
            break;
        }
        if (buff[1] == 'q' && buff[2] == '0'){
            q0 = buff.substr(6);
        }
    }else{
        std::vector<std::string> stringArray;
        std::istringstream iss(buff);
        std::string item;
        while (iss >> item) {
            stringArray.push_back(item);
        }
        if (q.find(stringArray[0]) != q.end()){
            delta_functions_map[stringArray[0]].push_back(buff);
        }

    }
    return true;
}

void TuringMachineAdapter::initialize_tm(){
    if (input != "")
        tm = new TuringMachine(n, input);
    else
        tm = new TuringMachine(n, "_");
}

string get_next_state(string delta){
    std::vector<std::string> stringArray;
    std::istringstream iss(delta);
    std::string item;
    while (iss >> item) {
        stringArray.push_back(item);
    }
    return stringArray[4];
}

void print_verbose_information(int epi_num, string st, bool acc){
    cout<<"Step   : "<<epi_num<<endl;
    cout<<"State  : "<<st<<endl;
    if (acc == false)
        cout<<"Acc    : "<<"No"<<endl;
    else
        cout<<"Acc    : "<<"Yes"<<endl;
}

void TuringMachineAdapter::run(bool verbose){
    if (error == true){
        return;
    }
    if (verbose == true){
        cout<<"Input: "<<input<<endl;
    }
    state = q0;
    bool step_next_flag = true;
    bool accept = false;
    //TODO: HOW ABOUT NOT HALT?
    if (verbose == true)
        cout<<"==================== RUN ===================="<<endl;
    int episode_num = 0;
    while(step_next_flag == true){
        if (f.find(state) != f.end()){
            accept = true;
        }
        if (verbose == true){
            print_verbose_information(episode_num, state, accept);
            tm -> print_tape_info();
            cout<<"---------------------------------------------"<<endl;
        }
        episode_num ++;
        vector<string> delta_functions = delta_functions_map[state];

        tm -> refresh_present_vec();
        step_next_flag = false;
        for (int i = 0; i < delta_functions.size(); i++){
            step_next_flag = tm -> step_next(delta_functions[i]);
            if (step_next_flag == true){
                    state = get_next_state(delta_functions[i]);
                break;
            }
        }
    }
    accepted = accept;
}

void TuringMachineAdapter::print_result(bool verbose){
    string res = tm -> get_result();
    if (verbose == false){
        if (error == true){
            fprintf(stderr, "Input: ");
            const char* i = (input + "\n").c_str();
            fprintf(stderr, i);
            fprintf(stderr, "illegal input string\n");
            exit(23);
        }
        if (accepted == true){
            cout<<"(ACCEPTED) ";
        }else{
            cout<<"(UNACCEPTED) ";
        }
        cout<<res<<endl;
    }else{
        if (error == true ){
            fprintf(stderr, "Input: ");
            const char* i = (input + "\n").c_str();
            fprintf(stderr, i);
            fprintf(stderr, "==================== ERR ====================\n");
            if (error_pos != -1){
                string pii;
                pii[0] = input[error_pos];
                const char* p = ("error: Symbol " + pii ).c_str();
                fprintf(stderr, p);
                fprintf(stderr, " in input is not defined in the set of input symbols\n");
                const char* pi = ("Input: "+input + "\n").c_str();
                fprintf(stderr, pi);
                fprintf(stderr, "       ");
                for (int i = 0; i < error_pos; i++){
                    fprintf(stderr, " ");
                }
                fprintf(stderr, "^\n");
                fprintf(stderr, "==================== END ====================\n");
                exit(23);
            }

        }else{
            if (accepted == true){
            cout<<"ACCEPTED"<<endl;
            }else{
                cout<<"UNACCEPTED"<<endl;
            }
            cout<<"Result: "<<res<<endl;
            cout<<"==================== END ===================="<<endl;
        }
    }
}

