#ifndef TEMA3_GESTIONAREFARMACII_H
#define TEMA3_GESTIONAREFARMACII_H

#include "Farmacii.h"

#include <iostream>
#include <vector>
#include <memory>

template <class F>
class GestionareFramacii {
private:
    int numarFarmacii;
    vector<F> farmacii;

public:
    GestionareFramacii(){
        numarFarmacii = 0;
    }

    int getNumarFarmacii(){
        return numarFarmacii;
    }

    friend ostream& operator<<(ostream& os, GestionareFramacii& g){
        for(int i =0; i<g.farmacii.size(); i++)
            os << *g.farmacii[i] << "\n";
        return os;
    }

    void operator+=(F f){
        farmacii.push_back(f);
        numarFarmacii ++;
    }

    ~GestionareFramacii() = default;

};

template<>
class GestionareFramacii<FarmacieOnline>{
private:
    int numarFarmacii;
    vector<FarmacieOnline> farmacii;
    int sumaNumarVizitatori;

public:
    int suma() {
        int sumaNumarVizitatori = 0;
        for (auto &f : farmacii){
            sumaNumarVizitatori+=f.getNumarVizitatori();
        }
        return sumaNumarVizitatori;
    }

    friend ostream& operator<<(ostream& os, GestionareFramacii<FarmacieOnline>& g){
        for(int i =0; i<g.farmacii.size(); i++)
            os << g.farmacii[i] << "\n";
        return os;
    }

    void operator+=(FarmacieOnline f){
        farmacii.push_back(f);
        numarFarmacii ++;
    }
};


#endif
