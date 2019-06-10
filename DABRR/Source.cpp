#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "RoundR.hpp"

using namespace std;


int main() {
	RR *r = new RR();
	vector<CWaiting_time*>arr = r->Round_Robin(5);
	for (CWaiting_time *i : arr) cout << i->index << "-" << i->wait << endl;

	system("pause");
	return 0;

}