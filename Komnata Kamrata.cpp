#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <string>
#include <windows.h>
#include <locale>

using namespace std;
struct statystyki_postaci {
    string imie = "Wojownik";
    int sila = 1;
    int hp = 1;
    int zwinnosc = 1;
    string helm = "Brak";
    string zbroja = "Brak";
    string buty = "Brak";
    string bron = "Brak";
};

void start();
void tworzenie_postaci(statystyki_postaci& postac, string& klasa_postaci_napis);
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, double& punkty_postaci, int wybor_akcji);
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci);
int losowanie();
void opis_statystyk();
void przedmioty(statystyki_postaci& postac);
void liczenie_punktow_postaci(statystyki_postaci postac, int klasa_postaci, double& punkty_postaci);
void opis_liczenia_punktow(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci);
void ekwipunek(statystyki_postaci postac);
void rysuj_drzwi(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci, int& wybor_drzwi);
void ulecz(statystyki_postaci postac);
void plus_sila(statystyki_postaci postac);
void plus_zwinnosc(statystyki_postaci postac);

const int losowych_zdarzen = 10;
const int max_statystyki = 30;
int punkty_ulepszen = 1;
int klasa_postaci = 0; //1 dla wojownika, 2 dla Ninja
int wybor_drzwi;
double punkty_postaci = 0;
string klasa_postaci_napis = "Bezimienny";

int main() {
    setlocale(LC_ALL, "pl_PL");
    srand(time(0));
    statystyki_postaci postac;
    int wybor_akcji{};
    //start();
    //tworzenie_postaci(postac, klasa_postaci_napis);
    liczenie_punktow_postaci(postac, klasa_postaci, punkty_postaci); //trzeba dodawac zawsze po zalozeniu przedmiotu!
    menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);

    return 0;
}

