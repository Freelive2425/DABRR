#ifndef __ROUND_HPP__
#define __ROUND_HPP__

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

class CProcess {
public:
	int index;
	int burst;
	int arrive;
	int waiting;

	CProcess(int index, int burst, int arrive) {
		this->index = index;
		this->burst = burst;
		this->arrive = arrive;
		waiting = 0;
	}

};

class CWaiting_time {

public:
	int index;
	int wait;

	CWaiting_time(int index) { this->index = index; }
};


class RR {

private:
	vector<CProcess*> process;

public:
	RR() { process = vector<CProcess*>(); }

private:
	void generateProcess(int n) {
		srand(time(NULL));
		process.clear();
		for (int i = 0; i < n; ++i)
			process.push_back(new CProcess(i, int(rand() % 9) + 1, int(0)));
		/*	process.push_back(new CProcess(i, int(rand() % 9) + 1, int(rand() % 10)));*/

	}

	void sortProcess() { sort(process.begin(), process.end(), [](CProcess *a, CProcess *b)->bool {return a->burst < b->burst; }); }

	int getMinor(vector<CProcess*>arr) {
		int aux = arr.at(0)->arrive;

		for (CProcess *i : arr) {
			if (aux > i->arrive)
				aux = i->arrive;
		}
		return aux;
	}

	int getMinorBurst(vector<CProcess*>arr) {
		int aux = arr.at(0)->burst;

		for (CProcess *i : arr) {
			if (aux > i->burst)
				aux = i->burst;
		}
		return aux;
	}

	int getAverage(vector<CProcess*>arr) {
		int avg = 0;

		for (CProcess *i : arr)
			avg += i->burst;

		return avg / arr.size();

	}

	void addProcess(vector<CProcess*> &queue, int time) {
		for (int i = 0; i < process.size(); ++i) {
			if (process.at(i)->arrive <= time) {
				queue.push_back(process.at(i));
				process.erase(process.begin() + i);
				--i;
			}
		}
	}

	bool check(vector<CProcess*>queue) {

		bool flag = false;

		for (CProcess *p : queue) {
			if (p->burst != 0)
				flag = true;
		}
		return flag;

	}

	void generateWaitArr(vector<CWaiting_time*> &arr) {
		for (CProcess *i : process)
			arr.push_back(new CWaiting_time(i->index));
	}

	int search(vector<CWaiting_time*>arr, int ind) {
		int aux = 0;
		for (int i = 0; i < arr.size(); ++i) {
			if (arr.at(i)->index == ind) {
				aux = i;
				break;
			}
		}

		return aux;
	}


public:

	vector<CWaiting_time*> Round_Robin(int n) {

		vector<CProcess*>queue = vector<CProcess*>();
		vector<CWaiting_time*>wait = vector<CWaiting_time*>();
		generateProcess(n);
		generateWaitArr(wait);
		sortProcess();

		int time = getMinor(process);
		addProcess(queue, time);

		sort(queue.begin(), queue.end(), [](CProcess *a, CProcess *b)->bool {return a->arrive < b->arrive; });

		int quamtum;


		while (process.size() != 0 || queue.size() != 0) {
			//quamtum = getMinorBurst(queue);
			quamtum = getAverage(queue);
			cout << "Round" << endl;

			for (int i = 0; i < queue.size(); ++i) {

				cout << "Arrive: " << queue.at(i)->arrive << endl;
				cout << "Process: " << queue.at(i)->index << endl;
				cout << "Burst: " << queue.at(i)->burst << endl;


				queue.at(i)->waiting += time - queue.at(i)->arrive;

				if (queue.at(i)->burst > quamtum) {
					queue.at(i)->burst -= quamtum;
					time += quamtum;
					queue.at(i)->arrive = time;
				}
				else {
					time += queue.at(i)->burst;
					queue.at(i)->burst = 0;
					wait.at(search(wait, queue.at(i)->index))->wait = queue.at(i)->waiting;
					queue.erase(queue.begin() + i);
					--i;
				}
				cout << time << endl << endl;
			}

			addProcess(queue, time);

			if (!process.empty() && queue.empty()) {
				time += getMinor(process);
				addProcess(queue, time);
			}

			sort(queue.begin(), queue.end(), [](CProcess *a, CProcess *b)->bool {return a->arrive < b->arrive; });

		}
		return wait;
	}
};

#endif
