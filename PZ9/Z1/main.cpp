#include <iostream>
#include <ctime>
#include <string>

unsigned int TheHash(int ulaz, unsigned int max){
    return ulaz+100;
}

using namespace std;

template <typename T1, typename T2>
struct Cvor {
    T1 prvi;
    T2 drugi;
    Cvor<T1,T2>* desno=nullptr;
    Cvor<T1,T2>* lijevo=nullptr;
    Cvor<T1,T2>*roditelj=nullptr;

};

template <typename T1, typename T2>
struct par {
    T1 prvi=T1();
    T2 drugi=T2();
};

template <typename T1, typename T2>
class Mapa
{
public:
    Mapa<T1,T2>() {}
    virtual ~Mapa() {}
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const T1 &kljuc)=0;
    virtual T2 operator[] (T1 n)const=0;
    virtual T2 &operator[] (T1 n)=0;

};

template <typename T1, typename T2>
class NizMapa : public Mapa<T1,T2>
{
    par<T1,T2>*mapa=nullptr;
    int broj_el=0;
    int kapacitet=500;

public:

    NizMapa(): broj_el(0)
    {
        mapa=new par<T1,T2>[kapacitet];
    }

    ~NizMapa()
    {
        delete[] mapa;
    }

    NizMapa(const NizMapa &m);
    NizMapa(NizMapa &&m);
    int brojElemenata()const
    {
        return broj_el;
    }

    void obrisi();
    void obrisi(const T1 &kljuc);
    T2 operator[](T1 n)const;
    T2 &operator[](T1 n);
    NizMapa& operator=(const NizMapa &m);
    NizMapa& operator=(NizMapa &&m);


};

template <typename T1, typename T2>
NizMapa<T1,T2>::NizMapa(const NizMapa<T1,T2>&m)
{
    kapacitet=m.kapacitet;
    mapa=new par<T1,T2>[kapacitet];
    for(int i=0; i<m.brojElemenata(); i++) {
        mapa[i]=m.mapa[i];
        broj_el++;
    }
}

template <typename T1, typename T2>
NizMapa<T1,T2>::NizMapa(NizMapa<T1,T2> &&m)
{
    if(this==&m) return;
    mapa=m.mapa;
    broj_el=m.brojElemenata();
    kapacitet=m.kapacitet;

}


template <typename T1, typename T2>
void NizMapa<T1,T2>::obrisi()
{
    delete[] mapa;
    kapacitet=100;
    mapa=new par<T1,T2>[kapacitet];
    broj_el=0;
}

template <typename T1, typename T2>
void NizMapa<T1,T2>::obrisi(const T1 &kljuc)
{
    for(int i=0; i<broj_el; i++) {
        if(mapa[i].prvi==kljuc) {
            for(int j=i; j<broj_el-1; j++) mapa[j]=mapa[j+1];
            broj_el--;
        }
    }

}

template <typename T1, typename T2>
T2 NizMapa<T1,T2>::operator[] (T1 n) const
{
    for(int i=0; i<broj_el; i++) {
        if(mapa[i].prvi==n) {
            return mapa[i].drugi;
        }
    }
    return T2();
}

template <typename T1, typename T2>
T2 &NizMapa<T1,T2>::operator[] (T1 n)
{
    for(int i=0; i<broj_el; i++) {
        if(mapa[i].prvi==n) {
            return mapa[i].drugi;
        }
    }

    if(broj_el==kapacitet) {
        kapacitet*=2;
        par<T1,T2> *novi=new par<T1,T2>[kapacitet];
        for(int j=0; j<broj_el; j++) {
            novi[j]=mapa[j];
        }
        delete[] mapa;
        mapa=novi;
    }

    broj_el++;
    par<T1,T2> temp;
    temp.prvi=n;
    temp.drugi=T2();
    mapa[broj_el-1]=temp;
    return mapa[broj_el-1].drugi;

}

template <typename T1, typename T2>
NizMapa<T1,T2> &NizMapa<T1,T2>::operator=(const NizMapa &m)
{
    if(this==&m) return *this;
    delete[] mapa;
    kapacitet=m.kapacitet;
    mapa=new par<T1,T2>[kapacitet];

    for(int i=0; i<m.brojElemenata(); i++) {
        mapa[i]=m.mapa[i];
    }
    broj_el=m.broj_el;
    return *this;

}

template <typename T1, typename T2>
NizMapa<T1,T2> &NizMapa<T1,T2>::operator=(NizMapa &&m)
{
    if(this==&m) return *this;
    delete[] mapa;
    mapa=m.mapa;
    broj_el=m.broj_el;
    kapacitet=m.kapacitet;
    return *this;
}

