#include <iostream>

using namespace std;

struct element {
	element* next;
	double data;
	element() {
		next = nullptr;
		data = NULL;
	}
};

struct queue {
	element* head;
	element* tail;

	queue() {
		head = nullptr;
		tail = nullptr;
	}

	bool empty() {
		if (head == nullptr && tail == nullptr) {
			return true;
		}
		return false;
	}

	void push(double d) {
		if (empty()!=true) {
			element* el = new element;
			el->data = d;
			tail->next = el;
			tail = el;
		}
		else {
			element* el = new element;
			el->data = d;
			head = el;
			tail = el;
		}
	}

	void pop() {
		if (head != nullptr) {
			head = head->next;
		}
	}

	double front() {
		if (head!=nullptr) {
			return head->data;
		}
	}
}; 

int main() {
	int size;
	cout << "Enter size of queue";
	cin >> size;
	queue arr;
	double summ = 0;
	for (int i = 0; i < size; i++) {
		double v;
		cin >> v;
		summ += v;
		arr.push(v);
	}
	double avg = summ / size;
	arr.pop();
	queue answ;

 	answ.push(avg);
	while (!arr.empty()) {
		answ.push(arr.front());
		arr.pop();
	}
	while (answ.empty()!=true) {
		cout << answ.front() << endl;
		answ.pop();
	}

}
