#include<iostream>
#include<Windows.h>
#include<fstream>
#include<direct.h>
#include <conio.h>
using namespace std;

bool space = false; // true Когда нажата \ функция SpaceUp
bool Exit = false; // false Пока цикл живет \ функция ExitEscape
bool Click = false; // false пока не кликнут \ функция ClickUp
bool H = false; // true Если нажата \ функция HUp
bool E = false; //
bool ShopOpen = false; // Для функции Eup()
bool DirectoryOpen = false;
bool BackUp = false; // Для функции BackSpaceCLS()
int cookies = 0; // Печеньки которые записываются и считываются с создаваемого файла
int cookiesInThisGame = 0; // Печеньки полученные в данный заход

char current_work_dir[FILENAME_MAX];
string file_path = _getcwd(current_work_dir, sizeof(current_work_dir)); // отображает путь к исполняемому файлу без имени файла
string cookies_file_name = "\\Твои печеньки.txt"; // Имя файла. Обязательно с расширением
string shop_file_name = "\\Твой закуп.txt";
string cookies_full_path = file_path + cookies_file_name; // cookies_full_path
string shop_full_path = file_path + shop_file_name;
void ExitEscape(); // Функция выхода с цикла при нажатии escape
void cleansing(); // Анти клик
void SpaceUp(); // Функция нажатия клавиши Space
void ClickUp(); // Функция клика левой кнопки мыши
void RecordingCookies(); // Запись печенек. Запоминание количества печенек
void ConsoleMoDe(); // Делает невозможным выделения текста в консоли(Для кликов в консоли левой кнопкой мыши)
void HUp(); // Функция нажатия H открывает справочник
void Directory(); // Функция работы справочника
void EUp(); // Функция нажатия E открывает магазин
void Shop(); // Функция работы магазина
void BackSpaceCLS(); // Очищает консоль 
enum ShopAssortment { Auto_clicker = '1', q = '2', w = '3', e = '4', r = '5' };
enum ShopPrices { pAuto_clicker = 10, pq = 20, pw = 30, qe = 40, qr = 50 };
bool bAuto_clicker = false, bq = false, bw = false, be = false, br = false; // b значит bool

BOOL WINAPI HandlerRoutine(
	_In_ DWORD dwCtrlType
) {
	switch (dwCtrlType) {
	case CTRL_CLOSE_EVENT:
		RecordingCookies();
		break;
	}
	return TRUE;
} // Эта команда вызывает RecordingCookies() если пользователь вышел не через escape, а через другие способы

