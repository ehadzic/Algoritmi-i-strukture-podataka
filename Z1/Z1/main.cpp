#include <iostream>
#include <stdexcept>

template <typename Tip> //kopirano sa pripremne zadace 2
class Lista{
    
    public:
    
    Lista(){};
    virtual~Lista(){};
    virtual int brojElemenata()const=0;
    virtual Tip& trenutni()const=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip &el)=0;
    virtual void dodajIza(const Tip &el)=0;
    virtual Tip& operator[](int n)const=0;
    
};

template <typename Tip>
class DvostrukaLista : public Lista<Tip>{
  template<class DvostrukaLista>friend class Iterator;
  struct Cvor{
    Tip element;
    Cvor *sljedeci;
    Cvor *prethodniel;
  };
  int duzina;
  Cvor *pocetakListe;
  Cvor *tekuci;
  Cvor *krajListe;
  
  public:
  DvostrukaLista():duzina(0),pocetakListe(nullptr),tekuci(nullptr),krajListe(nullptr){}
  
  ~DvostrukaLista(){
      Cvor *obrisi;
      tekuci=pocetakListe;
      while(tekuci!=nullptr){
          obrisi=tekuci;
          tekuci=tekuci->sljedeci;
          obrisi->sljedeci=nullptr;
          delete obrisi;
      }
  }
  
  DvostrukaLista(const DvostrukaLista<Tip>&jl):duzina(jl.duzina){
    Cvor *p(jl.pocetakListe);
    pocetakListe=nullptr;
    krajListe=nullptr;
    for(int i=0; i<duzina; i++){
      Cvor *novi=new Cvor();
      novi->element=p->element;
      novi->sljedeci=nullptr;
      novi->prethodniel=nullptr;
      if(pocetakListe==nullptr){
        pocetakListe=novi;
        krajListe=novi;
        tekuci=novi;
      }else{
        tekuci->sljedeci=novi;
        novi->prethodniel=tekuci;
        tekuci=novi;
        krajListe=novi;
      }
      p=p->sljedeci;
      
    }
  }
  
  int brojElemenata()const override{
    return duzina;
  }
  
  Tip &trenutni() const override{
    return tekuci->element;
  }
  
  bool prethodni() override{
    if(duzina==0) throw std::domain_error("Lista je prazna!");
    if(tekuci==pocetakListe) return false;
    Cvor *p(pocetakListe);
    while(p->sljedeci!=tekuci){
      p=p->sljedeci;
      
    }
    tekuci=p;
    return true;
    
  }
  
  bool sljedeci() override{
    if(duzina==0) throw std::domain_error("Lista je prazna!");
    if(tekuci->sljedeci==nullptr) return false;
    tekuci=tekuci->sljedeci;
    return true;
  }
  
  
  void pocetak() override{
    if(duzina==0) throw std::domain_error("Lista je prazna!");
    tekuci=pocetakListe;
  }
  
  void kraj() override{
    if(duzina==0) throw std::domain_error("Lista je prazna!");
    tekuci=krajListe;
  }
  
  DvostrukaLista<Tip>& operator=(const DvostrukaLista<Tip>&jl){
    if(this==&jl) return *this;
    
    //tijelo destruktora
      Cvor *obrisi;
      tekuci=pocetakListe;
      while(tekuci!=nullptr){
          obrisi=tekuci;
          tekuci=tekuci->sljedeci;
          obrisi->sljedeci=nullptr;
          delete obrisi;
      }
    //tijelo konstruktora
    duzina=jl.duzina;
    Cvor *p(jl.pocetakListe);
    pocetakListe=nullptr;
    krajListe=nullptr;
    for(int i=0; i<duzina; i++){
      Cvor *novi=new Cvor();
      novi->element=p->element;
      novi->sljedeci=nullptr;
      novi->prethodniel=nullptr;
      if(pocetakListe==nullptr){
        pocetakListe=novi;
        krajListe=novi;
        tekuci=novi;
      }else{
        tekuci->sljedeci=novi;
        novi->prethodniel=tekuci;
        tekuci=novi;
        krajListe=novi;
      }
      p=p->sljedeci;
      
    }
    return *this;
    
    
  }
  
  
  void obrisi()override{
    if(duzina==0){
      pocetakListe==nullptr;
      krajListe=nullptr;
    }
    
    else if(duzina==1){
      delete tekuci;
      pocetakListe=nullptr;
      krajListe=nullptr;
      duzina--;
    }
    
    else if(tekuci==pocetakListe && duzina!=1){
      Cvor *novi(tekuci);
      tekuci=tekuci->sljedeci;
      delete novi;
      pocetakListe=tekuci;
      duzina--;
    }
    else if(tekuci->sljedeci==nullptr){
      Cvor *obrisi(tekuci);
      prethodni();
      tekuci->sljedeci=nullptr;
      delete obrisi;
      duzina--;
    }else{
      Cvor *obrisi(tekuci);
      Cvor *p(pocetakListe);
      while(p->sljedeci!=tekuci) p=p->sljedeci;
      sljedeci();
      delete obrisi;
      p->sljedeci=tekuci;
      tekuci->prethodniel=p;
      duzina--;
    }
    
    
  }
  
