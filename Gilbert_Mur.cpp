// ��� ������ ��������
// ���������� ��������� �������-����.
// minGW 7.0.0

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct letter_prob{
    double prob;
    double q;
    double b;
    char letter;
    string binary;
    int L;
};

struct letter_prob *find_prob(string);
struct letter_prob *find_binary(struct letter_prob *);
struct letter_prob *find_q(struct letter_prob *);
struct letter_prob *find_L(struct letter_prob *);
int find_length(struct letter_prob *);
string double_to_binary(double, int );

int main (){
    struct letter_prob *lp;
    string str,str2;
    int i,j,a,tsum1=0,tsum2=0;
    string test1[5] = {"001","011","1011","1101","11110"},
        test2[6] = {"0001","0100","0111","1010","1101","11110"},
        test3[9] = {"0001","0011","0101","0111","1001","1011","11010","11100","11110"};
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    system("cls");
    cout << "-------------------------------------------" << endl;
    cout << "��������� ����������� �������� �������-����." << endl;
    cout << "�����: ��� ������ �������� 2 ���� ��\n���� ��������: 20.12.2021." << endl;
    cout << "-------------------------------------------" << endl;
    cout << "������� ������, ���� ������� \"~\" ����������: " << endl;
    getline(cin>>ws, str);
    lp = find_binary(find_L(find_q(find_prob(str))));
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
    system("set /p help=��� ����������� ������� ����...");
    system("cls");

    cout << "���� �1.\n��������� ������ ��������� �� ShFano-1.hs � ��������� ������� \"abbcccddddeeeee\":\n";
    lp = find_binary(find_L(find_q(find_prob("abbcccddddeeeee"))));
    for (j = 0; j < find_length(lp); j++) {
        tsum1 += test1[j].length();
        tsum2 += (lp+j)->binary.length();
    }
    for (j = 0; j < find_length(lp); j++) cout << test1[j] << " ";
    cout << endl;
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->binary << " ";
    cout << "\n������� � ����������� ������ ������ ���������: ";
    if(tsum1 == tsum2) cout << "True\n";
        else  cout << "False\n";;
    tsum1 = 0;
    tsum2 = 0;

    cout << "\n���� �2.\n��������� ������ ��������� �� ShFano-1.hs � ��������� ������� \"qazwsxqazws\":\n";
    lp = find_binary(find_L(find_q(find_prob("qazwsxqazws"))));
    for (j = 0; j < find_length(lp); j++) {
        tsum1 += test2[j].length();
        tsum2 += (lp+j)->binary.length();
    }
    for (j = 0; j < find_length(lp); j++) cout << test2[j] << " ";
    cout << endl;
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->binary << " ";
    cout << "\n������� � ����������� ������ ������ ���������: ";
    if(tsum1 == tsum2) cout << "True\n";
        else  cout << "False\n";
    tsum1 = 0;
    tsum2 = 0;

    cout << "\n���� �3.\n��������� ������ ��������� ShFano-1.hs, ����� \"���������������\":\n";
    lp = find_binary(find_L(find_q(find_prob("���������������"))));
    for (j = 0; j < find_length(lp); j++) {
        tsum1 += test3[j].length();
        tsum2 += (lp+j)->binary.length();
    }
    for (j = 0; j < find_length(lp); j++) cout << test3[j] << " ";
    cout << endl;
    for (j = 0; j < find_length(lp); j++) cout << (lp+j)->binary << " ";
    cout << "\n������� � ����������� ������ ������ ���������: ";
    if(tsum1 == tsum2) cout << "True\n";
        else  cout << "False\n";;

    delete(lp);

    return 0;
}

//  ������� ���������� ������� �� ���������� ������ 
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

// ���������� ��������� ��������-����
struct letter_prob *find_binary(struct letter_prob *lb){
    struct letter_prob *lb2=lb;
    int len=find_length(lb),i;

    for (i = 0; i < len; i++) (lb2+i)->binary = double_to_binary((lb2+i)->b, (lb2+i)->L);
    return lb;
}

// ������� ������� ������
int find_length(struct letter_prob *lb){
    int len=0;

    while ((lb->letter) != '~'){
        len++;
        lb++;
    }

    return len;
}

// ������� ������ q ��� ������� ��������.
struct letter_prob *find_q(struct letter_prob *lb){
    struct letter_prob *lb2 = lb;
    int len = find_length(lb2),i;

    lb2->q=0;
    lb2->b=lb2->prob;

    for (i = 1; i < len; i++) {
        (lb2+i)->q = (lb2+i-1)->q + (lb2+i-1)->prob;
        (lb2+i)->b = (lb2+i)->q + ((lb2+i-1)->prob/2.0);
    }

    return lb;
}

// ������� ������ L ��� ������� �������� 
struct letter_prob *find_L(struct letter_prob *lb){
    struct letter_prob *lb2 = lb;
    int len = find_length(lb2),i;

    for (i = 0; i < len; i++) (lb2+i)->L = ceil(-log2((lb2+i)->prob/2.0));
    
    return lb;
}

// ������� ������������� ����� � �������� ���
string double_to_binary(double val, int L){
    int i;
    string str;

    str.clear();
    if(val == 0.5){
        for (i = 0; i < L; i++){
            val *= 2;
            if(val >= 1.0){
                str += '1';
                val = fmod(val,1.0);
            }else str += '0';
        }
    }else{
        for (i = 0; i < L; i++){
            val *= 2;
            if(val > 1.0){
                str += '1';
                val = fmod(val,1.0);
            }else str += '0';
        }

    }
    return str;
}
