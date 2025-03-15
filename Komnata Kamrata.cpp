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
    int zrecznosc = 1;
    double kryt = 1.0;
    double punkty = 1.0;
    string helm = "Brak";
    string zbroja = "Brak";
    string buty = "Brak";
    string bron = "Brak";
};

void start();
void tworzenie_postaci(statystyki_postaci& postac, string& klasa_postaci_napis);
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, int wybor_akcji);
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis);
void opis_statystyk();
void przedmioty(statystyki_postaci& postac);
void liczenie_punktow_postaci(statystyki_postaci& postac, int klasa_postaci);
void opis_liczenia_punktow(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis);
void ekwipunek(statystyki_postaci postac);
void rysuj_drzwi(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, int& wybor_drzwi);
void przeciwnik(struct statystyki_postaci& postac, struct statystyki_postaci& enemy);
void walka(statystyki_postaci &postac, statystyki_postaci enemy);
int koniec_gry();
void przygoda(statystyki_postaci& postac, statystyki_postaci enemy);

const int losowych_zdarzen = 10;
const int max_statystyki = 30; //jeszcze nie uzywane
int punkty_ulepszen = 0;
int klasa_postaci = 0; //1 dla wojownika, 2 dla Ninja
int wybor_drzwi;
int wybor_akcji{};
int pokonani_wrogowie = 0;
int odwiedzone_pokoje = 0;
int otwarte_skrzynki = 0;
string klasa_postaci_napis = "Bezimienny";
statystyki_postaci postac;
statystyki_postaci enemy;

