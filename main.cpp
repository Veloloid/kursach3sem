#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "mln.h"

using namespace std;
using namespace mln;





class Good
{
private:
	int id;
	string name;
	int count;
	double weight;
public:
	void SetName(string name) {
		this->name = name;
	}

	void SetCount(int count) {
		this->count = count;
	}

	void SetWeight(double weight) {
		this->weight = weight;
	}

	string GetName() {
		return this->name;
	}

	int GetCount()
	{
		return this->count;
	}


	double GetWeight() {
		return this->weight;
	}

	void SetId(int id) {
		this->id = id;
	}

	int GetId() {
		return this->id;
	}


	Good(int id, string name, int count, double weight) {
		this->id = id;
		this->name = name;
		this->count = count;
		this->weight = weight;
	}

	Good(const Good& good) {
		this->id = good.id;
		this->name = good.name;
		this->count = good.count;
		this->weight = good.weight;
	}


	Good() {
		this->id = 0;
		this->name = "Нет названия";
		this->count = 0;
		this->weight = 0;
	}


	void print() {
		cout << "Good(" << to_string(this->id) << ", " << this->name << ", " << to_string(this->count) << to_string(this->weight) << ")" << endl;
	 }

	void save(char mode='a') {
		char str[150], coma[] = ",";
		string weight1 = to_string(this->weight);
		strcpy(str, weight1.c_str());
		for (int i = 0; i < 20; i++) {
			if (str[i] == coma[0]) {
				char str1[2] = { str[i + 1], str[i + 2] };
				weight1 = "";
				for (int j = 0; j < i; j++) {
					weight1 += str[j];
				}
				weight1 += "." + string(str1, sizeof(str1));
				break;
			}
		}
		string good = to_string(id)+","+name + "," + to_string(count) + "," + weight1 + "|";
		Record("Goods.txt", good, mode);
	}
};

class User
{
protected:
	int id;
	string name;
	string lastname;
	string login;
	string password;

public:

	int GetId() { return this->id; }

	void save(char mode = 'a') {
		string user = to_string(id) + "," + name + "," + lastname + "," + login + "," + password+"|";
		Record("users.txt", user, mode);
	}


	void ChangeGood() {
		PrintGoods();
		int id_change;
		cout << "Введите id товара, который хотите изменить: " << endl;
		id_change = getValue();
		string check = Fsearch("Goods.txt", to_string(id_change), 0);
		if (check == "Error") {
			cout << "Такого товара нет" << endl;
		}
		else {
			vector<string> goods = notes("Goods.txt");
			int index = 0;
			for (std::vector<string>::size_type i = 0; i != goods.size(); i++) {
				int id = stoi(GetParameter(goods[i], 0));
				string name = GetParameter(goods[i], 1);
				int count = stoi(GetParameter(goods[i], 2));
				double weight = stof(GetParameter(goods[i], 3));
				Good* good = new Good(id, name, count, weight);
				if (good->GetId() == id_change) {
					int choice, count;
					string name;
					double weight;
					cout << "Введите параметр товара, который хотите изменить: " << endl;
					cout << "1-Название" << endl;
					cout << "2-Количество" << endl;
					cout << "3-Вес" << endl;
					choice = getValue();
					switch (choice) {
					case 1:
						cout << "Введите новое название: " << endl;
						cin >> name;
						good->SetName(name);
						break;
					case 2: cout << "Введите новое количество товара: " << endl;
						count = getValue();
						good->SetCount(count);
						break;
					case 3:
						cout << "Введите новый вес товара: " << endl;
						cin >> weight;
						good->SetWeight(weight);
						break;
					default:
						cout << "Такого вариант нет" << endl;
						break;
					}
				}
				if (index == 0) {
					good->save('c');

				}
				else {
					good->save();
				}
				index++;
			}
		}
	}


	static int GenerateId(string path) {
		ifstream file(path);
		string line;
		int i = 0;
		if (!file.is_open()) {
			cout << "Невозможно открыть файл" << endl;
			i = 0;
		}
		else {
			int max = 0;
			while (getline(file, line)) {
				if (stoi(GetParameter(line, 0)) > max) {
					max = stoi(GetParameter(line, 0));
				}
			}
			i = max+2;
		}
		return i;
	}

	void PrintGoods() {
		vector<string> goods = notes("Goods.txt");
		for (std::vector<string>::size_type i = 0; i != goods.size(); i++) {
			int id = stoi(GetParameter(goods[i], 0));
			string name = GetParameter(goods[i], 1);
			int count = stoi(GetParameter(goods[i], 2));
			double weight = stof(GetParameter(goods[i], 3));
			Good *good = new Good(id, name, count, weight);
			good->print();
		}
	}

