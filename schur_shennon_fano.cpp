// Щур Богдан Олегович
// Реализация алгоритма Шеннона-Фано.
// minGW 7.0.0

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct letter_prob{
    double prob,q,L;
    char letter;
    string binary;
};

struct letter_prob *find_prob(string);
struct letter_prob *sort_prob(struct letter_prob *);
struct letter_prob *find_q(struct letter_prob *);
struct letter_prob *find_L(struct letter_prob *);
struct letter_prob *find_binary(struct letter_prob *);
string double_to_binary(double, int);
int find_length(struct letter_prob *);

int main (){
    struct letter_prob *lp;
    string str,str2;
    int i,j,a,tflag=1;
    string test1[5] = {"11","10","011","001","0001"},
           test2[6] = {"111","110","101","011","010","0001"},
           test3[9] = {"111","110","101","100","011","010","0011","0010","0001"};

    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Программа реализующая алгоритм Шеннона-Фано." << endl;
    cout << "Автор: Щур Богдан Олегович 2 курс ИС\nДата создания: 21.12.2021." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Введите строку, ввод символа \"~\" недопустим: " << endl;
    getline(cin>>ws, str);
    lp = find_binary(find_L(find_q(sort_prob(find_prob(str)))));

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

    cout << "Тест №1.\nРезультат работы программы от ShFano-1.hs с введенным текстом \"abbcccddddeeeee\":\n";
    lp = find_binary(find_L(sort_prob(find_prob("abbcccddddeeeee"))));
    for (j = 0; j < find_length(lp); j++) {
        if(((lp+j)->binary).length()!= test1[j].length()){
            tflag = 0;
        }
    }
    cout << " Schur_shennon.cpp" << endl;
    cout << "Сравним с результатом работы данной программы: ";
    if(tflag) cout << "True\n";
        else  cout << "False\n";;
    tflag = 1;


    cout << "\nТест №2.\nРезультат работы программы от ShFano-1.hs с введенным текстом \"qazwsxqazws\":\n";
    lp = find_binary(find_L(sort_prob(find_prob("qazwsxqazws"))));
    for (j = 0; j < find_length(lp); j++) {
        if(((lp+j)->binary).length()!= test2[j].length()){
            tflag = 0;
        }
    }
    cout << "Сравним с результатом работы данной программы: ";
    if(tflag) cout << "True\n";
        else  cout << "False\n";;
    tflag = 1;

    cout << "\nТест №3.\nРезультат работы программы ShFano-1.hs, текст \"йфяцычйфяцычкам\":\n";
    lp = find_binary(find_L(sort_prob(find_prob("йфяцычйфяцычкам"))));
    for (j = 0; j < find_length(lp); j++) {
        if(((lp+j)->binary).length()!= test3[j].length()){
            tflag = 0;
        }
    }
    cout << "Сравним с результатом работы данной программы: ";
    if(tflag) cout << "True\n";
        else  cout << "False\n";
    
    delete(lp);

    return 0;
}

// Функция частотного анализа из полученной строки 
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

// Функция сортировки набора вероятностей от большего к меньшему
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

// функция поиска q для каждого элемента.
struct letter_prob *find_q(struct letter_prob *lb){
    struct letter_prob *lb2 = lb;
    int len = find_length(lb2),i;

    lb2->q=0;
    for (i = 1; i < len; i++) (lb2+i)->q = (lb2+i-1)->q + (lb2+i-1)->prob;  
    
    return lb;
}

// функция поиска L для каждого элемента 
struct letter_prob *find_L(struct letter_prob *lb){
    struct letter_prob *lb2 = lb;
    int len = find_length(lb2),i;

    for (i = 0; i < len; i++) (lb2+i)->L = ceil(-log2((lb2+i)->prob));
    
    return lb;
}

// Реализация алгоритма Шеннона-Фано
struct letter_prob *find_binary(struct letter_prob *lb){
    struct letter_prob *lb2=lb;
    int len=find_length(lb),i;

    for (i = 0; i < len; i++){
        (lb2+i)->binary = double_to_binary((lb2+i)->q, (lb2+i)->L);
    }

    return lb;
}

// Перевод вещественного числа в бинарный код
string double_to_binary(double val, int L){
    int i;
    string str;

    str.clear();
    for (i = 0; i < L; i++){
        val *= 2;
        if(val > 1.0){
            str += '1';
            val = fmod(val,1.0);
        }else str += '0';
    }
    return str;
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
