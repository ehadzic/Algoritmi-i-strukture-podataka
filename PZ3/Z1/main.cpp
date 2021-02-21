#include <iostream>

template <typename Tip>
class Stek{
    struct Cvor{
        Tip element;
        Cvor *sljedeci;
        Cvor(const Tip &element, Cvor *sljedeci): element(element), sljedeci(sljedeci){}
    };
    
    Cvor *naVrhu;
    int duzina;
    
    public:
    
    Stek(): naVrhu(nullptr),duzina(0){}
    Stek(const Stek<Tip> &s){
        
        Cvor *p(s.naVrhu);
        Cvor *q = 0;
        duzina=s.duzina;
        
        while(p!=0){
            Cvor *novi=new Cvor(p->element,0);
            if(q==0){
                naVrhu=novi;
                
            }else{
                
            q->sljedeci=novi;
                
            }
            q=novi;
            p=p->sljedeci;
           
            
            
    
        }
         duzina=s.duzina;
    }
    
    ~Stek(){
        while(duzina!=0){
            Cvor *pomocni=naVrhu;
            naVrhu=naVrhu->sljedeci;
            delete pomocni;
            duzina--;
        }
    }
    
    
    Stek &operator=(const Stek &s){
        if(&s==this) return *this;
        Cvor *p(s.naVrhu);
        Cvor *q = 0;
        duzina=s.duzina;
        while(p!=0){
            Cvor *novi=new Cvor(p->element,0);
            if(q==0){
                naVrhu=novi;
                
            }else{
                
            q->sljedeci=novi;
                
            }
            q=novi;
            p=p->sljedeci;
           
            
            
    
        }
         duzina=s.duzina;
        return *this;
        
    }
    
    
    void brisi(){
        Cvor *pomocni;
        while(naVrhu!=nullptr){
            pomocni=naVrhu;
            naVrhu=naVrhu->sljedeci;
            delete pomocni;
            duzina--;
        }
        duzina=0;
        
    }
    
    
    void stavi(const Tip &el){
        if(duzina==0){
            Cvor *novi=new Cvor(el,0);
            naVrhu=novi;
            
        }else{
            Cvor *novi=new Cvor(el,0);
            novi->sljedeci=naVrhu;
            naVrhu=novi;
        }
        duzina++;
        
    }
    
    
    Tip skini(){
        if(duzina==0)throw("Stek je prazan/n");
        Tip x=naVrhu->element;
        Cvor *pomocni(naVrhu);
        
        if(duzina==1){
            naVrhu=nullptr;
            delete pomocni;
            
        }else{
            Cvor *p(naVrhu);
            p=p->sljedeci;
            naVrhu=naVrhu->sljedeci;
            pomocni->sljedeci=nullptr;
            delete pomocni;
            pomocni=p;
        }
        
        duzina--;
        return x;
        
    }
    
    Tip &vrh(){
        if(naVrhu==0)throw("Stek je prazan/n");
        return naVrhu->element;
    }
    
    int brojElemenata() {return duzina;}
    
    
    
    
    
};


int main() {
    
    Stek<int>s;
    for(int i=0; i<5;i++){
        s.stavi(i);
    }
    std::cout<<s.vrh()<<" ";
    s.vrh()++;
    std::cout<<s.vrh();
    
    std::cout << "Pripremna Zadaca Za Vjezbu 3, Zadatak 1"; 
    return 0;
}