template <typename T1, typename T2>
class BinStabloMapa: public Mapa<T1,T2>
{
    Cvor<T1,T2>*korijen;
    int broj_el;
public:
    BinStabloMapa(): korijen(nullptr), broj_el(0) {}
    ~BinStabloMapa()
    {
        this->obrisi();
    }
    BinStabloMapa(const BinStabloMapa &b);
    BinStabloMapa(BinStabloMapa &&b);
    int brojElemenata()const
    {
        return broj_el;
    }
    void obrisi();
    void obrisi(const  T1 &k);
    T2 &operator [](T1 k);
    T2 operator [](T1 k) const;
    BinStabloMapa &operator = (const BinStabloMapa &b);
    BinStabloMapa &operator=(BinStabloMapa &&b);
    void ppkopiraj(Cvor<T1,T2>* c1, Cvor<T1,T2>* &c2, Cvor<T1,T2>* pret=nullptr);

};

template <typename T1, typename T2>
BinStabloMapa<T1,T2>::BinStabloMapa(const BinStabloMapa &b)
{
    broj_el=b.broj_el;
    ppkopiraj(b.korijen, korijen);
}


template <typename T1, typename T2>
BinStabloMapa<T1,T2>::BinStabloMapa(BinStabloMapa &&b)
{
    broj_el=b.broj_el;
    korijen=b.korijen;
}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>::obrisi(const T1 &k)
{
    Cvor<T1,T2> *p=korijen, *roditelj=nullptr;
    while(p!=nullptr && k!=p->prvi) {
        roditelj=p;
        if(k<p->prvi) p=p->lijevo;
        else p=p->desno;
    }
    if(p==nullptr) return;
    Cvor<T1,T2>*m;
    if(p->lijevo==nullptr) m=p->desno;
    else {
        if(p->desno==nullptr) m=p->lijevo;
        else {
            Cvor<T1,T2> *pm=p, *temp;
            m=p->lijevo;
            temp=m->desno;
            while(temp!=nullptr) {
                pm=m;
                m=temp;
                temp=m->desno;

            }
            if(pm!=p) {
                pm->desno=m->lijevo;
                m->lijevo=p->lijevo;
            }
            m->desno=p->desno;

        }
    }
    if(roditelj==nullptr) korijen=m;
    else {
        if(p==roditelj->lijevo) roditelj->lijevo=m;
        else roditelj->desno=m;
    }
    delete p;
    broj_el--;


}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>::obrisi()
{
    while(korijen!=nullptr) obrisi(korijen->prvi);
}

template <typename T1, typename T2>
T2 BinStabloMapa<T1,T2>::operator [](T1 k)const
{
    Cvor<T1,T2> *temp=korijen;
    while(temp!=nullptr && k!=temp->prvi) {
        if(k<temp->prvi) temp=temp->lijevo;
        else temp=temp->desno;
    }
    if(temp==nullptr) return T2();
    return temp->drugi;

}

template <typename T1, typename T2>
T2 &BinStabloMapa<T1,T2>::operator [](T1 k)
{
    Cvor<T1,T2> *temp=korijen;
    while(temp!=nullptr && k!=temp->prvi) {
        if(k<temp->prvi) temp=temp->lijevo;
        else temp=temp->desno;
    }

    if(temp==nullptr) {
        temp=new Cvor<T1,T2>();
        broj_el++;
        temp->prvi=k;
        temp->drugi=T2();
        Cvor<T1,T2>*x=korijen, *y=nullptr;
        while(x!=nullptr) {
            y=x;
            if(temp->prvi < x->prvi) x=x->lijevo;
            else x=x->desno;
        }

        if(y==nullptr) korijen=temp;
        else {
            if(temp->prvi < y->prvi) y->lijevo=temp;
            else y->desno=temp;
            temp->roditelj=y;
        }

    }
    return temp->drugi;

}

template <typename T1, typename T2>
BinStabloMapa<T1,T2> &BinStabloMapa<T1,T2>::operator=(BinStabloMapa &&b)
{
    if(this==&b) return *this;
    this->obrisi();
    korijen=b.korijen;
    broj_el=b.broj_el;
    return *this;
}

template <typename T1, typename T2>
BinStabloMapa<T1,T2> &BinStabloMapa<T1,T2>::operator=(const BinStabloMapa &b)
{
    if(this==&b) return *this;
    this->obrisi();
    ppkopiraj(b.korijen, korijen);
    broj_el=b.broj_el;
    return *this;
}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>:: ppkopiraj(Cvor<T1,T2>* c1, Cvor<T1,T2>* &c2, Cvor<T1,T2>* pret)
{
    if(c1!=nullptr) {
        c2=new Cvor<T1,T2>();
        c2->prvi=c1->prvi;
        c2->drugi=c1->drugi;
        c2->roditelj=pret;
        ppkopiraj(c1->lijevo, c2->lijevo, c2);
        ppkopiraj(c1->desno, c2->desno, c2);
    }
}


