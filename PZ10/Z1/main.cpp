#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename TipOznake>
class UsmjereniGraf;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class MatricaGraf;

template <typename TipOznake>
class Grana;
template <typename TipOznake>
class GranaIterator;
template <typename TipOznake>
class UsmjereniGraf {
    
    public:
    UsmjereniGraf(){}
    UsmjereniGraf(int brojcvorova) { }
    virtual ~UsmjereniGraf(){}
    virtual int dajBrojCvorova() =0;
    virtual void postaviBrojCvorova(int brojcvorova) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina =0)=0;
    virtual void obrisiGranu(int polazni, int dolazni)=0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina)=0;
    virtual float dajTezinuGrane(int polazni, int dolazni)=0;
    virtual bool postojiGrana(int polazni, int dolazni)=0;
 
    virtual void postaviOznakuCvora(int brojcvora, TipOznake oznaka)=0;
  
    virtual TipOznake dajOznakuCvora(int brojcvora)=0;
  
    virtual void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka)=0;
   
    virtual TipOznake dajOznakuGrane(int polazni, int dolazni)=0;
    virtual Cvor<TipOznake> dajCvor(int brojcvora)=0; ////
    virtual Grana<TipOznake> &dajGranu(int polazni, int dolazni)=0; /////
    virtual GranaIterator<TipOznake> dajGranePocetak()=0;
    virtual GranaIterator<TipOznake> dajGraneKraj()=0;
    virtual Cvor<TipOznake> prvisusjed(Cvor<TipOznake> cvor)=0;
    virtual Cvor<TipOznake> SljedeciSusjed(Cvor<TipOznake> cvor1, Cvor<TipOznake> cvor2)=0;
};

template <typename TipOznake>
class Cvor {
    TipOznake oznaka;
    UsmjereniGraf<TipOznake>* pokanausmjgraf;
    int redniBroj;
    public:
    Cvor() {}
    Cvor(UsmjereniGraf<TipOznake>* usmjgraf, int rednibrcvora, TipOznake oznaka = TipOznake()) {pokanausmjgraf = usmjgraf; redniBroj = rednibrcvora;}
    void postaviOznaku(TipOznake oznaka1) {pokanausmjgraf->postaviOznakuCvora(redniBroj, oznaka1);}
    
    TipOznake dajOznaku() { return pokanausmjgraf->dajOznakuCvora(redniBroj);}
    int dajRedniBroj() { return redniBroj;}
    
};

template <typename TipOznake>
class Grana {
    
    UsmjereniGraf<TipOznake> *pokanausmjgraf;
    float tezina;
    TipOznake oznaka;
    // int polazni;
    //int dolazni;
    Cvor<TipOznake> polazni; /////
    Cvor<TipOznake> dolazni;/////
    public:
    Grana(UsmjereniGraf<TipOznake>* usmjgraf, Cvor<TipOznake> *polazni1, Cvor<TipOznake> *dolazni1, float tezina =0); //{pokanausmjgraf=usmjgraf; this->polazni=polazni1; this->dolazni=dolazni1; this->tezina=tezina; oznaka= TipOznake();}
    float dajTezinu() {return tezina;}
    void postaviTezinu(float tezina1, int) {tezina=tezina1;}
    void postaviTezinu(float tezina1) { pokanausmjgraf->postaviTezinuGrane(polazni.dajRedniBroj(), dolazni.dajRedniBroj(), tezina1);}
    TipOznake dajOznaku() {return oznaka;}
    void postaviOznaku(TipOznake oznaka1) { pokanausmjgraf->postaviOznakuGrane(polazni.dajRedniBroj(), dolazni.dajRedniBroj(), oznaka1);}
    void postaviOznaku(TipOznake oznaka1, int) {oznaka=oznaka1;}
    Cvor<TipOznake> dajPolazniCvor () { return polazni;}
    Cvor<TipOznake> dajDolazniCvor() {return dolazni;}
    UsmjereniGraf<TipOznake> *dajpok() {return pokanausmjgraf;}
    
    
};

template <typename TipOznake>
Grana<TipOznake>::Grana(UsmjereniGraf<TipOznake>* usmjgraf, Cvor<TipOznake> *polazni1, Cvor<TipOznake> *dolazni1, float tezina ) {
    pokanausmjgraf=usmjgraf; this->polazni = *polazni1; this->dolazni = *dolazni1; this->tezina=tezina; oznaka= TipOznake();

}

