#include <iostream>
#include <exception>
#include <stdexcept>
#include <set>
#include <iterator>
#include <utility>
using std::runtime_error;
using namespace std;
template <class Vanzare>  //template pentru calculul masinilor ramase in stoc, scade din numarul total de masini, pe cele cumparate
Vanzare nr_total_masini(Vanzare a, Vanzare b)
{
    return a-b;
}

class automobil   //clasa principala
{
    protected:
        string producator;
        string model;
        int vechime;
        double pret;
        bool nou;
    public:
        virtual ostream& Afisare_virtuala(ostream &out) const;  //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);   //citire virtuala
        friend istream & operator >> (istream & in, automobil & A);  //implementarea operatorului de citire ca functie prieten
        friend ostream & operator << (ostream & out, const automobil & A); //implementarea operatorului de afisare ca functie prieten
        automobil& operator=(const automobil& autom);  //supraincarcarea operatorului =
        automobil();  //constructor fara parametri
        automobil(string producator, string model, int vechime, double pret, bool nou);  //constructor cu parametri
        automobil(const automobil &autom);   //copy-constructor
        ~automobil();   //destructor
};
ostream& automobil::Afisare_virtuala(ostream &out)const //afisare virtuala
{
    out<<"Numele producatorului este: ";
    out<<this->producator<<"\n";
    out<<"Numele modelului este: ";
    out<<this->model<<"\n";
    out<<"Vechimea automobilului este: ";
    out<<this->vechime<<"\n";
    out<<"Pretul automobilului este: ";
    out<<this->pret<<"\n";
    if(nou==1)
        out<<"Autoturismul este nou."<<"\n";
        else
        out<<"Autoturismul este sh."<<"\n";
    return out;
}

istream& automobil::Citire_virtuala(istream &in)  //citire virtuala
{
    cout<<"Introduceti numele producatorului: ";
    in>>this->producator;
    cout<<"Introduceti numele modelului: ";
    in>>this->model;
    cout<<"Introduceti vechimea automobilului: ";
    in>>this->vechime;
    cout<<"Introduceti pretul automobilului este: ";
    in>>this->pret;
    cout<<"Automobilul este nou sau sh?( 0 = sh, 1 = nou): ";
    in>>this->nou;
    return in;
}

istream & operator >>(istream & in,automobil &A)
{
    return A.Citire_virtuala(in);
}

ostream & operator <<(ostream & out,const automobil& A)
{
    return A.Afisare_virtuala(out);
}

automobil::automobil()  //constructor fara parametri
{
    this->producator="Necunoscut";
    this->model="Necunoscut";
    this->vechime=0;
    this->pret=0;
    this->nou=1;
}

automobil::automobil(string producator, string model, int vechime, double pret, bool nou)  //constructor cu parametri
{
    this->producator=producator;
    this->model=model;
    this->vechime=vechime;
    this->pret=pret;
    this->nou=1;
}

automobil::automobil(const automobil &autom)   //copy constructor
{
    this->producator=autom.producator;
    this->model=autom.model;
    this->vechime=autom.vechime;
    this->pret=autom.pret;
    this->nou=autom.nou;
}

automobil::~automobil()  //destructor
{
    this->producator="Ascuns";
    this->model="Ascuns";
    this->vechime=0;
    this->pret=0;
    this->nou=1;
}

automobil& automobil::operator=(const automobil& autom)   //supraincarcarea operatorului =
{
    if(this!=&autom)
    {
        this->producator=autom.producator;
        this->model=autom.model;
        this->vechime=autom.vechime;
        this->pret=autom.pret;
        this->nou=autom.nou;
    }
    return *this;
}

class mini:public automobil     //clasa derivata din clasa automobil
{
    private:
        double lungime_mini;
    public:
        mini();    //constructor fara parametri
        mini(string producator, string model, int vechime, double pret,bool nou, double lungime_mini);  //constructor cu parametri
        mini(const mini& autom_mini);  //copy constructor
        mini& operator=(const mini& autom_mini);  //supraincarcarea operatorului =
        ~mini();  //destructor
        virtual ostream& Afisare_virtuala(ostream& out) const;   //referire la implementarea in clasa de baza
        virtual istream& Citire_virtuala(istream &in);   //referire la implementarea in clasa de baza

};

ostream &mini::Afisare_virtuala(ostream &out) const
{
    automobil::Afisare_virtuala(out);   //referire la implementarea in clasa principala
    out<<"Lungimea automobilului mini: "<<this->lungime_mini<<"\n";
    return out;
}