template<typename T1, typename T2>
class HashMapa : public Mapa<T1,T2>
{
    int kapacitet=100;
    int broj_el;
    par<T1,T2>* hmapa;
    unsigned int(*hash)(T1, unsigned int)=0;
public:
    HashMapa(): broj_el(0)
    {
        hmapa=new par<T1, T2>[kapacitet];
    }
    HashMapa(const HashMapa &h);
    HashMapa(HashMapa &&h);
    ~HashMapa()
    {
        delete[] hmapa;
    }
    int brojElemenata() const
    {
        return broj_el;
    }
    void obrisi();
    void obrisi(const T1 &kljuc);
    void definisiHashFunkciju(unsigned int (*fun)(T1, unsigned int))
    {
        hash=fun;
    }
    HashMapa &operator =(const HashMapa &h);
    HashMapa &operator =(HashMapa &&h);
    T2 &operator [](T1 k);
    T2 operator [](T1 k) const;
};
template <typename T1, typename T2>
HashMapa<T1, T2>::HashMapa(const HashMapa &h)
{
    kapacitet=h.kapacitet;
    broj_el=h.broj_el;
    hash=h.hash;
    hmapa=new par<T1, T2> [kapacitet];
    for(int i(0); i<kapacitet; i++) {
        hmapa[i]=h.hmapa[i];
    }
}
template <typename T1, typename T2>
HashMapa<T1, T2>:: HashMapa(HashMapa &&h)
{
    kapacitet=h.kapacitet;
    broj_el=h.broj_el;
    hmapa=h.hmapa;
    hash=h.hash;
}

template<typename T1, typename T2>
void HashMapa<T1, T2>::obrisi()
{
    delete[] hmapa;
    kapacitet=100;
    broj_el=0;
    hmapa=new par<T1, T2>[kapacitet];
}
template<typename T1, typename T2>
void HashMapa<T1, T2>::obrisi(const T1 &k)
{
    for(int i(0); i<kapacitet; i++) {
        if(hmapa[i].prvi==k) {
            for(int j(i); j<kapacitet-1; j++) {
                hmapa[j]=hmapa[j+1];
            }
            broj_el--;
        }
    }
}
template<typename T1, typename T2>
HashMapa<T1, T2> &HashMapa<T1,T2>::operator =(const HashMapa &h)
{
    if(this==&h) return *this;
    delete[] hmapa;
    kapacitet=h.kapacitet;
    broj_el=h.broj_el;
    hash=h.hash;
    hmapa=new par<T1, T2>[kapacitet];
    for (int i(0); i<kapacitet; i++) {
        hmapa[i]=h.hmapa[i];

    }
    return *this;
}
template<typename T1, typename T2>
HashMapa<T1, T2> &HashMapa<T1, T2>:: operator=(HashMapa &&h)
{
    if(this==&h) return *this;
    delete[] hmapa;
    kapacitet=h.kapacitet;
    broj_el=h.broj_el;
    hash=h.hash;
    hmapa=h.hmapa;
    return *this;
}

template<typename T1, typename T2>
T2 &HashMapa<T1,T2>::operator [] (T1 k)
{
    if(hash==0) throw ("Greska");
    for(int i(0); i<kapacitet; i++) {
        if(hmapa[i].prvi==k) return hmapa[i].drugi;
    }
    int indeks=hash(k,kapacitet);
    while(indeks<kapacitet && hmapa[indeks].prvi!=T1()) indeks++;
    if(indeks>=kapacitet) {
        par<T1,T2>* temp=new par<T1,T2>[kapacitet*2];
        for(int i(0); i<kapacitet; i++) {
            temp[i]=hmapa[i];
        }
        delete[] hmapa;
        kapacitet*=2;
        hmapa=temp;
    }
    broj_el++;
    hmapa[indeks].prvi=k;
    hmapa[indeks].drugi=T2();
    return hmapa[indeks].drugi;
}


template<typename T1, typename T2>
T2 HashMapa<T1,T2>::operator [] (T1 k) const
{

    if(hash==0) throw ("Greska");
    for(int i(0); i<kapacitet; i++) {
        if(hmapa[i].prvi==k) return hmapa[i].drugi;
    }
    return T2();

}




void test(){
    NizMapa<int, int> n;
    BinStabloMapa<int, int> b;
    HashMapa<int,int>h;
    h.definisiHashFunkciju(TheHash);
    clock_t t1=clock();
    for(int i(0); i<1000; i++){
        n[i]=rand();
    }
    
    clock_t t2=clock();
    std::cout<<"vrijeme generisanja 1000 cifri i dodavanje u nizMapu je: "<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<std::endl;
    t1=clock();
    for(int i(0); i<1000; i++){
        b[i]=rand();
    }
    t2=clock();
    std::cout<<"vrijeme generisanja 1000 cifri i dodavanje u BinStabloMapu je: "<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<std::endl;
    t1=clock();
    for(int i(0); i<1000; i++){
        h[i]=rand();
    }
    t2=clock();
    std::cout<<"vrijeme generisanja 1000 cifri i dodavanje u HashMapu je: "<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<std::endl;

    
}

















int main()
{

   

    std::cout << "Pripremna Zadaca Za Vjezbu 9, Zadatak 1";
    return 0;
}
