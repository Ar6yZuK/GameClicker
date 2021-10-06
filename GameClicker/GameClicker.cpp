// GameClicker v. Test
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<direct.h>
#include<conio.h>
using namespace std;

bool space = false; // true Когда нажата \ функция SpaceUp
bool Exit = false; // false Пока цикл живет \ функция ExitEscape
bool Click = false; // false пока не кликнут \ функция ClickUp
bool H = false; // true Если нажата \ функция HUp
bool E = false; //
bool ShopOpen = false; // Для функции Eup()
bool DirectoryOpen = false; // HUp()
bool BackUp = false; // Для функции BackSpaceCLS()
float cookies = 0.0; // Печеньки которые записываются и считываются с создаваемого файла
int cookiesInThisGame = 0; // Печеньки полученные в данный заход

char current_work_dir[FILENAME_MAX];
string file_path = _getcwd(current_work_dir, sizeof(current_work_dir)); // отображает путь к исполняемому файлу без имени файла
string cookies_file_name = "\\Твои печеньки.txt"; // Имя файла. Обязательно с расширением
string shop_file_name = "\\Твой закуп.txt";
string cookies_full_path = file_path + cookies_file_name; // cookies_full_path
string shop_full_path = file_path + shop_file_name;
void ExitEscape(); // Функция выхода с цикла при нажатии escape
void cleansing(); // Анти клик
//void SpaceUp(); // Функция нажатия клавиши Space
void ClickUp(); // Функция клика левой кнопки мыши
void RecordingCookies(); // Запись печенек. Запоминание количества печенек
void RecordingShop();
void ConsoleMoDe(); // Делает невозможным выделения текста в консоли(Для кликов в консоли левой кнопкой мыши)
void HUp(); // Функция нажатия H открывает справочник
void Directory(); // Функция работы справочника
void EUp(); // Функция нажатия E открывает магазин
void Shop(); // Функция работы магазина
bool AutoClicker_buy = false, q_buy = false, w_buy = false, e_buy = false, r_buy = false; // Если пользователь купил чтото то bool станет true
void BackSpaceCLS(); // Очищает консоль 
void printcookies(bool BoL = true); // Отображает количество печенек с endl
void printcookiesone(); // Отображает количество печенек полученное за этот заход
enum ShopAssortment { Auto_clicker = '1', q = '2', w = '3', e = '4', r = '5' };
const float pAuto_clicker = 10.0, pq = 20.0, pw = 30.0, pe = 40.0, pr = 50.0 ; // Цена ShopAssortment
int Auto_clickerbuys = 0, qbuys = 0, wbuys = 0, ebuys = 0, rbuys = 0;
bool bAuto_clicker = false, bq = false, bw = false, be = false, br = false; // b значит bool
void CheckBuyShop(ShopAssortment); // Принимает клавишу от 1 до 5 покупает чтото в магазине

BOOL WINAPI HandlerRoutine(
	_In_ DWORD dwCtrlType
) {
	switch (dwCtrlType) {
	case CTRL_CLOSE_EVENT:
		RecordingCookies();
		RecordingShop();
		break;
	}
	return TRUE;
} // Эта команда вызывает RecordingCookies() если пользователь вышел не через escape, а через другие способы

