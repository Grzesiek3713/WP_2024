//WP* ćwiczenia 4, zadanie "Łańcuch"
//Autor: Grzegorz Pierczyński

#include <iostream>
using namespace std;


/*
Mamy n-elementowy łańcuch którego część ogniw jest nawleczona na pręt. Zasady 
zakładania i zdejmowania ogniw są następujące:
	* w jednym ruchu możemy zawsze zdjąć tylko jedno ogniwo,
	* ogniwo nr 0 możemy zdjąć lub założyć zawsze,
	* dla i = 1, 2, ..., n-1, ogniwo nr i możemy zdjąć lub założyć tylko wtedy 
		gdy ogniwa nr 0, 1, ..., i-2 są zdjęte, a ogniwo nr i-1 jest założone.
Łańcuch jest dany w postaci tablicy binarnej (1 oznacza że ogniwo jest założone,
0 że zdjęte). Zwrócić minimalną liczbę ruchów prowadzącą do zdjęcia całego
łańcucha.

Załóżmy że wynik zmieści się w typie int (oryginalnie zadanie to pojawiło się na 
VIII OI bez tego założenia, co dodatkowo wymagało zaimplementowania arytmetyki 
dużych liczb; tę część zadania tu pomijamy).

Rozwiązanie:
	* łańcuch postaci 00..01 można zdjąć w 2^n-1 krokach. Dowód indukcyjny: 
		dla n=1 jest to prawda, przyjmijmy więc że jest to prawda dla pewnego n.
		Wtedy dla łańcucha długości n+1 musimy najpierw dojść do postaci
		00..011 (co zajmuje 2^n-1 kroków z założenia indukcyjnego oraz symetrii
		ruchów), następnie zdjąć (n+1)-sze ogniwo, następnie jeszcze raz 
		skorzystać z założenia indukcyjnego. Łącznie mamy 2^(n+1)-1 kroków, co 
		kończy dowód.
	* Uogólnijmy zadanie: przypuśćmy że chcemy sprowadzić nasz łańcuch do 
		postaci 0..0x, gdzie x = 0 lub 1.
	* Rozwiązujemy zadanie rekurencyjnie. Jeśli n-te ogniwo łańcucha jest równe
		x, to odcinamy je i zwracamy wynik dla mniejszego łańcucha i x==0.
		Jeśli n-te ogniwo łańcucha jest różne od x, to odcinamy je i zwracamy 
		wynik dla mniejszego łańcucha i x==1, powiększony dodatkowo o 2^(n-1).

Złożoność czasowa: O(n). Złożoność pamięciowa: O(n) (rekurencja). 

Ten sam algorytm można by też zapisać iteracyjnie, zapisując wyniki dla
mniejszych długości łańcucha w tablicy.
 
*/

int power2(int k) {
	return 1 << k;
}

int lan_rek(int t[], int n, int x) {
	if (n == 1)
		return t[0] != x; 
	if (t[n-1] == x)
		return lan_rek(t, n-1, 0);
	else
		return lan_rek(t, n-1, 1) + power2(n-1);
	
}

int lan(int t[], int n) {
	return lan_rek(t, n, 0);
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
	int t1[] = {0, 1, 1, 0};
	test(lan(t1, 4) == 4);
	int t2[] = {0, 1, 1, 0, 0, 1, 1, 1, 0, 1};
	test(lan(t2, 10) == 836);
	int t3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	test(lan(t3, 10) == 0);
	int t4[] = {1, 1, 1, 1};
	test(lan(t4, 4) == 10);
	return 0;
}