istream &mini::Citire_virtuala(istream &in)
{
    automobil::Citire_virtuala(in);         //referire la implementarea in clasa principala
    cout<<"Introduceti lungimea automobilului mini: ";
    in>>this->lungime_mini;
    try             //testarea exceptiei. se verifica lungimea masinii de clasa mini, sa fie in parametri indicati de cerinta
    {
        if(this->lungime_mini>4)
            throw this->lungime_mini;
    }
    catch(double)
    {
            while(this->lungime_mini>4)
            {
                cout<<"Reintroduceti o lungime valida. Lungimea automobilului mini trebuie sa fie sub 4 metri. ";
                in>>this->lungime_mini;
                }
    }
    cout<<"\n";
    return in;
}

mini::mini():automobil()    //constructor fara parametri
{
    this->lungime_mini=0;
}

mini::mini(string producator, string model, int vechime, double pret, bool nou, double lungime_mini):automobil(producator,model,vechime,pret,nou)  //constructor cu parametri
{
    this->lungime_mini=lungime_mini;
}

mini::mini(const mini &autom_mini):automobil(autom_mini)  //copy-constructor
{
    this->lungime_mini=autom_mini.lungime_mini;
}

mini& mini::operator =(const mini& autom_mini)    //supraincarcarea operatorului=
{
    if(this!=&autom_mini)
    {
        automobil::operator=(autom_mini);
        this->lungime_mini=autom_mini.lungime_mini;
    }
    return *this;
}

mini::~mini()   //destructor
{
    this->lungime_mini=0;
}

class mica:public automobil   //clasa derivata din clasa automobil
{
    private:
        double lungime_mica;
    public:
        mica();       //constructor fara parametri
        mica(string producator, string model, int vechime, double pret, bool nou, double lungime_mica);
        mica(const mica& autom_mica); // copy constructor
        mica& operator=(const mica& autom_mica);  //supraincarcarea operatorului =
        ~mica();   //destructor
        virtual ostream& Afisare_virtuala(ostream& out) const;   //referinta la afisarea virtuala din clasa de baza
        virtual istream& Citire_virtuala(istream &in);  //referinta la citirea virtuala din clasa de baza
};

ostream &mica::Afisare_virtuala(ostream &out) const  //afisare virtuala
{
    automobil::Afisare_virtuala(out);
    out<<"Lungimea automobilului de clasa mica: "<<this->lungime_mica<<"\n";
    return out;
}

istream &mica::Citire_virtuala(istream &in)   //citire virtuala
{
    automobil::Citire_virtuala(in);
    cout<<"Introduceti lungimea automobilului de clasa mica: ";
    in>>this->lungime_mica;
        try                 //testarea exceptiei. se verifica lungimea masinii de clasa mica, sa fie in parametri indicati de cerinta
    {
        if(this->lungime_mica<3.85 || this->lungime_mica>4.1)
            throw this->lungime_mica;
    }
    catch(double)
    {
            while(this->lungime_mica<3.85 || this->lungime_mica>4.1)
            {
                cout<<"Reintroduceti o lungime valida. Lungimea automobilului de clasa mica trebuie sa fie cuprinsa intre 3.85 si 4.1 metri. ";
                in>>this->lungime_mica;
                }
    }
    cout<<"\n";
    return in;
}

mica::mica():automobil()
{
    this->lungime_mica=0;
}

mica::mica(string producator, string model, int vechime, double pret,bool nou, double lungime_mica):automobil(producator,model,vechime,pret,nou)
{
    this->lungime_mica=lungime_mica;
}

mica::mica(const mica &autom_mica):automobil(autom_mica)
{
    this->lungime_mica=autom_mica.lungime_mica;
}

mica& mica::operator =(const mica& autom_mica)
{
    if(this!=&autom_mica)
    {
        automobil::operator=(autom_mica);
        this->lungime_mica=autom_mica.lungime_mica;
    }
    return *this;
}

mica::~mica()
{
    this->lungime_mica=0;
}

class compacta:public automobil   //clasa derivata din clasa automobil
{
    protected:
        double lungime_compacta;
    public:
        compacta();       //constructor fara parametri
        compacta(string producator, string model, int vechime, double pret,bool nou,double lungime_compacta);
        compacta(const compacta& autom_compacta); //copy constructor
        compacta& operator=(const compacta& autom_compacta);  //supraincarcare =
        ~compacta();  //destructor
        virtual ostream& Afisare_virtuala(ostream& out) const;  //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);  //citire virtuala
};

