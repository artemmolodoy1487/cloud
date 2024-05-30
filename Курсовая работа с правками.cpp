#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <windows.h>
#include <conio.h>

using namespace std;

const string FILE_DIR = "file.txt";
const string SAMPLE_FILE_DIR = "samplefile.txt";


string get_str_from_file(string file_name) {
	ifstream file;
	file.open(file_name);

	if (file.is_open()) {
		string data;
		getline(file, data);
		file.close();
		return data;
	}
	else {
		return "";
	}
}

struct Employee {

	string full_name;
	string faculty_name;
	string department_name;
	string job_title;
	int load_volume;

	Employee() {//конструктор по умолчанию
		full_name = "undefined";
		department_name = "undefined";
		job_title = "undefined";
		load_volume = 0;
	}
	Employee(string f_name, string fac_name, string dep_name, string j_title, int l_volume) {
		full_name = f_name;
		faculty_name = fac_name;
		department_name = dep_name;
		job_title = j_title;
		load_volume = l_volume;
	}

};
ostream& operator<<(ostream& output, const Employee& employee) {
	output << employee.full_name << '\t' << '\t' << employee.faculty_name << '\t' << '\t' << employee.department_name << '\t' << '\t' << employee.job_title << '\t' << '\t' << employee.load_volume << endl;

	return output;
}

void write_sample_to_file(vector<Employee> sample, const string filename) {

	string to_sample_txt;
	for (auto i : sample) {
		to_sample_txt += i.full_name; to_sample_txt.push_back(',');
		to_sample_txt += i.faculty_name; to_sample_txt.push_back(',');
		to_sample_txt += i.department_name; to_sample_txt.push_back(',');
		to_sample_txt += i.job_title; to_sample_txt.push_back(',');
		to_sample_txt += to_string(i.load_volume); to_sample_txt.push_back(';');
	}
	ofstream file(filename);

	if (file.is_open()) {
		file << to_sample_txt;
		cout << "Происходит запись в файл" << endl;
		file.close();
	}
	else {
		cout << "Ошибка записи в файл" << endl;
	}


}


struct current_list {
	vector<Employee>list;

	vector<Employee> string_parser(string str) {

		vector<Employee>list;

		vector<string>Employee_parameters = {}; Employee_parameters.reserve(4);
		string current_value;

		for (auto s : str) {

			if (s == ',') { Employee_parameters.push_back(current_value); current_value = ""; }
			else if (s == ';') {
				Employee_parameters.push_back(current_value); current_value = "";
				Employee current(Employee_parameters[0], Employee_parameters[1], Employee_parameters[2], Employee_parameters[3], stoi(Employee_parameters[4]));
				Employee_parameters = {};
				list.push_back(current);

			}
			else {
				current_value.push_back(s);
			}

		}

		return list;
	}

	current_list() {
		string data = get_str_from_file(FILE_DIR);

		list = string_parser(data);

	}

	vector<Employee> linearSearch() {
		cout << "Введите объем нагрузки" << endl;
		int lv; cin >> lv;
		vector<Employee> sample;
		cout << "Результаты поиска: " << endl;
		for (auto i : list) {
			if (i.load_volume == lv) {
				sample.push_back(i); cout << i << endl;
			}
		}
		if (sample.empty() == true) {
			cout << "Нет совпадений" << endl;
		}
		return sample;
	}

	vector<Employee> binarySearch() {
		cout << "Введите объем нагрузки: ";
		int lv;
		cin >> lv;

		vector<Employee> sample;
		cout << "Результаты поиска: " << endl;

		int left = 0;
		int right = list.size() - 1;

		while (left <= right) {
			int mid = left + (right - left) / 2;

			if (list[mid].load_volume == lv) {
				sample.push_back(list[mid]);
				cout << list[mid] << endl;
			}

			if (list[mid].load_volume < lv) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		if (sample.empty()) {
			cout << "Нет совпадений" << endl;
		}

		return sample;
	}

	void bubbleSort() {
		int n = list.size();
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (list[j].load_volume < list[j + 1].load_volume) {
					swap(list[j], list[j + 1]);
				}
			}
		}

		cout << "Сортировка пузырьком выполнена" << endl;
		write_sample_to_file(list, FILE_DIR);
	}

	void heapify(vector<Employee>& arr, int n, int i) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < n && arr[left].load_volume > arr[largest].load_volume) {
			largest = left;
		}

		if (right < n && arr[right].load_volume > arr[largest].load_volume) {
			largest = right;
		}

		if (largest != i) {
			swap(arr[i], arr[largest]);
			heapify(arr, n, largest);
		}
	}

	void heapSort() {
		int n = list.size();

		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(list, n, i);
		}

		for (int i = n - 1; i >= 0; i--) {
			swap(list[0], list[i]);
			heapify(list, i, 0);
		}
		cout << "Сортировка кучей выполнена" << endl;
		write_sample_to_file(list, FILE_DIR);
	}

	int partition(vector<Employee>& arr, int low, int high) {
		int pivot = arr[high].load_volume;
		int i = low - 1;

		for (int j = low; j <= high - 1; j++) {
			if (arr[j].load_volume < pivot) {
				i++;
				swap(arr[i], arr[j]);
			}
		}

		swap(arr[i + 1], arr[high]);
		return i + 1;
	}

	void Recursion_quickSort(vector<Employee>& arr, int low, int high) {
		if (low < high) {
			int pi = partition(arr, low, high);
			Recursion_quickSort(arr, low, pi - 1);
			Recursion_quickSort(arr, pi + 1, high);
		}
	}

	void quickSort() {
		int n = list.size();
		Recursion_quickSort(list, 0, n - 1);
		cout << "Быстрая сортировка выполнена" << endl;
		write_sample_to_file(list, FILE_DIR);
	}

};
ostream& operator<<(ostream& output, const current_list& curr) {
	for (auto i : curr.list) {
		output << i;
	}
	return output;
}





