#include <iostream>
#include <string>
using namespace std;

/*
Zad: Zrotować cyklicznie tablicę t zawierającą n liczb całkowitych w prawo o k pozycji.
Dla ujemnych k, należy zrotować tablicę w lewo.

Rozwiązanie (najprostsze w implementacji):
	* obracamy podtablicę z pierwszymi n-k elementami,
	* obracamy podtablicę z ostatnimi k elementami,
	* obracamy całą tablicę.

Dowód poprawności: na pocżątku mamy:
t_0, t_1, ..., t_{n-1}
Po pierwszym kroku:
t_{n-k-1}, t_{n-k-2}, ..., t_1, t_0, t_{n-k}, ..., t_{n-1}
Po drugim kroku:
t_{n-k-1}, t_{n-k-2}, ..., t_1, t_0, t_{n-1}, ..., t_{n-k}
Po trzecim kroku:
t_{n-k}, t_{n-k+1}, ..., t_{n-1}, t_1, t_2, ..., t_{n-k-1}
*/


void reverse(int t[],  int a, int b) {
	for (int i = a; i < a+b-i-1; i++) {
		int x = t[i];
		t[i] = t[a+b-i-1];
		t[a+b-i-1] = x;
	}
}

void rotate(int t[], int n, int k) {
	if (k < 0)
		rotate(t, n, n+k);
	else {
		reverse(t, 0, n-k);
		reverse(t, n-k, n);
		reverse(t, 0, n);
	}
}

/******************* TESTY ***********************/


void test(bool warunek) {
	if (warunek)
		cout << "OK\n";
	else
		cout << "ERR\n";
}

string tab_to_str(int t[], int n) {
	string wynik = "";
	for (int i = 0; i < n; i++) {
		wynik += to_string(t[i]) + ";";
	}
	return wynik;
}

int main() {
	int n = 10;
	int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	rotate(t, n, 3);
	test(tab_to_str(t, n) == "8;9;10;1;2;3;4;5;6;7;");
	rotate(t, n, n);
	test(tab_to_str(t, n) == "8;9;10;1;2;3;4;5;6;7;");
	rotate(t, n, 0);
	test(tab_to_str(t, n) == "8;9;10;1;2;3;4;5;6;7;");
	rotate(t, n, -4);
	test(tab_to_str(t, n) == "2;3;4;5;6;7;8;9;10;1;");
	return 0;
}