ostream &compacta::Afisare_virtuala(ostream &out) const
{
    automobil::Afisare_virtuala(out);
    out<<"Lungimea automobilului de clasa compacta: "<<this->lungime_compacta<<"\n";
    return out;
}

istream &compacta::Citire_virtuala(istream &in)
{
    automobil::Citire_virtuala(in);
    cout<<"Introduceti lungimea automobilului de clasa compacta: ";
    in>>this->lungime_compacta;
            try             //testarea exceptiei. se verifica lungimea masinii compacte, sa fie in parametri indicati de cerinta
    {
        if(this->lungime_compacta<4.2 || this->lungime_compacta>4.5)
            throw this->lungime_compacta;
    }
    catch(double)
    {
            while(this->lungime_compacta<4.2 || this->lungime_compacta>4.5)
            {
                cout<<"Reintroduceti o lungime valida. Lungimea automobilului de clasa compacta trebuie sa fie cuprinsa intre 4.2 si 4.5 metri. ";
                in>>this->lungime_compacta;
                }
    }
    cout<<"\n";
    return in;
}

compacta::compacta():automobil()
{
    this->lungime_compacta=0;
}

compacta::compacta(string producator, string model, int vechime, double pret,bool nou,double lungime_compacta):automobil(producator,model,vechime,pret,nou)
{
    this->lungime_compacta=lungime_compacta;
}

compacta::compacta(const compacta &autom_compacta):automobil(autom_compacta)
{
    this->lungime_compacta=autom_compacta.lungime_compacta;
}

compacta& compacta::operator =(const compacta& autom_compacta)
{
    if(this!=&autom_compacta)
    {
        automobil::operator=(autom_compacta);
        this->lungime_compacta=autom_compacta.lungime_compacta;
    }
    return *this;
}

compacta::~compacta()
{
    this->lungime_compacta=0;
}

class monovolum:public automobil   //clasa monovolum, derivata din clasa automobil
{
    private:
        int nr_locuri;
    public:
        monovolum();  //constructor fara parametri
        monovolum(string producator, string model, int vechime, double pret, bool nou, int nr_locuri);  //constructor cu parametri
        monovolum(const monovolum& autom_monovolum); //copy constructor
        monovolum& operator=(const monovolum& autom_monovolum);  //supraincarcare operator =
        virtual ostream& Afisare_virtuala(ostream& out) const;   //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);  //citire virtuala
        ~monovolum();  //destructor
};

ostream &monovolum::Afisare_virtuala(ostream &out) const   //afisare virtuala
{
    automobil::Afisare_virtuala(out);
    out<<"Numarul de locuri al monovolumului: "<<this->nr_locuri<<"\n";
    return out;
}

istream &monovolum::Citire_virtuala(istream &in)   //citire virtuala
{
    automobil::Citire_virtuala(in);
    cout<<"Introduceti numarul de locuri al monovolumului: ";
    in>>this->nr_locuri;
            try         //testarea exceptiei. se verifica numarul de locuri al monovolumului, sa fie in parametri indicati de cerinta
    {
        if(this->nr_locuri<5 || this->nr_locuri>7)
            throw this->nr_locuri;
    }
    catch(int)
    {
            while(this->nr_locuri<5 || this->nr_locuri>7)
            {
                cout<<"Reintroduceti numarul de locuri.Numarul de locuri al unui monovolum trebuie sa fie cuprins intre 5 si 7.";
                in>>this->nr_locuri;
                }
    }
    cout<<"\n";
    return in;
}

monovolum::monovolum():automobil() //constructor fara parametri
{
    this->nr_locuri=0;
}

monovolum::monovolum(string producator, string model, int vechime, double pret, bool nou, int nr_locuri):automobil(producator,model,vechime,pret,nou)
{
    this->nr_locuri=nr_locuri;
}

monovolum::monovolum(const monovolum &autom_monovolum):automobil(autom_monovolum)  //copy constructor
{
    this->nr_locuri=autom_monovolum.nr_locuri;
}

monovolum& monovolum::operator =(const monovolum& autom_monovolum)   //supraincarcare =
{
    if(this!=&autom_monovolum)
    {
        automobil::operator=(autom_monovolum);
        this->nr_locuri=autom_monovolum.nr_locuri;
    }
    return *this;
}

monovolum::~monovolum()   //destructor
{
    this->nr_locuri=0;
}

