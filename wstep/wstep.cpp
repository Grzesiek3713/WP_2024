//WP* ćwiczenia 1
//Autor: Grzegorz Pierczyński

#include<iostream>
#include<vector>
using namespace std;

struct pkt {
	int x, y;
};

/*
Zad1: Czy 2 dane prostokąty P i Q o bokach równoległych do osi układu 
współrzędnych się przecinają? Załóżmy że każdy prostokąt jest dany 
poprzez współrzędne dwóch wierzchołków leżących po przekątnej. 

Rozwiązanie:
	* rzutujemy prostokąty na oś OX i sprawdzamy czy powstałe w ten sposób
		przedziały się przecinają
	* tak samo dla osi OY
*/

typedef pair<int, int> przedzial;

typedef pair<pkt, pkt> prostokat;


bool przedzialy_przeciecie(przedzial p, przedzial q) {
	return max(p.first, q.first) <= min(p.second, q.second);
}

bool prostokaty_przeciecie(prostokat p, prostokat q) {
	przedzial px = {min(p.first.x, p.second.x), max(p.first.x, p.second.x)}, 
		py = {min(p.first.y, p.second.y), max(p.first.y, p.second.y)},
		qx = {min(q.first.x, q.second.x), max(q.first.x, q.second.x)}, 
		qy = {min(q.first.y, q.second.y), max(q.first.y, q.second.y)};
	return przedzialy_przeciecie(px, qx) and  przedzialy_przeciecie(py, qy);
}

/*
Zad2: Czy 2 dane odcinki P i Q się przecinają?
Załóżmy że odcinek jest dany jako para punktów.

Rozwiązanie (jedno z kilku omawianych na zajęciach):
	* dla każdego odcinka chcemy wiedzieć czy obydwa końce drugiego odcinka 
		leżą "po przeciwnych stronach" prostej będącej przedłużeniem odcinka.
	* aby wyliczyć orientację punktu względem odcinka, porównujemy ze sobą 
		współczynniki nachylenia odpowiednich prostych (lub równoważnie:
		wyliczamy iloczyn wektorowy)
	* szczególny przypadek: oba odcinki są współliniowe. Wtedy sprawdzenie 
		czy się przecinają jest takie samo jak dla prostokątów.
*/

typedef pair<pkt, pkt> odcinek;


int orientacja(pkt a, pkt b, pkt c) {
	return (c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x);
}

bool przeciwne_strony(odcinek o, pkt p1, pkt p2) {
	return orientacja(o.first, o.second, p1) * orientacja(o.first, o.second, p2) <= 0;
}

bool odcinki_wspolliniowe(odcinek p, odcinek q) {
	return orientacja(p.first, p.second, q.first) == 0 
		and orientacja(p.first, p.second, q.second) == 0;
}

bool odcinki_przeciecie(odcinek p, odcinek q) {
	if (odcinki_wspolliniowe(p, q)) {
		prostokat p_ = {p.first, p.second};
		prostokat q_ = {q.first, q.second};
		return prostokaty_przeciecie(p_, q_);
	}
	return przeciwne_strony(p, q.first, q.second) and przeciwne_strony(q, p.first, p.second);
}

/*
Zad4: Mamy dany wielokąt (niekoniecznie wypukły, ale bez samoprzecięć) i punkt. 
Czy punkt leży w wielokącie? 

Rozwiązanie:
	* prowadzimy półprostą "na prawo" od naszego punktu równoległą do osi OX
	* dla każdej krawędzi wielokąta, sprawdzamy czy przecina się z naszą półprostą
	* jeśli mamy nieparzyście wiele przecięć, to nasz punkt jest wewnątrz, wpp. 
		jest na zewnątrz.
Żeby uniknąć rozważania skomplikowanych przypadków brzegowych (wierzchołek 
wielokąta na półprostej, krawędzie pokrywające się z półprostą) zakładamy że 
nasza półprosta jest lekko odchylona w górę względem osi OX o nieskończenie 
mały kąt. Oznacza to że poza samym punktem początkowym, nasza półprosta jest 
"tuż nad" prostą równoległą do OX.
*/

typedef vector<pkt> wielokat; //wierzchołki w kolejności wg. ruchu wskazówek zegara