  void dodajIspred(const Tip &el)override{
    if(duzina==0){
      pocetakListe=new Cvor;
      pocetakListe->element=el;
      pocetakListe->sljedeci=nullptr;
      pocetakListe->prethodniel=nullptr;
      tekuci=pocetakListe;
      krajListe=pocetakListe;
      duzina++;
    }else{
      Cvor *novi=new Cvor;
      novi->element=el;
      if(tekuci==pocetakListe){
        novi->sljedeci=tekuci;
        pocetakListe=novi;
        tekuci->prethodniel=novi;
      }else{
        tekuci->prethodniel->sljedeci=novi;
        novi->prethodniel=tekuci->prethodniel;
        novi->sljedeci=tekuci;
        tekuci->prethodniel=novi;
      }
      duzina++;
      novi=nullptr;
      
    }
  }
  
  void dodajIza(const Tip &el) override{
    if(duzina==0){
      pocetakListe=new Cvor;
      pocetakListe->element=el;
      tekuci=pocetakListe;
      krajListe=pocetakListe;
      tekuci->sljedeci=nullptr;
      tekuci->prethodniel=nullptr;
      duzina++;
    }else{
      Cvor *novi=new Cvor;
      novi->element=el;
      if(tekuci==pocetakListe && duzina==1){
        tekuci->sljedeci=novi;
        novi->prethodniel=tekuci;
        novi->sljedeci=nullptr;
        krajListe=novi;
      }
      else if(tekuci->sljedeci==nullptr){
        tekuci->sljedeci=novi;
        novi->prethodniel=tekuci;
        novi->sljedeci=nullptr;
        krajListe=novi;
      }else{
        Cvor *p(tekuci->sljedeci);
        tekuci->sljedeci=novi;
        novi->prethodniel=tekuci;
        novi->sljedeci=p;
        p->prethodniel=novi;
      }
      duzina++;
      novi=nullptr;
    }
    
  }
  
  Tip &operator[](int n)const{
    if(n<0 || n>duzina) throw("Izvan opsega!");
    Cvor *klizi=pocetakListe;
    for(int i=0; i<n; i++){
      klizi=klizi->sljedeci;
    }
    
    return klizi->element;
  }
    
};

template <typename Tip>
class Iterator{
  const DvostrukaLista<Tip>*dvLista;
  typename DvostrukaLista<Tip>::Cvor *tekuci;
  
  public:
  
  Iterator(const DvostrukaLista<Tip>&dl):tekuci(dl.tekuci){}
  Iterator(const Lista<Tip>&l): dvLista((DvostrukaLista<Tip>*)&l),tekuci((*dvLista).tekuci){}
  void pocetak(){
    if(dvLista->duzina==0) throw("Lista je prazna");
    tekuci=dvLista->pocetakListe;
  }
  
  void kraj(){
    if(dvLista->duzina==0) throw("Lista je prazna");
    tekuci=dvLista->krajListe;
  }
  
  bool sljedeci(){
    if(dvLista->duzina==0) throw("Lista je prazna");
    if(tekuci->sljedeci==nullptr) return false;
    tekuci=tekuci->sljedeci;
    return true;
    
  }
  
