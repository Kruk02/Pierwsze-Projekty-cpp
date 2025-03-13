#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;
struct statystyki_postaci {
    string imie;
    int sila = 1;
    int hp = 1;
    int zwinnosc = 1;
    string helm;
    string zbroja;
    string buty;
    string bron;
};

void start();
void tworzenie_postaci(statystyki_postaci& postac, string& klasa_postaci_napis);
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, double& punkty_postaci);
void statystyki(statystyki_postaci postac);
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci);
int losowanie();
void opis_statystyk();
void przedmioty(statystyki_postaci& postac);
void liczenie_punktow_postaci(statystyki_postaci postac, int klasa_postaci, double &punkty_postaci);
void opis_liczenia_punktow(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci);

const int losowych_zdarzen = 10;
const int max_statystyki = 30;
int punkty_ulepszen = 1;
int klasa_postaci; //1 dla wojownika, 2 dla Ninja
double punkty_postaci = 0;
string klasa_postaci_napis;

int main() {
    srand(time(0));
    statystyki_postaci postac;
    int wybor_akcji{};
    start();
    tworzenie_postaci(postac, klasa_postaci_napis);
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
    cout << "\n\n\tWcisnij dowolny klawisz by rozpoczac... \n";
    _getch();

    system("cls");
}
void tworzenie_postaci(statystyki_postaci& postac, string& klasa_postaci_napis) {
    cout << "\nPodaj imie postaci: ";
    cin >> postac.imie;
    cout << "\nWybierz klase: ";
    cout << "\n1. Wojownik - Silny i twardy ale wolny";
    cout << "\n2. Ninja - Szybki i silny ale miekki";
    cout << "\nWybor : ";
    cin >> klasa_postaci;

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
// Naprawic zeby punkty_ulepszen zerowalo po przydzieleniu ich gdzies. 
// Mam 1 punkt do przydzielenia, przydzielam a liczbnik sie nie resetuje i mozna w nieskonczonosc przydzielac.
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, double& punkty_postaci) {
    int wybor_statystyki;
    cout << "\n\t1.Sila\t\t2.Zycie\t\t3.Zrecznosc";
    cout << "\n\t     Masz " << punkty_ulepszen << " punkt(y) do przydzielenia!\n\nWybierz numer statystyki by przydzielic : ";
    cin >> wybor_statystyki;
    switch (wybor_statystyki) {
    case 1: {
        postac.sila += punkty_ulepszen;
        cout << "\nPomyslnie zwiekszono sile!\n\tAktualnie : " << postac.sila;
        break;
    }
    case 2: {
        postac.hp += punkty_ulepszen;
        cout << "\nPomyslnie zwiekszono zycie!\n\tAktualnie : " << postac.hp;
        break;
    }
    case 3: {
        postac.zwinnosc += punkty_ulepszen;
        cout << "\nPomyslnie zwiekszono zwinnosc!\n\tAktualnie : " << postac.zwinnosc;
        break;
    }
    }
    liczenie_punktow_postaci(postac, klasa_postaci, punkty_postaci); //aktualizacja punktow po dodaniu punktow
    system("cls");
}
void statystyki(statystyki_postaci postac) {
    system("cls");
    cout << "\n     Aktualne statystyki :";
    cout << "\n\t1. Sila : " << postac.sila;
    cout << "\n\t2. Zycie : " << postac.hp;
    cout << "\n\t3. Zwinnosc : " << postac.zwinnosc;
}
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, double punkty_postaci) {
    do {
        cout << "\n  * ======================================================= *";
        cout << "\n  I                  # Komnata Kamrata #                    I";
        cout << "\n  I                                                         I";
        cout << "\n  I\tSila: " << postac.sila << "\t\tHP: " << postac.hp << "\t\tZrecznosc: " << postac.zwinnosc << "        I";
        cout << "\n  I                                                         I";
        cout << "\n                       " << klasa_postaci_napis << " " << postac.imie;
        cout << "\n                     " << "Punkty postaci: " << punkty_postaci;
        cout << "\n  * ======================================================= *";
        cout << "\n\n   Co chcesz zrobic : \n";
        cout << "\n   1. Rusz na PRZYGODE ! (nie dziala jeszcze) ";
        cout << "\n   2. Zwieksz statystyki ";
        cout << "\n   3. Opis statystyk";
        cout << "\n   4. Opis liczenia punktow";
        cout << "\n   0. Koniec programu";
        cout << "\n   \tWybor: ";
        cin >> wybor_akcji;

        switch (wybor_akcji) {
        case 1: {
            system("cls");
            for (int i = 1; i < 10; i++) {
                cout << "\nP r  Z yYyY  G  ooOo D   a";
                Sleep(150);
            }
            break;
        }
        case 2: {
            postac_upgrade(postac, klasa_postaci, punkty_postaci);
            break;
        }
        case 3: {
            opis_statystyk();
            break;
        }
        case 4: {
            opis_liczenia_punktow(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
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
    cout << "\n  I          Kazda statystyka (oprocz HP) przyczynia sie do obrazen!            I";
    cout << "\n  I                                                                             I";
    cout << "\n  I             Sila to mnoznik obrazen (obrazenia bazowe * sila)               I";
    cout << "\n  I  Zrecznosc zmniejsza otrzymywane obrazenia (za kazdy punkt sa 10% mniejsze) I";
    cout << "\n  I               ******  Kup przedmiot by odblokowac  ******                   I";
    cout << "\n  I               ******  Kup przedmiot by odblokowac  ******                   I";
    cout << "\n  * =========================================================================== *\n\n";
}
void liczenie_punktow_postaci(statystyki_postaci postac, int klasa_postaci, double& punkty_postaci) {
    if (klasa_postaci == 1) { //wojownik
        punkty_postaci = 2 * postac.sila + 1 * postac.zwinnosc + 2 * postac.hp;
    }
    if (klasa_postaci == 2) { //ninja
        punkty_postaci = 1 * postac.sila + 3 * postac.zwinnosc + 1 * postac.hp;
    }
}
void przedmioty(statystyki_postaci& postac) {
    int a = 1; //tymczasowe
    if (a == 2) //helm1
    {
        postac.helm = "Ciezki helm";
        postac.hp += 2;
        postac.zwinnosc -= 1;
    }
    if (a == 3) //helm2
    {
        postac.helm = "Lekki helm";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 4) { //zbroja1
        postac.zbroja = "Ciezka zbroja";
        postac.hp += 3;
        postac.zwinnosc -= 1;
    }
    if (a == 5) { //zbroja2
        postac.zbroja = "Lekka zbroja";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 6) { //buty2
        postac.buty = "Ciezkie buty";
        postac.hp += 3;
        postac.zwinnosc -= 1;
    }
    if (a == 7) { //buty2
        postac.buty = "Lekkie buty";
        postac.hp += 1;
        postac.zwinnosc += 1;
    }
    if (a == 8) { //miecz 1
        postac.bron = "Maly miecz";
        postac.sila += 1;
        postac.zwinnosc += 1;
    }
    if (a == 9) { //miecz 2
        postac.bron = "Sredni miecz";
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
    cout << "\n  I                      Sposob liczenia punktow postaci                        I";
    cout << "\n  I                                                                             I";
    cout << "\n  I            Kazda klasa otrzymuje inne bonusu ze swoich statystyk            I";
    cout << "\n  I                                                                             I";
    cout << "\n  I                   Wojownik otrzymuje bonus za sile i HP                     I";
    cout << "\n  I                     Ninja otrzymuje bonus za zrecznosc                      I";
    cout << "\n  * =========================================================================== *";
    menu(postac, wybor_akcji, klasa_postaci_napis, punkty_postaci);
}