template <typename TipOznake>
class GranaIterator {
    UsmjereniGraf<TipOznake> *pokanausmjgraf;
    Grana<TipOznake> *poknagranu;
    int maxBrojCvorova;
    int trenutnibroj=0;
    public:
    GranaIterator(UsmjereniGraf<TipOznake> *pokanausmjgraf1, Grana<TipOznake> *poknagranu1, int maxBrojCvorova1, int trenutnibroj1 ) {pokanausmjgraf=pokanausmjgraf1; poknagranu=poknagranu1; maxBrojCvorova=maxBrojCvorova1; trenutnibroj=trenutnibroj1; if(poknagranu==nullptr) {
        
        
        do{ if((1+trenutnibroj)/maxBrojCvorova!= maxBrojCvorova) poknagranu= &pokanausmjgraf->dajGranu((1+trenutnibroj)/maxBrojCvorova, (1+trenutnibroj)%maxBrojCvorova); trenutnibroj++; } while(poknagranu==nullptr);
    }}
    
    Grana<TipOznake> operator*(){return *poknagranu;}
    bool operator ==(const GranaIterator &iter) const {if(maxBrojCvorova==iter.maxBrojCvorova && trenutnibroj==iter.trenutnibroj && (poknagranu==nullptr||(poknagranu->dajDolazniCvor().dajRedniBroj()==iter.poknagranu->dajDolazniCvor().dajRedniBroj() && poknagranu->dajPolazniCvor().dajRedniBroj()==iter.poknagranu->dajPolazniCvor().dajRedniBroj() && poknagranu->dajpok()==iter.poknagranu->dajpok()))) return true; return false;}
    bool operator !=(const GranaIterator &iter) const {return !(*this==iter);}
    GranaIterator& operator++() { do{if((1+trenutnibroj)/maxBrojCvorova !=maxBrojCvorova && pokanausmjgraf->postojiGrana((1+trenutnibroj)/maxBrojCvorova, (1+trenutnibroj)%maxBrojCvorova) ) poknagranu= &pokanausmjgraf->dajGranu((1+trenutnibroj)/maxBrojCvorova, (1+trenutnibroj)%maxBrojCvorova); else poknagranu=nullptr; trenutnibroj++; } while(poknagranu==nullptr); return *this;}
    GranaIterator operator++(int) {do{if((1+trenutnibroj)/maxBrojCvorova != maxBrojCvorova && pokanausmjgraf->postojiGrana((1+trenutnibroj)/maxBrojCvorova, (1+trenutnibroj)%maxBrojCvorova)) poknagranu= & pokanausmjgraf->dajGranu((1+trenutnibroj)/maxBrojCvorova, (1+trenutnibroj)%maxBrojCvorova); else poknagranu=nullptr; trenutnibroj++;} while (poknagranu==nullptr); return *this;}
    
};

//nece biti implementacija prim, dijkstra... dfs i bfs ce biti, quick merge, bubble, insertion moze, radix nece implementacija, nece ni counting ni adresni, 
//faze kreiranja avl, azuriranje balansa teorija.. vrste hesiranja