int main() {
    setlocale(LC_ALL, "pl_PL");
    srand(time(0));
    //start();
    tworzenie_postaci(postac, klasa_postaci_napis);
    liczenie_punktow_postaci(postac, klasa_postaci); //trzeba dodawac zawsze po zalozeniu przedmiotu!
    menu(postac, wybor_akcji, klasa_postaci_napis);

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
        postac.zrecznosc = 2;
        postac.kryt = 1.2;
        klasa_postaci_napis = "Wojownik";
    }
    if (klasa_postaci == 2) {
        //ninja
        postac.hp = 6;
        postac.sila = 7;
        postac.zrecznosc = 4;
        postac.kryt = 1.5;
        klasa_postaci_napis = "Ninja";
    }
    system("cls");
}
void postac_upgrade(statystyki_postaci& postac, int klasa_postaci, int wybor_akcji) {
    int wybor_statystyki;
    system("cls");
    cout << "\n\t1.Siła\t\t2.Życie\t\t3.Zręczność\t\t4. Kryt";
    cout << "\n\t     Masz " << punkty_ulepszen << " punkt(y) do przydzielenia!";
    cout << "\n\n( By wrócić do menu, wybierz 0 )";
    cout << "\nWybierz numer statystyki by przydzielić : ";
    cin >> wybor_statystyki;
    switch (wybor_statystyki) {
    case 1: {
        if (punkty_ulepszen > 0) {
            postac.sila++;
            punkty_ulepszen--;
            cout << "Pomyslnie ulepszono sile";
        }
        else cout << "\n\nNie masz punktow";
        Sleep(1000);
        break;
    }

    case 2: {
        if (punkty_ulepszen > 0) {
            postac.hp++;
            punkty_ulepszen--;
            cout << "Pomyslnie ulepszono życie";
        }
        else cout << "\n\nNie masz punktow";
        Sleep(1000);
        break;
    }

    case 3: {
        if (punkty_ulepszen > 0) {
            postac.zrecznosc++;
            punkty_ulepszen--;
            cout << "Pomyslnie ulepszono zręcznosc";
        }
        else cout << "\n\nNie masz punktow";
        Sleep(1000);
        break;
    }

    case 4: {
        if (punkty_ulepszen > 0) {
            postac.kryt++;
            punkty_ulepszen--;
            cout << "Pomyslnie ulepszono kryta";
        }
        else cout << "\n\nNie masz punktow";
        Sleep(1000);
        break;
    }

    case 0: {
        break;
    }
    }
    liczenie_punktow_postaci(postac, klasa_postaci); //aktualizacja punktow po dodaniu punktow
    system("cls");
}
void menu(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis) {
    do {
        cout << "\n  * ======================================================= *";
        cout << "\n  I                  # Komnata Kamrata #                    I";
        cout << "\n  I                                                         I";
        cout << "\n  I\tSila: " << postac.sila << "\t\tHP: " << postac.hp << "\t\tZrecznosc: " << postac.zrecznosc << "        I";
        cout << "\n  I\t\tMnoznik punktow ( kryt ) : " << postac.kryt << "              I";
        cout << "\n  I                                                         I";
        cout << "\n                      " << klasa_postaci_napis << " " << postac.imie;
        cout << "\n  I                 " << "Punkty postaci: " << postac.punkty << "                    I";
        cout << "\n  * ======================================================= *";
        cout << "\n\n   Co chcesz zrobić : \n";
        cout << "\n   1. Rusz na PRZYGODE ! ";
        cout << "\n   2. Zwieksz statystyki";
        cout << "\n   3. Zobacz ekwipunek";
        cout << "\n   4. O grze";
        cout << "\n   0. Koniec programu";
        cout << "\n   \tWybór: ";
        cin >> wybor_akcji;

        switch (wybor_akcji) {
        case 1: {
            system("cls");
            rysuj_drzwi(postac, wybor_akcji, klasa_postaci_napis, wybor_drzwi);
            break;
        }
        case 2: {
            postac_upgrade(postac, klasa_postaci, wybor_akcji);
            break;
        }
        case 3: {
            system("cls");
            ekwipunek(postac);
            menu(postac, wybor_akcji, klasa_postaci_napis);
            break;
        }
        case 4: {
            system("cls");
            cout << "\n  * ======================================================= *";
            cout << "\n  I                  # Komnata Kamrata #                    I";
            cout << "\n  I                                                         I";
            cout << "\n  I\tSiła: " << postac.sila << "\t\tHP: " << postac.hp << "\t\tZreczność: " << postac.zrecznosc << "        I";
            cout << "\n  I\t\tMnoznik punktow ( kryt ) : " << postac.kryt << "              I";
            cout << "\n  I                                                         I";
            cout << "\n                       " << klasa_postaci_napis << " " << postac.imie;
            cout << "\n  I                 " << "Punkty postaci: " << postac.punkty << "                    I";
            cout << "\n  * ======================================================= *";
            cout << "\n\n   Co chcesz zrobić : \n";
            cout << "\n   1. Opis statystyk";
            cout << "\n   2. Opis liczenia punktów";
            cout << "\n   3. O co chodzi w grze?";
            cout << "\n   4. Wystepowanie przeciwnikow";
            cout << "\n   0. Powrót";
            cout << "\n\tWybór : ";
            int w = 0;
            cin >> w;
            switch (w) {
            case 1: {
                opis_statystyk();
                menu(postac, wybor_akcji, klasa_postaci_napis);
                break;
            }
            case 2: {
                opis_liczenia_punktow(postac, wybor_akcji, klasa_postaci_napis);
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
            case 4: {
                system("cls");
                cout << "\n Wystepowanie przeciwników :";
                cout << "\n 1. Najprostszy - 40%";
                cout << "\n 1. Średni - 30%";
                cout << "\n 1. Trudny - 20%";
                cout << "\n 1. Boss - 20%";
                break;
            }
            case 0: {
                system("cls");
                menu(postac, wybor_akcji, klasa_postaci_napis);
            }
            }
        }
        case 0: {
            koniec_gry();
            break;
        }
        }

    } while (wybor_akcji != 0);
}

void opis_statystyk() {
    system("cls");
    cout << "\n  * =========================================================================== *";
    cout << "\n  I           Każda statystyka (oprócz HP) przyczynia sie do obrażeń!           I";
    cout << "\n  I                                                                             I";
    cout << "\n  I              Siła to mnożnik obrażeń (obrażenia bazowe * siła)              I";
    cout << "\n  I  Zreczność zmniejsza otrzymywane obrażenia (za każdy punkt są 10% mniejsze) I";
    cout << "\n  I              Kryt to mnoznik obrazen 1pkt to 10% wieksze punkty             I";
    cout << "\n  I                 ******  Kup przedmiot by odblokowac  ******                 I";
    cout << "\n  I                 ******  Kup przedmiot by odblokowac  ******                 I";
    cout << "\n  * =========================================================================== *\n\n";
}
void liczenie_punktow_postaci(statystyki_postaci& postac, int klasa_postaci) {
    if (klasa_postaci == 0) { //default
        postac.punkty = (1 * postac.sila + 1 * postac.zrecznosc + 1 * postac.hp) * postac.kryt;
    }
    if (klasa_postaci == 1) { //wojownik
        postac.punkty = (2 * postac.sila + 1 * postac.zrecznosc + 2 * postac.hp) * postac.kryt;
    }
    if (klasa_postaci == 2) { //ninja
        postac.punkty = (1 * postac.sila + 3 * postac.zrecznosc + 1 * postac.hp) * postac.kryt;
    }
    //liczenie punktow przeciwnika
    enemy.punkty = (1 * enemy.sila + 1 * enemy.zrecznosc + 1 * enemy.hp) * enemy.kryt;
}

//zarys przedmiotow, jeszcze brak funkcjonalnosci
void przedmioty(statystyki_postaci& postac) {
    int a = 1; //tymczasowe
    if (a == 2) //helm1
    {
        postac.helm = "Ciężki hełm";
        postac.hp += 2;
        postac.zrecznosc -= 1;
    }
    if (a == 3) //helm2
    {
        postac.helm = "Lekki hełm";
        postac.hp += 1;
        postac.zrecznosc += 1;
    }
    if (a == 4) { //zbroja1
        postac.zbroja = "Ciężka zbroja";
        postac.hp += 3;
        postac.zrecznosc -= 1;
    }
    if (a == 5) { //zbroja2
        postac.zbroja = "Lekka zbroja";
        postac.hp += 1;
        postac.zrecznosc += 1;
    }
    if (a == 6) { //buty2
        postac.buty = "Ciężkie buty";
        postac.hp += 3;
        postac.zrecznosc -= 1;
    }
    if (a == 7) { //buty2
        postac.buty = "Lekkie buty";
        postac.hp += 1;
        postac.zrecznosc += 1;
    }
    if (a == 8) { //miecz 1
        postac.bron = "Mały miecz";
        postac.sila += 1;
        postac.zrecznosc += 1;
    }
    if (a == 9) { //miecz 2
        postac.bron = "Średni miecz";
        postac.sila += 2;
    }
    if (a == 10) { // miecz 3
        postac.bron = "Wielki miecz";
        postac.sila += 3;
        postac.zrecznosc -= 1;
    }
}
void opis_liczenia_punktow(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis) {
    system("cls");
    cout << "\n  * =========================================================================== *";
    cout << "\n  I                      Sposób liczenia punktow postaci                        I";
    cout << "\n  I                                                                             I";
    cout << "\n  I            Kazda klasa otrzymuje inne bonusy ze swoich statystyk            I";
    cout << "\n  I                                                                             I";
    cout << "\n  I                   Wojownik otrzymuje bonus za siłe i HP                     I";
    cout << "\n  I                     Ninja otrzymuje bonus za zręczność                      I";
    cout << "\n  I               Wzor : (x * sila + x * hp + x * zrecznosc) * kryt             I";
    cout << "\n  I                     Gdzie 'x' to mnoznik bonusu postaci                     I";
    cout << "\n  * =========================================================================== *";
    menu(postac, wybor_akcji, klasa_postaci_napis);
}
void ekwipunek(statystyki_postaci postac) {
    cout << "\nHełm : " << "\t\t" << postac.helm;
    cout << "\nZbroja : " << "\t" << postac.zbroja;
    cout << "\nButy : " << "\t\t" << postac.buty;
    cout << "\nBroń : " << "\t\t" << postac.bron;
}
void rysuj_drzwi(statystyki_postaci postac, int wybor_akcji, string klasa_postaci_napis, int& wybor_drzwi) {
    cout << "\nPokuj nr. " << odwiedzone_pokoje + 1;
    cout << "\n\t#########    \t#########\n";
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
        odwiedzone_pokoje++;
        przygoda(postac, enemy);
        break;
    }
    case 2: {
        system("cls");
        odwiedzone_pokoje++;
        przygoda(postac, enemy);
        break;
    }
    case 0: {
        system("cls");
        menu(postac, wybor_akcji, klasa_postaci_napis);
        break;
    }
    }
}

