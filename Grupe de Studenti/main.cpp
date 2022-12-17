/// TEMA 1

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/// Implementam clasa student.

class Student{

private:
    char *nume;
    int anul_nasterii;
    int numar_credite;
    double medie_generala;

public:

    /// Implementam constructorii de initializare.

    Student (){ nume=new char[10];   }

    Student(const char* nume_, int anul_nasterii_, int numar_credite_, double medie_generala_) {
        size_t len = strlen(nume_);
        nume = new char[len];
        strcpy(nume, nume_);
        anul_nasterii = anul_nasterii_;
        numar_credite = numar_credite_;
        medie_generala = medie_generala_;
    }

    /// Implementam un constructor de copiere.

    Student(const Student &stud){
        size_t len = strlen(stud.nume);
        nume = new char[len];
        strcpy(nume, stud.nume);
        anul_nasterii = stud.anul_nasterii;
        numar_credite = stud.numar_credite;
        medie_generala = stud.medie_generala;
    }

    /// Implementam un destructor pentru numele alocat.

    ~Student() {
        delete[] nume;
    }

    /// Implementam metode publice de setare informatii (set).

    void setNume(const char* newNume){
        delete[] nume;
        size_t len = strlen(newNume);
        nume = new char[len];
        strcpy(nume, newNume);
    }

    void setAnul_nasterii(int newAnul_nasterii){
        anul_nasterii = newAnul_nasterii;
    }

    void setNumar_credite(int newNumar_credite){
        numar_credite = newNumar_credite;
    }

    void setMedie_generala (double newMedie_generala){
        medie_generala = newMedie_generala;
    }

    /// Implementam metode publice de furnizare informatii (get).

    char *getNume() const {
        return nume;
    }

    int getAnul_nasterii() const{
        return anul_nasterii;
    }

    int getNumar_credite() const{
        return numar_credite;
    }

    double getMedie_generala() const{
        return medie_generala;
    }

    /// Implementam supraincarcarea pe operatorii de citire si afisare.

    friend istream& operator >> (istream &is, Student &s){
        char buf[100];
        cout << "Numele studentului: ";
        is.get();
        is.getline(buf, 100);
        s.setNume(buf);
        cout << "Anul de nastere al studentului: ";
        is >> s.anul_nasterii;
        cout << "Numarul de credite al studentului: ";
        is >> s.numar_credite;
        cout << "Medie generala a studentului: ";
        is >> s.medie_generala;
        return is;
    }

    friend ostream& operator <<(ostream &os, Student &s){
        if(!s.nume){
            os << "Nu a fost introdus nici un nume!\n";
            return os;
        }
        os << "Numele studentului: " << s.nume << endl;
        os << "Anul nasterii: " << s.anul_nasterii << endl;
        os << "Numar credite: " << s.numar_credite << endl;
        os << "Medie generala: " << s.medie_generala << endl;
        return os;
    }

    bool operator==(const Student &rhs) const {
        return nume == rhs.nume &&
               anul_nasterii == rhs.anul_nasterii &&
               numar_credite == rhs.numar_credite &&
               medie_generala == rhs.medie_generala;
    }

    bool operator!=(const Student &rhs) const {
        return !(rhs == *this);
    }

    Student& operator = (Student s) {
        int l = strlen(nume);
        delete[] nume;
        nume = new char[l];
        strcpy (nume, s.nume);
        anul_nasterii = s.anul_nasterii;
        numar_credite = s.numar_credite;
        medie_generala = s.medie_generala;
        return *this;
    }
};

/// Implementam clasa grupa.

class Grupa{

private:
    Student *vector_studenti;
    int nr_studenti = 0;
    double medie_grupa;

public:

    /// Implementam constructorii de initializare.

    Grupa() {
        vector_studenti = new Student [1];
    }

    Grupa(const Student *vector_studenti_, int nr_studenti_, double medie_grupa_){
        nr_studenti = nr_studenti_;
        medie_grupa = medie_grupa_;
        vector_studenti = new Student [nr_studenti_];
        for (int i=0; i<nr_studenti_; i++)
            vector_studenti[i] = vector_studenti_[i];
    }

    /// Implementam un destructor pentru vectorul de studenti.

    ~Grupa(){
        delete[] vector_studenti;
    }

