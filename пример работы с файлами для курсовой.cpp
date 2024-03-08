#include <iostream>
#include <sstream>
#include  <fstream>
#include <unordered_map>
using namespace std;

struct STUDENT {
    string NAME;
    string NUMBER;
    string ADDRESS;
    string GRADE;
};

string ReadFileToString(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << filename << std::endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    setlocale(LC_ALL, "ru");
    unordered_map<string, STUDENT>LIST;

    string TEXT = ReadFileToString("text.txt");
    cout << TEXT << endl;
    STUDENT* back = new STUDENT;
    int Student_Parameter_counter=0;
    for (char s : TEXT) {
        if (s == ':') { Student_Parameter_counter++; }
        if (s == '\n') { LIST[back->NAME] = *back; Student_Parameter_counter = 0; delete back; back = new STUDENT; }
        if (s != ':' && s != '\n') {
            switch (Student_Parameter_counter) {
            case 0:
                back->NAME.push_back(s);
                break;
            case 1:
                back->NUMBER.push_back(s);
                break;
            case 2:
                back->ADDRESS.push_back(s);
                break;
            case 3:
                back->GRADE.push_back(s);
                break;
            }
        }
    }


    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct STUDENT {

	string name;
	int group;
	string city;
	double mark;

	STUDENT() {
		name = "idk";
		group = 0;
		city = "idk";
		mark = 0;
	}
	STUDENT(string name, int group, string city, double mark) {
		this->name=name;
		this->group = group;
		this->city = city;
		this->mark = mark;
	}

	void Print() {
		cout << "Name: " << name << " Group: " << group << " City: " << city << " Mark: " << mark << endl;
	}
};


int partitionByName(vector<STUDENT>& arr, int low, int high) {
	string pivot = arr[high].name;  // Выбираем последний элемент в качестве опорного
	int i = low - 1;  // Индекс меньшего элемента

	for (int j = low; j <= high - 1; j++) {
		// Если текущее имя меньше или равно опорному
		if (arr[j].name <= pivot) {
			i++;  // Увеличиваем индекс меньшего элемента
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

// Функция быстрой сортировки по имени
void quickSortByName(vector<STUDENT>& arr, int low, int high) {
	if (low < high) {
		// Поиск разделителя (опорного элемента) и разделение массива
		int pi = partitionByName(arr, low, high);

		// Рекурсивно сортируем две части массива
		quickSortByName(arr, low, pi - 1);
		quickSortByName(arr, pi + 1, high);
	}
}

// Обертка для вызова быстрой сортировки по имени
void quickSortByName(vector<STUDENT>& arr) {
	int low = 0;
	int high = arr.size() - 1;
	quickSortByName(arr, low, high);
}
int binarySearchByName(const vector<STUDENT>& arr, const string& targetName) {
	int low = 0;
	int high = arr.size() - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (arr[mid].name == targetName) {
			return mid; // Имя найдено, возвращаем индекс
		}
		else if (arr[mid].name < targetName) {
			low = mid + 1; // Искомое имя находится во второй половине
		}
		else {
			high = mid - 1; // Искомое имя находится в первой половине
		}
	}

	return -1; // Имя не найдено
}
int main() {

	string path = "myText.txt";

	STUDENT test("Svetlana", 321701, "Minsk", 2);
	test.Print();

	ofstream fout;
	fout.open(path, ofstream::app);//app значит записись не сначала а дополнение

	if (!fout.is_open()) { cout << "Error of opening the fout file" << endl; }

	else {
		cout << "Fout file is open" << endl;
		fout.write((char*)&test, sizeof(STUDENT));
	}

	fout.close();

	vector<STUDENT>list;

	ifstream fin;

	fin.open(path);

	if (!fin.is_open()) {
		cout << "Error of opening the fin file" << endl;
	}

	else {
		cout << "Fin file is open" << endl;
		STUDENT local;
		while (fin.read((char*)&local, sizeof(STUDENT))) {
			list.push_back(local);
		}
	}
	fin.close();

	for (STUDENT student: list) {
		student.Print();
	}
	for (int i = 0; i < list.size(); i++) {
		if (list[i].mark < 8.5 || list[i].city != "Minsk") {
			list.erase(list.begin() + i);
		}
	}

	for (STUDENT student : list) {
		student.Print();
	}
	cout << "sorted" << endl << endl << endl;
	
	quickSortByName(list);

	
	cout << "Sorted list by name:" << endl;
	for (STUDENT student : list) {
		student.Print();
	}
	

}
