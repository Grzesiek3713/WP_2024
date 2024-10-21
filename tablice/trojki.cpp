//WP* ćwiczenia 3, zadanie "Trójki"
//Autor: Grzegorz Pierczyński

#include <iostream>
using namespace std;

/*
Zad: Mając daną posortowaną ściśle rosnąco tablicę t, znaleźć w niej liczbę
wszystkich trójek a, b, c takich że a < b < c oraz c < a + b (co oznacza że 
a, b, c spełniają nierówność trójkąta). 


Rozwiązanie:
	* mamy trzy iteratory, ia, ib, ic (wskazujące odpowiednio na indeks z
		obecnie rozważanym kandydatem na a, na b, i na maksymalny możliwy indeks
		c dla obecnie rozważanych a i b).
	* ia idzie po całej tablicy od lewej do prawej,
	* ib idzie po fragmencie tablicy [ia+1..ic-1] od lewej do prawej,
	* ic idzie po sufiksie tablicy [ib+1..n-1] od lewej do prawej,
	* spostrzeżenie: dla ustalonych ia, ib, nie musimy resetować ic za każdym 
		razem, lecz może on iść "razem" z ib. Jeśli bowiem jakaś wartość ic 
		spełnia nierówność trójkąta dla ustalonych ia, ib, to zwiększenie ia, ib
		(przy zachowaniu ia < ib < ic) sprawi że ic będzie spełniać nierówność 
		trójkąta jeszcze bardziej.

Złożoność czasowa: O(n^2). Złożoność pamięciowa: O(1).
*/


int trojki(int t[], int n) {
	int wynik = 0;
	for (int ia = 0; ia < n; ia++) {
		int ic = ia+1;
		for (int ib = ia+1; ib < n; ib++) {
			ic = max(ic, ib);
			while (ic+1 < n and t[ic+1] < t[ia] + t[ib]) {
				ic++;
			}
			wynik += ic - ib;
		}
	}
	return wynik;
}



/************************** TESTY *********************************************/



void test(bool warunek) {
	if (warunek) {
		cout << "OK\n";
	}
	else {
		cout << "ERR\n";
	}
}


int main() {
	int t1[] = {3, 4, 6, 7, 9, 13};
	test(trojki(t1, 6) == 9);
	int t2[] = {1, 3, 6, 10};
	test(trojki(t2, 4) == 0);
	int t3[] = {2, 3, 5, 8, 11, 14, 16, 20};
	test(trojki(t3, 8) == 14);
	int t4[] = {1};
	test(trojki(t4, 1) == 0);
	return 0;
}
