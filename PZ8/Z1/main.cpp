#include <iostream>
#include <ctime>
using namespace std;

template <typename T1, typename T2>
struct Cvor{
    T1 prvi;
    T2 drugi;
    Cvor<T1,T2>* desno=nullptr;
    Cvor<T1,T2>* lijevo=nullptr;
    Cvor<T1,T2>*roditelj=nullptr;
    
};

template <typename T1, typename T2>
struct par{
    T1 prvi;
    T2 drugi;
};

template <typename T1, typename T2>
class Mapa{
    public:
    Mapa<T1,T2>(){}
    virtual ~Mapa(){}
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const T1 &kljuc)=0;
    virtual T2 operator[] (T1 n)const=0;
    virtual T2 &operator[] (T1 n)=0;
    
};

template <typename T1, typename T2>
class NizMapa : public Mapa<T1,T2>{
    par<T1,T2>*mapa=nullptr;
    int broj_el=0;
    int kapacitet=500;
    
    public:
    
    NizMapa(): broj_el(0){
        mapa=new par<T1,T2>[kapacitet];
    }
    
    ~NizMapa(){
        delete[] mapa;
    }
    
    NizMapa(const NizMapa &m);
    NizMapa(NizMapa &&m);
    int brojElemenata()const{
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
NizMapa<T1,T2>::NizMapa(const NizMapa<T1,T2>&m){
    kapacitet=m.kapacitet;
    mapa=new par<T1,T2>[kapacitet];
    for(int i=0; i<m.brojElemenata(); i++){
        mapa[i]=m.mapa[i];
        broj_el++;
    }
}

template <typename T1, typename T2>
NizMapa<T1,T2>::NizMapa(NizMapa<T1,T2> &&m){
    if(this==&m) return;
    mapa=m.mapa;
    broj_el=m.brojElemenata();
    kapacitet=m.kapacitet;
    
}


template <typename T1, typename T2>
void NizMapa<T1,T2>::obrisi(){
    delete[] mapa;
    kapacitet=100;
    mapa=new par<T1,T2>[kapacitet];
    broj_el=0;
}

template <typename T1, typename T2>
void NizMapa<T1,T2>::obrisi(const T1 &kljuc){
    for(int i=0; i<broj_el; i++){
        if(mapa[i].prvi==kljuc){
            for(int j=i; j<broj_el-1; j++) mapa[j]=mapa[j+1];
        broj_el--;
        }
    }
    
}

template <typename T1, typename T2>
T2 NizMapa<T1,T2>::operator[] (T1 n) const{
    for(int i=0; i<broj_el; i++){
        if(mapa[i].prvi==n){
            return mapa[i].drugi;
        }
    }
    return T2();
}

template <typename T1, typename T2>
T2 &NizMapa<T1,T2>::operator[] (T1 n){
     for(int i=0; i<broj_el; i++){
        if(mapa[i].prvi==n){
            return mapa[i].drugi;
        }
    }
    
    if(broj_el==kapacitet){
        kapacitet*=2;
        par<T1,T2> *novi=new par<T1,T2>[kapacitet];
        for(int j=0; j<broj_el; j++){
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
NizMapa<T1,T2> &NizMapa<T1,T2>::operator=(const NizMapa &m){
    if(this==&m) return *this;
    delete[] mapa;
    kapacitet=m.kapacitet;
    mapa=new par<T1,T2>[kapacitet];
    
    for(int i=0; i<m.brojElemenata(); i++){
        mapa[i]=m.mapa[i];
    }
    broj_el=m.broj_el;
    return *this;
    
}

template <typename T1, typename T2>
NizMapa<T1,T2> &NizMapa<T1,T2>::operator=(NizMapa &&m){
    if(this==&m) return *this;
    delete[] mapa;
    mapa=m.mapa;
    broj_el=m.broj_el;
    kapacitet=m.kapacitet;
    return *this;
}

template <typename T1, typename T2>
class BinStabloMapa: public Mapa<T1,T2>{
    Cvor<T1,T2>*korijen;
    int broj_el;
    public:
    BinStabloMapa(): korijen(nullptr), broj_el(0){}
    ~BinStabloMapa(){this->obrisi();}
    BinStabloMapa(const BinStabloMapa &b);
    BinStabloMapa(BinStabloMapa &&b);
    int brojElemenata()const {return broj_el;}
    void obrisi();
    void obrisi(const  T1 &k);
    T2 &operator [](T1 k);
    T2 operator [](T1 k) const;
    BinStabloMapa &operator = (const BinStabloMapa &b);
    BinStabloMapa &operator=(BinStabloMapa &&b);
    void ppkopiraj(Cvor<T1,T2>* c1, Cvor<T1,T2>* &c2, Cvor<T1,T2>* pret=nullptr);
    
};

template <typename T1, typename T2>
BinStabloMapa<T1,T2>::BinStabloMapa(const BinStabloMapa &b){
    broj_el=b.broj_el;
    ppkopiraj(b.korijen, korijen);
}


template <typename T1, typename T2>
BinStabloMapa<T1,T2>::BinStabloMapa(BinStabloMapa &&b){
    broj_el=b.broj_el;
    korijen=b.korijen;
}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>::obrisi(const T1 &k){
    Cvor<T1,T2> *p=korijen, *roditelj=nullptr;
    while(p!=nullptr && k!=p->prvi){
        roditelj=p;
        if(k<p->prvi) p=p->lijevo;
        else p=p->desno;
    }
    if(p==nullptr) return;
    Cvor<T1,T2>*m;
    if(p->lijevo==nullptr) m=p->desno;
    else{
        if(p->desno==nullptr) m=p->lijevo;
        else{
            Cvor<T1,T2> *pm=p, *temp;
            m=p->lijevo;
            temp=m->desno;
            while(temp!=nullptr){
                pm=m;
                m=temp;
                temp=m->desno;
                
            }
            if(pm!=p){
                pm->desno=m->lijevo;
                m->lijevo=p->lijevo;
            }
            m->desno=p->desno;
            
        }
    }
    if(roditelj==nullptr) korijen=m;
    else{
        if(p==roditelj->lijevo) roditelj->lijevo=m;
        else roditelj->desno=m;
    }
    delete p;
    broj_el--;
    
    
}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>::obrisi(){
    while(korijen!=nullptr) obrisi(korijen->prvi);
}

template <typename T1, typename T2>
T2 BinStabloMapa<T1,T2>::operator [](T1 k)const{
    Cvor<T1,T2> *temp=korijen;
    while(temp!=nullptr && k!=temp->prvi){
        if(k<temp->prvi) temp=temp->lijevo;
        else temp=temp->desno;
    }
    if(temp==nullptr) return T2();
    return temp->drugi;
    
}

template <typename T1, typename T2>
T2 &BinStabloMapa<T1,T2>::operator [](T1 k){
    Cvor<T1,T2> *temp=korijen;
    while(temp!=nullptr && k!=temp->prvi){
        if(k<temp->prvi) temp=temp->lijevo;
        else temp=temp->desno;
    }
    
    if(temp==nullptr){
        temp=new Cvor<T1,T2>();
        broj_el++;
        temp->prvi=k;
        temp->drugi=T2();
        Cvor<T1,T2>*x=korijen, *y=nullptr;
        while(x!=nullptr){
            y=x;
            if(temp->prvi < x->prvi) x=x->lijevo;
            else x=x->desno;
        }
        
        if(y==nullptr) korijen=temp;
        else{
            if(temp->prvi < y->prvi) y->lijevo=temp;
            else y->desno=temp;
            temp->roditelj=y;
        }
        
    }
    return temp->drugi;
    
}

template <typename T1, typename T2>
BinStabloMapa<T1,T2> &BinStabloMapa<T1,T2>::operator=(BinStabloMapa &&b){
    if(this==&b) return *this;
    this->obrisi();
    korijen=b.korijen;
    broj_el=b.broj_el;
    return *this;
}

template <typename T1, typename T2>
BinStabloMapa<T1,T2> &BinStabloMapa<T1,T2>::operator=(const BinStabloMapa &b){
    if(this==&b) return *this;
    this->obrisi();
    ppkopiraj(b.korijen, korijen);
    broj_el=b.broj_el;
    return *this;
}

template <typename T1, typename T2>
void BinStabloMapa<T1,T2>:: ppkopiraj(Cvor<T1,T2>* c1, Cvor<T1,T2>* &c2, Cvor<T1,T2>* pret){
    if(c1!=nullptr){
        c2=new Cvor<T1,T2>();
        c2->prvi=c1->prvi;
        c2->drugi=c1->drugi;
        c2->roditelj=pret;
        ppkopiraj(c1->lijevo, c2->lijevo, c2);
        ppkopiraj(c1->desno, c2->desno, c2);
    }
}











int main() {
    
   {
       clock_t vrijeme1=clock();
       BinStabloMapa<int, int>m;
       int vel(1000);
       for(int i=0; i<vel; i++){
           m[rand()%(3*vel)-vel]=i;
       }
       
       for(int i(-vel); i<vel; i++){
           m[i]=i;
       }
       
       for(int i(-vel); i<vel; i++){
           m.obrisi(i);
       }
       cout<<"OK";
       clock_t vrijeme2=clock();
       int uvrijeme=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000);
       std::cout<<"Vrijeme izvrsenja: "<<uvrijeme<<" ms."<<std::endl;
       
       
   }
   
   {
       clock_t vrijeme1=clock();
       NizMapa<int, int>m1;
       int vel2(1000);
       
       for(int i=0; i<vel2; i++){
           m1[rand()%(3*vel2)-vel2]=i;
       }
       
       for(int i(-vel2); i<vel2; i++){
           m1[i]=i;
       }
       
       for(int i(-vel2); i<vel2; i++){
           m1.obrisi(i);
       }
       cout<<"OK";
       clock_t vrijeme2=clock();
       int uvrijeme=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000);
       std::cout<<"Vrijeme izvrsenja: "<<uvrijeme<<" ms."<<std::endl;
       
   }
    
    std::cout << "Pripremna Zadaca Za Vjezbu 8, Zadatak 1";
    return 0;
}
