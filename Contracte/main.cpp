#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class ContractType {
    ContractInchiriere,
    ContractVizionare
};

class Exceptii : public std::exception {
public:
    Exceptii() = default;

    const char* what() const noexcept override{
        return "Numerele contractelor trebuie sa fie unice!";
    }
};

class ExceptiiDoi : public std::exception {
public:
    ExceptiiDoi() = default;

    const char* what() const noexcept override{
        return "Nu exista nici un contract de acest tip!";
    }
};


class Contract {
private:
    int nrContract;
    int anul;
    std::string beneficiar;
    std::string furnizor;
    int valoare;

public:

    ///CONSTRUCTOR FARA PARAMETRII
    Contract() {
        nrContract = -1;
        anul = -1;
        beneficiar = "beneficiar";
        furnizor = "furnizor";
        valoare = -1;
    }

    /// CONSTRUCTOR DE INITIALIZARE
    Contract(int nrContract, int anul, std::string beneficiar, std::string furnizor, int valoare) : nrContract(nrContract), anul(anul), beneficiar(std::move(beneficiar)), furnizor(std::move(furnizor)), valoare(valoare) {}

    /// SETTER
    void setNrContract(int nrContract_) {
        Contract::nrContract = nrContract_;
    }
    void setAnul(int anul_) {
        Contract::anul = anul_;
    }
    void setBeneficiar(const std::string &beneficiar_) {
        Contract::beneficiar = beneficiar_;
    }
    void setFurnizor(const std::string &furnizor_) {
        Contract::furnizor = furnizor_;
    }
    void setValoare(int valoare_) {
        Contract::valoare = valoare_;
    }

    /// GETTER
    int getNrContract() const {
        return nrContract;
    }
    int getAnul() const {
        return anul;
    }
    const std::string &getBeneficiar() const {
        return beneficiar;
    }
    const std::string &getFurnizor() const {
        return furnizor;
    }
    int getValoare() const {
        return valoare;
    }

    /// SUPRAINCARCARE PE == SI PE !=
    bool operator==(const Contract &rhs) const {
        return nrContract == rhs.nrContract &&
               anul == rhs.anul &&
               beneficiar == rhs.beneficiar &&
               furnizor == rhs.furnizor &&
               valoare == rhs.valoare;
    }
    bool operator!=(const Contract &rhs) const {
        return !(rhs == *this);
    }

    /// TIPUL CONTRACTULUI
    virtual ContractType getType() const = 0;

    /// DESTRUCTOR
    virtual ~Contract() = default;

    /// SUPRAINCARCARE PE AFISARE
    virtual void print(std::ostream &os) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Contract *contract) {
        contract -> print(os);
        return os;
    }
};


class ContractInchiriere : public Contract {
private:
    int perioada;

public:

    ///CONSTRUCTOR FARA PARAMETRII
    ContractInchiriere() : Contract() {
        perioada = -1;
    }

    /// CONSTRUCTOR
    ContractInchiriere(int nrContract, int anul, std::string beneficiar, std::string furnizor, int valoare, int perioada_):
            Contract(nrContract, anul, (std::move(beneficiar)), (std::move(furnizor)), valoare){
        perioada = perioada_;
    }
    ContractInchiriere(const ContractInchiriere& contractInchiriere, int perioada_) :
            Contract(contractInchiriere.getNrContract(), contractInchiriere.getAnul(), contractInchiriere.getBeneficiar(), contractInchiriere.getFurnizor(), contractInchiriere.getValoare()) {
        perioada = perioada_;
    }

    /// GETTER
    int getPerioada() const {
        return perioada;
    }

    /// SETTER
    void setPerioada(int perioada_) {
        ContractInchiriere::perioada = perioada_;
    }

    /// SUPRAINCARCARE PE == SI PE !=
    bool operator==(const ContractInchiriere &rhs) const {
        return static_cast<const Contract &>(*this) == static_cast<const Contract &>(rhs) &&
               perioada == rhs.perioada;
    }
    bool operator!=(const ContractInchiriere &rhs) const {
        return !(rhs == *this);
    }

    /// SUPRAINCARCARE PE =
    ContractInchiriere& operator =(ContractInchiriere const &ctr) {
        setPerioada(ctr.getPerioada());
        setValoare(ctr.getValoare());
        setNrContract(ctr.getNrContract());
        setFurnizor(ctr.getFurnizor());
        setBeneficiar(ctr.getBeneficiar());
        setAnul(ctr.getAnul());
        return *this;
    }


