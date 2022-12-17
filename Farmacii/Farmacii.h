#include <utility>

#ifndef TEMA3_FARMACII_H
#define TEMA3_FARMACII_H

using namespace std;

class Farmacie {
protected:
    string denumire;
    int numarAngajati;
    int profitLuna;

public:
    Farmacie() {
        denumire = "denumire";
        numarAngajati = 0;
        profitLuna = 0;
    }

    Farmacie(string denumire_, int numarAngajati_, int profitLuna_) : denumire(move(denumire_)), numarAngajati(numarAngajati_), profitLuna(profitLuna_) {};

    virtual void citire(istream& is){
        cout << "\nDenumire: ";
        is >> denumire;
        cout << "\nNumar angajati: ";
        is >> numarAngajati;
        cout << "\nProfit luna: ";
        is >> profitLuna;
    }

    friend istream& operator >> (istream& is, Farmacie& f){
        f.citire(is);
        return is;
    }

    virtual ~Farmacie() = default;
};

class FarmacieFizica : public Farmacie {
private:
    string locatie;

public:
    FarmacieFizica(string locatie_, string denumire_, int numarAngajati_, int profitLuna_ ) : Farmacie(move(denumire_), numarAngajati_, profitLuna_), locatie(move(locatie_)) {};

    void citire(istream& is) override {
        is >> dynamic_cast<Farmacie&> (*this);
        cout << "\nLocatie: ";
        is.get();
        getline(is, locatie);
    }

    friend istream& operator>>(istream& is, FarmacieFizica& f){
        f.citire(is);
        return is;
    }

    void afisare (ostream& os) {
        os << "Denumire: ";
        os << denumire<< endl;
        os << "Numar angajati: ";
        os << numarAngajati<< endl;
        os << "Profit luna: ";
        os << profitLuna<< endl;
        os << "Locatie: ";
        os << locatie<< endl;
    }

    friend ostream& operator<<(ostream& os, FarmacieFizica& f){
        f.afisare(os);
        return os;
    }

    ~FarmacieFizica() override = default;
};

class FarmacieOnline : public Farmacie {
private:
    string adresaWeb;
    int numarVizitatori;
    string discount;

public:
    FarmacieOnline(string adresaWeb_, int numarVizitatori_, string discount_, string denumire_, int numarAngajati_, int profitLuna_) : Farmacie(move(denumire_), numarAngajati_, profitLuna_), adresaWeb(move(adresaWeb_)), numarVizitatori(numarVizitatori_), discount(move(discount_)) {};

    int getNumarVizitatori() {
        return numarVizitatori;
    }

    void citire (istream& is) override {
        is >> dynamic_cast<Farmacie&> (*this);
        cout << "\nAdresa WEB: ";
        is >> adresaWeb;
        cout << "\nNumar vizitatori: ";
        is >> numarVizitatori;
        cout << "\nDiscount: ";
        is >> discount;
    }

    friend istream& operator>>(istream& is, FarmacieOnline& f){
        f.citire(is);
        return is;
    }

    void afisare (ostream& os) {
        os << "Denumire: ";
        os << denumire << endl;
        os << "Numar angajati: ";
        os << numarAngajati<< endl;
        os << "Profit luna: ";
        os << profitLuna<< endl;
        os << "Adresa WEB: ";
        os << adresaWeb<< endl;
        os << "Numar vizitatori: ";
        os << numarVizitatori<< endl;
        os << "Discount: ";
        os << discount<< endl;
    }

    friend ostream& operator<<(ostream& os, FarmacieOnline& f){
        f.afisare(os);
        return os;
    }

    ~FarmacieOnline() override = default;
};


#endif

