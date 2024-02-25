export module smartArr;

int find_min(int a,int b) {
	if (a < b) { return a; }
	else { return b; }
}


export template<typename T>
struct arr {
	
	T* list = nullptr;

	int size = 0;

	void resize(int newsize) {

		if (list == nullptr && size == 0) {

			list = new T[newsize];
			size = newsize;

		}
		else {

			T* back = new T[find_min(size, newsize)];

			for (int i = 0; i < find_min(size, newsize); i++) { back[i] = list[i]; }

			size = newsize; list = back; delete[] back;

		}

	}

	void push_back(const T& push) {

		resize(size + 1);
		list[size - 1] = push;

	}

	void pop_back() {

		resize(size -  1);

	}
	T& operator[](int index) {
        return list[index];
    }

};