class compacta_combi:public compacta   //clasa derivata din clasa principala compacta
{
    private:
        string avantaje_combi;
    public:
        compacta_combi();  //constructor
        compacta_combi(string producator, string model, int vechime, double pret,bool nou,double lungime_compacta,string avantaje_combi);
        compacta_combi(const compacta_combi& autom_compacta_combi);  //copy constructor
        compacta_combi& operator=(const compacta_combi& autom_compacta_combi);   //supraincarcare =
        virtual ostream& Afisare_virtuala(ostream& out) const; //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);  //citire virtuala
        ~compacta_combi();
};

ostream &compacta_combi::Afisare_virtuala(ostream &out) const  //afisare virtuala
{
    compacta::Afisare_virtuala(out);
    out<<"Avantajele unei masini compacte combi: "<<this->avantaje_combi<<"\n";
    return out;
}

istream &compacta_combi::Citire_virtuala(istream &in)   //citire virtuala
{
    compacta::Citire_virtuala(in);
    cout<<"Introduceti avantajele alegerii unei masini compacta combi: ";
    in>>this->avantaje_combi;
    return in;
}

compacta_combi::compacta_combi():compacta()  //constructor
{
    this->avantaje_combi="";
}

compacta_combi::compacta_combi(string producator, string model, int vechime, double pret, bool nou,double lungime_compacta,string avantaje_combi):compacta(producator,model,vechime,pret,nou,lungime_compacta)
{
    this->avantaje_combi=avantaje_combi;
}

compacta_combi::compacta_combi(const compacta_combi &autom_compacta_combi):compacta(autom_compacta_combi)  //copy constructor
{
    this->avantaje_combi=autom_compacta_combi.avantaje_combi;
}

compacta_combi& compacta_combi::operator =(const compacta_combi& autom_compacta_combi)  //supraincarcare =
{
    if(this!=&autom_compacta_combi)
    {
        compacta::operator=(autom_compacta_combi);
        this->avantaje_combi=autom_compacta_combi.avantaje_combi;
    }
    return *this;
}

compacta_combi::~compacta_combi()  //destructor
{
    this->avantaje_combi="Nespecificat";
}

class compacta_hatchback:public compacta   //clasa derivata din clasa compacta
{
    private:
        string avantaje_hatchback;
    public:
        compacta_hatchback();  //constructor
        compacta_hatchback(string producator, string model, int vechime, double pret,bool nou,double lungime_compacta,string avantaje_hatchback);
        compacta_hatchback(const compacta_hatchback& autom_compacta_hatchback);  //copy constructor
        compacta_hatchback& operator=(const compacta_hatchback& autom_compacta_hatchback);  //supraincarcare =
        virtual ostream& Afisare_virtuala(ostream& out) const;   //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);   //citire virtuala
        ~compacta_hatchback();  //destructor
};

ostream &compacta_hatchback::Afisare_virtuala(ostream &out) const  //afisare virtuala
{
    compacta::Afisare_virtuala(out);
    out<<"Avantajele unei masini compacte hatchback "<<this->avantaje_hatchback<<"\n";
    return out;
}

istream &compacta_hatchback::Citire_virtuala(istream &in)  //citire virtuala
{
    compacta::Citire_virtuala(in);
    cout<<"Introduceti avantajele alegerii unei masini compacta hatchback: ";
    in>>this->avantaje_hatchback;
    cout<<"\n";
    return in;
}

compacta_hatchback::compacta_hatchback():compacta()  //constructor
{
    this->avantaje_hatchback="";
}

compacta_hatchback::compacta_hatchback(string producator, string model, int vechime, double pret, bool nou,double lungime_compacta,string avantaje_hatchback):compacta(producator,model,vechime,pret,nou,lungime_compacta)
{
    this->avantaje_hatchback=avantaje_hatchback;
}

compacta_hatchback::compacta_hatchback(const compacta_hatchback &autom_compacta_hatchback):compacta(autom_compacta_hatchback) //copy constructor
{
    this->avantaje_hatchback=autom_compacta_hatchback.avantaje_hatchback;
}

compacta_hatchback& compacta_hatchback::operator =(const compacta_hatchback& autom_compacta_hatchback)  //supraincarcare operator =
{
    if(this!=&autom_compacta_hatchback)
    {
        compacta::operator=(autom_compacta_hatchback);
        this->avantaje_hatchback=autom_compacta_hatchback.avantaje_hatchback;
    }
    return *this;
}

compacta_hatchback::~compacta_hatchback()  //destructor
{
    this->avantaje_hatchback="Nespecificat";
}

