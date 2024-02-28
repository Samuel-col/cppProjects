#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> get_names(string line,char sep){
	// Find positions
	vector<int> positions;
    int pos = -1;
    do{
        positions.push_back(pos);
        pos = line.find(sep,pos+1);
    }while(pos != string::npos);
    if(line[line.size()-1] != ',')
	    positions.push_back(line.size());

    vector<string> names;
    for(int i = 0; i < positions.size()-1; i++){
        names.push_back(line.substr(positions[i]+2,positions[i+1]-positions[i]-3));
    }

    return names;

}

int name_score(string name){
    transform(name.begin(),name.end(),name.begin(),::toupper);
    int s = 0;
    for(int i = 0; i < name.size();i++)
        s += name[i] - 'A' + 1;
    return s;
}

int main(){
    // Project Euler problem 22

    // Read names
    vector<string> names;
    vector<string> line_names;
    ifstream file("p022_names.txt");
    string line;
    while(getline(file,line)){
        line_names = get_names(line,',');
        names.insert(names.end(),line_names.begin(),line_names.end());
    }

    // Sort names
    sort(names.begin(),names.end());

    // Sum scores
    int s = 0;
    for(int k = 0; k < names.size();k++)
        s += (k+1)*name_score(names[k]);

    cout << "Answer: " << s << endl;

    return 0;
}