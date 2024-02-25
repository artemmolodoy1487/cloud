#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template<typename A, typename B> struct hash_table {
	int table_size = 0;
	vector<deque<pair<A, B>>>table;

	hash_table(int size) {
		table_size = size;
		table.resize(table_size);
	}

	int hash_funct(const A& key) {
		int hash = 0;
		for (auto c : key) {
			hash += static_cast<int>(c);
		}
		return hash % table_size;
	}

	void in(const A& key, const B& value) {

		int index = hash_funct(key);

		deque < pair < A, B >> test = table[index];


		bool unic = true;

		if (test.empty() != true) {
			//проверить на уникальность 
			while (test.empty() != true) {
				if (test.back().first == key ) {
					unic = false;
					break;
				}
				test.pop_back();
				if (test.empty() != true) {
					if (test.front().first == key ) {
						unic = false;
						break;
					}
					test.pop_front();
				}
			}
		}
		test.clear();
		//если уникально 
		if (unic == true) {
			pair<A, B>to_in; to_in.first = key; to_in.second = value;
			table[index].push_back(to_in);
		}

	}

	B get(const A& key) {

		int index = hash_funct(key);

		deque < pair < A, B >> test = table[index];


		int counter = 0; bool unic = true;

		while (test.empty() != true) {
			if (test.back().first == key) {
				return test.back().second;
			}
			test.pop_back();
			if (test.empty() != true) {
				if (test.front().first == key) {
					return test.front().second;
				}
				test.pop_front();
			}
		}

	}



};

int main() {
	hash_table<string, int> test(7);
	test.in("amelia", 10);
	test.in("artem", 4);
	test.in("pasha", 3);
	test.in("ulyna", 9);
	cout << test.get("amelia");
}

