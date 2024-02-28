#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Read in the names from the text file
    ifstream file("p022_names.txt");
    vector<string> names;
    string name;
    while (getline(file, name, ',')) {
        names.push_back(name);
    }
    file.close();

    // Remove the quotes surrounding the names
    for (int i = 0; i < names.size(); i++) {
        names[i].erase(remove(names[i].begin(), names[i].end(), '\"'), names[i].end());
    }

    // Sort the names alphabetically
    sort(names.begin(), names.end());

    // Calculate the total name score
    long long total = 0;
    for (int i = 0; i < names.size(); i++) {
        int name_score = 0;
        for (int j = 0; j < names[i].length(); j++) {
            name_score += (names[i][j] - 'A' + 1) * (i + 1);
        }
        total += name_score;
    }

    // Print the total name score
    cout << total << endl;

    return 0;
}