void start() {
    cout << ".................................................................\n";
    cout << ".................................................................\n";
    cout << ".##...##..######..###....###.###....##..#####..########..#####...\n";
    cout << ".##..##..##....##.####..####.####...##.##...##....##....##...##..\n";
    cout << ".#####...##....##.##.####.##.##.##..##.#######....##....#######..\n";
    cout << ".##..##..##....##.##..##..##.##..##.##.##...##....##....##...##..\n";
    cout << ".##...##..######..##......##.##...###..##...##....##....##...##..\n";
    cout << ".................................................................\n";
    cout << ".................................................................\n";
    cout << "...##...##..#####..###....###.######...#####..########..#####....\n";
    cout << "...##..##..##...##.####..####.##...##.##...##....##....##...##...\n";
    cout << "...#####...#######.##.####.##.######..#######....##....#######...\n";
    cout << "...##..##..##...##.##..##..##.##...##.##...##....##....##...##...\n";
    cout << "...##...##.##...##.##......##.##...##.##...##....##....##...##...\n";
    cout << ".................................................................\n";
    cout << ".................................................................\n";
    cout << "\n\n\tWciśnij dowolny klawisz by rozpocząc... \n";
    _getch();

    system("cls");
}
void tworzenie_postaci(statystyki_postaci& postac, string& klasa_postaci_napis) {
    cout << "\nPodaj imie postaci: ";
    cin >> postac.imie;
    do {
        cout << "\nWybierz klasę: ";
        cout << "\n1. Wojownik - Silny i twardy ale wolny";
        cout << "\n2. Ninja - Szybki i silny ale miękki";
        cout << "\nWybór : ";
        cin >> klasa_postaci;
    } while (klasa_postaci != 1 && klasa_postaci != 2);
    if (klasa_postaci == 1) {
        //wojownik
        postac.hp = 10;
        postac.sila = 5;
        postac.zwinnosc = 2;
        klasa_postaci_napis = "Wojownik";
    }
    if (klasa_postaci == 2) {
        //ninja
        postac.hp = 6;
        postac.sila = 7;
        postac.zwinnosc = 4;
        klasa_postaci_napis = "Ninja";
    }
    system("cls");
}
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, double& punkty_postaci, int wybor_akcji) {
    int wybor_statystyki;
    system("cls");
    cout << "\n\t1.Siła\t\t2.Życie\t\t3.Zręczność";
    cout << "\n\t     Masz " << punkty_ulepszen << " punkt(y) do przydzielenia!";
    cout << "\n\n( By wrócić do menu, wybierz 0 )";
    cout << "\nWybierz numer statystyki by przydzielić : ";
    cin >> wybor_statystyki;
    switch (wybor_statystyki) {
    case 1: {
        postac.sila += punkty_ulepszen;
        cout << "\nPomyslnie zwiększono siłe!\n\tAktualnie : " << postac.sila;
        punkty_ulepszen -= 1;
        break;
    }
    case 2: {
        postac.hp += punkty_ulepszen;
        cout << "\nPomyslnie zwiększono życie!\n\tAktualnie : " << postac.hp;
        punkty_ulepszen -= 1;
        break;
    }
    case 3: {
        postac.zwinnosc += punkty_ulepszen;
        cout << "\nPomyślnie zwiększono zwinność!\n\tAktualnie : " << postac.zwinnosc;
        punkty_ulepszen -= 1;
        break;
    }
    case 0: {
        break;
    }
    }
    liczenie_punktow_postaci(postac, klasa_postaci, punkty_postaci); //aktualizacja punktow po dodaniu punktow
    system("cls");
}
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci) {
    do {
        cout << "\n  * ======================================================= *";
        cout << "\n  I                  # Komnata Kamrata #                    I";
        cout << "\n  I                                                         I";
        cout << "\n  I\tSila: " << postac.sila << "\t\tHP: " << postac.hp << "\t\tZrecznosc: " << postac.zwinnosc << "        I";
        cout << "\n  I                                                         I";
        cout << "\n                      " << klasa_postaci_napis << " " << postac.imie;
        cout << "\n                     " << "Punkty postaci: " << punkty_postaci;
        cout << "\n  * ======================================================= *";
        cout << "\n\n   Co chcesz zrobić : \n";
        cout << "\n   1. Rusz na PRZYGODE ! (nie dziala jeszcze) ";
        cout << "\n   2. Zwieksz statystyki";
        cout << "\n   3. Zobacz ekwipunek";
        cout << "\n   4. O grze";
        cout << "\n   0. Koniec programu";
        cout << "\n   \tWybór: ";
        cin >> wybor_akcji;

        switch (wybor_akcji) {
        case 1: {
            system("cls");
            rysuj_drzwi(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci, wybor_drzwi);
            break;
        }
        case 2: {
            postac_upgrade(postac, klasa_postaci, punkty_postaci, wybor_akcji);
            break;
        }
        case 3: {
            system("cls");
            ekwipunek(postac);
            menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
            break;
        }
        case 4: {
            system("cls");
            cout << "\n  * ======================================================= *";
            cout << "\n  I                  # Komnata Kamrata #                    I";
            cout << "\n  I                                                         I";
            cout << "\n  I\tSiła: " << postac.sila << "\t\tHP: " << postac.hp << "\t\tZreczność: " << postac.zwinnosc << "        I";
            cout << "\n  I                                                         I";
            cout << "\n                       " << klasa_postaci_napis << " " << postac.imie;
            cout << "\n                     " << "Punkty postaci: " << punkty_postaci;
            cout << "\n  * ======================================================= *";
            cout << "\n\n   Co chcesz zrobić : \n";
            cout << "\n   1. Opis statystyk";
            cout << "\n   2. Opis liczenia punktów";
            cout << "\n   3. O co chodzi w grze?";
            cout << "\n   0. Powrót";
            cout << "\n\tWybór : ";
            int w = 0;
            cin >> w;
            switch (w) {
            case 1: {
                opis_statystyk();
                menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
                break;
            }
            case 2: {
                opis_liczenia_punktow(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
                break;
            }
            case 3: {
                system("cls");
                cout << "Opis gry Opis gry Opis gry\n";
                cout << "Opis gry Opis gry Opis gry\n";
                cout << "Opis gry Opis gry Opis gry\n";
                cout << "Opis gry Opis gry Opis gry\n";
                cout << "Opis gry Opis gry Opis gry\n";
                cout << "Opis gry Opis gry Opis gry\n";

                break;
            }
            case 0: {
                system("cls");
                menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
            }
            }
        }
        case 0: {
            break;
        }
        }

    } while (wybor_akcji != 0);
}
int losowanie() {
    int losowa_liczba = rand() % losowych_zdarzen + 1;
    return losowa_liczba;

}
void opis_statystyk() {
    system("cls");
    cout << "\n  * =========================================================================== *";
    cout << "\n  I          Każda statystyka (oprócz HP) przyczynia sie do obrażeń!            I";
    cout << "\n  I                                                                             I";
    cout << "\n  I             Siła to mnożnik obrażeń (obrażenia bazowe * siła)               I";
    cout << "\n  I  Zreczność zmniejsza otrzymywane obrażenia (za każdy punkt są 10% mniejsze) I";
    cout << "\n  I               ******  Kup przedmiot by odblokowac  ******                   I";
    cout << "\n  I               ******  Kup przedmiot by odblokowac  ******                   I";
    cout << "\n  * =========================================================================== *\n\n";
}
void liczenie_punktow_postaci(statystyki_postaci postac, int klasa_postaci, double& punkty_postaci) {
    if (klasa_postaci == 0) { //default
        punkty_postaci = 1 * postac.sila + 1 * postac.zwinnosc + 1 * postac.hp;
    }
    if (klasa_postaci == 1) { //wojownik
        punkty_postaci = 2 * postac.sila + 1 * postac.zwinnosc + 2 * postac.hp;
    }
    if (klasa_postaci == 2) { //ninja
        punkty_postaci = 1 * postac.sila + 3 * postac.zwinnosc + 1 * postac.hp;
    }
}
//zarys przedmiotow, jeszcze brak funkcjonalnosci
void przedmioty(statystyki_postaci& postac) {
    int a = 1; //tymczasowe
    if (a == 2) //helm1
    {
        postac.helm = "Ciężki hełm";
        postac.hp += 2;
        postac.zwinnosc -= 1;
    }
    if (a == 3) //helm2
    {
        postac.helm = "Lekki hełm";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 4) { //zbroja1
        postac.zbroja = "Ciężka zbroja";
        postac.hp += 3;
        postac.zwinnosc -= 1;
    }
    if (a == 5) { //zbroja2
        postac.zbroja = "Lekka zbroja";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 6) { //buty2
        postac.buty = "Ciężkie buty";
        postac.hp += 3;
        postac.zwinnosc -= 1;
    }
    if (a == 7) { //buty2
        postac.buty = "Lekkie buty";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 8) { //miecz 1
        postac.bron = "Mały miecz";
        postac.sila += 1;
        postac.zwinnosc += 1;
    }
    if (a == 9) { //miecz 2
        postac.bron = "Średni miecz";
        postac.sila += 2;
    }
    if (a == 10) { // miecz 3
        postac.bron = "Wielki miecz";
        postac.sila += 3;
        postac.zwinnosc -= 1;
    }
}
void opis_liczenia_punktow(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci) {
    system("cls");
    cout << "\n  * =========================================================================== *";
    cout << "\n  I                      Sposób liczenia punktow postaci                        I";
    cout << "\n  I                                                                             I";
    cout << "\n  I            Kazda klasa otrzymuje inne bonusy ze swoich statystyk            I";
    cout << "\n  I                                                                             I";
    cout << "\n  I                   Wojownik otrzymuje bonus za siłe i HP                     I";
    cout << "\n  I                     Ninja otrzymuje bonus za zręczność                      I";
    cout << "\n  * =========================================================================== *";
    menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
}
void ekwipunek(statystyki_postaci postac) {
    cout << "\nHełm : " << postac.helm;
    cout << "\nZbroja : " << postac.zbroja;
    cout << "\nButy : " << postac.buty;
    cout << "\nBroń : " << postac.bron;
}
void rysuj_drzwi(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci, int& wybor_drzwi) {
    cout << "\t#########    \t#########\n";
    cout << "\t#  ___  #    \t#  ___  #\n";
    cout << "\t#  |1|  #    \t#  |2|  #\n";
    cout << "\t#       #    \t#       #\n";
    cout << "\t#-      #    \t#-      #\n";
    cout << "\t#       #    \t#       #\n";
    cout << "\t#       #    \t#       #\n\n";
    cout << "( By wrócić do menu, wpisz 0 )\n";
    cout << "   Które drzwi wybierasz? :";
    cin >> wybor_drzwi;

    switch (wybor_drzwi) {
    case 1: {
        system("cls");
        cout << "\tWybrano drzwi numer 1";
        break;
    }
    case 2: {
        system("cls");
        cout << "\tWybrano drzwi numer 2";
        break;
    }
    case 0: {
        system("cls");
        menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
        break;
    }
    }
}
void ulecz(statystyki_postaci postac) {
    postac.hp = +5;
}
void plus_sila(statystyki_postaci postac) {
    postac.sila += 3;
}
void plus_zwinnosc(statystyki_postaci postac) {
    postac.zwinnosc += 3;
}