    /// SUPRAINCARCARE PE CITIRE
    friend std::istream &operator>>(std::istream &is, ContractInchiriere &inchiriere) {
        std::string beneficiar_, furnizor_;
        int anul_, valoare_, perioada_, nrContract_;
        std::cout << "Numar contract: ";
        is >> nrContract_;
        std::cout << "Anul: ";
        is >> anul_;
        std::cout << "Valoarea: ";
        is >> valoare_;
        std::cout << "Beneficiar: ";
        is >> beneficiar_;
        std::cout << "Furnizor: ";
        is >> furnizor_;
        std::cout << "Perioada: ";
        is >> perioada_;

        inchiriere.setPerioada(perioada_);
        inchiriere.setAnul(anul_);
        inchiriere.setBeneficiar(beneficiar_);
        inchiriere.setFurnizor(furnizor_);
        inchiriere.setNrContract(nrContract_);
        inchiriere.setValoare(valoare_);

        return is;
    }

    /// SUPRAINCARCARE PE AFISARE
    void print(std::ostream &os) const override {
        os << "Numarul contractului: " << getNrContract() << '\n' << "Anul: " << getAnul() << '\n' << "Beneficiar: "
           << getBeneficiar() << '\n' << "Furnizor: " << getFurnizor() << '\n' << "Valoare: " << getValoare() << '\n'
           << "Perioada: " << getPerioada() << '\n';
    }
    friend std::ostream &operator<<(std::ostream &os, const ContractInchiriere &contractInchiriere) {
        contractInchiriere.print(os);
        return os;
    }

    /// TIPUL CONTRACTULUI
    ContractType getType () const override {
        return ContractType::ContractInchiriere;
    }

    /// AFISARE TIP
    static void afisareContractInchiriere () {
        std::cout << "Contract de inchiriere";
    }

    /// PLATA
    static void plata(const std::shared_ptr<ContractInchiriere> &inchiriere) {
        std::cout << "Plata Contract " << inchiriere->getNrContract() << ": " << inchiriere->getPerioada() * inchiriere->getValoare() << " euro.";
    }
};


class ContractVizionare : public Contract {
private:
    int nrOre;

public:

    ///CONSTRUCTOR FARA PARAMETRII
    ContractVizionare() : Contract() {
        nrOre = -1;
    }

    /// CONSTRUCTOR
    ContractVizionare(int nrContract, int anul, std::string beneficiar, std::string furnizor, int valoare, int nrOre_):
            Contract(nrContract, anul, (std::move(beneficiar)), (std::move(furnizor)), valoare){
        nrOre = nrOre_;
    }
    ContractVizionare(const ContractVizionare& contractVizionare, int nrOre_) : Contract(contractVizionare.getNrContract(), contractVizionare.getAnul(), contractVizionare.getBeneficiar(), contractVizionare.getFurnizor(), contractVizionare.getValoare()) {
        nrOre = nrOre_;
    }

    /// GETTER
    int getNrOre() const {
        return nrOre;
    }

    /// SETTER
    void setNrOre(int nrOre_) {
        ContractVizionare::nrOre = nrOre_;
    }

    /// SUPRAINCACRCARE PE == SI PE !=
    bool operator==(const ContractVizionare &rhs) const {
        return static_cast<const Contract &>(*this) == static_cast<const Contract &>(rhs) &&
               nrOre == rhs.nrOre;
    }
    bool operator!=(const ContractVizionare &rhs) const {
        return !(rhs == *this);
    }

    /// SUPRAINCARCARE PE =
    ContractVizionare& operator =(ContractVizionare const &ctr) {
        setNrOre(ctr.getNrOre());
        setValoare(ctr.getValoare());
        setNrContract(ctr.getNrContract());
        setFurnizor(ctr.getFurnizor());
        setBeneficiar(ctr.getBeneficiar());
        setAnul(ctr.getAnul());
        return *this;
    }

