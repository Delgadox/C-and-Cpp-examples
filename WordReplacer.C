// ��� ������ ��������
/////////////////////////////////////////////////////////////////////////////////////
//                                     ������.        							   //
// ���� ��� ��������� ����� f1 � f2. ���� f1 �������� ������������				   //
// �����. ����� � ������ ��������� ��������� � ������� ����������. ���� f2		   //
// �������� �� ����� 40 ����, ������� ��������� ��������. ��� ����� ��������	   //
// ����: ������ ������ ����� ��������� ����������, ������ ������ ����� ����������. //
// ������� � ����� f1 ��� ���������� ����� � �������� �� ��						   //
// ��������������� ����������. ��������� ��������� � ����� ����.				   //
/////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include<conio.h>
#include<locale.h>
#include<string.h>

char* func(char*, char*, char*);

int main(int argc,char *argv[]){
	FILE *fp;
	char ch, buf[100], *buffer = 0,*buffer2 = 0, *filter;
	long length;
	setlocale(LC_CTYPE,"Russian");
	srand(time(NULL));
	
	if (argc != 3) {
		printf("�������� ���������� ����������");
		return 0;
	}

	if ((fp=fopen(argv[1],"rt"))==NULL) printf("�� ���� ������� ���� � ��������� ������.\n");
	else {
		fseek (fp, 0, SEEK_END);
		length = ftell (fp);
		fseek (fp, 0, SEEK_SET);
		buffer =(char *)malloc (length);
		if (buffer) fread (buffer, 1, length, fp);
		fclose(fp);
	}
	if ((fp=fopen(argv[2],"rt"))==NULL) printf("�� ���� ������� ���� � ��������� ������.\n");
	else {
		fseek (fp, 0, SEEK_END);
		length = ftell (fp);
		fseek (fp, 0, SEEK_SET);
		buffer2 = (char *)malloc (length);
		if (buffer2) fread (buffer2, 1, length, fp);
		fclose(fp);
	}	
	
	filter = strtok(buffer2,",");
    while (filter != NULL){
    	buffer = func(buffer, filter, strtok (NULL,","));
    	filter = strtok (NULL,",");
    }
    fp=fopen("2_12.txt","wt");
    fprintf(fp,"%s",buffer);
	fclose(fp);
	
	free(filter);	
	free(buffer);
	free(buffer2);
	return 0;
}

char* func(char* s, char* oldW, char* newW){
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
 
    for (i = 0; s[i] != '\0'; i++){
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
 
    i = 0;
    while (*s) {
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
 
    result[i] = '\0';
    return result;
}