    /// Implementam un constructor de copiere.

    Grupa(const Grupa &gr){
        delete[] vector_studenti;
        vector_studenti = new Student[nr_studenti];
        for (int i=0; i<nr_studenti; i++)
            vector_studenti[i] = gr.vector_studenti[i];
        nr_studenti = gr.nr_studenti;
        medie_grupa = gr.medie_grupa;
    }

    /// Implementam metode publice de setare informatii (set).

    void setVectorStudenti(const Student *vectorStudenti) {
        for(int i=0; i<nr_studenti; i++)
            vector_studenti[i] = vectorStudenti[i];
    }

    void setNr_studenti(int newNr_studenti){
        nr_studenti = newNr_studenti;
        if(vector_studenti)
            delete[] vector_studenti;
        vector_studenti=new Student[nr_studenti];
    }

    void setMedie_grupa (double newMedie_grupa){
        medie_grupa = newMedie_grupa;
    }

    /// Implementam metode publice de furnizare informatii (get).

    void getVector_Studenti(Student *vector_studenti_) const {
        vector_studenti_=new Student[nr_studenti];
        for(int i=0; i<nr_studenti; i++)
            vector_studenti_[i] = vector_studenti[i];
    }

    int getNr_studenti() const{
        return nr_studenti;
    }

    double getMedie_grupa() const{
        return medie_grupa;
    }

    /// Implementam metoda publica ce verifica existenta unui student dupa nume.

    bool verificare( char verif[]){
        for (int i=0; i<nr_studenti; i++) {
            if (strcmp(vector_studenti[i].getNume(), verif) == 0)
                return true;
            return false;
        }
    }

    /// Implementam metoda publica ce adauga un student intr-o grupa.

    void adaugare(const Student& s){
        medie_grupa=(double)(medie_grupa*nr_studenti+s.getMedie_generala())/(nr_studenti+1);
        nr_studenti++;
        Student *aux = new Student[nr_studenti];
        for(int i=0; i<nr_studenti-1; i++)
            aux[i] = vector_studenti[i];
        aux[nr_studenti-1] = s;
        this->setNr_studenti(nr_studenti);
        this->setVectorStudenti(aux);
    }

    /// Implementam metoda publica ce elimina un student dintr-o grupa. Atentie! Studentii sunt numerotati in meniu de la 0.

    void eliminare(const int& indice){
        medie_grupa=(double)(medie_grupa*nr_studenti-vector_studenti[indice].getMedie_generala())/(nr_studenti-1);
        Student *aux=new Student[nr_studenti-1];
        int k=0;
        for(int i=0;i<nr_studenti;i++)
            if(i!=indice)
                aux[k++] = vector_studenti[i];
        this->setNr_studenti(nr_studenti-1);
        this->setVectorStudenti(aux);
    }


    /// Implementam supraincarcarea pe operatorii de citire si afisare.

    friend istream& operator >> (istream &is, Grupa &g){
        double suma = 0;
        cout << "Numarul de studenti din grupa: ";
        is >> g.nr_studenti;
        g.vector_studenti=new Student[g.nr_studenti];
        for (int i=0; i<g.nr_studenti; i++) {
            cout<<"Studentul "<< i << " :" << endl;
            is >> g.vector_studenti[i];
            suma += g.vector_studenti[i].getMedie_generala();
        }
        g.medie_grupa=(double)(suma/g.nr_studenti);

        return is;
    }

    friend ostream& operator <<(ostream &os, Grupa &g){
        os << "Numarul de studenti: " << g.nr_studenti << endl;
        for(int i=0; i<g.nr_studenti; i++)
            os <<"Studentul "<< i <<" :" << endl << g.vector_studenti[i] << endl;
        os << "Media grupei: " << g.medie_grupa << endl;
        return os;
    }

    /// Implementam supraincarcarea pe operatorul ==.

    bool operator==(const Grupa &rhs) const {
        return vector_studenti == rhs.vector_studenti &&
               nr_studenti == rhs.nr_studenti &&
               medie_grupa == rhs.medie_grupa;
    }

    bool operator!=(const Grupa &rhs) const {
        return !(rhs == *this);
    }

    /// Implementam supraincarcarea pe =.