    /// SUPRAINCARCARE PE CITIRE
    friend std::istream &operator>>(std::istream &is, ContractVizionare &vizionare) {
        std::string beneficiar_, furnizor_;
        int anul_, valoare_, nrOre_, nrContract_;
        std::cout << "Numar contract: ";
        is >> nrContract_;
        std::cout << "Anul: ";
        is >> anul_;
        std::cout << "Valoarea: ";
        is >> valoare_;
        std::cout << "Beneficiar: ";
        is >> beneficiar_;
        std::cout << "Furnizor: ";
        is >> furnizor_;
        std::cout << "Numar ore: ";
        is >> nrOre_;

        vizionare.setNrOre(nrOre_);
        vizionare.setAnul(anul_);
        vizionare.setBeneficiar(beneficiar_);
        vizionare.setFurnizor(furnizor_);
        vizionare.setNrContract(nrContract_);
        vizionare.setValoare(valoare_);

        return is;
    }

    /// SUPRAINCARCARE PE AFISARE
    void print(std::ostream &os) const override {
        os << "Numarul contractului: " << getNrContract() << '\n' << "Anul: " << getAnul() << '\n' << "Beneficiar: "
           << getBeneficiar() << '\n' << "Furnizor: " << getFurnizor() << '\n' << "Valoare: " << getValoare() << '\n'
           << "Numarul de ore: " << getNrOre() << '\n';
    }
    friend std::ostream &operator<<(std::ostream &os, const ContractVizionare &contractVizionare) {
        contractVizionare.print(os);
        return os;
    }

    /// TIPUL CONTRACTULUI
    ContractType getType () const override {
        return ContractType::ContractVizionare;
    }

    /// AFISARE TIP
    static void afisareContractVizionare () {
        std::cout << "Contract de vizionare";
    }

    /// PLATA
    static void plata(const std::shared_ptr<ContractVizionare> &vizionare) {
        std::cout << "Plata Contract " << vizionare->getNrContract() << ": " << vizionare->getNrOre() * vizionare->getValoare() << " euro.";
    }
};


class Dosar {
private:
    unsigned long long numardosare;
    static std::vector<std::shared_ptr<Contract>> Contracte;

public:

    ///CONSTRUCTOR FARA PARAMETRII
    Dosar() {
        numardosare = 0;
    }

    /// GETTER - nu este folosit
    unsigned long long getNumardosare() const {
        return numardosare;
    }

    /// SETTER - nu este folosit
    void setNumardosare(unsigned long long numardosare_) {
        numardosare_ = Contracte.size();
        Dosar::numardosare = numardosare_;
    }

    /// ADAUGARE CONTRACT
    static void addContract (const std::shared_ptr<Contract> &contract) {
        Contracte.push_back(contract);
    }

    /// GETTER CONTRACT
    static const std::vector<std::shared_ptr<Contract>> &getContracte() {
        return Contracte;
    }

    /// EXCEPTIE 1
    static void tratareexceptie1(const std::shared_ptr<Contract> &ctr) {
        int ok = 2;
        for(auto &contract:Dosar::getContracte()){
            if (contract->getNrContract() == ctr->getNrContract())
            {
                ok = 3;
                break;
            }
        }
        if (ok == 3) throw Exceptii();
    }

    /// EXCEPTIE 2
    static void tratareexceptie2() {
        int ok = 2;
        for(auto &contract:Dosar::getContracte()){
            if (contract->getType() == ContractType::ContractInchiriere)
            {
                ok = 3;
                break;
            }
        }
        if (ok == 2) throw ExceptiiDoi();
    }

    /// EXCEPTIE 3
    static void tratareexceptie3() {
        int ok = 2;
        for(auto &contract:Dosar::getContracte()){
            if (contract->getType() == ContractType::ContractVizionare)
            {
                ok = 3;
                break;
            }
        }
        if (ok == 2) throw ExceptiiDoi();
    }

    /// AFISARE CONTRACTE INCHIRIERE SAU CONTRACTE VIZIONARE
    static void showContracteInchiriere() {
        for (auto &contract: Dosar::getContracte()) {
            if (contract->getType() == ContractType::ContractInchiriere) {
                auto contractInchiriere = std::dynamic_pointer_cast<ContractInchiriere>(contract);
                contractInchiriere -> afisareContractInchiriere();
                std::cout << '\n' << contract;
                ContractInchiriere::plata(std::dynamic_pointer_cast<ContractInchiriere>(contract));
                std::cout << '\n' << '\n';
            }
        }
    }
    static void showContracteVizionare() {
        for (auto &contract: Dosar::getContracte()) {
            if (contract->getType() == ContractType::ContractVizionare) {
                auto contractVizionare = std::dynamic_pointer_cast<ContractVizionare>(contract);
                contractVizionare -> afisareContractVizionare();
                std::cout << '\n' << contract;
                ContractVizionare::plata(std::dynamic_pointer_cast<ContractVizionare>(contract));
                std::cout << '\n' << '\n';
            }
        }
    }