	virtual void ChangePassword(int id) = 0;

	virtual void SignIn() = 0;


	static void Registration() {
		string name, lastname, login, password;
		cout << "Введите имя: " << endl;
		cin >> name;
		cout << "Введите фамилию: " << endl;
		cin >> lastname;
		cout << "Введите логин: " << endl;
		cin >> login;
		cout << "Введите пароль: " << endl;
		cin >> password;
		int id = GenerateId("users.txt");
		string user = to_string(id) + "," + name + "," + lastname + "," + login + "," + password + "|";
		mln::Record("users.txt", user, 'a');
	}

	void AddGood() {
		string name;
		int count;
		double weight;
		cout << "Введите название товара: " << endl;
		cin >> name;
		cout << "Введите количество: " << endl;
		count = getValue();
		cout << "Введите вес: " << endl;
		cin >> weight;
		int id = GenerateId("Goods.txt");
		Good *good = new Good(id, name, count, weight);
		good->save();
	}

	void ChangeGood(Good goodToUpdate, Good NewGood) {}

	void DeleteGood(int id) {};

};


class Worker : public User
{

private:
	string tasks[10];

public:
	//string[] GetTasks();
	//void SetTasks(string[] tasks);

	void MakeReport();
	void CompleteTask();

	Worker() {
		this->id = 0;
		this->name = "Никто";
		this->lastname = "Никто";
		this->login = "Логин";
		this->password = "Пароль";
	}

	Worker(int id, string name, string lastname, string login, string password) {
		this->id = id;
		this->name = name;
		this->lastname;
		this->login = login;
		this->password = password;
	}

	static void WorkerMenu(int id, string name, string lastname, string login, string password) {
		Worker *worker = new Worker(id, name, lastname, login, password);
		int choice;
		while (true) {
			cout << "Меню: " << endl;
			cout << "1-Добавить товар" << endl;
			cout << "2-Изменить товар" << endl;
			cout << "3-Изменить аккаунт" << endl;
			cout << "4-Выполнить таски" << endl;
			cout << "0-Выйти" << endl;
			choice = getValue();
			switch (choice) {
			case 1: worker->AddGood();
				break;
			case 2: worker -> ChangeGood();
				break;
			case 3: break;
			case 4: break;
			case 0: exit(0);
				break;
			default: cout << "Такой команды нет" << endl;
				break;
			}
		}
	}

	virtual void ChangePassword(int id){}

	virtual void SignIn(){
		string login, password;
		cout << "Введите логин: " << endl;
		cin >> login;
		cout << "Введите пароль: " << endl;
		cin >> password;
		string check, check_password;
		check = Fsearch("users.txt", login, 3);
		cout << check << endl;
		cout << password << endl;
		if (check == "Error") {
			cout << "Неверный логин" << endl;
		}
		else {
			check_password = GetParameter(check, 4);
			if (check_password == password) {
				Worker::WorkerMenu(stoi(GetParameter(check, 0)), GetParameter(check, 1), GetParameter(check, 2), GetParameter(check, 3), GetParameter(check, 4));
			}
			else {
				cout << "Неверный пароль" << endl;
			}
		}
	}

};

class Admin : public User
{

public:
	void WatchReport();
	void SetTask();

	void print_users() {
		vector<string> users = notes("users.txt");
		for (std::vector<string>::size_type i = 0; i != users.size(); i++) {
			cout << GetParameter(users[i], 0) << GetParameter(users[i], 1) << GetParameter(users[i], 2) <<  GetParameter(users[i], 3) << "*****" << endl;
		}
	}

	Admin() {
		this->id = 0;
		this->name = "Алексей";
		this->lastname = "Лебедев";
		this->login = "admin";
		this->password = "admin";
	}

	Admin(int id, string name, string lastname, string login, string password) {
		this->id = id;
		this->name = name;
		this->lastname;
		this->login = login;
		this->password = password;
	}


	static void adminMenu(int id, string name, string lastname, string login, string password) {
		Admin *admin = new Admin(id, name, lastname, login, password);
		while (true) {
			int choice;
			cout << "Меню" << endl;
			cout << "1-Добавить товар" << endl;
			cout << "2-Добавить пользователя" << endl;
			cout << "3-Посмотреть товары" << endl;
			cout << "4-Посмотреть пользователей" << endl;
			cout << "5-Удалить товар" << endl;
			cout << "6-Удалить пользователя" << endl;
			cout << "7-Изменить товар" << endl;
			cout << "8-Посмотреть отчёты" << endl;
			cout << "9-Поставить задачу" << endl;
			cout << "0-Выход из программы" << endl;
			cout << "Ваш выбор: " << endl;
			choice = getValue();
			switch (choice) {
			case 1: admin->AddGood();
				break;
			case 2: admin->Registration();
				break;
			case 3: admin->PrintGoods();
				break;
			case 4: admin->print_users();
				break;
			case 5: admin->DeleteGood();
				break;
			case 6: admin->DelUser();
				break;
			case 7: admin->ChangeGood();
				break;
			case 8: break;
			case 9: break;
			case 0: exit(0);
				break;
			default: cout << "Такой функции нет" << endl;
				break;
			}
		}
	}


	

