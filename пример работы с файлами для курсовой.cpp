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