template <typename TipOznake>
class MatricaGraf : public UsmjereniGraf<TipOznake> {
    std::vector<TipOznake> nizcvorova;
    int maxBrojCvorova;
    int brojcvorova;
    int brojgrana;
    Grana<TipOznake> ***M;
    public:
    int dajBrojCvorova(){return maxBrojCvorova;}
    ~MatricaGraf() {for(int i=0; i<maxBrojCvorova; i++) {for(int j=0; j<maxBrojCvorova; j++ ) delete M[i][j]; delete[] M[i];} delete[] M; }
    MatricaGraf (int maxBrojCvorova1) ;
    void obrisiGranu(int polazni, int dolazni);
    void postaviBrojCvorova(int brojcvorova) {this->brojcvorova=brojcvorova;}
    void dodajGranu(int polazni, int dolazni, float tezina=0);
    void postaviTezinuGrane(int polazni, int dolazni, float tezina);
    float dajTezinuGrane(int polazni, int dolazni) {return M[polazni][dolazni]->dajTezinu();}
    bool postojiGrana(int polazni, int dolazni) {if(M[polazni][dolazni]==nullptr) return false; return true;}
    void postaviOznakuCvora(int brojcvora, TipOznake oznaka) {nizcvorova[brojcvora] = oznaka;}
    TipOznake dajOznakuCvora(int brojcvora) {return nizcvorova[brojcvora];}
    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {M[polazni][dolazni]->postaviOznaku(oznaka,3);}
    TipOznake dajOznakuGrane(int polazni, int dolazni){ return M[polazni][dolazni]->dajOznaku();}
    Cvor<TipOznake> dajCvor(int brojcvora) {return Cvor<TipOznake>(this,brojcvora, nizcvorova[brojcvora]);}
    Grana<TipOznake> &dajGranu(int polazni, int dolazni) {if(M[polazni][dolazni]!=nullptr) return *M[polazni][dolazni];}
    GranaIterator<TipOznake> dajGranePocetak() {return GranaIterator<TipOznake>(this, M[0][0], maxBrojCvorova,0);}
    GranaIterator<TipOznake> dajGraneKraj(){ return GranaIterator<TipOznake>(this, M[maxBrojCvorova-1][maxBrojCvorova-1], maxBrojCvorova+1, maxBrojCvorova+1);}
    Cvor<TipOznake> prvisusjed(Cvor<TipOznake> cvor);
    Cvor<TipOznake> SljedeciSusjed(Cvor<TipOznake> cvor1, Cvor<TipOznake> cvor2);
};


template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviTezinuGrane(int polazni, int dolazni, float tezina) {
    if(M[polazni][dolazni]==nullptr) throw("Ne postoji grana");
    M[polazni][dolazni]->postaviTezinu(tezina,5);
    
    


    
}
template <typename TipOznake>
void MatricaGraf<TipOznake>::dodajGranu(int polazni, int dolazni, float tezina) {
    if(M[polazni][dolazni]==nullptr) brojgrana++;
    Cvor<TipOznake> cvor1=Cvor<TipOznake>(this, polazni, nizcvorova[polazni]);
    Cvor<TipOznake> cvor2=Cvor<TipOznake>(this, dolazni, nizcvorova[dolazni]);
    M[polazni][dolazni]=new Grana<TipOznake>( this, &cvor1, &cvor2, tezina);
    
}
template<typename TipOznake>
void MatricaGraf<TipOznake>::obrisiGranu(int polazni, int dolazni) {
    if(M[polazni][dolazni]!=nullptr) brojgrana--;
    delete M[polazni][dolazni];
    M[polazni][dolazni]=nullptr;
}



template<typename TipOznake>
MatricaGraf<TipOznake>::MatricaGraf(int maxBrojCvorova1) {
    maxBrojCvorova = maxBrojCvorova1;
    nizcvorova.resize(maxBrojCvorova);
    M=new Grana<TipOznake>**[maxBrojCvorova]{};
    for(int i=0; i<maxBrojCvorova; i++) M[i]=new Grana<TipOznake>*[maxBrojCvorova]{};
    for(int i=0; i<maxBrojCvorova; i++) for(int j=0; j<maxBrojCvorova; j++) M[i][j]=nullptr;
    
}

template<typename TipOznake>
Cvor<TipOznake> MatricaGraf<TipOznake>::prvisusjed(Cvor<TipOznake> cvor) {
    int i;
    for(i=0; i<maxBrojCvorova; i++) {
        if(M[cvor.dajRedniBroj()][i] != nullptr) return Cvor<TipOznake>(this, i, nizcvorova[i]);
        
    }
    return Cvor<TipOznake>(this, i, nizcvorova[i]);
}

template<typename TipOznake>
Cvor<TipOznake> MatricaGraf<TipOznake>::SljedeciSusjed(Cvor<TipOznake> cvor1, Cvor<TipOznake> cvor2 ) {
    int i;
     for(i=cvor2.dajRedniBroj()+1; i<maxBrojCvorova; i++){
         if(M[cvor1.dajRedniBroj()][i]!=0) return Cvor<TipOznake>(this, i, nizcvorova[i] );
         
     }
     return Cvor<TipOznake>(this, i, nizcvorova[i]);
}