int main() {
	ConsoleMoDe();
	setlocale(LC_ALL, "Rus"); // Русификация
	ifstream fileCheck(cookies_full_path);
	if (!fileCheck.is_open()) {// Проверка на существование файла 
		cout << "Файл с печеньками не найден!" << endl;
		cout << "Создание файла " << cookies_full_path << endl;
		ofstream file2(cookies_full_path);
		file2.close();
		cout << "Файл " << cookies_full_path << " создан!" << endl; // Если файла нет то он создастся
	}
	else {
		cout << "Файл с печеньками найден!" << endl;
	}
	fileCheck.close();
	ifstream findOutCookies(cookies_full_path);
	findOutCookies >> cookies;
	findOutCookies.close(); // Запись печенек в переменную cookies из файла

	string countc;
	ifstream findStrlen(cookies_full_path);
	findStrlen >> countc;
	if (strlen(countc.c_str()) == 0) {
		ofstream findStrlenC(cookies_full_path);
		findStrlenC << "0";
		findStrlenC.close();
	}
	findStrlen.close();

	ofstream shop(shop_full_path);

	shop.close();

	cout << "Прошу не изменяй txt файлы" << endl;
	cout << "Чтобы посмотреть справочник нажми h" << endl;
	cout << "У тебя имеется " << cookies << " печенек" << endl;
	while (!Exit) {
		cleansing();
		HUp();
		EUp();
		Shop();
		Directory();
		ClickUp();
		BackSpaceCLS();
		ExitEscape();
		SetConsoleCtrlHandler(HandlerRoutine, TRUE);
		Sleep(1);
	}
	cout << "У имеется есть " << cookies << " печенек" << endl; // Отображает количество печенек на данный момент. После выхода из цикла
	cout << "Ты набрал " << cookiesInThisGame << " печенек, за этот заход" << endl; // Печеньки которые набраны за данный заход
	RecordingCookies(); // Запись печенек. Запоминание количества печенек
	return 0;
}
void ConsoleMoDe() {
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prevConsoleMode = 0;
	GetConsoleMode(hConsole, &prevConsoleMode);
	SetConsoleMode(hConsole, prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE); // Делает невозможным выделения текста в консоли(Для кликов в консоли левой кнопкой мыши)
}
void ExitEscape() { // Функция выхода с цикла при нажатии escape
	if (GetAsyncKeyState(VK_ESCAPE)) {
		Exit = true;
		ShopOpen = false;
	}
}
void SpaceUp() { // Функция нажатия клавиши Space
	if (GetAsyncKeyState(VK_SPACE) and space == false) {
		space = true;
		cookies++;
		cookiesInThisGame++;
		cout << "|SpaceUp + 1 печенька " << cookies << "|" << endl;
	}
	if (GetAsyncKeyState(VK_SPACE) == 0 and space == true) {
		space = false;
	}
}
void EUp() {
	if (GetAsyncKeyState('E') and E == false) {
		E = true;
		ShopOpen = true;
	}
	if (GetAsyncKeyState('E') == 0 and E == true) {
		E = false;
	}
}
void Shop() {
	if (ShopOpen) {
		system("cls");
		cout << "Ты открыл магазин!" << endl;
		cout << "Чтобы чтонибудь купить тебе нужно накопить печеньки кликая" << endl;
		cout << "Если ты уже накопил печеньки, то можешь купить усилители нажимая на цифры 1-9" << endl;
		cout << "Если ты купишь усиление то проиграется звук" << endl;
		cout << "Чтобы выйти из магазина нажми E" << endl;
		cout << "Чтобы выйти с игры нажми escape" << endl;
		cout << "У тебя есть " << cookies << " печенек" << endl;

		while (ShopOpen) {
			cleansing();
			ExitEscape(); // Если пользователь захочет выйти с игры
			if (GetAsyncKeyState('E') and E == false) {
				E = true;
				ShopOpen = false;
				system("cls");
				cout << "Вы покинули Магазин!" << endl;
				cout << "У тебя имеется " << cookies << " печенек" << endl;
			}
			if (GetAsyncKeyState('E') == 0 and E == true) {
				E = false;
			} // Если в магазине нажмут E закроется магазин
			if (GetAsyncKeyState(Auto_clicker) and bAuto_clicker == false) {
				bAuto_clicker = true;
				if (cookies > 0 and cookies - 10 >= 0) {
					cookies -= 10;
					Beep(4000, 100);
					cout << "Ты прикупил 1!" << " У тебя имеется " << cookies << " печенек" << endl;
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 1!" << endl;
					cout << "У тебя имеется " << cookies << " печенек. " << "А тебе нужно " << pAuto_clicker << "!" << endl;
				}
			}
			if (GetAsyncKeyState(Auto_clicker) == 0 and bAuto_clicker == true) {
				bAuto_clicker = false;
			} // Если в магазине нажмут 1 купится предмет Auto_clicker
			Sleep(1);
		}
	}
}
void HUp() { // Функция нажатия H открывает справочник
	if (GetAsyncKeyState('H') and H == false) {
		H = true;
		DirectoryOpen = true;
	}
	if (GetAsyncKeyState('H') == 0 and H == true) {
		H = false;
	}
}
void Directory() {
	if (DirectoryOpen) {
		cleansing();
		system("cls");
		cout << "Ты открыл справочник" << endl;
		cout << "Путь до файла с количеством печенек: \"" << cookies_full_path << "\"\nЧтобы выйти с игры используй escape\nЧтобы зайти в магазин нажми e\nЧтобы очистить экран от лишнего текста нажми backspace\nЧтобы продолжить играть нажми e" << endl;
		while (DirectoryOpen) {
			ExitEscape(); // Если пользователь захочет выйти
			if (GetAsyncKeyState('H') and H == false) {
				system("cls");
				cout << "Ты закрыл справочник!" << endl;
				cout << "У тебя имеется " << cookies << " печенек" << endl;
				DirectoryOpen = false;
				H = true;
			}
			if (GetAsyncKeyState('H') == 0 and H == true) {
				H = false;
			}
		}
	}
}
void BackSpaceCLS() {
	if (GetAsyncKeyState(VK_BACK) and BackUp == false) {
		BackUp = true;
		system("cls");
	}
	if (GetAsyncKeyState(VK_BACK) == 0 and BackUp == true) {
		BackUp = false;
	}
}
void ClickUp() { // Функция клика левой кнопки мыши
	if (GetAsyncKeyState(VK_LBUTTON) and Click == false) {
		Click = true;
		cookies++;
		cookiesInThisGame++;
		cout << "Click + 1 печенька. " << "У тебя сейчас " << cookies << " печенек" << endl;
		RecordingCookies(); // Когда пользователь отпускает левую кнопку мыши тогда происходит запись печенек в файл cookies_full_path
	}
	if (GetAsyncKeyState(VK_LBUTTON) == 0 and Click == true) {
		Click = false;
	}
}
void cleansing() {
	if (GetAsyncKeyState('H') == 0 and H == true) {
		H = false;
	}
	if (GetAsyncKeyState('E') == 0 and E == true) {
		E = false;
	}
	if (GetAsyncKeyState(VK_SPACE) == 0 and space == true) {
		space = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON) == 0 and Click == true) {
		Click = false;
	}
	if (GetAsyncKeyState(Auto_clicker) == 0 and bAuto_clicker == true) {
		bAuto_clicker = false;
	}
	if (GetAsyncKeyState(q) == 0 and bAuto_clicker == true) {
		bq = false;
	}
	if (GetAsyncKeyState(w) == 0 and bAuto_clicker == true) {
		bw = false;
	}
	if (GetAsyncKeyState(e) == 0 and bAuto_clicker == true) {
		be = false;
	}
	if (GetAsyncKeyState(r) == 0 and bAuto_clicker == true) {
		br = false;
	}

} // Анти клик
void RecordingCookies() { // Запись печенек. Запоминание количества печенек
	ofstream file3(cookies_full_path);
	file3 << cookies;
	file3.close();
}
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<Windows.h>
//	using namespace std;
//
//int main() {
//	setlocale(LC_ALL, "Rus");
//	char path[] = "C:\\cpp\\aboba.txt";
//	int money = 0;
//	char text[30];
//
//	ifstream filetest(path);
//	if (!filetest.is_open()) { // Проверка на существование файла
//		ofstream createfile(path); // Если файл не существует. Он создается
//		createfile.close();
//	}
//	filetest >> text;
//	filetest.close();
//	if (size(text) == 0) { // Проверка на ЛОГ
//		ofstream fileopen(path);
//		fileopen << money;
//		fileopen.close();
//	}
//	ifstream moneyS2(path);
//	moneyS2 >> money;
//	moneyS2.close(); // Считываем с файла aboba.txt данные и запиваем их в money
//	cout << "Your money: " << money << endl;
//	while (true) { // Game is here \|/
//		if (GetAsyncKeyState(VK_ESCAPE)){
//			cout << "Escaped" << endl;
//			break;
//		}
//		if (GetAsyncKeyState(VK_LBUTTON)) {
//			money++;
//			Sleep(100);
//			cout << "Your money: " << money << endl;
//		}
//	}
//	cout << "Your money: " << money << endl;
//
//	ofstream moneyS(path);
//	moneyS << money;
//	moneyS.close(); // Запоминаем в aboba.txt свои деньги
//	//system("pause");
//	
//	return 0;
//}