	void DeleteGood() {
		PrintGoods();
		int id_delete;
		cout << "Введите id товара, который хотите удалить: " << endl;
		id_delete = getValue();
		string check = Fsearch("Goods.txt", to_string(id_delete), 0);
		if (check == "Error") {
			cout << "Такого товара нет" << endl;
		}
		else {
			vector<string> goods = notes("Goods.txt");
			int index = 0;
			for (std::vector<string>::size_type i = 0; i != goods.size(); i++) {
				int id = stoi(GetParameter(goods[i], 0));
				string name = GetParameter(goods[i], 1);
				int count = stoi(GetParameter(goods[i], 2));
				double weight = stof(GetParameter(goods[i], 3));
				Good* good = new Good(id, name, count, weight);
				if (good->GetId() == id_delete) { cout << "Товар " << good << " удалён" << endl; }
				else {
					if (index == 0) {
						good->save('c');
						
					}
					else {
						good->save();
					}
					index++;
				}
			}
		}
	}

	void DelUser() {
		print_users();
		int id_delete;
		cout << "Введите id пользователя, который хотите удалить: " << endl;
		id_delete = getValue();
		string check = Fsearch("users.txt", to_string(id_delete), 0);
		if (check == "Error") {
			cout << "Такого пользователя нет" << endl;
		}
		else {
			vector<string> users = notes("users.txt");
			int index = 0;
			for (std::vector<string>::size_type i = 0; i != users.size(); i++) {
				int id = stoi(GetParameter(users[i], 0));
				string name = GetParameter(users[i], 1);
				string  lastname = GetParameter(users[i], 2);
				string login = GetParameter(users[i], 3);
				string password = GetParameter(users[i], 4);
				Worker* worker = new Worker(id, name, lastname, login, password);
				if (worker->GetId() == id_delete) { cout << "Пользователь " << worker << " удалён" << endl; }
				else {
					if (index == 0) {
						worker->save('c');

					}
					else {
						worker->save();
					}
					index++;
				}
			}
		}
	}

	virtual void SignIn() {
		string login, password;
		cout << "Введите логин: " << endl;
		cin >> login;
		cout << "Введите пароль: " << endl;
		cin >> password;
		if (login == "admin" && password == "admin") {
			Admin::adminMenu(0, "Лебедев", "Алексей", "admin", "admin");
		}
	}

	virtual void ChangePassword(int id) {}
};//функция выводит меню админа 




void main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice;
	Admin *admin = new Admin();
	Worker *worker = new Worker();
	while (true) {
		cout << "Главное меню" << endl;
		cout << "1 - Вход под администратором" << endl;
		cout << "2 - Вход под клиентом" << endl;
		cout << "3 - Зарегистрироваться" << endl;
		cout << "0 - Выйти" << endl;
		choice = getValue();
		switch (choice) {
		case 1:
			admin->SignIn();
			break;
		case 2:
			worker->SignIn();
			break;
		case 3: User::Registration();
			break;
		case 0: exit(0);
		default: cout << "Неккоректный ввод, попробуйте ещё раз" << endl;
		}
	}
}



/*void outPut(int per, int index) { //номер в файле ещё надо отправлять
	string line;
	string path = "offers.txt";
	ifstream put(path);
	Offers offer;
	int help, help1;
	if (per == 1) {
		help = index;
		help1 = index;
	}
	else {
		help = 0;
		help1 = fsize(path);
	}
	if (!put.is_open()) {
		cout << "Невозможно открыть файл с путёвками" << endl;
	}
	else {
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = help; i <= help1; i++)
		{
			offer.ID = stoi(fulldata(path, i, 0));
			offer.name = fulldata(path, i, 1);
			offer.Cname.name = fulldata(path, i, 2);
			offer.Cname.clim.name = fulldata(path, i, 3);
			offer.Cname.clim.tempreture = stoi(fulldata(path, i, 4));
			offer.Cname.clim.humidity = stoi(fulldata(path, i, 5));
			offer.Cname.sea = fulldata(path, i, 6);
			offer.cost = stoi(fulldata(path, i, 7));
			cout << setw(5) << offer.ID << "|";
			cout << setw(20) << offer.name << "|";
			cout << setw(15) << offer.Cname.name << "|";
			cout << setw(15) << offer.Cname.clim.name << "|";
			cout << setw(15) << offer.Cname.clim.tempreture << "|";
			cout << setw(15) << offer.Cname.clim.humidity << "|";
			cout << setw(10) << offer.Cname.sea << "|";
			cout << setw(15) << offer.cost << "|" << endl;
		}
	}
}*/















