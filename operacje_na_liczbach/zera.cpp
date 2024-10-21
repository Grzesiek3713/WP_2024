//WP* ćwiczenia 2, zadanie "Zera"
//Autor: Grzegorz Pierczyński

#include<iostream>
using namespace std;

/*
Zad: Dla danych dodatnich liczb naturalnych a i b obliczyć ile jest łącznie zer 
w zapisie dziesiętnym liczb a, a+1, ..., b.

Rozwiązanie:
	* sprowadzamy zadanie do obliczenia ile jest łącznie zer w zapisie
		dziesiętnym liczb 1, 2, ..., x dla danego x. Wtedy rozwiązanie
		naszego problemu to wynik(b) - wynik(a-1).
	* w dalszej części opisu niech n = liczba cyfr w zapisie liczby x, a
		c_i = i-ta cyfra wiodąca w zapisie x (numerując pozycje od 0).
	* najpierw rozwiązujemy problem analitycznie dla x == 99...9 z liczeniem
		również liczby 0 i wiodących zer. Wynik to n*10^(n-1). Dowód: liczba 
		wszystkich n-elementowych kombinacji 10 cyfr to 10^n, suma wszystkich 
		cyfr we wszystkich kombinacjach to n*10^n, a dokładnie 1/10 spośród tych 
		cyfr jest zerami.
	* następnie rozwiązujemy powyższy problem bez liczenia wiodących zer
		oraz liczby 0. Łączna liczba zer w liczbach które można zapisać przy 
		użyciu i = 2, ..., n cyfr to 9*(i-1)*10^(i-2). Dowód: pierwszą cyfrę 
		wybieramy na 9 sposobów, a potem korzystamy ze wzoru udowodnionego 
		wyżej. Zatem końcowy wynik to \sum_{i=2}^{n} 9*(i-1)*10^(i-2).
	* powyższy podproblem wywołany dla n-1 będzie częścią składową naszego 
		rozwiązania. Pozostaje jedynie dodać do niego liczbę zer w liczbach
		dokładnie n-cyfrowych mniejszych lub równych x. Liczymy to następująco:
		dla i = 0, 1, 2, ..., n-1, liczymy łączną liczbę zer w liczbach 
		n-cyfrowych które na pierwszych i-1 pozycjach mają 
		c_0, c_1, c_2, ..., c_{i-1} a potem cyfrę mniejszą niż c_i. Czyli: 
			- dla c_i == 0: 0,
			- dla i == 0: (c_0-1)*(n-1)*10^(n-2),
			- dla c_i > 0 oraz i > 0: 
				(c_i*d+1)*10^(n-i-1) + c_i*(n-i-1)*10^(n-i-2), 
				gdzie d to liczba zer wśród cyfr c_0, c_1, ..., c_{i-1}.
		Na koniec do wyniku dodajemy łączną liczbę zer w zapisie x.

Złożoność czasowa i pamięciowa: O(log(a)+log(b)).
*/




int zapis_dziesietny(int x, int t[]) {
	int n = 0;
	while (x > 0) {
		t[n] = x % 10;
		x /= 10;
		n++;
	}
	for (int i = 0; i < n-i-1; i++) {
		int tmp = t[i];
		t[i] = t[n-i-1];
		t[n-i-1] = tmp;
	}
	return n;
}


int zera_od_1(int x) {
	int c[10]; //x jest intem, więc w szczególności jest mniejszy niż 10^10
	int n = zapis_dziesietny(x, c);
	int wynik = 0, potega10[10];
	potega10[0] = 1;
	
	for (int i = 2; i < n; i++) {
		wynik += 9*(i-1)*potega10[i-2];
		potega10[i-1] = potega10[i-2]*10;
	}
	
	wynik += (c[0]-1)*(n-1)*potega10[n-2];
	
	int ile_zer_w_x = 0;
	for (int i = 1; i < n; i++) {
		if (c[i] != 0) {
			 wynik += (c[i]*ile_zer_w_x+1)*potega10[n-i-1] 
						+ c[i]*(n-i-1)*potega10[n-i-2]; 
		}
		else {
			ile_zer_w_x++;
		}
	}
	
	wynik += ile_zer_w_x;

	return wynik;
}

int zera(int a, int b) {
	if (a == 1)
		return zera_od_1(b);
	return zera_od_1(b) - zera_od_1(a-1);
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
	test(zera(1, 10) == 1);
	test(zera(1, 211) == 41);
	test(zera(10, 100) == 11);
	test(zera(129, 131) == 1);
	test(zera(130, 130) == 1);
	test(zera(131, 131) == 0);
	test(zera(11, 230) == 42);
	return 0;
}
