#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void radixSort(vector<int> &a)
{
    bool control;
    vector<int> pomocni(a.size());
    int m=1;
    for(;;) {
        control = true;
        int brojevi[10]= {0};
        for(int i=0; i<a.size(); i++) {
            if(a[i]/(m*10)!=0) control=false;
            brojevi[a[i]/m%10]++;
        }
        for(int i=1; i<10; i++) brojevi[i] += brojevi[i-1];
        for(int i=a.size()-1; i>=0; i--) pomocni[--brojevi[a[i]/m%10]]=a[i];
        a=pomocni;
        if(control) break;
        m*=10;

    }


}

bool jeLiList(vector<int> &a, int i, int velicina=-1)
{
    if(velicina==-1)
        velicina=a.size();
    return(i>=velicina/2 && i<velicina);



}

void popraviDolje(vector<int> &a, int i, int velicina)
{
    while (!jeLiList(a,i,velicina)) {
        int veci=2*i+1;
        int dd=2*i+2;
        if(dd<velicina && a[dd] > a[veci]) veci=dd;
        if(a[i] > a[veci]) return;
        int temp=a[i];
        a[i]=a[veci];
        a[veci]=temp;
        i=veci;


    }


}

void stvoriGomilu(vector<int> &a)
{
    for(int i=a.size()/2; i>=0; i--) popraviDolje(a,i,a.size());

}
void popraviGore(vector<int> &a, int i)
{
    while(i!=0 && a[i] > a[(i-1)/2]) {
        int temp=a[i];
        a[i]=a[(i-1)/2];
        a[(i-1)/2]=temp;
        i=(i-1)/2;


    }
}
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina)
{
    if(++velicina> a.size()) a.resize(velicina);
    a[a.size()-1]=umetnuti;
    popraviGore(a,a.size()-1);
}

int izbaciPrvi(vector<int> &a, int &velicina)
{

    if(velicina==0) throw "Gomila je prazna!";
    velicina--;
    int povratni=a[0];
    a[0]=a[velicina];
    a[velicina]=povratni;
    if(velicina != 0) popraviDolje(a,0,velicina);
    return povratni;

}

void gomilaSort(vector<int>&a)
{
    stvoriGomilu(a);
    for(int i=a.size()-1; i>=1; i--) {
        int temp=a[0];
        a[0]=a[i];
        a[i]=temp;
        popraviDolje(a,0,i);
    }

}



int main()
{

    vector<int>a{24,12,45,12,17,3,7,47,2,12,4};
    for(int i(0); i<a.size(); i++) {
        cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
    stvoriGomilu(a);
    for(int i(0); i<a.size(); i++) {
        cout<<a[i]<<" ";
    }

    std::cout<<std::endl;
    a.push_back(545);
    a.push_back(5454);
    a.push_back(1);
    a.push_back(95468);
    int velicina=a.size();
    umetniUGomilu(a,100000,velicina);
    umetniUGomilu(a,3,velicina);
    umetniUGomilu(a,1,velicina);
    umetniUGomilu(a,100,velicina);
    gomilaSort(a);

    for(int i=0; i<a.size(); i++) {
        cout<<a[i]<<" ";
    }
    std::cout<<std::endl;


    std::cout << "Zadaća 3, Zadatak 1";
    return 0;
}
