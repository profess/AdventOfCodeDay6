#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    ifstream ifs = ifstream("input.txt");
    map<string, set<string> > planet;
    char c;
    string body, sat;
    string* cur = &body;
    while (ifs.get(c)) {
        if (c == ')') {
            cur = &sat;
        }
        else if (c == '\n' || ifs.peek() == EOF) {
            planet[body].insert(sat);
            body = "";
            sat = "";
            cur = &body;
        }
        else {
            *cur += c;
        }
    }
}