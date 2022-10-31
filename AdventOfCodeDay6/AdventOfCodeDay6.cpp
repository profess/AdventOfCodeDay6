#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

void levelMapper(map<string, set<string> > m, map<string, long> &n, string body, long level) {
    if (m[body].size() == 1) {
        n[body] = level++;
        levelMapper(m, n, *m[body].begin(), level);
    }
    else if (m[body].size() > 1) {
        n[body] = level;
        for (string s : m[body]) {
            levelMapper(m, n, s, level+1);
        }
    }
    else {
        n[body] = level;
    }
}
void levelMapper2(map<string, set<string> > m, map<string, pair<string, long> > & n, string parent, string body, long level) {
    n[body].first = parent;
    if (m[body].size() == 1) {
        n[body].second = level++;
        levelMapper2(m, n, body, *m[body].begin(), level);
    }
    else if (m[body].size() > 1) {
        n[body].second = level;
        for (string s : m[body]) {
            levelMapper2(m, n, body, s, level + 1);
        }
    }
    else {
        n[body].second = level;
    }
}

int main() {

    ifstream ifs = ifstream("input");
    map<string, set<string> > planet;
    char c;
    string body = "", sat = "";
    string* cur = &body;
    while (ifs.get(c)) {
        if (c == ')') {
            cur = &sat;
        }
        else if (c == '\n') {
            planet[body].insert(sat);
            body = "";
            sat = "";
            cur = &body;
        }
        else {
            *cur += c;
        }
    }
    planet[body].insert(sat);
    long level = 0;
    map<string, pair<string, long> > levels2;
    levelMapper2(planet, levels2, "", "COM", 0);
    string parent = levels2.find("YOU")->second.first;
    vector<string> youPath;
    while (parent != "") {
        youPath.push_back(parent);
        parent = levels2.find(parent)->second.first;
    }
    parent = levels2.find("SAN")->second.first;
    while (find(youPath.begin(), youPath.end(), parent) == youPath.end()) {
        parent = levels2.find(parent)->second.first;
    }
    cout << "Common Parent: " << parent << endl;
    long commonNode = levels2.find(parent)->second.second;
    cout << "Common Parent Location: " << commonNode << endl;
    long stepsToCommonNode = levels2.find("YOU")->second.second - commonNode - 1;
    cout << "Transfers from YOU to Common Parent: " << stepsToCommonNode << endl;
    long totalSteps = stepsToCommonNode + levels2.find("SAN")->second.second - commonNode - 1;
    cout << "Transfers from YOU to Common Parent to SAN: " << totalSteps << endl;
}