/*void sort() {
	int choice, index;
	cout << "Сортировать по убыванию или по возрастанию?(1- По возрастанию, 2 - По убыванию)" << endl;
	choice = getValue();
	string path = "offers.txt";
	string line;
	Offers* arr = new Offers[fsize(path)+1];
	int* arr1 = new int[fsize(path)+1];
	for (int i = 0; i <= fsize(path); i++)
	{
		arr[i].ID = stoi(fulldata(path, i, 0));
		arr[i].name = fulldata(path, i, 1);
		arr[i].Cname.name = fulldata(path, i, 2);
		arr[i].Cname.clim.name = fulldata(path, i, 3);
		arr[i].Cname.clim.tempreture = stoi(fulldata(path, i, 4));
		arr[i].Cname.clim.humidity = stoi(fulldata(path, i, 5));
		arr[i].Cname.sea = fulldata(path, i, 6);
		arr[i].cost = stoi(fulldata(path, i, 7));
		arr1[i] = stoi(fulldata(path, i, 7));
	}
	switch (choice) {
	case 1: {
		int schoice;
		qsort(arr1, fsize(path) + 1, sizeof(int), comp1);
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = 0; i <= fsize(path); i++)
		{
			line = to_string(arr1[i]);
			index = stoi(Fsearch(path, to_string(arr1[i]), 7, 'k'));
			cout << setw(5) << arr[index].ID << "|";
			cout << setw(20) << arr[index].name << "|";
			cout << setw(15) << arr[index].Cname.name << "|";
			cout << setw(15) << arr[index].Cname.clim.name << "|";
			cout << setw(15) << arr[index].Cname.clim.tempreture << "|";
			cout << setw(15) << arr[index].Cname.clim.humidity << "|";
			cout << setw(10) << arr[index].Cname.sea << "|";
			cout << setw(15) << arr[index].cost << "|" << endl;
		}
		cout << "Вывести это в файл?(1-да, 2-нет)" << endl;
		schoice = getValue();
		string message;
		if (schoice == 1)
		{
			for (int i = 0; i <= fsize(path); i++)
			{
				message = to_string(arr[index].ID) + "," + arr[index].name + "," + arr[index].Cname.name + "," + arr[index].Cname.clim.name + "," + to_string(arr[index].Cname.clim.tempreture) + "," + to_string(arr[index].Cname.clim.humidity) + ",Есть," + to_string(arr[index].cost) + "|";
				if (i == 0)
					Record(path, message);
				else
					Record(path, message, 'a');
			}
			cout << "Сортированный список успешно выведен" << endl;
		}
		break;
	}
	case 2: {
		qsort(arr1, fsize(path) + 1, sizeof(int), comp2);
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = 0; i <= fsize(path); i++)
		{
			line = to_string(arr1[i]);
			index = stoi(Fsearch(path, to_string(arr1[i]), 7, 'k'));
			cout << setw(5) << arr[index].ID << "|";
			cout << setw(20) << arr[index].name << "|";
			cout << setw(15) << arr[index].Cname.name << "|";
			cout << setw(15) << arr[index].Cname.clim.name << "|";
			cout << setw(15) << arr[index].Cname.clim.tempreture << "|";
			cout << setw(15) << arr[index].Cname.clim.humidity << "|";
			cout << setw(10) << arr[index].Cname.sea << "|";
			cout << setw(15) << arr[index].cost << "|" << endl;
		}
		cout << "Вывести это в файл?(1-да, 2-нет)" << endl;
		int schoice = getValue();
		string message;
		if (schoice == 1)
		{
			for (int i = 0; i <= fsize(path); i++)
			{
				message = to_string(arr[index].ID) + "," + arr[index].name + "," + arr[index].Cname.name + "," + arr[index].Cname.clim.name + "," + to_string(arr[index].Cname.clim.tempreture) + "," + to_string(arr[index].Cname.clim.humidity) + ",Есть," + to_string(arr[index].cost) + "|";
				if (i == 0)
					Record(path, message);
				else
					Record(path, message, 'a');
			}
			cout << "Сортированный список успешно выведен" << endl;
		}
		break;
	}
	default: cout << "Неверный ввод" << endl;
		break;
	}
}*/