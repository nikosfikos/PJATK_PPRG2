#include <iostream>
using namespace std;

const int WEEKS = 10;
const int DAYS = 7;
// Historia wagi (kg)
double weightHistory[WEEKS] = {82.5, 81.2, 81.8, 80.5, 80.1, 79.8, 80.2, 79.5, 78.9, 78.5};

// Dziennik kalorii: [Tydzien][DzienTygodnia]
int calorieJournal[WEEKS][DAYS]= {
    //calculated via MS Excel : =2000 + RANDBETWEEN(-100; 150) - ($A2-1)*10
    { 2100, 2100, 2100, 2000, 2000, 2500, 2800 },
    { 2086, 2062, 1951, 1899, 2071, 2371, 2571 },
    { 1909, 1897, 2043, 1903, 1921, 2420, 2746 },
    { 2017, 2032, 2044, 2110, 1941, 2489, 2693 },
    { 2013, 1945, 2023, 1899, 1907, 2469, 2852 },
    { 1939, 1865, 2020, 1999, 1961, 2376, 2785 },
    { 1996, 1901, 1997, 1952, 2027, 2241, 2656 },
    { 1875, 2056, 2050, 1911, 1860, 2345, 2779 },
    { 1876, 1824, 1964, 1969, 1888, 2224, 2589 },
    { 1829, 1831, 1874, 1968, 1840, 2294, 2732 }
};
string nazwyDni[7] = {"Pon", "Wt", "Sr", "Czw", "Pt", "Sob", "Nd"};

// .md 1
void runTests() {
}
// .md 2.1 Moving average
double* dataSmoothing(double source[], int dataLength) {
    double* target = new double[dataLength];
    for (int i=0; i<dataLength; i++) {
        if (i==0 || i==dataLength-1) {
            target[i] = source[i];
        } else {
            target[i] = (source[i-1] + source[i] + source[i+1]) / 3.0;
        }
    }
    return target;
}


// .md 2.2 Weight trends
int yoyoEffect(double weightData[]) {
    weightData = dataSmoothing(weightData, WEEKS);
    int counter = 0;
    for (int i=0; i<WEEKS; i++) {
        if (i==0 || i==WEEKS-1) {
            continue;
        } if (weightData[i-1] > weightData[i] && weightData[i] < weightData[i+1]) {
                counter++;
        }
    }
    delete[] weightData;
    return counter;
}

int weightLossStreak(double weightData[]) {
    int sequence = 0;
    int max_sequence = 0;
    int endOfStreak = 0;
    int startOfStreak = 0;
    for (int i = 0; i < WEEKS; i++) {
        if (weightData[i] < weightData[i-1]) {
            sequence++;
        } else if (sequence > max_sequence) {
            max_sequence = sequence;
            endOfStreak = i;
            startOfStreak = endOfStreak-sequence;
            sequence = 0;
        }
    }
    // sprawdzenie wyniku wyswietlanie tygodnia
    // for (int i = startOfStreak; i < endOfStreak; i++) {
    //     cout <<"tydzien: "<< i << " waga: " << weightData[i]<< endl;
    // }
    return max_sequence;
}


// .md 3
void mostDifficultDay(int calorieData[WEEKS][DAYS], string nazwaDni[] ) {
    //indeks tablicy nazwadni
    int counter = 0;
    double* calorieJournalAvg = new double[DAYS];

    while (counter < DAYS) {
        for (int i=0; i < WEEKS; i++){
            for (int j = 0; j < DAYS; j++) {
                if (j==counter) {
                    calorieJournalAvg[counter] += calorieData[i][j];
                }
            }
        }
        calorieJournalAvg[counter] = static_cast<double>(calorieJournalAvg[counter]) / static_cast<double>(WEEKS) ;
        counter++;
    }

    double greatestAvg = calorieJournalAvg[0];
    string result = nazwaDni[0];

    for (int i = 0; i < DAYS; i++) {
        if (calorieJournalAvg[i] > greatestAvg ) {
            greatestAvg = calorieJournalAvg[i];
            result = nazwaDni[i];
        }
    }

    cout << "najciezszy dzien: "<< result << " Srednia liczba kalorii "<<greatestAvg<< endl;
    delete[] calorieJournalAvg;
}


// .md4


int main() {

    // 2.1 TESTS
    // int dataLength = 5;
    // cout<<"Podaj liczby: "<<endl;
    // double* example_1 = new double[dataLength];
    // for (int i=0; i<5; i++) {
    //     cin>>example_1[i];
    // }
    // double* example_2 = new double[dataLength];
    // dataSmoothing(example_1, example_2, dataLength);
    // for (int i=0; i<5; i++) {
    //     cout<<example_2[i]<<" ";
    // }

    //sprawdzanie yoyo
    // cout<<yoyoEffect(weightHistory);

    //sprawdzanie streak
    // cout<<"Najdluzsza passa: "<< weightLossStreak(weightHistory);

    //sprawdzanie najtrudniejszy dzien
    mostDifficultDay(calorieJournal,nazwyDni);




    // wyczyścić pamięć!
}