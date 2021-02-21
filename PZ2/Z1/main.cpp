#include <iostream>

template <typename Tip>
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
class NizLista : public Lista<Tip>{
    protected:
    int kapacitet;
    int duzina;
    int tekuci;
    Tip *L;
    
    public:
    NizLista(){
        kapacitet=0;
        duzina=0;
        tekuci=0;
        L=nullptr;
    }
    
    ~NizLista(){
        delete[]L;
        
    }
    
    NizLista(const NizLista<Tip> &niz):kapacitet(niz.kapacitet), duzina(niz.duzina), L(new Tip[niz.duzina]){
        std::copy(niz.L, niz.L+duzina-1,L);
    }
    
    
    NizLista<Tip>&operator=(const NizLista<Tip>&niz){
        if(this==&niz) return *this;
        delete []L;
        kapacitet=niz.kapacitet;
        duzina=niz.duzina;
        L=new Tip[kapacitet];
        std::copy(niz.L,niz.L+duzina-1,L);
        return *this;
    }
  
  int brojElemenata()const override{
      static int brel;
      brel++;
      return duzina;
  }
  
  Tip &trenutni()const override{
      static int trenutni;
      trenutni++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      return L[tekuci];
      
  }
  
  bool prethodni() override{
      static int prethodni;
      prethodni++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      if(tekuci==0) return false;
      tekuci--;
      return true;
  }
  
  bool sljedeci() override{
      
      static int sljedeci;
      sljedeci++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      if(tekuci==duzina-1) return false;
      tekuci++;
      return true;
  }
  
  void pocetak() override{
      static int pocetak;
      pocetak++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      tekuci=0;
  }
  
  void kraj() override{ // ????
      static int kraj;
      kraj++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      tekuci=duzina-1;
      
  }
  
  void obrisi() override{
      static int obrisi;
      obrisi++;
      if(duzina==0) throw std::domain_error("Lista je prezna!");
      for(int i=tekuci; i<duzina-1; i++){
        L[i]=L[i+1];
      }
      
      duzina--;
      if(duzina==0) tekuci=0;
      else if(tekuci>=duzina) tekuci--;
      
  }
  
  
  void dodajIspred(const Tip &el) override {
      static int dodajispred;
      dodajispred++;
      if(duzina==0){
          L=new Tip[1];
          L[0]=el;
          kapacitet++;
      } else{
          Tip *p = new Tip[kapacitet+1];
          for(int i=0; i<duzina; i++){
              p[i]=L[i];
          }
          
          for (int i=duzina; i>tekuci; i--){
              p[i]=p[i-1];
          }
          
          p[tekuci]=el;
          delete[] L;
          L=p;
          kapacitet++;
          tekuci=duzina;
      }
      
      duzina++;
      
  }
  
  void dodajIza(const Tip &el)override{
      static int dodajiza;
      dodajiza++;
      if(kapacitet==0){
          L=new Tip[1];
          L[0]=el;
          kapacitet++;
      }else{
          Tip *P=new Tip[kapacitet+1];
          for(int i=0; i<duzina; i++){
              P[i]=L[i];
          }
          
          for(int i=duzina; i>tekuci; i--){
              P[i]=P[i-1];
          }
          
          P[tekuci+1]=el;
          delete[] L;
          L=P;
          kapacitet++;
      }
      duzina++;
  }
  
  Tip &operator[](int i)const{
      if(i<0 || i>duzina) throw std::domain_error("Nedozvoljen opseg!");
      return L[i];
  }
  
    
};


template <typename Tip>
class JednostrukaLista : public Lista<Tip>{
    
    private:
    int duzina;
    
    struct Cvor{
      Tip element;
      Cvor *sljedeci;
    };
    
    Cvor *pocetakListe;
    Cvor *prethodniel;
    Cvor *tekuci;
    
    public:
    
    JednostrukaLista() : duzina(0), prethodniel(nullptr){}
    ~JednostrukaLista(){
        tekuci=pocetakListe;
        while (tekuci!=nullptr) {
            prethodniel=tekuci;
            tekuci=tekuci->sljedeci;
            prethodniel->sljedeci=nullptr;
            delete prethodniel;
        }
    }
    