template<typename TipOznake>
void TraziPoDubini(UsmjereniGraf<TipOznake> *graf, Cvor<TipOznake> cvor, std::vector<Cvor<TipOznake>> &dfs_obilazak) {
    dfs_obilazak.push_back(cvor);
    cvor.postaviOznaku(true);
    for(int w=graf->prvisusjed(cvor).dajRedniBroj();w<graf->dajBrojCvorova(); w=graf->SljedeciSusjed(cvor, Cvor<TipOznake> (graf, w, graf->dajOznakuCvora(w))).dajRedniBroj())
    if(graf->dajOznakuCvora(w)==false) TraziPoDubini(graf, Cvor<TipOznake>(graf, w, graf->dajOznakuCvora(w) ), dfs_obilazak);
    
}
template<typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *graf, std::vector<Cvor<TipOznake>> &dfs_obilazak, Cvor<TipOznake> cvor) {
    for(int v=0; v<graf->dajBrojCvorova(); v++) graf->postaviOznakuCvora(v, false);
    for(int v=0; v<graf->dajBrojCvorova(); v++) {
        if(graf->dajOznakuCvora(v)==false) TraziPoDubini(graf, Cvor<TipOznake>(graf, v, graf->dajOznakuCvora(v)), dfs_obilazak);
        
    }
}

template<typename TipOznake>
void TraziPoSirini(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake>> &bfs_obilazak, Cvor<TipOznake> cvor) {
    std::queue<Cvor<TipOznake>> Q;
    Q.push(cvor);
    graf->postaviOznakuCvora(cvor.dajRedniBroj(), true);
    while(!Q.empty()) {
        Cvor<TipOznake> v=Q.front(); Q.pop();
        bfs_obilazak.push_back(v);
        for(int w=graf->prvisusjed(v).dajRedniBroj();w<graf->dajBrojCvorova(); w=graf->SljedeciSusjed(v, Cvor<TipOznake>(graf, w, graf->dajOznakuCvora(w))).dajRedniBroj()) {
            if(graf->dajOznakuCvora(w)==false) {
                graf->postaviOznakuCvora(w, true);
                Q.push(Cvor<TipOznake>(graf, w, graf->dajOznakuCvora(w)));
            }
        }
    }
}

template<typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake>> &bfs_obilazak, Cvor<TipOznake> pocetni_cvor ) {
    for(int v=0; v<graf->dajBrojCvorova(); v++) graf->postaviOznakuCvora(v, false);
    TraziPoSirini(graf,bfs_obilazak, pocetni_cvor);
    for(int v=0; v<graf->dajBrojCvorova(); v++)
    if(graf->dajOznakuCvora(v)==false) TraziPoSirini(graf, bfs_obilazak, Cvor<TipOznake>(graf, v, graf->dajOznakuCvora(v)));
    
}
int main() { 
    UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.555);
    g->dodajGranu(1, 2, 6.2);
    g->dodajGranu(1, 3, 0.7);
    g->dodajGranu(5, 2, 5.0);
    std::vector<Cvor<bool>> dfs_obilazak;
    dfs(g, dfs_obilazak, g->dajCvor(0));
    for(int i=0; i< dfs_obilazak.size(); i++)
    cout<< dfs_obilazak[i].dajRedniBroj() << ",";
    delete g;
    std::cout<< std::endl;
    UsmjereniGraf<bool> *g2= new MatricaGraf<bool>(6);
    g2->dodajGranu(0, 1, 2.5);
    g2->dodajGranu(1, 2, 1.2);
    g2->dodajGranu(1, 3, 0.1);
    g2->dodajGranu(2, 4, 3.14);
    std::vector<Cvor<bool>> bfs_obilazak;
    bfs(g2, bfs_obilazak, g2->dajCvor(0));
    for(int i=0; i<bfs_obilazak.size(); i++)
    cout<<bfs_obilazak[i].dajRedniBroj()<< ",";
    delete g2;
    std::cout<<std::endl;
    UsmjereniGraf<std::string> *g3 = new MatricaGraf<std::string>(4);
    g3->dodajGranu(0, 1, 24);
    g3->dodajGranu(1, 2, 34);
    g3->dodajGranu(1, 3, 56);
    g3->dodajGranu(3, 3, 9);
    g3->postaviOznakuGrane(3, 3, "aa");
    g3->dajGranu(0,1).postaviOznaku("bb");
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) if(g3->postojiGrana(i,j))
    cout<<"(" <<i <<","<< j << ") -> '" <<g3->dajOznakuGrane(i, j) <<"','" << g3->dajGranu(i, j).dajOznaku() << "';";
    delete g3;
    std::cout<<std::endl; 
    return 0;
    
    
}

