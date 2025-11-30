#include <iostream>
#include <cfloat>
#include <thread>
#include <chrono>
using namespace std;

constexpr int WEEKS = 10;
constexpr int DAYS = 7;
constexpr int KCAL_PROTEINS = 4;
constexpr int KCAL_CARBOHYDRATES = 9;
constexpr int KCAL_FATS = 4;

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



// .md 2.1 Moving average
double* dataSmoothing(double source[], int dataLength) {
    if (dataLength < 2) {
        return source;
    }
    double* target = new double[dataLength];
    for (int i=0; i<dataLength; i++) {
        // edge cases
        if (i==0 || i==dataLength-1) {
            target[i] = source[i];
        } else {
            target[i] = (source[i-1] + source[i] + source[i+1]) / 3.0;
        }
    }
    return target;
}


// .md 2.2 Weight trends
int yoyoEffect(double weightData[], int dataLength) {
    if (dataLength < 3) {
        return 0;
    }
    double* smoothWeightData = dataSmoothing(weightData, dataLength);
    int counter = 0;
    for (int i=0; i<dataLength; i++) {
        if (i==0 || i==dataLength-1) {
            continue;
        }
        if (smoothWeightData[i-1] > smoothWeightData[i]) {
            if (smoothWeightData[i+1] > smoothWeightData[i]) {
                counter++;
                }
            }
    }
    delete[] smoothWeightData;
    return counter;
}

int weightLossStreak(double weightData[], int dataLength) {
    if (dataLength < 2) {
        return 0;
    }
    int sequence = 0;
    int max_sequence = 0;
    int endOfStreak = 0;
    int startOfStreak = 0;
    for (int i = 1; i< dataLength; i++) {
        if (weightData[i] < weightData[i-1]) {
            sequence++;
        } else {
            if (sequence > max_sequence) {
                max_sequence = sequence;
            }
            endOfStreak = i;
            startOfStreak = endOfStreak-sequence;
            sequence = 0;
        }
    }
    if (sequence > max_sequence) {
        max_sequence = sequence;
    }
    return max_sequence;
}


// .md 3
void mostDifficultDay(int calorieData[WEEKS][DAYS], string nazwaDni[] ) {
    //indeks tablicy nazwadni
    double* calorieJournalAvg = new double[DAYS];

    for (int dzien = 0; dzien < DAYS; dzien++) {
        double sum = 0.0;
        for (int tydzien=0; tydzien < WEEKS; tydzien++){
                sum += calorieData[tydzien][dzien];
            }
        calorieJournalAvg[dzien] = sum / WEEKS;
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


// .md4.1

double skalujPosilek(double makro[3], double limit) {
    double caloriesSum = (makro[0]*KCAL_PROTEINS) + (makro[1]*KCAL_CARBOHYDRATES) + (makro[2]*KCAL_FATS);
    double rate = 1.0;
    if (caloriesSum > limit) {
        rate = (limit / caloriesSum);
    }
    for (int i = 0; i < 3; i++) {
        makro[i] = makro[i] * rate;
    }

    return rate;
}


// .md 4.2
void raportGenerator(double wyniki[3]) {
    wyniki[0] = DBL_MAX;
    wyniki[1] = DBL_MAX;
    wyniki[2] = DBL_MAX;
    // Linear search extended to 3 values, new value
        for (int i = 0; i < WEEKS; i++) {
            for (int j = 0; j < DAYS; j++) {
                if (calorieJournal[i][j] < wyniki[0]) {
                    wyniki[2] = wyniki[1];
                    wyniki[1] = wyniki[0];
                    wyniki[0] = calorieJournal[i][j];
                } else if (calorieJournal[i][j] < wyniki[1]){
                    wyniki[2] = wyniki[1];
                    wyniki[1] = calorieJournal[i][j];
                } else if (calorieJournal[i][j] < wyniki[2]) {
                    wyniki[2] = calorieJournal[i][j];
                }
            }
        }
}


// .md 1
void uruchomTesty() {
    cout<<"Running tests...\n";
    cout<<"["<<flush;
    double dataSmoothingSample[5] = {10,20,30,40,50};
    double* result = dataSmoothing(dataSmoothingSample,
        sizeof(dataSmoothingSample) / sizeof(double));
    for (int i = 1; i <= 3; i++) {
        cout<<'#' << flush;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    double yoyoEffectSample[5] = {100,90,95,90,85};

    for (int i = 1; i <= 3; i++) {
        cout<<'#' << flush;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    double weightLossStreakSample[5] = {100,99,98,97,101};
    for (int i = 1; i <= 4; i++) {
        cout<<'#' << flush;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    cout<<"]"<<endl<<flush;
    if (result[1] == 20) {
        cout<<"Data Smoothing STATUS: OK\n";
        this_thread::sleep_for(chrono::milliseconds(200));
    } else {
        cout<<"Data Smoothing STATUS: NOT OK\n";
    }
    if (yoyoEffect(yoyoEffectSample, sizeof(yoyoEffectSample) / sizeof(double)) == 1) {
        cout<<"YoYo effect STATUS: OK\n";
        this_thread::sleep_for(chrono::milliseconds(200));
    } else {
        cout<<"Yoy effect STATUS: NOT OK\n";
    }
    if (weightLossStreak(weightLossStreakSample,sizeof(weightLossStreakSample) / sizeof(double)) == 3 ) {
        cout<<"Weight Loss Streak STATUS: OK\n";
    } else {
        cout<<"Weight Loss Streak STATUS: NOT OK\n";
    }
    delete[] result;
}

void displayResults() {
    double makro[3] = {50, 30, 80};
    double wyniki[3] = {};
    double* smoothData = dataSmoothing(weightHistory, WEEKS);
    cout<<"2. Analyzing data..."<<endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout<<"2.1 New array filled with moving average: ";
    for (int i = 0; i < WEEKS; i++) {
        cout<<smoothData[i]<<" ";
    }
    cout<<"\n";
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "2.2 YoYo effect: " << yoyoEffect(weightHistory, sizeof(weightHistory) / sizeof(double)) <<
            " | 2.2 Weight loss streak: " <<
        weightLossStreak(weightHistory,sizeof(weightHistory) / sizeof(double)) <<endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    mostDifficultDay(calorieJournal, nazwyDni);
    this_thread::sleep_for(chrono::milliseconds(200));
    cout<<"4.1 Macro normalization: "<<skalujPosilek(makro,500);
    this_thread::sleep_for(chrono::milliseconds(200));
    cout<<"\n";
    cout<<"4.2 Top 3 values of greatest calorie deficit : ";
    raportGenerator(wyniki);
    for (double wynik : wyniki) {
        cout<<wynik<<" ";
    }
    delete[] smoothData;
}

int main() {
    uruchomTesty();
    displayResults();

    return 0;


}