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

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades)
{
    ifstream receiveFile;
    receiveFile.open(filename);
    int s1 , s2 , s3;
    char n[50];
    string alltext;
    char format[] = "%[^:]: %d %d %d";
    while(getline(receiveFile , alltext))
    {
        sscanf(alltext.c_str() , format , n ,&s1,&s2,&s3);
        int ScoreSum = s1 + s2 + s3;
        names.push_back(n);
        scores.push_back(ScoreSum);
        grades.push_back(score2grade(ScoreSum));
    }
}

void getCommand(string &command, string &key)
{
    string Text;
    char Com[10] , Key[20];
    char format[] = "%[^ ,] %[^,],"; 
 
    cout << "Please input your command: "; 
    getline(cin , Text);
    
    sscanf(Text.c_str() , format , Com,Key);
    command = Com;
    key = Key;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------\n";
    bool found = 0;
    for(unsigned int i = 0 ; i < names.size() ; i++)
    {
        string NAME = toUpperStr(names[i]);
        if(NAME == key)
        {
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = 1;
            break;
        }
        
    }
    if(found == false) cout << "Cannot found.\n";
    cout << "---------------------------------\n";

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    cout << "---------------------------------\n"; 
    bool found = 0;
    for(unsigned int i = 0 ; i < names.size() ; i++)
    {   
        const char * K = key.c_str(); 
        if(*K == grades[i])
        { 
            cout << names[i] << " (" << scores[i] << ")\n";
            found = 1;
        }
    }

    if(found == false) cout << "Cannot found.\n";
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