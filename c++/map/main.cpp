#include <map>
#include <string>
#include <iostream>

using namespace std;

void print_map(map<string, string> & m) {
    map<string, string>::iterator iter = m.begin();
    for (; iter != m.end(); ++iter) {
	cout << iter->first << " = " << iter->second << endl;
    }
}

int main(int argc, char *argv[])
{
    map<string, string> m;

    m["a"] = "A";
    m["b"] = "B";
    m["c"] = "C";
    m["d"] = "D";

    cout << " == map ==" << endl;
    print_map(m);

    map<string, string>::iterator iter = m.begin();
    while (iter != m.end()) {
	if (iter->first == "a" || iter->first == "d") {
	    m.erase(iter++);
	} else {
	    iter++;
	}
    }

    cout << " == map ==" << endl;
    print_map(m);

    
    return 0;
}