struct button {
	string text;
	function<void()> funct;

	button() {
		text = "";
		funct = nullptr;
	}

};
ostream& operator<<(ostream& output, const button& b) { output << b.text; return output; }



struct Screen {
	vector<button>buttons;
	signed char active_button_index = 0;
	current_list actual_list;
	Screen() {
		buttons.resize(9);
		buttons[0].text = "- Индивидуальное задание";
		buttons[1].text = "- Записать нового сотрудника";
		buttons[2].text = "- Линейный поиск";
		buttons[3].text = "- Бинарный поиск";
		buttons[4].text = "- Сортировка пузырьком";
		buttons[5].text = "- Сортировка кучей";
		buttons[6].text = "- Быстрая сортировка";
		buttons[7].text = "- Удалить сотрудника";
		buttons[8].text = "- Выйти";

		buttons[0].funct = ([this]() {
			clear();
			cout << actual_list;
			});

		buttons[1].funct = ([this]() {
			clear();
			while (true) {
				Employee emp;
				cout << "Полное имя:"; cin >> emp.full_name;
				cout << "Наименование факультета:"; cin >> emp.faculty_name;
				cout << "Наименование кафедры:"; cin >> emp.department_name;
				cout << "Должность:"; cin >> emp.job_title;
				cout << "Объем нагрузки:"; cin >> emp.load_volume;
				cout << "Нажмите пробел, если вы ввели верные данные" << endl;
				cout << emp;
				char space = _getch();
				if (space == ' ') {
					actual_list.list.push_back(emp);
					write_sample_to_file(actual_list.list, FILE_DIR);
					break;
				}
				else {}

			}
			});

		buttons[2].funct = ([this]() {
			clear();
			vector<Employee> sample = actual_list.linearSearch();
			write_sample_to_file(sample, SAMPLE_FILE_DIR);

			});

		buttons[3].funct = ([this]() {
			clear();
			vector<Employee> sample = actual_list.binarySearch();
			write_sample_to_file(sample, SAMPLE_FILE_DIR);

			});

		buttons[4].funct = ([this]() {
			clear();
			actual_list.bubbleSort();
			});

		buttons[5].funct = ([this]() {
			clear();
			actual_list.heapSort();
			});

		buttons[6].funct = ([this]() {
			clear();
			actual_list.quickSort();
			});

		buttons[7].funct = ([this]() {
			system("cls");
			cout << "Введите объем нагрузки" << endl;
			int lv;
			cin >> lv;
			actual_list.list.erase(
				remove_if(actual_list.list.begin(), actual_list.list.end(),
					[lv](const Employee& s) {
						return s.load_volume == lv;
					}), actual_list.list.end());
			write_sample_to_file(actual_list.list, FILE_DIR);

			});

		buttons[8].funct = ([this]() {
			write_sample_to_file(actual_list.list, FILE_DIR); exit(0);
			});

	}

	void up() {
		if (active_button_index > 0) { active_button_index--; }
	}

	void down() {
		if (active_button_index < buttons.size() - 1) { active_button_index++; }
	}

	void clear() {
		system("cls");
	}

	void get_move() {
		char m = _getch();
		switch (m) {
		case 'w': up();
			break;

		case 's': down();
			break;

		case ' ':
			buttons[active_button_index].funct();
			cout << endl << "Нажмите пробел чтоб вернуться в главное меню";
			while (true) {
				char space = _getch();
				if (space == ' ') { break; }
			}
			break;

		default:

			break;
		}
	}

};
ostream& operator<<(ostream& output, const Screen& s) {
	for (int i = 0; i < static_cast<int>(s.active_button_index); i++) {
		output << s.buttons[i] << endl;
	} cout << s.buttons[static_cast<int>(s.active_button_index)] << " <---" << endl;
	for (int i = static_cast<int>(s.active_button_index) + 1; i < s.buttons.size(); i++) {
		output << s.buttons[i] << endl;
	}
	return output;
}



int main() {
	setlocale(LC_ALL, "ru");
	Screen test;
	while (true) {
		cout << test;
		cout << endl << endl;
		cout << test.actual_list;
		test.get_move();
		test.clear();
	}

}