//statystyki przeciwnikow do balansu, narazie przykladowe
void przeciwnik(struct statystyki_postaci& postac, struct statystyki_postaci& enemy) {
    int losowanie = rand() % 10 + 1;
    int wylosowany_przeciwnik = losowanie;

    switch (losowanie) {
    case 1: {
        enemy.imie = "Przeciwnik 1, slaby";
        enemy.hp = 1;
        enemy.sila = 1;
        enemy.zrecznosc = 1;
        enemy.kryt = 1.1;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 2: {
        enemy.imie = "Przeciwnik 1, slaby";
        enemy.hp = 1;
        enemy.sila = 1;
        enemy.zrecznosc = 1;
        enemy.kryt = 1.1;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 3: {
        enemy.imie = "Przeciwnik 1, slaby";
        enemy.hp = 1;
        enemy.sila = 1;
        enemy.zrecznosc = 1;
        enemy.kryt = 1.1;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 4: {
        enemy.imie = "Przeciwnik 1, slaby";
        enemy.hp = 1;
        enemy.sila = 1;
        enemy.zrecznosc = 1;
        enemy.kryt = 1.1;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }    
    case 5: {
        enemy.imie = "Przeciwnik 2, sredni";
        enemy.hp = 2;
        enemy.sila = 2;
        enemy.zrecznosc = 2;
        enemy.kryt = 1.3;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 6: {
        enemy.imie = "Przeciwnik 2, sredni";
        enemy.hp = 2;
        enemy.sila = 2;
        enemy.zrecznosc = 2;
        enemy.kryt = 1.3;
        cout << "\nStatystyki przeciwnika : \n";
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 1;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 7: {
        enemy.imie = "Przeciwnik 3, silny";
        enemy.hp = 3;
        enemy.sila = 3;
        enemy.zrecznosc = 3;
        enemy.kryt = 1.5;
        cout << "\nStatystyki przeciwnika : \n" << endl;
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 2;
        Sleep(1500);
        walka(postac, enemy);
        break;

    }
    case 8: {
        enemy.imie = "Przeciwnik 3, silny";
        enemy.hp = 3;
        enemy.sila = 3;
        enemy.zrecznosc = 3;
        enemy.kryt = 1.5;
        cout << "\nStatystyki przeciwnika : \n" << endl;
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 2;
        Sleep(1500);
        walka(postac, enemy);
        break;
    }
    case 9: {
        enemy.imie = "Przeciwnik 4, ciezkie sie wylosowalo, boss";
        enemy.hp = 4;
        enemy.sila = 4;
        enemy.zrecznosc = 4;
        enemy.kryt = 1.8;
        cout << "\nStatystyki przeciwnika : \n" << endl;
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 3;
        Sleep(1500);
        walka(postac, enemy);
        break;
    }
    case 10: {
        enemy.imie = "Przeciwnik 4, ciezkie sie wylosowalo, boss";
        enemy.hp = 4;
        enemy.sila = 4;
        enemy.zrecznosc = 4;
        enemy.kryt = 1.8;
        cout << "\nStatystyki przeciwnika : \n" << endl;
        cout << enemy.imie << endl;
        cout << "Sila : " << enemy.sila << endl;
        cout << "Życie : " << enemy.hp << endl;
        cout << "Zręczność : " << enemy.zrecznosc << endl << endl;
        cout << "\n\nWalka..";
        punkty_ulepszen += 3;
        Sleep(1500);
        walka(postac, enemy);
        break;
    }
    } // switch
}// funkcja
//zrobic bardziej realistyczna walke, turowa czy cos
void walka(statystyki_postaci &postac, statystyki_postaci enemy) {
    if (postac.hp < enemy.sila) {
        Sleep(1000);
        cout << "\nPrzegrywasz, koniec gry";
        cout << "\nWcisnij dowolny klawisz by kontynuuowac...";
        _getch();
        koniec_gry();
    }
    if (postac.punkty > enemy.punkty and postac.hp > enemy.sila) {
        Sleep(1000);
        pokonani_wrogowie++;
        cout << "\nWygrywasz walke";
        postac.hp = postac.hp - enemy.sila;
        cout << "\nZdobywasz punkt(y) ulepszen"; // pozniej zrobic jakies poziomy, typu lvl to 100exp i kazdy potwor daje inna ilosc expa, jeden caly poziom to jeden punkt 
        Sleep(400);
        cout << "\nWcisnij dowolny klawisz by kontynuuowac...";
        _getch();
        system("cls");
        menu(postac, wybor_akcji, klasa_postaci_napis);
    }
    if (postac.punkty == enemy.punkty or (postac.hp == enemy.sila and enemy.hp == postac.sila) ) {
        Sleep(1000);
        cout << "\nRemis, kazdy odszedl w swoja strone";
        cout << "\nWcisnij dowolny klawisz by kontynuuowac...";
        _getch();
        menu(postac, wybor_akcji, klasa_postaci_napis);
    }
}
int koniec_gry() {
    system("cls");
    cout << "\n=============================================";
    cout << "\n        Niestety to twój koniec gry !";
    cout << "\n\n               Statystyki:";
    cout << "\n          Zdobyte punkty : " << postac.punkty << " !";
    cout << "\n\           Pokonwni wrogowie: " << pokonani_wrogowie << " !";
    cout << "\n           Odwiedzone pokoje : "<< odwiedzone_pokoje << " !";
    cout << "\n          Otworzone skrzynki : "<< otwarte_skrzynki << " !";
    cout << "\n\n           Sproboj jeszcze raz !";
    cout << "\n=============================================";
    cout << "\n\nWcisnij dowolny klawisz by kontynuuowac...";
    _getch();
    return 0;
}
void przygoda(statystyki_postaci &postac, statystyki_postaci enemy) {
    cout << "\nW " << wybor_drzwi << " drzwiach czai sie : " << endl;
    int wylosowane = rand() % losowych_zdarzen + 1;
    switch (wylosowane) {
    case 1: {
        przeciwnik(postac, enemy);
        break;
    }
    case 2: {
        przeciwnik(postac, enemy);
        break;
    }
    case 3: {
        przeciwnik(postac, enemy);
        break;
    }
    case 4: {
        przeciwnik(postac, enemy);
        break;
    }
    case 5: {
        przeciwnik(postac, enemy);
        break;
    }
    case 6: {
        przeciwnik(postac, enemy);
        break;
    }
    case 7: {
        przeciwnik(postac, enemy);
        break;
    }
    case 8: {
        Sleep(700);
        cout << "\nZnalazles Skrzynie !";
        Sleep(700);
        cout << "\nOtwieranie ...";
        Sleep(2000);
        punkty_ulepszen += 1;
        cout << "\n " << postac.imie << " znajduje 1pkt ulepszen !";
        otwarte_skrzynki++;
        break;
    }
    case 9: {
        Sleep(700);
        cout << "\nZnalazles Skrzynie !";
        Sleep(700);
        cout << "\nOtwieranie ...";
        Sleep(2000);
        punkty_ulepszen += 2;
        cout << "\n " << postac.imie << " znajduje 2pkt ulepszen !";
        otwarte_skrzynki++;
        break;
    }
    case 10: {
        Sleep(700);
        cout << "\nZnalazles Skrzynie !";
        Sleep(700);
        cout << "\nOtwieranie ...";
        Sleep(2000);
        punkty_ulepszen += 3;
        cout << "\n " << postac.imie << " znajduje 3pkt ulepszen !";
        otwarte_skrzynki++;
        break;
    }

    }
}