    JednostrukaLista(const JednostrukaLista<Tip>&jl) : duzina(jl.duzina){
        Cvor *p(jl.pocetakListe);
        pocetakListe=nullptr;
        for(int i=0; i<duzina; i++){
            Cvor *novi=new Cvor();
            novi->element=p->element;
            novi->sljedeci=nullptr;
            if(pocetakListe==nullptr) pocetakListe=novi;
            else {
                prethodniel->sljedeci=novi;
                p=p->sljedeci;
            }
            if(i!=duzina-1) prethodniel=novi;
            
        }
    }
    
    int brojElemenata()const override{
        return duzina;
    }
    
    Tip &trenutni()const override{
        return tekuci->element;
    }
    
    bool prethodni() override{
        if(duzina==0) throw std::domain_error("Lista je prezna!");
        if(tekuci==pocetakListe) return false;
        tekuci=prethodniel;
        if(tekuci!=pocetakListe){
            prethodniel=pocetakListe;
            while(prethodniel->sljedeci!=tekuci){
                prethodniel=prethodniel->sljedeci;
            }
        }
        return true;
    }
    
    bool sljedeci() override{
        if(duzina==0) throw std::domain_error("Lista je prezna!");
        if(tekuci->sljedeci==nullptr) return false;
        prethodniel=tekuci;
        tekuci=tekuci->sljedeci;
        return true;
    }
    
    void pocetak() override{
        if(duzina==0) throw std::domain_error("Lista je prezna!");
        tekuci=pocetakListe;
    }
    
    void kraj()override{
        if(duzina==0) throw std::domain_error("Lista je prezna!");
        while (tekuci->sljedeci!=nullptr) {
            tekuci=tekuci->sljedeci;
        }
    }
    
    JednostrukaLista<Tip> &operator =(const JednostrukaLista<Tip>&jl){
        duzina=jl.duzina;
        Cvor *novi(jl.pocetakListe);
        pocetakListe=nullptr;
        for(int i=0; i<duzina; i++){
            Cvor *p=new Cvor;
            p->element=novi->element;
            p->sljedeci=nullptr;
            if(pocetakListe==nullptr) pocetakListe=p;
            else prethodniel->sljedeci=p;
            novi=novi->sljedeci;
            if(i!=duzina-1) prethodniel=p;
            
            return *this;
        }
    }
    
    void obrisi()override{
        if(tekuci->sljedeci==nullptr){
            if(duzina==1){delete tekuci; duzina--;}
            else{
                Cvor *novi(tekuci);
                prethodni();
                tekuci->sljedeci=nullptr;
                delete novi;
                duzina--;
            }
        }else{
            Cvor *pomocni(tekuci);
            tekuci=tekuci->sljedeci;
            if(pocetakListe==pomocni) {pocetakListe=tekuci;}
            else {prethodniel->sljedeci=tekuci;}
            pomocni->sljedeci=nullptr;
            delete pomocni;
            duzina--;
        } 
        if(duzina==0) pocetakListe=nullptr;
    }
    
    void dodajIspred(const Tip &el)override{
        if(duzina==0){
            pocetakListe=new Cvor;
            pocetakListe->element=el;
            pocetakListe->sljedeci=nullptr;
            tekuci=pocetakListe;
            duzina++;
        }else{
            Cvor *novi=new Cvor;
            novi->element=el;
            if(tekuci==pocetakListe){
                novi->sljedeci=tekuci;
                pocetakListe=novi;
                prethodniel=novi;
            }else{
                novi->sljedeci=tekuci;
                prethodniel->sljedeci=novi;
                prethodniel=novi;
            }
            duzina++;
            novi=nullptr;
        }
    }
    
    
    void dodajIza(const Tip &el)override{
        if(duzina==0){
            pocetakListe=new Cvor;
            pocetakListe->element=el;
            tekuci=pocetakListe;
            tekuci->sljedeci=nullptr;
            duzina++;
        }else{
            Cvor *novi=new Cvor;
            novi->element=el;
            novi->sljedeci=tekuci->sljedeci;
            tekuci->sljedeci=novi;
            duzina++;
            novi=nullptr;
            
            
        }
    }
    
    Tip &operator [] (int n) const{
        if(n<0 || n>duzina) throw("Izvan opsega");
        Cvor *prolazi=pocetakListe;
        for(int i=0; i<n; i++){
            prolazi=prolazi->sljedeci;
        }
        return prolazi->element;
    }   
    
}; 

int main() {
    std::cout << "Pripremna Zadaća 2 2017/2018, Zadatak 1";
    return 0;
}