    Grupa& operator = (const Grupa &g) {
        delete vector_studenti;
        vector_studenti = new Student[g.nr_studenti];
        for (int i=0; i<=g.nr_studenti; i++)
            vector_studenti[i] = g.vector_studenti[i];
        nr_studenti = g.nr_studenti;
        medie_grupa = g.medie_grupa;
        return *this;
    }
};

int main() {

    cout << endl << "! Meniu interactiv !" << endl;
    cout << "Pentru a rula o comanda, tastati numarul comenzii." << endl << endl;

    int comanda;
    int ok = 1;
    Grupa *salvam_grupa[100];
    vector <Student> salvam_student;
    int nr_stud = 0;
    int nr_grupa = 0;

    while (ok != 0) {

        cout << endl << "Lista comenzi: " << endl;
        cout << "1. Introducere detalii student." << endl;
        cout << "2. Afisare detalii student." << endl;
        cout << "3. Introducere grupe de studenti." << endl;
        cout << "4. Afisare grupe de studenti." << endl;
        cout << "5. Verificare existenta student." << endl;
        cout << "6. Introducere student in grupa." << endl;
        cout << "7. Eliminare student din grupa." << endl << endl;
        cout << endl << "Comanda: ";

        cin >> comanda;
        if (comanda == 1) {
            Student s;
            cout << "Studentul " << nr_stud << endl;
            cin >> s;
            salvam_student.push_back(s);
            nr_stud += 1;
        } else if (comanda == 2) {
            if (salvam_student.size() == 0)
                cout << "Nu a fost introdus nici un student! Nu se pot afisa detalii!" << endl;
            else {
                cout << "Introdu numarul studentului pentru mai multe detalii: ";
                int i;
                cin >> i;
                cout << salvam_student[i];
            }
        } else if (comanda == 3) {
            Grupa *g;
            g = new Grupa;
            cout << "Grupa " << nr_grupa << endl;
            cin >> *g;
            salvam_grupa[nr_grupa] = g;
            nr_grupa += 1;
        } else if (comanda == 4) {
            if (nr_grupa == 0)
                cout << "Nu a fost introdusa nici o grupa! Nu se pot afisa detalii!" << endl;
            else {
                cout << "Introdu numarul grupei pentru mai multe detalii: ";
                int j;
                cin >> j;
                cout << *salvam_grupa[j];
            }
        } else if (comanda == 5) {
            if (nr_grupa == 0)
                cout << "Nu a fost introdusa nici o grupa! Cautarea nu poate avea loc!" << endl;
            else {
                char student_cautat[30];
                int i;
                cout << "Introdu numarul grupei in care doresti sa faci cautarea: ";
                cin >> i;
                cout << "Introdu numele studentului pe care doresti sa il cauti: ";
                cin >> student_cautat;
                bool k = salvam_grupa[i]->verificare(student_cautat);
                if (k) cout << "Elevul a fost gasit." << endl;
                else cout << "Elevul nu a fost gasit." << endl;
            }
        } else if (comanda == 6) {
            if (nr_grupa == 0)
                cout << "Nu a fost introdusa nici o grupa! Nu se pot introduce studenti!" << endl;
            else {
                int a;
                cout << "Introdu numarul grupei in care doresti sa adaugi un student: ";
                cin >> a;
                Student *student_adaugat;
                cin >> *student_adaugat;
                salvam_grupa[a]->adaugare(*student_adaugat);
                cout << "Student adaugat cu succes!" << endl;
            }
        } else if (comanda == 7) {
            if (nr_grupa == 0)
                cout << "Nu a fost introdusa nici o grupa! Nu se pot elimina studenti!" << endl;
            else {
                int e;
                cout << "Introdu numarul grupei din care doresti sa elimini un student: ";
                cin >> e;
                int student_eliminat;
                cout << "Introdu numarul studentului pe care doresti sa il elimini: ";
                cin >> student_eliminat;
                salvam_grupa[e]->eliminare(student_eliminat);
                cout << "Student eliminat cu succes!" << endl;
            }
        }
        else cout << "Comanda nu exista!";
        cout << endl;
        cout << "Daca doriti sa opriti rularea programului, tastati 0!" << endl;
        cout << "Daca doriti sa rulati comenzi in continuare, tastati 1!" << endl;
        cin >> ok;
    }

    return 0;
}
