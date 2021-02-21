#include <iostream>
#include <string>
#include <utility>
#define KAP 1000


template<typename TipKljuca, typename TipVrijednosti>
class Mapa
{
public:
    Mapa() {};
    virtual ~Mapa() {};
    virtual TipVrijednosti& operator[](const TipKljuca& kljuc)=0;
    virtual const TipVrijednosti& operator[](const TipKljuca& kljuc)const=0;
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca& kljuc)=0;
};

template<typename TipKljuca, typename TipVrijednosti>
class NizMapa: public Mapa<TipKljuca, TipVrijednosti>
{
    int brel, kapacitet;
    TipVrijednosti p;
    std::pair<TipKljuca, TipVrijednosti>*par=nullptr;
    void povecaj()
    {
        kapacitet*=2;
        std::pair<TipKljuca,TipVrijednosti>*pomocni=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0; i<brel; i++) {
            pomocni[i].first=par[i].first;
            pomocni[i].second=par[i].second;
        }
        delete[]par;
        par=pomocni;
        pomocni=nullptr;
    }
public:

    NizMapa():kapacitet(KAP),brel(0), par(new std::pair<TipKljuca,TipVrijednosti>[kapacitet]),p(TipVrijednosti()) {}
    ~NizMapa()
    {
        delete []par;
    }

    NizMapa(const NizMapa<TipKljuca, TipVrijednosti>&nm): kapacitet(nm.kapacitet),brel(nm.brel), par(new std::pair<TipKljuca,TipVrijednosti>[kapacitet])
    {
        for(int i=0; i<brel; i++) {
            par[i].first=nm.par[i].first;
            par[i].second=nm.par[i].second;
        }
    }

    NizMapa<TipKljuca, TipVrijednosti>&operator=(const NizMapa<TipKljuca,TipVrijednosti>&nm)
    {
        if(this==&nm) return *this;
        delete[] par;
        kapacitet=nm.kapacitet;
        brel=nm.brel;
        par=new std::pair<TipKljuca,TipVrijednosti>[kapacitet];

        for(int i=0; i<brel; i++) {
            par[i].first=nm.par[i].first;
            par[i].second=nm.par[i].second;
        }
        return *this;
    }

    TipVrijednosti& operator[](const TipKljuca &kljuc)
    {
        for(int i=0; i<brel; i++) {
            if(par[i].first==kljuc) return par[i].second;
        }

        if(brel==kapacitet) povecaj();
        par[brel]=std::pair<TipKljuca,TipVrijednosti>(kljuc,TipVrijednosti());
        return par[brel++].second;
    }

    const TipVrijednosti& operator[](const TipKljuca& kljuc)const
    {
        for(int i=0; i<brel; i++) {
            if(par[i].first==kljuc) return par[i].second;
        }
        return p;
    }

    int brojElemenata()const
    {
        return brel;
    }

    void obrisi(const TipKljuca &kljuc)
    {
        for(int i=0; i<brel; i++) {
            if(par[i].first==kljuc) {
                par[i].first=par[brel-1].first;
                par[i].second=par[brel-1].second;
                brel--;
                return;
            }
        }
        throw("Nije pronadjen element\n");
    }
    void obrisi()
    {
        brel=0;
    }
};


int main()
{

    NizMapa<std::string, std::string>glavni_gradovi;
    glavni_gradovi["Bosna i Hercegovina"]="Sarajevo";
    glavni_gradovi["Hrvatska"]="Zagreb";
    glavni_gradovi["Srbija"]="Beograd";

    std::cout << "Pripremna Zadaca Za Vjezbu 7, Zadatak 1";
    return 0;
}
