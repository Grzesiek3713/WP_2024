//WP*, zadanie Krążki (XIII OI)
//Treść zadania i testy na platformie Szkopuł:
//https://szkopul.edu.pl/problemset/problem/fYXVXOreVxlXTRoHZJXyXF2l/site/?key=statement
//Autor: Grzegorz Pierczyński

/*
Rozwiązanie:
	* Przycinamy rurkę: jeśli po odcinku o szerokości x następuje odcinek o
		szerokości y > x, , to fakt że jest on szerszy nie ma znaczenia; równie
		dobrze możemy przyjąć że też ma szerokość x.
	* Następnie idziemy po rurce od dołu. Dzięki powyższemu przycięciu mamy 
		pewność że jeśli dany odcinek jest za wąski dla aktualnie rozważanego 
		krążka, to nigdy nic tam nie dotrze. Z tego powodu wystarczy że po rurce
		przejdziemy tylko raz.

Złożoność czasowa i pamięciowa: O(n+m).
*/


#include <iostream>
using namespace std;

#define N 1000005
#define INF 1000000005

int n, m, kra, r[N];

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    
    r[0] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        r[i] = min(r[i], r[i - 1]);
    }
    
    while (m--) {
        cin >> kra;
        while (n >= 0 and r[n] < kra) {
            n--;
        }
        n--;
    }
    
    cout << max(n + 1, 0) << "\n";
    
    return 0;
}
