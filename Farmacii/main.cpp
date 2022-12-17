#include <iostream>
#include "GestionareFarmacii.h"
#include <memory>

using namespace std;

template<class F>
Farmacie* citire(){
    string denumire;
    int numarAngajati;
    int profitLuna;
    string locatie;
    cout << "Denumire: ";
    cin >> denumire;
    cout << "Numar angajati: ";
    cin >> numarAngajati;
    cout << "Profit luna: ";
    cin >> profitLuna;
    cout << "Locatie: ";
    cin >> locatie;
    Farmacie* f = new FarmacieFizica(locatie, denumire, numarAngajati, profitLuna);
    return f;
}

template<>
Farmacie* citire<FarmacieOnline>(){
    string adresaWeb;
    int numarVizitatori;
    string discount;
    string denumire;
    int numarAngajati;
    int profitLuna;
    cout << "Denumire: ";
    cin >> denumire;
    cout << "Numar angajati: ";
    cin >> numarAngajati;
    cout << "Profit luna: ";
    cin >> profitLuna;
    cout << "Adresa WEB: ";
    cin >> adresaWeb;
    cout << "Numar vizitatori: ";
    cin >> numarVizitatori;
    cout << "Discount: ";
    cin >> discount;
    Farmacie* fo = new FarmacieOnline(adresaWeb, numarVizitatori, discount, denumire, numarAngajati, profitLuna);
    return fo;
}

int main() {
    GestionareFramacii<FarmacieFizica*> farmaciiFizice;
    GestionareFramacii<FarmacieOnline> farmaciiOnline;
    int nr;
    string tip;

    cout << "Numarul de farmacii citite: ";
    cin >> nr;
    cout << endl;
    int nrfo = 0, nrffiz = 0;

    while (nr--){
        cout << "Tipul farmaciei: ";
        cin >> tip;

        if(tip == "online"){
            farmaciiOnline += *(FarmacieOnline*)citire<FarmacieOnline>();
            cout << endl;
            nrfo ++;
        }
        else {
            farmaciiFizice += (FarmacieFizica*)citire<FarmacieFizica>();
            cout << endl;
            nrffiz ++;
        }
    }


    cout << "Farmaciile proprietarului: " << endl << endl;
    cout << "Farmacii fizice: " << endl << endl;
    if(nrffiz != 0)
        cout << farmaciiFizice << endl;
    else cout << "Proprietarul nu detine farmacii fizice.\n" << endl;
    cout << "Farmacii online: " << endl << endl;
    if(nrfo != 0)
        cout << farmaciiOnline << endl;
    else cout << "Proprietarul nu detine farmacii online.\n" << endl;
    cout << "Cate persoane au vizitat farmaciile online?" << endl;
    if (nrfo != 0 )
    cout << farmaciiOnline.suma();
    else cout << 0;
    return 0;
}