    /// AFISAREA TUTUROR CONTRACTELOR
    static void showAll () {
        Dosar::showContracteVizionare();
        Dosar::showContracteInchiriere();
    }

    /// PROFIT FIRMA
    static void profit(){
        int suma = 0;
        for (auto &contract : Dosar::getContracte()){
            if (contract->getType() == ContractType::ContractVizionare){
                    std::shared_ptr<ContractVizionare> p = std::dynamic_pointer_cast<ContractVizionare>(contract);
                    suma += p->getValoare() *p->getNrOre();
            }
            if (contract->getType() == ContractType::ContractInchiriere){
                std::shared_ptr<ContractInchiriere> p = std::dynamic_pointer_cast<ContractInchiriere>(contract);
                suma += p->getValoare() *p->getPerioada();
            }
        }
        std::cout << "Valoarea incasata de firma este " << suma << " euro. ";
        std::cout << '\n';
    }
};

/// SHARED POINTER LA CONTRACTE
std::vector<std::shared_ptr<Contract>> Dosar::Contracte;


int main() {

    int comanda, ok = 1;

    while (ok){
        std::cout << "MENIU" << '\n';
        std::cout << "1. Adaugare contract inchiriere" << '\n';
        std::cout << "2. Adaugare contract vizionare" << '\n';
        std::cout << "3. Afisare contracte inchiriere, inclusiv suma de bani necesara" << '\n';
        std::cout << "4. Afisare contracte vizionare, inclusiv suma de bani necesara" << '\n';
        std::cout << "5. Afisare suma totala incasata de firma" << '\n';
        std::cout << "6. Afisarea tuturor contractelor in functie de tip" << '\n' << '\n';
        std::cout << "Introdu numarul comenzii: ";
        std::cin >> comanda;
        if (comanda == 1){
            std::shared_ptr<Contract> ptr = std::make_shared<ContractInchiriere>();
            try {
                std::cin >> *std::dynamic_pointer_cast<ContractInchiriere>(ptr);
                Dosar::tratareexceptie1(ptr);
                Dosar::addContract(ptr);
            }
            catch (const Exceptii &e) {
                std::cout << '\n' << e.what() << '\n';
            }
            std::cout << '\n';
        }
        else if (comanda == 2) {
            std::shared_ptr<Contract> ptr = std::make_shared<ContractVizionare>();
            try {
                std::cin >> *std::dynamic_pointer_cast<ContractVizionare>(ptr);
                Dosar::tratareexceptie1(ptr);
                Dosar::addContract(ptr);
            }
            catch (Exceptii& e) {
                std::cout << '\n' << e.what() << '\n';
            }
            std::cout << '\n';
        }
        else if (comanda == 3){
            try {
                Dosar::tratareexceptie2();
                Dosar::showContracteInchiriere();
                std::cout << '\n';
            }
            catch (ExceptiiDoi& e) {
                std::cout << '\n' << e.what() << '\n';
            }
            std::cout<<'\n';
        }
        else if (comanda == 4) {
            try {
                Dosar::tratareexceptie3();
                Dosar::showContracteVizionare();
                std::cout << '\n';
            }
            catch (ExceptiiDoi& e) {
                std::cout << '\n' << e.what() << '\n';
            }
            std::cout<<'\n';
        }
        else if (comanda == 5) {
            Dosar::profit();
            std::cout << '\n';
        }
        else if (comanda == 6){
            Dosar::showAll();
            std::cout << '\n';
        } else
        {
            std::cout << "Comanda nu exista!";
        }

        std::cout << "Daca doriti sa opriti rularea programului, tastati 0!" << '\n';
        std::cout << "Daca doriti sa rulati comenzi in continuare, tastati 1!" << '\n';
        std::cout << "Raspuns: ";
        std::cin >> ok;
        std::cout << '\n';
    }

    return 0;
}
