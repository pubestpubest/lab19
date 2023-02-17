#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names, vector<int> &score, vector<char> &grade){
    ifstream source(filename.c_str());
    string cpps; 
    char format[]="%[^:]: %d %d %d";
    while(getline(source,cpps)){
        const char * cs = cpps.c_str();
        int scores[3]={0,0,0};
        char name[40];
        sscanf(cs,format,name,&scores[0],&scores[1],&scores[2]);
        names.push_back(name);
        score.push_back(scores[0]+scores[1]+scores[2]);
        grade.push_back(score2grade(scores[0]+scores[1]+scores[2]));
    }
}

void getCommand(string &comm,string &key){
    string txt;
    cout<<"Please input your command: ";
    getline(cin,txt);
    int start=0;
    int end = txt.find_first_of(" ");
    comm=txt.substr(start,end-start);
    start=end+1;
    key=txt.substr(start);
}

void searchName(vector<string> names,vector<int> score,vector<char> grade,string key){
    unsigned i=0;
    bool found=false;
    cout << "---------------------------------\n";
    while(i<names.size()){
        if(toUpperStr(names.at(i))==toUpperStr(key)){
            found=true;
            cout<<names.at(i)<<"'s score = "<<score.at(i)<<endl;
            cout<<names.at(i)<<"'s grade = "<<grade.at(i)<<endl;
        }
        i++;
    }
    if(!found)  printf("Cannot found.\n");
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> score,vector<char> grade,string key){
    unsigned i=0;
    bool found=false;
    cout << "---------------------------------\n";
    while(i<names.size()){
        string g(1,grade.at(i));
        if(toUpperStr(g)==toUpperStr(key)){
            found = true;
            cout<<names.at(i)<<" ("<<score.at(i)<<")\n";
        }
        i++;
    }
    if(!found)  printf("Cannot found.\n");
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
