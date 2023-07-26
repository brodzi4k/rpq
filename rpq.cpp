#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



struct Zadanie
{
    int r; /* Czas Przygotowania */
    int p; /* Czas wykonanania */
    int q; /* Czas stygniecia */
};

std::ostream& operator<<(std::ostream& os, const Zadanie& zad)
{
    os << zad.r << " "<< zad.p << " "<< zad.q;
    return os;
}


std::ostream& operator<<(std::ostream& os, const vector<Zadanie>& lst) {
    auto it = lst.begin();
    if (it != lst.end()) {
        os << *it;
        ++it;
    }
    for (; it != lst.end(); ++it) {
        os << "\n" << *it;
    }
    return os;
}


/* Sortowanie zadania po czasie stygniecia */
bool porownaj_q(const Zadanie& a, const Zadanie& b)
{
    return a.q < b.q;
}

/* Sortowanie zadania po czasie przygotowania */
bool porownaj_r(const Zadanie& a, const Zadanie& b)
{
    return a.r < b.r;
}

/* Metoda Schrage z podziałem na listy Gotowe i Niegotowe */
int schrage(vector<Zadanie>& zadania)
{
    /* posortowanie zadań po czasie przygotowania */
    sort(zadania.begin(), zadania.end(), porownaj_r);

    /* utworzenie listy Gotowe i NieGotowe */
    vector<Zadanie> Gotowe;
    vector<Zadanie> Niegotowe = zadania;

    /*pomocniczy wektor do wyswietlania*/
    vector<Zadanie> pi;

    int t = 0;
    int Cmax = 0;

    /* Petla sprawdzajaca czy sa zadania na liscie Gotowe lub NieGotowe */
    while (!Gotowe.empty() || !Niegotowe.empty())
    {
        while (!Niegotowe.empty() && Niegotowe.front().r <= t)
        {
            /* Przesuniecie zadania z listy NieGotowe do listy Gotowe */
            Gotowe.push_back(Niegotowe.front());

            /* Usuniecie zadania z listy NieGotowe */
            Niegotowe.erase(Niegotowe.begin());

            /* Aktualizacja Cmax */
            Cmax = max(Cmax, t + Gotowe.back().q);
        }
        /* Jesli lista Gotowe jest pusta to czas ustawiamy na czas przygotowania pierwszego zadania z listy NieGotowe */
        if (Gotowe.empty())
        {
            t = Niegotowe.front().r;
        }
        else
        {
            /* Wybór zadania z listy Gotowe o największym czasie stygniecia */
            auto maxq = max_element(Gotowe.begin(), Gotowe.end(), porownaj_q);

            /* Dodanie wybranego zadania do wektora pi */
            pi.push_back(*maxq);

            /* Wykonanie zadania */
            t += maxq->p;

            /* Usuwanie zadania z listy Gotowe */
            Gotowe.erase(maxq);

            /* Aktualizacja Cmax */
            Cmax = max(Cmax, t + maxq->q);
        }
    }
    /*wyswietl kolejnosc*/
    cout<< pi <<endl;
    return Cmax;
}


int main()
{
    vector<Zadanie> zadania;
    vector<Zadanie> pi;
    int N,R[100], P[100], Q[100];
    int data_id;

    /*dane do wczytania pliku*/
    ifstream file("data.txt");
    std::string z = "data.";
    std::string s;
    ostringstream data;


    /*wybor parti danych z pliku*/
    cout << "podaj numer parti danych(1-4)" << endl;
    cin >> data_id;
    if(data_id > 4 || data_id < 1)
    {
        cerr << "Nieprawidlowy numer parti danych" << endl;
        return 1;
    }

    /*wczytanie danych*/
    else
    {
        data << data_id;
        z += data.str();
    }

    while (s != z)
    {
        file >> s;
    }

    file >> N;

    for(int i = 0; i < N; i++)
    {
        file >> R[i] >> P[i] >> Q[i];
        zadania.push_back({R[i], P[i], Q[i]});
    }
    file.close();

    int cmax = schrage(zadania);

    /*wyswietlenie liczby danych i koncowego wyniku cmax*/
    cout<<endl;
    cout<< N <<endl;
    cout<< cmax <<endl;
    return 0;

}