bool punkt_na_odcinku(odcinek o, pkt p) {
	return odcinki_przeciecie(o, odcinek(p, p));
}

bool punkt_w_wielokacie(wielokat w, pkt p) {
	int ile_przeciec = 0;
	for (int i = 0; i < w.size(); i++) {
		odcinek k = odcinek(w[i], w[(i+1)%w.size()]);
		if (punkt_na_odcinku(k, p)) {
			return true;
		}
		if (min(k.first.y, k.second.y) <= p.y and p.y < max(k.first.y, k.second.y)
				and orientacja(k.first, k.second, p)*(k.first.y - k.second.y) <= 0) {
			ile_przeciec++;
		}
	}
	return ile_przeciec % 2 == 1;
}

/*
Zad3: Czy 2 dane równoległoboki się przecinają?

Rozwiązanie:
	* dla każdej pary krawędzi z obydwu równoległoboków sprawdzamy czy się przecinają
	* jeśli nic się nie przecina, to albo są rozłączne albo jeden jest w całości zawarty w drugim
	* więc dla pewności sprawdzamy czy wierzchołek jednego równoległoboku nie leży w drugim

To że rozważamy akurat równoległoboki, potencjalnie upraszcza nam wykonanie ostatniego kroku
(można np. wyliczyć orientację punktu względem wszystkich krawędzi). Ponieważ jednak zrobiliśmy 
zadanie 4 i ostatni punkt mamy "za darmo", to możemy to zadanie zrobić dla dowolnych wielokątów.
*/

bool wielokaty_przeciecie(wielokat w1, wielokat w2) {
	for (int i = 1; i < w1.size(); i++) {
		odcinek k1 = odcinek(w1[i-1], w1[i]);
		for (int j = 1; j < w2.size(); j++) {
			odcinek k2 = odcinek(w2[j-1], w2[j]);
			if (odcinki_przeciecie(k1, k2)) {
				return true;
			}
		}
	}
	return punkt_w_wielokacie(w1, w2[0]) or punkt_w_wielokacie(w2, w1[0]);
}



/*** TESTY ***/

void test(bool warunek) {
	if (warunek) {
		cout << "OK\n";
	}
	else {
		cout << "ERR\n";
	}
}


int main() {
	
	cout << "TESTY ZAD 1\n";
	test(prostokaty_przeciecie({{0, 0}, {4, 5}}, {{3, 1}, {6, 6}}));
	test(!prostokaty_przeciecie({{0, 0}, {4, 5}}, {{4, 6}, {6, 6}}));
	
	cout << "TESTY ZAD 2\n";
	test(odcinki_przeciecie({{0, 0}, {4, 4}}, {{2, 3}, {3, 1}}));
	test(odcinki_przeciecie({{0, 0}, {4, 4}}, {{2, 0}, {2, 4}}));
	test(!odcinki_przeciecie({{0, 0}, {0, 4}}, {{2, 0}, {2, 4}}));
	test(odcinki_przeciecie({{0, 0}, {1, 1}}, {{1, 1}, {2, 0}}));
	test(!odcinki_przeciecie({{0, 0}, {1, 1}}, {{2, 2}, {3, 3}}));
	test(odcinki_przeciecie({{0, 0}, {2, 2}}, {{1, 1}, {3, 3}}));
	
	cout << "TESTY ZAD 3\n";
	test(wielokaty_przeciecie({{0, 0}, {2, 3}, {5, 3}, {3, 0}}, {{5, 3}, {5, 4}, {6, 4}, {6, 3}}));
	test(wielokaty_przeciecie({{0, 0}, {2, 3}, {5, 3}, {3, 0}}, {{2, 1}, {2, 2}, {3, 2}, {3, 1}}));
	test(!wielokaty_przeciecie({{0, 0}, {2, 3}, {5, 3}, {3, 0}}, {{4, 0}, {4, 1}, {5, 1}, {5, 0}}));
	
	cout << "TESTY ZAD 4\n";
	test(punkt_w_wielokacie({{0, 4}, {3, 2}, {2, 5}, {4, 3}, {2, 0}, {2, 1}}, {1, 3}));
	test(!punkt_w_wielokacie({{0, 4}, {3, 2}, {2, 5}, {4, 3}, {2, 0}, {2, 1}}, {1, 2}));
	
	return 0;
}