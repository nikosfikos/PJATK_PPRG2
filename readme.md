# Polecenie
Instrukcje
Dane zbierane przez aplikację Michała są zaszumione i trudne do interpretacji. Użytkownicy mają wahania wagi, ukryte nawyki (np. podjadanie w weekendy) i często wpadają w efekt Yo-Yo.
Twoim zadaniem jest stworzenie silnika analitycznego, który:
Wyczyści dane (średnia ruchoma).
Wykryje trendy (Yo-Yo, najdłuższa seria spadkowa).
Znajdzie słabe punkty (najtrudniejszy dzień).
Zweryfikuje sam siebie (wbudowane testy).

Baza Danych (Zmienne Globalne)

Zadeklaruj poniższe tablice jako globalne (przed main). Funkcje będą na nich operować lub przyjmować je jako argumenty do testów.
const int TYGODNIE = 10;
const int DNI = 7;

// Historia wagi (kg)
double historiaWagi[TYGODNIE] = {82.5, 81.2, 81.8, 80.5, 80.1, 79.8, 80.2, 79.5, 78.9, 78.5};

// Dziennik kalorii: [Tydzien][DzienTygodnia]
int dziennikKalorii[4][DNI] = {
{2100, 2100, 2100, 2000, 2000, 2500, 2800},
// ... (dopisz brakujące tygodnie)
};

// Mapa nazw
string nazwyDni[7] = {"Pon", "Wt", "Sr", "Czw", "Pt", "Sob", "Nd"};

## 1. Autoweryfikacja (6 pkt)

Stwórz funkcję void uruchomTesty(). To w niej sprawdzisz, czy Twoje algorytmy działają poprawnie, zanim uruchomisz je na danych klienta.
Stwórz wewnątrz tej funkcji lokalne tablice testowe (np. double testWagi[] = {100, 99, 98, 100};).
Wywołaj na nich swoje funkcje analityczne.
Jeśli funkcja zwróci zły wynik (np. passę 10 zamiast 3), wypisz BŁĄD. Jeśli dobry - OK.

## 2. Analiza Danych (Tablice 1D, 7 pkt)

### 2.1 Wygładzanie Danych (2 pkt)

Surowe dane skaczą. Napisz funkcję, która wypełnia nową tablicę średnią ruchomą:
nowa_waga[i] = (stara[i-1] + stara[i] + stara[i+1]) / 3.0
### 2.2 Trendy: Yo-Yo i Streak (5 pkt)
Stwórz funkcje analizujące wygładzoną tablicę:

Efekt Yo-Yo: 
Policz ile razy wystąpił schemat: 
Spadek (tydz 1->2) a potem Wzrost (tydz 2->3).

Najdłuższa Passa (Streak): 
Znajdź najdłuższy nieprzerwany ciąg tygodni, w których waga spadała. 

Musisz użyć pętli i pamiętać o resetowaniu licznika serii.

## 3. Metoda 2: "Najtrudniejszy Dzień" (6 pkt)

Analiza 2D w pionie + Mapowanie.
Zadanie: Znajdź dzień tygodnia (np. "Sobota"), 
w którym średnie spożycie kalorii ze wszystkich tygodni jest najwyższe.
Komplikacja: Student musi zsumować kolumny macierzy kalorie, 
znaleźć indeks maksimum (np. 5), a następnie użyć tego indeksu,
by wyciągnąć nazwę dnia z tablicy dniTygodnia.
To uczy łączenia danych z dwóch różnych tablic.

## 4. Inżynieria Danych (11 pkt)

### 4.1 Normalizacja Makro (5 pkt)

Napisz funkcję skalujPosilek(double makro[3], double limit).
Jeśli suma kalorii (B*4 + T*9 + W*4) przekracza limit, 
proporcjonalnie zmniejsz ilość białka, tłuszczu i węglowodanów, aby idealnie trafić w limit.

### 4.2 Metoda 3: Generowanie Raportu (6 pkt)

Transformacja tablic.
Zadanie: Stwórz funkcję, która nie wyświetla danych,
ale wypełnia przekazaną jej pustą tablicę wyniki[3]
trzema największymi deficytami kalorycznymi 
(wymaga przeszukania danych i znalezienia Top 3 wartości).

int main() {
uruchomTesty(); // Najpierw testy!

    // Potem analiza danych globalnych...
    double wagaCzysta[TYGODNIE];
    wygladzDane(historiaWagi, wagaCzysta);
    
    ...
}
 
