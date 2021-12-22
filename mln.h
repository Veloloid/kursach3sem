#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "stdafx.h"
using namespace std;
namespace mln
{

	void Record(string path, string line, char parametr = 'c')//���� �������� ����� c (change), �� ���� ����� ����������������,� ���� a (add), �� ����������� � �����.������� ������ ������ � ����
	{
		if (parametr == 'a')
		{
			ofstream file(path, ios::app);
			if (file.is_open())
			{
				file << line << endl;
			}
			file.close();
		}
		else if (parametr == 'c')
		{
			ofstream file(path);
			if (file.is_open())
			{
				file << line << endl;
			}
			file.close();
		}
		else {
			cout << endl << "Error 1.0: incorrect parametr input" << endl;
		}
	}


	string Fsearch(string path, string search, int parameter, char back = 's')//����� ������ � �����
	{
		char str[150], fline[30];
		ifstream file(path);
		string line;
		int count, k, check = 0;
		bool flag = false;
		if (!file.is_open()) {
			cout << "���������� ������� ����" << endl;
		}
		else {
			while (getline(file, line)) {
				strcpy(str, line.c_str());
				count = 0;
				k = 0;
				for (int i = 0; i < sizeof(str); i++, k++)
				{
					fline[k] = str[i];
					if (str[i] == ',' || str[i] == '|')

						if (count == parameter)
						{
							fline[k] = '\0';
							if (strcmp(fline, search.c_str()) == 0) {
								flag = true;
								break;
							}
							else
							{
								memset(fline, 0, 30);
								k = -1;
							}
						}
						else {
							memset(fline, 0, 30);
							count++;
							k = -1;
						}

				}
				str[0] = '\0';
				fline[0] = '\0';
				check++;
				if (flag == true)
					break;

			}
		}
		if (flag == false) {
			cout << "����� ������� �� �������" << endl;
			return "Error";
		}
		else {
			if (back == 's')
				return line;
			else
				return to_string(check - 1);
		}
	}

	void fdel(string path, int parameter)//������� �������� ������ �� �����
	{
		ifstream del(path);
		string line, records[255];
		int i = 0, k = 0;
		if (!del.is_open()) {
			cout << "���������� ������� ���� ��� ��������" << endl;
		}
		else {
			while (getline(del, line)) {
				if (i == parameter) { i++; }
				else {
					records[k] = line;
					i++;
					k++;
				}
			}
		}
		del.close();
		for (int j = 0; !records[j].empty(); j++)
		{
			if (j == 0)
				Record(path, records[j]);
			else
				Record(path, records[j], 'a');
		}
	}

	string fulldata(string path, int index, int parameter)//������� ��� ���������� ������ ���������
	{
		char str[150], fline[30];
		ifstream data(path);
		string line, inf;
		int count = 0, p = 0, k = 0;
		if (!data.is_open())
		{
			cout << "���������� ������� ����" << endl;
		}
		else {
			while (getline(data, line)) {
				if (index == count) {
					strcpy(str, line.c_str());
					for (int i = 0; i < sizeof(str); i++, k++)
					{
						fline[k] = str[i];
						if (str[i] == ',' || str[i] == '|')
							if (p == parameter) {
								fline[k] = '\0';
								inf = string(fline);
								break;
							}
							else {
								memset(fline, 0, 30);
								p++;
								k = -1;
							}
					}
				}
				count++;
			}
			return inf;
		}
	}

	int fsize(string path)//������ ��� ����������� ������� �����
	{
		ifstream file(path);
		string line;
		int i = 0;
		if (!file.is_open()) {
			cout << "���������� ������� ����" << endl;
			i = 0;
		}
		else {
			while (getline(file, line)) {
				i++;
			}
		}
		return i;
	}


	vector<string> notes(string path) {
		vector<string> kek;
		ifstream file(path);
		string line;
		int count, k, check = 0;
		bool flag = false;
		if (!file.is_open()) {
			cout << "���������� ������� ����" << endl;
		}
		else {
			while (getline(file, line)) {
				kek.push_back(line);
			}
		}
		return kek;
	}

	void allnotes(string path, string param, int indexpar = 0)//������� ��� ������ ���� ������� �� ������������ ����������
	{
		char str[150], fline[30];
		string lines[25], line;
		ifstream file(path);
		int i = 0;
		int count = 0, k = 0, check = 0;
		bool flag = false;
		if (!file.is_open()) {
			cout << "���� �� ����� ���� ������" << endl;
		}
		else {
			cout << setw(5) << "ID";
			cout << setw(20) << "�������� ������ ";
			cout << setw(15) << "������ ";
			cout << setw(17) << "������ ";
			cout << setw(15) << "����������� ";
			cout << setw(15) << "��������� ";
			cout << setw(15) << "���� ";
			cout << setw(15) << "��������� " << endl;
			while (getline(file, line))
			{
				strcpy(str, line.c_str());
				count = 0;
				k = 0;
				for (int i = 0; i < sizeof(str); i++, k++)
				{
					fline[k] = str[i];
					if (str[i] == ',' || str[i] == '|')
						if (count == indexpar)
						{
							fline[k] = '\0';
							if (strcmp(fline, param.c_str()) == 0) {
								cout << setw(5) << fulldata(path, check, 0) << "|";
								cout << setw(20) << fulldata(path, check, 1) << "|";
								cout << setw(15) << fulldata(path, check, 2) << "|";
								cout << setw(15) << fulldata(path, check, 3) << "|";
								cout << setw(15) << fulldata(path, check, 4) << "|";
								cout << setw(15) << fulldata(path, check, 5) << "|";
								cout << setw(10) << fulldata(path, check, 6) << "|";
								cout << setw(15) << fulldata(path, check, 7) << "|" << endl;
								break;
							}
							else
							{
								memset(fline, 0, 30);
								k = -1;
							}
						}
						else
						{
							memset(fline, 0, 30);
							count++;
							k = -1;
						}

				}
				str[0] = '\0';
				fline[0] = '\0';
				check++;
			}
		}
	}

	int getValue()//������ ��� �������� �� ���� ������ �����
	{
		int a;
		while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
		{
			cin >> a;

			// �������� �� ���������� ����������
			if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
			{
				std::cin.clear(); // �� ���������� cin � '�������' ����� ������
				std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
				std::cout << "������������ ����. ���������� ��� ��� ������ ������������� ��������\n";
			}
			else
			{
				std::cin.ignore(32767, '\n'); // ������� ������ ��������
				return a;
			}
		}
	}

	int comp1(const void* a, const void* b)// 1 �����.������� ��� ���������� �� �����������
	{
		return (*(int*)a - *(int*)b);
	}

	int comp2(const void* a, const void* b)//������� ��� ���������� �� ��������
	{
		return (*(int*)b - *(int*)a);
	}

	string GetParameter(string line, int parameter) {
		char str[150], fline[30];
		int count, k = 0, check = 0;
		strcpy(str, line.c_str());
		count = 0;
		k = 0;
		for (int i = 0; i < sizeof(str); i++, k++)
		{
			fline[k] = str[i];
			if (str[i] == ',' || str[i] == '|')

				if (count == parameter)
				{
					fline[k] = '\0';
					return fline;
				}
				else {
					memset(fline, 0, 30);
					count++;
					k = -1;
				}
		}
		return "Error";
	}
}