int main() {
	ConsoleMoDe();
	setlocale(LC_ALL, "Rus"); // Русификация
	cout << "Прошу не изменяй txt файлы" << endl;
	ifstream fileCheckcookies(cookies_full_path);
	if (!fileCheckcookies.is_open()) {// Проверка на существование файла 
		cout << "Файл с печеньками не найден!" << endl;
		cout << "Создание файла " << cookies_full_path << endl;
		ofstream file2(cookies_full_path);
		file2.close();
		cout << "Файл " << cookies_full_path << " создан!" << endl; // Если файла нет то он создастся
	}
	else {
		cout << "Файл с печеньками найден!" << endl;
	}
	fileCheckcookies.close();
	ifstream findOutCookies(cookies_full_path);
	findOutCookies >> cookies;
	findOutCookies.close(); // Запись печенек в переменную cookies из файла

	string countc;
	ifstream findStrlencookies(cookies_full_path);
	findStrlencookies >> countc;
	if (strlen(countc.c_str()) == 0) {
		ofstream findStrlenC(cookies_full_path);
		findStrlenC << "0.0";
		findStrlenC.close();
	}
	findStrlencookies.close();

	ifstream fileCheckShop(shop_full_path);
	if (!fileCheckShop.is_open()) {
		cout << "Файл с закупом не найден!" << endl;
		ofstream shopcreate(shop_full_path);
		cout << "Создание файла " << shop_full_path << endl;
		shopcreate.close();
		cout << "Файл " << shop_full_path << " создан!" << endl;
	}
	else {
		cout << "Файл с закупом найден!" << endl;
	}
	fileCheckShop.close();
	ifstream fileShopOut(shop_full_path);
	fileShopOut >> Auto_clickerbuys;
	fileShopOut >> qbuys;
	fileShopOut >> wbuys;
	fileShopOut >> ebuys;
	fileShopOut >> rbuys;
	fileShopOut.close();

	string countb1, countb2, countb3, countb4, countb5;
	fstream shha(shop_full_path, ios_base::in);
	shha >> countb1 >> countb2 >> countb3 >> countb4 >> countb5;
	shha.close();
	if (strlen(countb1.c_str()) == 0 or strlen(countb5.c_str()) == 0) {
		ofstream shas(shop_full_path);
		shas << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0;
		shas.close();
	}

	cout << "Чтобы посмотреть справочник нажми h" << endl;
	
	printcookies();
	while (!Exit) {
			cleansing();
			HUp();
			EUp();
			Shop();
			Directory();
			ClickUp();
			BackSpaceCLS();
			ExitEscape();
			SetConsoleCtrlHandler(HandlerRoutine, TRUE); // Для сохранения печенек в экстренных ситуациях
		Sleep(1);
	}
	printcookies(); // Отображает количество печенек на данный момент. После выхода из цикла
	cout << "Ты набрал "; printcookiesone(); cout << " за этот заход" << endl; // Печеньки которые набраны за данный заход
	RecordingShop();
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
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (GetAsyncKeyState(VK_ESCAPE)) {
			Exit = true;
			ShopOpen = false;
			DirectoryOpen = false;
		}
	}
}
//void SpaceUp() { // Функция нажатия клавиши Space
//	if (GetAsyncKeyState(VK_SPACE) and space == false) {
//		space = true;
//		cookies++;
//		cookiesInThisGame++;
//		cout << "|SpaceUp + 1 печенька " << cookies << "|" << endl;
//	}
//	if (GetAsyncKeyState(VK_SPACE) == 0 and space == true) {
//		space = false;
//	}
//}
void EUp() {
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (GetAsyncKeyState('E') and E == false) {
			E = true;
			ShopOpen = true;
		}
		if (GetAsyncKeyState('E') == 0 and E == true) {
			E = false;
		}
	}
}
void Shop() {
	if (ShopOpen) {
		cleansing();
		system("cls");
		cout << "Ты открыл магазин!                                                            |Цена 1: " << pAuto_clicker << "|Количество 1: " << Auto_clickerbuys << "|" << endl;
		cout << "Чтобы чтонибудь купить тебе нужно накопить печеньки кликая                    |Цена 2: " << pq << "|Количество 2: " << qbuys << "|" << endl;
		cout << "Если ты уже накопил печеньки, то можешь купить усилители нажимая на цифры 1-9 |Цена 3: " << pw << "|Количество 3: " << wbuys << "|" << endl;
		cout << "Если ты купишь усиление то проиграется звук                                   |Цена 4: " << pe << "|Количество 4: " << ebuys << "|" << endl;
		cout << "Чтобы выйти из магазина нажми E                                               |Цена 5: " << pr << "|Количество 5: " << rbuys << "|" <<endl;
		cout << "Чтобы выйти с игры нажми escape" << endl;
		printcookies();
		if (AutoClicker_buy) {
			cout << "Ты прикупил 1!" << endl;
		}
		if (q_buy) {
			cout << "Ты прикупил 2!" << endl;
		}
		if (w_buy) {
			cout << "Ты прикупил 3!" << endl;
		}
		if (e_buy) {
			cout << "Ты прикупил 4!" << endl;
		}
		if (r_buy) {
			cout << "Ты прикупил 5!" << endl;
		} // Если пользователь купил чтото то напишется что он купил
		AutoClicker_buy = false, q_buy = false, w_buy = false, e_buy = false, r_buy = false;

		while (ShopOpen) {
			cleansing();
			ExitEscape(); // Если пользователь захочет выйти с игры
			if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
				if (GetAsyncKeyState('E') and E == false) {
					E = true;
					ShopOpen = false;
					system("cls");
					cout << "Ты закрыл магазин!" << endl;
					cout << "Прошу не изменяй txt файлы" << endl;
					cout << "Чтобы посмотреть справочник нажми h" << endl;
					printcookies(); // Отображает печеньки
				}
				if (GetAsyncKeyState('E') == 0 and E == true) {
					E = false;
				} // Если в магазине нажмут E закроется магазин
				CheckBuyShop(ShopAssortment::Auto_clicker); // Когда нажата клавиша 1
				CheckBuyShop(ShopAssortment::q); // Когда нажата клавиша 2
				CheckBuyShop(ShopAssortment::w); // Когда нажата клавиша 3
				CheckBuyShop(ShopAssortment::e); // Когда нажата клавиша 4
				CheckBuyShop(ShopAssortment::r); // Когда нажата клавиша 5
			}
			Sleep(1);
		}
	}
}
void CheckBuyShop(ShopAssortment ShopAssortiment) { // Принимает enum от 1 до 5 покупает чтото в магазине если хватает пченек
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (ShopAssortiment == Auto_clicker) { // Проверка на Аргумент в функции 1
			if (GetAsyncKeyState(Auto_clicker) and bAuto_clicker == false) {
				bAuto_clicker = true;
				if (cookies > 0 and cookies - pAuto_clicker >= 0) {
					cookies -= pAuto_clicker;
					Auto_clickerbuys++;
					Beep(2000, 10);
					ShopOpen = true;
					AutoClicker_buy = true;
					Shop(); 
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 1! "; printcookies(false); cout << ". А тебе нужно " << pAuto_clicker << "!" << endl;
				}
			}
			if (GetAsyncKeyState(Auto_clicker) == 0 and bAuto_clicker == true) {
				bAuto_clicker = false;
			} // Если в магазине нажмут 1 купится предмет Auto_clicker
		}
		if (ShopAssortiment == q) { // Проверка на Аргумент в функции 3
			if (GetAsyncKeyState(q) and bq == false) {
				bq = true;
				if (cookies > 0 and cookies - pq >= 0) {
					cookies -= pq;
					qbuys++;
					Beep(2000, 10);
					ShopOpen = true;
					q_buy = true;
					Shop();
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 2! "; printcookies(false); cout << ". А тебе нужно " << pq << "!" << endl;
				}
			}
			if (GetAsyncKeyState(q) == 0 and bq == true) {
				bq = false;
			} // Если в магазине нажмут 2 купится предмет q
		}
		if (ShopAssortiment == w) { // Проверка на Аргумент в функции 3
			if (GetAsyncKeyState(w) and bw == false) {
				bw = true;
				if (cookies > 0 and cookies - pw >= 0) {
					cookies -= pw;
					wbuys++;
					Beep(2000, 10);
					ShopOpen = true;
					w_buy = true;
					Shop();
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 3! "; printcookies(false); cout << ". А тебе нужно " << pw << "!" << endl;
				}
			}
			if (GetAsyncKeyState(w) == 0 and bw == true) {
				bw = false;
			} // Если в магазине нажмут 3 купится предмет w
		}
		if (ShopAssortiment == e) { // Проверка на Аргумент в функции 3
			if (GetAsyncKeyState(e) and be == false) {
				be = true;
				if (cookies > 0 and cookies - pe >= 0) {
					cookies -= pe;
					ebuys++;
					Beep(2000, 10);
					ShopOpen = true;
					e_buy = true;
					Shop();
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 4! "; printcookies(false); cout << ". А тебе нужно " << pe << "!" << endl;
				}
			}
			if (GetAsyncKeyState(e) == 0 and be == true) {
				be = false;
			} // Если в магазине нажмут 4 купится предмет e
		}
		if (ShopAssortiment == r) { // Проверка на Аргумент в функции 5
			if (GetAsyncKeyState(r) and br == false) {
				br = true;
				if (cookies > 0 and cookies - pr >= 0) {
					cookies -= pr;
					rbuys++;
					Beep(2000, 10);
					ShopOpen = true;
					r_buy = true;
					Shop();
				}
				else {
					cout << "У тебя не хватает печенек чтобы купить 5! "; printcookies(false); cout << ". А тебе нужно " << pr << "!" << endl;
				}
			}
			if (GetAsyncKeyState(r) == 0 and br == true) {
				br = false;
			} // Если в магазине нажмут 5 купится предмет r
		}
	}
}
void HUp() { // Функция нажатия H открывает справочник
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (GetAsyncKeyState('H') and H == false) {
			H = true;
			DirectoryOpen = true;
		}
		if (GetAsyncKeyState('H') == 0 and H == true) {
			H = false;
		}
	}
}
void Directory() { // Справочник
	if (DirectoryOpen) {
		cleansing();
		system("cls");
		cout << "Ты открыл справочник!" << endl;
		cout << "Путь до файла с количеством печенек: \"" << cookies_full_path << "\"\n" << "Путь до файла с закупом:             \"" << shop_full_path << "\"" << "\nЧтобы выйти с игры используй escape\nЧтобы зайти в магазин нажми e\nЧтобы очистить экран от лишнего текста нажми backspace\nЧтобы выйти со справочника нажми h" << endl;
		while (DirectoryOpen) {
			if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
				cleansing();
				ExitEscape(); // Если пользователь захочет выйти
				if (GetAsyncKeyState('H') and H == false) {
					system("cls");
					cout << "Ты закрыл справочник!" << endl;
					cout << "Прошу не изменяй txt файлы" << endl;
					cout << "Чтобы посмотреть справочник нажми h" << endl;
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
}
void BackSpaceCLS() {
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (GetAsyncKeyState(VK_BACK) and BackUp == false) {
			BackUp = true;
			system("cls");
			cout << "У имеется " << cookies << " печенек" << endl;
		}
		if (GetAsyncKeyState(VK_BACK) == 0 and BackUp == true) {
			BackUp = false;
		}
	}
}
void ClickUp() { // Функция клика левой кнопки мыши
	if (GetConsoleWindow() == GetForegroundWindow()) { // Если пользователь находится в консоли(в игре) то игра работает
		if (GetAsyncKeyState(VK_LBUTTON) and Click == false) {
			Beep(499, 20);
			Click = true;
			cookies++;
			cookiesInThisGame++;
			cout << "Click + 1 печенька. ";
			printcookies();
			RecordingCookies(); // Когда пользователь отпускает левую кнопку мыши тогда происходит запись печенек в файл cookies_full_path
		}
		if (GetAsyncKeyState(VK_LBUTTON) == 0 and Click == true) {
			Click = false;
		}
	}
}
void printcookiesone() {
	if (cookiesInThisGame % 10 == 0) {
		cout << cookiesInThisGame << " печенек";
	}
	else if (cookiesInThisGame % 10 == 1 and cookiesInThisGame % 100 != 11) {
		cout << cookiesInThisGame << " печеньку";
	}
	else if (cookiesInThisGame % 100 > 11 and cookiesInThisGame % 100 < 15) {
		cout << cookiesInThisGame << " печенек";
	}
	else if (cookiesInThisGame % 10 > 1 and cookiesInThisGame % 10 < 5 and cookiesInThisGame > 20) {
		cout << cookiesInThisGame << " печеньки";
	}
	else if (cookiesInThisGame % 10 > 1 and cookiesInThisGame % 10 < 5 and cookiesInThisGame < 10) {
		cout << cookiesInThisGame << " печеньки";
	}
	else {
		cout << cookiesInThisGame << " печенек";
	}
}
void printcookies(bool BoL) {
	if (BoL) {
		if ((int)cookies % 10 == 0) {
			cout << "У тебя имеется " << cookies << " печенек" << endl;
		}
		else if ((int)cookies % 10 == 1 and (int)cookies % 100 != 11) {
			cout << "У тебя имеется " << cookies << " печенька" << endl;
		}
		else if ((int)cookies % 100 > 11 and (int)cookies % 100 < 15) {
			cout << "У тебя имеется " << cookies << " печенек" << endl;
		}
		else if ((int)cookies % 10 > 1 and (int)cookies % 10 < 5 and (int)cookies > 20) {
			cout << "У тебя имеется " << cookies << " печеньки" << endl;
		}
		else if ((int)cookies % 10 > 1 and (int)cookies % 10 < 5 and cookies < 10) {
			cout << "У тебя имеется " << cookies << " печеньки" << endl;
		}
		else {
			cout << "У тебя имеется " << cookies << " печенек" << endl;
		}
	}
	else {
		if ((int)cookies % 10 == 0) {
			cout << "У тебя имеется " << cookies << " печенек";
		}
		else if ((int)cookies % 10 == 1 and (int)cookies % 100 != 11) {
			cout << "У тебя имеется " << cookies << " печенька";
		}
		else if ((int)cookies % 100 > 11 and (int)cookies % 100 < 15) {
			cout << "У тебя имеется " << cookies << " печенек";
		}
		else if ((int)cookies % 10 > 1 and (int)cookies % 10 < 5 and (int)cookies > 20) {
			cout << "У тебя имеется " << cookies << " печеньки";
		}
		else if ((int)cookies % 10 > 1 and (int)cookies % 10 < 5 and (int)cookies < 10) {
			cout << "У тебя имеется " << cookies << " печеньки";
		}
		else {
			cout << "У тебя имеется " << cookies << " печенек";
		}
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
	if (GetAsyncKeyState(VK_BACK) == 0 and BackUp == true) {
		BackUp = false;
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
void RecordingShop() {
	ofstream shoprecord(shop_full_path);
	shoprecord << Auto_clickerbuys << " " << qbuys << " " << wbuys << " " << ebuys << " " << rbuys;
	shoprecord.close();
}
void RecordingCookies() { // Запись печенек. Запоминание количества печенек
	ofstream cookiesrecord(cookies_full_path);
	cookiesrecord << (float)cookies;
	cookiesrecord.close();
}