  bool prethodni(){
    if(dvLista->duzina==0) throw("Lista je prazna");
    if(tekuci->prethodniel==nullptr) return false;
    tekuci=tekuci->prethodniel;
    return true;
  }
  
  Tip trenutni(){
    if(dvLista->duzina==0) throw("Lista je prazna");
    return tekuci->element;
  }
  
  
  
};


template <typename Tip>
Tip dajMaksimum(const Lista<Tip>&n){
  Iterator<Tip>it(n);
  it.pocetak();
  
  Tip maksimum(it.trenutni());
  while(it.sljedeci()){
    if(maksimum<it.trenutni()){
      maksimum=it.trenutni();
    }
    return maksimum;
  }
  
}

void TestDajMaksimum(){
  Lista<int>*l;
  l=new DvostrukaLista<int>;
  for(int i=0; i<100;i++){
    l->dodajIspred(i);
    
  }
  
  std::cout<<dajMaksimum(*l);
  delete l;
  std::cout<<"Uspjesno testiran dajMaksimum!"<<std::endl;
}

void TestKopirajucegKonstruktora(){
  DvostrukaLista<int>l1;
  auto l2(l1);
  DvostrukaLista<char>l3;
  DvostrukaLista<char>l4(l3);
  std::cout<<"Uspjesno testiran kopirajuci konstruktor!";
}

void TestDodajIspred(){
  DvostrukaLista<int>l1;
  l1.dodajIspred(8);
  l1.dodajIspred(3);
  DvostrukaLista<int>l2;
  l2.dodajIspred(14);
  std::cout<<l1.brojElemenata()<<" "<<l2.brojElemenata()<<std::endl;
  
  
}

void TestDodajIza(){
  DvostrukaLista<int>l1;
  l1.dodajIza(10);
  l1.dodajIza(5);
  std::cout<<l1.brojElemenata()<<std::endl;
  
  
}


void TestMetodeBrojElemenata(){
  DvostrukaLista<int>l1;
  std::cout<<l1.brojElemenata()<<std::endl;
  l1.dodajIspred(1);
  std::cout<<l1.brojElemenata()<<std::endl;
  
}

void TestMetodeTrenutni(){
  DvostrukaLista<int>l1;
  l1.dodajIspred(1);
  l1.dodajIza(2);
  std::cout<<l1.trenutni();
  
}


void TestMetodePrethodni(){
  DvostrukaLista<int>l1;
  l1.dodajIza(6);
  l1.dodajIza(100);
  if(l1.prethodni()){
    std::cout<<"Uspjesno testirano"<<std::endl;
  }
  
}

void TestMetodeSljedeci(){
  DvostrukaLista<int>l1;
  l1.dodajIza(6);
  l1.dodajIza(100);
  if(l1.sljedeci()){
    std::cout<<"Uspjesno testirano"<<std::endl;
  }
  
}

void TestMetodePocetak(){
  DvostrukaLista<int>l1;
  l1.dodajIza(10);
  l1.dodajIza(80);
  l1.pocetak();
  std::cout<<l1.trenutni()<<std::endl;
  }
  
  
  void TestMetodeKraj(){
  DvostrukaLista<int>l1;
  l1.dodajIza(10);
  l1.dodajIza(80);
  l1.kraj();
  std::cout<<l1.trenutni()<<std::endl;
  }
  
  
  void TestMetodeObrisi(){
    DvostrukaLista<int>l1;
    std::cout<<l1.brojElemenata()<<" ";
    l1.dodajIspred('a');
    l1.dodajIspred('b');
    std::cout<<l1.brojElemenata()<<" ";
    l1.obrisi();
    std::cout<<l1.brojElemenata()<<std::endl;
    
  }
  void TestOperatoraIndeks(){
    DvostrukaLista<int>l1;
    l1.dodajIza(1);
    l1.dodajIza(2);
    std::cout<<l1[0]<<std::endl;
    
  }
  





int main() {
  
  Lista<int>*l;
  l=new DvostrukaLista<int>;
  for(int i=0; i<10000; i++){
    l->dodajIspred(i);
  }
  
  std::cout<<dajMaksimum(*l);
  delete l;
  
    std::cout << "Zadaća 1, Zadatak 1";
    return 0;
}
