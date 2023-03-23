// Щур Богдан Олегович
// Реализация алгоритма Хаффмана.
// minGW 7.0.0

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct letter_prob{
    double prob;
    char letter;
    string binary;
};

struct letter_prob *find_prob(string);
struct letter_prob *sort_prob(struct letter_prob *);
struct letter_prob *find_binary(struct letter_prob *);
int find_length(struct letter_prob *);
void add_all_1(string str, struct letter_prob *lb);
void add_all_0(string str, struct letter_prob *lb);

int main (){
    struct letter_prob *lp;
    string str,str2,
           test1_1[5]={"11", "10", "01", "001", "000"},
           test1_2[5]={"11","10","01","001","000"},
           test2_1[5]={"11","10","00","011","010"},
           test2_2[5]={"11","10","01","001","000"},
           test3_1[12]={"00","100","010","1011","0110",
                        "1100","1111","1110", "1010", "1101",
                        "01110","01111"};
    int i,j,a,test3_1int=0,test3_2int=0;
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Программа реализующая алгоритм Хаффмана." << endl;
    cout << "Автор: Щур Богдан Олегович 2 курс ИС\nДата создания: 20.12.2021." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Введите строку, ввод символа \"~\" недопустим: " << endl;
    getline(cin>>ws, str);
    lp = find_binary(sort_prob(find_prob(str)));
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->letter << " " << (lp+j)->prob << " " << (lp+j)->binary << endl;
    if(!str.empty()){
        str2.clear();
        for (i = 0; i < str.length(); i++){
            for (j = 0; j < find_length(lp); j++) {
                if (str[i] == (lp+j)->letter) str2 = str2 + (lp+j)->binary;
            }
        }
        cout << endl << str2 << endl;
    }
    cout << endl;
    system("set /p help=Для продолжения нажмите ввод...");
    system("cls");
    cout << "Для тестирования программы, создается список чисел, которые являются количеством символов бинарной записи числа." << endl;
    cout << "Тест №1.\nРезультат работы программы от ИТМО с введенным текстом \"abbcccddddeeeee\":\n" << endl;
    cout << "0.33^     5 e 11" << endl << "0.26^     4 c 10" << endl << "0.2       3 c 01" << endl << "0.13^     2 b 001" << endl << "0.0666667 1 a 000" << endl << endl;
    cout << "Выделим только количество символов в бинарном представление" << endl;
    for (i = 0; i < 5; i++) cout << test1_1[i].length() << " ";
    cout << "\n\nТеперь запустим \"Huff-1.hs\" с параметрами \"main [\"e\",\"d\",\"c\",\"b\",\"a\"] [0.33,0.26,0.2,0.13,0.06]\"\n" << endl;
    cout << "> ([(\"...abc.de\",0.98)],[(\"e\",\"11\"),(\"d\",\"10\"),(\"c\",\"01\"),(\"b\",\"001\"),(\"a\",\"000\")]) :: ([([Char],Double)],[([Char],[Char])])" << endl;
    cout << "\nСнова выделяем кол-во символов" << endl;
    for (i = 0; i < 5; i++) cout << test1_2[i].length() << " ";
    
    cout << endl;
    system("set /p help=Для продолжения нажмите ввод...");
    system("cls");

    cout << "Теперь сравним с результатом работы данной программы: \n";
    lp = find_binary(sort_prob(find_prob("abbcccddddeeeee")));
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->letter << " " << (lp+j)->prob << " " << (lp+j)->binary << " | ";        
    cout << "\n\nВыделим кол-во символов\n";
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->binary.length() << " ";
    cout << "\n\nТеперь сравним это с результатами других программ\n";
    for (j = 0; j < find_length(lp); j++) {
        cout << (lp+j)->letter << " - ";  
        if(((lp+j)->binary.length() == test1_1[j].length()) == (test1_2[j].length() == (lp+j)->binary.length())) cout << "True\n";
            else  cout << "False\n";
    }
    cout << endl;
    system("set /p help=Для продолжения нажмите ввод...");
    system("cls");
    cout << "Тест №2.\nИтмо - текст: asdqwdasdawdasdawdasdawdasd\n";
    for (i = 0; i < 5; i++) cout << test2_1[i].length() << " ";
    cout << "\nHuff-1.hs - параметры: [\"d\",\"a\",\"s\",\"w\",\"q\"] [0.33,0.29629,0.1852,0.1482,0.037]\n";
    for (i = 0; i < 5; i++) cout << test2_2[i].length() << " ";
    cout << "\nСравним результаты\n";
    lp = find_binary(sort_prob(find_prob("asdqwdasdawdasdawdasdawdasd")));
    for (j = 0; j < find_length(lp); j++) {
        cout << (lp+j)->letter << " - ";  
        if(((lp+j)->binary.length() == test2_1[j].length()) == (test2_2[j].length() == (lp+j)->binary.length())) cout << "True\n";
            else  cout << "False\n";
    }
    cout << "\nТест №3.\nИтмо - текст:\nАБВ ГДЖ АБВ ГДЖ ЕПТ УПТ КПТ\n";
    for (i = 0; i < 12; i++) cout << test3_1[i].length() << " ";
    cout << "\nСравним результаты\n";
    lp = find_binary(sort_prob(find_prob("АБВ ГДЖ АБВ ГДЖ ЕПТ УПТ КПТ")));
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->binary.length() << " ";
    for (j = 0; j < find_length(lp); j++) {
        test3_1int += (lp+j)->binary.length();
        test3_2int += test3_1[j].length();
    }
    if(test3_1int == test3_2int) cout << "\nTrue\n";
        else  cout << "\nFalse\n";

    delete(lp);

    return 0;
}

