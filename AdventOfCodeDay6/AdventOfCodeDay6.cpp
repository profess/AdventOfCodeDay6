#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>

using namespace std;

//long countSubtree(map<string, set<string> > &m, string s, long level) {
//    //if (m[s].size() == 0) {
//    //    return level + 1;
//    //}
//    //while (m[s].size() == 1) {
//    //    level++;
//    //    s = *m[s].begin();
//    //}
//    //if (m[s].size() > 1) {
//    //    long curLevel = level;
//    //    for (string t : m[s]) {
//    //        level += countSubtree(m, t, curLevel);
//    //    }
//    //}
//    //return level;
//
//
//}

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

int main() {
    ifstream ifs = ifstream("input");
    map<string, set<string> > planet;
    char c;
    string body, sat;
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
    //cout << countSubtree(planet, "COM", 0) << endl;
    long level = 0;
    map<string, long> levels;
    levelMapper(planet, levels, "COM", 0);
    for (auto i = levels.begin(); i != levels.end(); i++) {
        cout << i->first << ", " << i->second << endl;
    }
    level = 0;
    for (auto i = levels.begin(); i != levels.end(); i++) {
        level += i->second;
    }
    cout << level << endl;

}