class compacta_sedan:public compacta  //clasa derivata clasei principale compacta
{
    private:
        string avantaje_sedan;
    public:
        compacta_sedan();  //constructor
        compacta_sedan(string producator, string model, int vechime, double pret,bool nou,double lungime_compacta,string avantaje_sedan);
        compacta_sedan(const compacta_sedan& autom_compacta_sedan);  //copy constructor
        compacta_sedan& operator=(const compacta_sedan& autom_compacta_sedan);  //supraincarcare operator =
        virtual ostream& Afisare_virtuala(ostream& out) const;  //afisare virtuala
        virtual istream& Citire_virtuala(istream &in);   //citire virtuala
        ~compacta_sedan();
};

ostream &compacta_sedan::Afisare_virtuala(ostream &out) const   //afisare virtuala
{
    compacta::Afisare_virtuala(out);
    out<<"Avantajele unei masini compacte sedan "<<this->avantaje_sedan<<"\n";
    return out;
}

istream &compacta_sedan::Citire_virtuala(istream &in)   //citire virtuala
{
    compacta::Citire_virtuala(in);
    cout<<"Introduceti avantajele alegerii unei masini compacta sedan: ";
    in>>this->avantaje_sedan;
    cout<<"\n";
    return in;
}

compacta_sedan::compacta_sedan():compacta()  //constructor
{
    this->avantaje_sedan="";
}

compacta_sedan::compacta_sedan(string producator, string model, int vechime, double pret, bool nou,double lungime_compacta,string avantaje_sedan):compacta(producator,model,vechime,pret,nou,lungime_compacta)
{
    this->avantaje_sedan=avantaje_sedan;
}

compacta_sedan::compacta_sedan(const compacta_sedan &autom_compacta_sedan):compacta(autom_compacta_sedan)  //copy constructor
{
    this->avantaje_sedan=autom_compacta_sedan.avantaje_sedan;
}

compacta_sedan& compacta_sedan::operator =(const compacta_sedan& autom_compacta_sedan)  //supraincarcare operator =
{
    if(this!=&autom_compacta_sedan)
    {
        compacta::operator=(autom_compacta_sedan);
        this->avantaje_sedan=autom_compacta_sedan.avantaje_sedan;
    }
    return *this;
}

compacta_sedan::~compacta_sedan()  //destructor
{
    this->avantaje_sedan="Nespecificat";
}




void meniu()    //meniu interactiv+citirea/memorarea a n obiecte
{
 automobil *lista_automobile[100];

    int k=1;
    int i=0;
    while(k==1){

        cout<<"\n1 Introducere masina mini. ";
        cout<<"\n2 Introducere masina mica. ";
        cout<<"\n3 Introducere masina compact combi. ";
        cout<<"\n4 Introducere masina compact hatchback.";
        cout<<"\n5 Introducere masina compact sedan.";
        cout<<"\n6 Introducere masina monovolum.";
        cout<<"\n7 Afisare detalii masini din stoc.";
        cout<<"\n8 Afisare numar total masini din stoc.";
        cout<<"\n9 Cumparati o masina.";
        cout<<"\n0 Iesire"<<"\n";
        int actiune;
        cin>> actiune;

int nr_cumparate=0;
        switch(actiune){
        case 0:
            {
                k=0;
                break;
            }

            case 1:{

                lista_automobile[i]=new mini();
                cin>>*lista_automobile[i];
                i++;
                break;


            }
            case 2:{

                lista_automobile[i]=new mica();
                cin>>*lista_automobile[i];
                i++;
                break;


            }
            case 3:{

                lista_automobile[i]=new compacta_combi();
                cin>>*lista_automobile[i];
                i++;
                break;


            }
            case 4:{

                lista_automobile[i]=new compacta_hatchback();
                cin>>*lista_automobile[i];
                i++;
                break;


            }
            case 5:{

                lista_automobile[i]=new compacta_sedan();
                cin>>*lista_automobile[i];
                i++;
                break;


            }
            case 6:{

                lista_automobile[i]=new monovolum();
                cin>>*lista_automobile[i];
                i++;
                break;


            }

            case 7:{
               for(int j=0; j<i;j++)
                    cout<<*lista_automobile[j];
            }

            case 8:
                { int q;
                q=nr_total_masini<int>(i,nr_cumparate);
                cout<<q;
                }
            case 9:
                {
                    nr_cumparate++;
                }


        }}}


int main()
{
    meniu();
}