//  Функция частотного анализа из полученной строки 
struct letter_prob *find_prob(string str){
    struct letter_prob *lb;
    string sorted_str;
    int i;

    for(char c : str) if(sorted_str.find(c) > str.length()) sorted_str += c;
    
    lb = new letter_prob[sorted_str.length()+1];
    (lb+(sorted_str.length()))->letter = '~';

    for (i = 0; i < sorted_str.length(); i++) (lb+i)->prob=0;
    
    for(char c : str) if(sorted_str.find(c) < sorted_str.length()) {
        (lb+(sorted_str.find(c)))->prob += 1;
        (lb+(sorted_str.find(c)))->letter = c;
        (lb+(sorted_str.find(c)))->binary.clear();
    }

    for (i = 0; i < sorted_str.length(); i++) (lb+i)->prob/=str.length();

    return lb;
}

//  Функция сортировки набора вероятностей от большего к меньшему
struct letter_prob *sort_prob(struct letter_prob *lb){
    struct letter_prob *lb2 = lb;
    int len=find_length(lb),i,j;
    double a;
    char b;
    string c;

    for (i = len-1; i > 0; i--){
        for (j = 0; j < i; j++){
            if((lb2+j)->prob < (lb2+j+1)->prob){
                a = (lb2+j)->prob;
                b = (lb2+j)->letter;
                c = (lb2+j)->binary;
                (lb2+j)->prob = (lb2+j+1)->prob;
                (lb2+j)->letter = (lb2+j+1)->letter;
                (lb2+j)->binary = (lb2+j+1)->binary;
                (lb2+j+1)->prob = a;
                (lb2+j+1)->letter = b;
                (lb2+j+1)->binary = c;
            }
        }      
    }

    return lb;
}

// Реализация алгоритма Хаффмана
struct letter_prob *find_binary(struct letter_prob *lb){
    struct letter_prob *lb2=lb,*lb3;
    int len=find_length(lb),len2,i;

    lb3 = new letter_prob[len+1];
    (lb3+len)->letter = '~';

    for (i = 0; i < len; i++){
        (lb3+i)->letter  = (lb2+i)->letter;
        (lb3+i)->prob    = (lb2+i)->prob;
        (lb3+i)->binary += (lb2+i)->letter;
    }

    while((lb3+1)->letter != '~'){
        len2 = find_length(lb3);
        (lb3+len2-2)->prob += (lb3+len2-1)->prob;
        add_all_1((lb3+len2-2)->binary,lb);
        add_all_0((lb3+len2-1)->binary,lb);
        (lb3+len2-2)->binary += (lb3+len2-1)->binary;
        (lb3+len2-1)->letter='~'; 
        lb3 = sort_prob(lb3);
    }

    delete(lb3);

    return lb;
}

// Подсчет размера списка
int find_length(struct letter_prob *lb){
    int len=0;

    while ((lb->letter) != '~'){
        len++;
        lb++;
    }

    return len;
}

// Добавление единицы в бинаруную запись, каждого из элементов строки
void add_all_1(string str, struct letter_prob *lb){
    int i, len = find_length(lb);
    
    for (i = 0; i < len; i++){
        for (char c : str) {
            if(c == (lb+i)->letter) (lb+i)->binary= "1" + (lb+i)->binary;
        }
    }
}

// Добавление нуля в бинаруную запись, каждого из элементов строки
void add_all_0(string str, struct letter_prob *lb){
    int i, len = find_length(lb);
    
    for (i = 0; i < len; i++){
        for (char c : str) {
            if(c == (lb+i)->letter) (lb+i)->binary= "0" + (lb+i)->binary;
        }
    }
}