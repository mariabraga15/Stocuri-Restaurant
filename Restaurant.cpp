// Proiect Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<cstring>
using namespace std;
class MateriePrima {
private:
    char* denumire;
    char lichidSauSolid; // "L" pt lichid, "S" pt solid
    float cantitateTotala;

public:
    MateriePrima() {
        this->cantitateTotala = 0;
        this->denumire = nullptr;
        this->lichidSauSolid = 'L';
    }

    MateriePrima(const char* denumire, char lichidSauSolid, float cantitateTotala) {
        if (denumire != nullptr && strlen(denumire) >= 2) {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else {
            this->denumire = nullptr;
        }


        if (lichidSauSolid == 'S' || lichidSauSolid == 'L') {
            this->lichidSauSolid = lichidSauSolid;
        }
        else {
            this->lichidSauSolid = 'L';
        }


        if (cantitateTotala > 0) {
            this->cantitateTotala = cantitateTotala;
        }
        else {
            this->cantitateTotala = 0;
        }

    }

    // Getteri si setteri
    const char* getNumeIngredient() const {
        return this->denumire != nullptr ? this->denumire : nullptr;
    }
    //sa schimb numele ingredientului in depozit
    void setNumeIngredient(const char* denumireNoua)
    {
        if (denumireNoua != nullptr && strlen(denumireNoua) >= 2) {
            if (this->denumire != nullptr) {
                delete[] this->denumire;
            }
            this->denumire = new char[strlen(denumireNoua) + 1];
            strcpy(this->denumire, denumireNoua);
        }
    }



    float getStoc() const {
        return this->cantitateTotala;
    }
    void addStoc(float cantitate)
    {
        if (cantitate > 0)
        {
            this->cantitateTotala += cantitate;
        }
    }

    MateriePrima(const MateriePrima& m)
    {
        if (m.denumire != nullptr && strlen(m.denumire) >= 2) {
            this->denumire = new char[strlen(m.denumire) + 1];
            strcpy(this->denumire, m.denumire);
        }
        else {
            this->denumire = nullptr;
        }
        this->lichidSauSolid = m.lichidSauSolid;
        this->cantitateTotala = m.cantitateTotala;
    }
    //operator atribuire
    MateriePrima& operator=(const MateriePrima& m) {
        if (this != &m) {
            // Delete existing dynamically allocated memory
            delete[] this->denumire;
            this->denumire = nullptr;

            // Allocate new memory and copy data
            if (m.denumire != nullptr && strlen(m.denumire) >= 3) {
                this->denumire = new char[strlen(m.denumire) + 1];
                strcpy(this->denumire, m.denumire);
            }

            // Copy other members
            this->lichidSauSolid = m.lichidSauSolid;
            this->cantitateTotala = m.cantitateTotala;
        }
        return *this;
    }


    //operator !
    bool operator!() const {
        return this->cantitateTotala == 0;
    }

    //operator ==
    bool operator==(const MateriePrima& m) const
    {
        if (this->denumire != nullptr && m.denumire != nullptr) {
            return strcmp(this->denumire, m.denumire) == 0;
        }
        return false;
    }

    MateriePrima& operator++() {
        this->cantitateTotala++;
        return *this;
    }

    MateriePrima operator++(int) {
        MateriePrima copie = *this;
        copie.cantitateTotala++;
        return copie;
    }

    //operator >=
    bool operator>=(const MateriePrima& other) const {
        return this->cantitateTotala >= other.cantitateTotala;
    }

    //operator -=
    MateriePrima& operator-=(float stocDeRedus)
    {
        if (stocDeRedus > 0 && this->cantitateTotala - stocDeRedus >= 0)
        {
            this->cantitateTotala -= stocDeRedus;
        }
        return *this;

    }

    MateriePrima operator+=(float stocAdaugat)
    {
        MateriePrima copie = *this;
        copie.addStoc(stocAdaugat);
        return copie;
    }
    //operator !=
    bool operator!=(const char* denumire) {
        if (this->denumire != nullptr && denumire != nullptr) {
            return strcmp(this->denumire, denumire) != 0;
        }
        return true;
    }

    //operator <
    bool operator<(const MateriePrima& other) {
        return this->cantitateTotala < other.cantitateTotala;
    }

    //afisare
    friend ostream& operator<<(ostream& out, const MateriePrima& m)
    {
        if (m.denumire != nullptr) {
            out << m.denumire << endl;
        }
        else {
            out << "Denumire: -" << endl;
        }

        out << "Cantitate : " << m.cantitateTotala;

        if (m.lichidSauSolid == 'S') {
            out << " kg" << endl;
        }
        else if (m.lichidSauSolid == 'L') {
            out << " litri" << endl;
        }
        else {
            out << " (Tip necunoscut)" << endl;
        }

        return out;
    }

    //citire
    friend istream& operator>>(istream& in, MateriePrima& m) {
        char temp[100];
        float cantitate;
        char tip;

        cout << "Introduceti denumire: ";
        in.getline(temp, sizeof(temp));

        if (strlen(temp) >= 2) {
            delete[] m.denumire;
            m.denumire = new char[strlen(temp) + 1];
            strncpy(m.denumire, temp, strlen(temp) + 1);
        }
        else {
            delete[] m.denumire;
            m.denumire = nullptr;
        }

        cout << "Introduceti cantitate: ";
        in >> cantitate;

        if (cantitate > 0) {
            m.cantitateTotala = cantitate;
        }
        else {
            m.cantitateTotala = 0;
        }

        // Consuma newline-ul ramas in buffer
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Introduceti tipul ('S' pentru solid, 'L' pentru lichid): ";
        in >> tip;
        if (tip == 'S' || tip == 'L') {
            m.lichidSauSolid = tip;
        }
        else {
            m.lichidSauSolid = 'S';
        }

        // Consuma newline-ul ramas in buffer
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << endl;
        return in;
    }






    ~MateriePrima() {
        delete[] this->denumire;
        this->denumire = nullptr;
    }
};


class Depozit {
private:
    int nrMateriiPrime;
    MateriePrima* materiiPrime;
public:
    friend class MateriePrima;
    Depozit() :nrMateriiPrime(0), materiiPrime(nullptr) {}
    Depozit(int nrMateriiPrime, const MateriePrima* materiiPrime)
    {
        if (nrMateriiPrime > 0 && materiiPrime != nullptr)
        {
            this->nrMateriiPrime = nrMateriiPrime;
            this->materiiPrime = new MateriePrima[this->nrMateriiPrime];

            for (int i = 0; i < this->nrMateriiPrime; i++)
            {
                this->materiiPrime[i] = materiiPrime[i];
            }
        }
        else
        {
            this->nrMateriiPrime = 0;
            this->materiiPrime = nullptr;
        }
    }
    //constructor copiere
    Depozit(Depozit& d)
    {
        if (d.nrMateriiPrime > 0 && d.materiiPrime != nullptr) {
            this->nrMateriiPrime = d.nrMateriiPrime;
            this->materiiPrime = new MateriePrima[this->nrMateriiPrime];

            for (int i = 0; i < this->nrMateriiPrime; i++) {
                this->materiiPrime[i] = d.materiiPrime[i];
            }
        }
        else {
            this->nrMateriiPrime = 0;
            this->materiiPrime = nullptr;
        }

    }
    //operator =
    Depozit& operator=(Depozit& d)
    {
        if (this != &d)
        {
            delete[] this->materiiPrime;
            this->materiiPrime = nullptr;
            if (d.nrMateriiPrime > 0 && d.materiiPrime != nullptr) {
                this->nrMateriiPrime = d.nrMateriiPrime;
                this->materiiPrime = new MateriePrima[this->nrMateriiPrime];

                for (int i = 0; i < this->nrMateriiPrime; i++) {
                    this->materiiPrime[i] = d.materiiPrime[i];
                }
            }
            else {
                this->nrMateriiPrime = 0;
                this->materiiPrime = nullptr;
            }

        }
    }

    const int getNrMateriiPrime() {
        return this->nrMateriiPrime;
    }

    void adaugaStoc(char* numeIngredient, float cantitate) {
        for (int i = 0; i < this->nrMateriiPrime; i++) {
            if (strcmp(this->materiiPrime[i].getNumeIngredient(), numeIngredient) == 0) {
                //verific operatorul
                this->materiiPrime[i].addStoc(cantitate);

            }
        }

    }


    void addMaterie(MateriePrima& m) {
        if (m.getNumeIngredient() != nullptr && m.getStoc() > 0) {
            MateriePrima* temp = new MateriePrima[this->nrMateriiPrime + 1];

            for (int i = 0; i < this->nrMateriiPrime; i++) {
                temp[i] = this->materiiPrime[i];
            }

            temp[this->nrMateriiPrime] = m;

            delete[] this->materiiPrime;
            this->materiiPrime = temp;
            this->nrMateriiPrime++;
        }
    }
    Depozit& operator+=(MateriePrima& materiePrima) {
        this->addMaterie(materiePrima);
        return *this;
    }



    MateriePrima& operator[](int index)
    {
        if (index >= 0 && index < this->nrMateriiPrime) {
            if (this->materiiPrime != nullptr) {
                return this->materiiPrime[index];
            }
        }

    }

    friend ostream& operator<<(ostream& out, Depozit& d)
    {
        out << "----------------------STOC DEPOZIT--------------------------" << endl;
        out << "          Numar materii prime: " << d.nrMateriiPrime << endl;
        if (d.materiiPrime != nullptr) {
            for (int i = 0; i < d.nrMateriiPrime; i++)
            {
                out << d.materiiPrime[i] << endl;
            }
        }
        else {
            out << "Nu exista produse in stoc";
        }
        return out;
    }

    friend istream& operator>>(istream& in, Depozit& d)
    {
        int nrStoc;
        cout << "Introduceti numarul de produse pe care sa le puneti in stoc: ";
        in >> nrStoc;


        if (d.nrMateriiPrime != nrStoc)
        {

            delete[] d.materiiPrime;
            d.nrMateriiPrime = nrStoc;
            d.materiiPrime = new MateriePrima[d.nrMateriiPrime];
        }


        for (int i = 0; i < d.nrMateriiPrime; i++)
        {
            in >> d.materiiPrime[i];
        }

        return in;
    }

    void scadeDepozit(const char* denumire, float cantitate) {
        if (this->materiiPrime != nullptr) {
            for (int i = 0; i < this->nrMateriiPrime; i++) {
                string ingredientName = this->materiiPrime[i].getNumeIngredient();
                float cantitateIngredient = this->materiiPrime[i].getStoc();

                if (ingredientName.find(denumire) != string::npos) {
                    if (cantitate > 0 && cantitateIngredient - cantitate >= 0) {
                        this->materiiPrime[i] -= cantitate;
                        break;
                    }
                }
            }
        }
    }

    //elimina din depozit produsele cu stoc epuizat
    Depozit& operator--() {
        int nrProduseZero = 0;
        for (int i = 0; i < this->nrMateriiPrime; i++) {
            if (this->materiiPrime[i].getStoc() == 0) {
                nrProduseZero++;
            }
        }
        if (nrProduseZero > 0 && this->nrMateriiPrime-nrProduseZero>0)
        {
            MateriePrima* temp = new MateriePrima[this->nrMateriiPrime - nrProduseZero];
            int k = 0;
            for (int i = 0; i < this->nrMateriiPrime; i++) {
                if (this->materiiPrime[i].getStoc() != 0) {
                    temp[k++] = this->materiiPrime[i];
                }
            }
            delete[] this->materiiPrime;
            this->materiiPrime = nullptr;
            this->materiiPrime = temp;
        }
    }

    void afisareStoc(const char* denumire)
    {
        bool found = false;

        if (this->materiiPrime != nullptr) {
            for (int i = 0; i < this->nrMateriiPrime && !found; i++) {
                string ingredientName = this->materiiPrime[i].getNumeIngredient();

                if (ingredientName.find(denumire) != string::npos) {
                    found = true;
                    cout << this->materiiPrime[i] << endl;
                }
            }
        }

        if (!found) {
            cout << "Acest produs nu se gaseste in stocuri!" << endl;
        }
    }

    bool exista(const char* denumire) {
        if (this->materiiPrime != nullptr && this->nrMateriiPrime > 0) {
            for (int i = 0; i < this->nrMateriiPrime; i++) {
                if (strcmp(this->materiiPrime[i].getNumeIngredient(), denumire) == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    void adaugaStoc(const char* denumire, float stoc) {
        if (this->materiiPrime != nullptr && this->nrMateriiPrime > 0) {
            for (int i = 0; i < this->nrMateriiPrime; i++) {
                if (strcmp(this->materiiPrime[i].getNumeIngredient(), denumire) == 0) {
                    this->materiiPrime[i].addStoc(stoc);
                }
            }
        }
    }




    ~Depozit() {
        delete[] this->materiiPrime;
        this->materiiPrime = nullptr;
    }
};


class Preparat {
private:
    string nume;
    int nrIngrediente;
    MateriePrima* IngredienteNecesare;
    bool esteBautura;
    bool esteMancare;
    float pretUnitar;
public:
    friend class MateriePrima;
    friend class Depozit;
    Preparat() : nrIngrediente(0), IngredienteNecesare(nullptr), nume("Anonim"), esteBautura(false), esteMancare(true), pretUnitar(0) {}

    Preparat(string nume, int nrIngrediente, MateriePrima* IngredienteNecesare, bool esteBautura, bool esteMancare, float pretUnitar)
    {
        if (nrIngrediente > 0 && IngredienteNecesare != nullptr && nume.size() >= 3) {
            this->nrIngrediente = nrIngrediente;
            this->IngredienteNecesare = new MateriePrima[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++) {
                this->IngredienteNecesare[i] = IngredienteNecesare[i];
            }

        }
        else {
            this->nrIngrediente = 0;
            this->IngredienteNecesare = nullptr;
        }

        this->nume = nume;

        if (esteBautura) {
            this->esteBautura = esteBautura;
            this->esteMancare = false;
        }
        else {
            this->esteBautura = esteBautura;
            this->esteMancare = true;
        }

        if (pretUnitar > 0) {
            this->pretUnitar = pretUnitar;
        }
        else {
            this->pretUnitar = 0;
        }
    }
    Preparat(const Preparat& p)
    {
        if (p.nrIngrediente > 0 && p.IngredienteNecesare != nullptr)
        {
            this->nrIngrediente = p.nrIngrediente;
            this->IngredienteNecesare = new MateriePrima[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++) {
                this->IngredienteNecesare[i] = p.IngredienteNecesare[i];
            }
            this->nume = p.nume;
            this->esteBautura = p.esteBautura;
            this->esteMancare = p.esteMancare;
            this->pretUnitar = p.pretUnitar;
        }
        else {
            this->nrIngrediente = 0;
            this->IngredienteNecesare = nullptr;
            this->nume = p.nume;
            this->esteBautura = p.esteBautura;
            this->esteMancare = p.esteMancare;
            this->pretUnitar = p.pretUnitar;
        }

    }

    Preparat& operator=(const Preparat& p)
    {
        if (this != &p)
        {
            delete[] this->IngredienteNecesare;
            this->IngredienteNecesare = nullptr;
            if (p.nrIngrediente > 0 && p.IngredienteNecesare != nullptr)
            {
                this->nrIngrediente = p.nrIngrediente;
                this->IngredienteNecesare = new MateriePrima[this->nrIngrediente];
                for (int i = 0; i < this->nrIngrediente; i++) {
                    this->IngredienteNecesare[i] = p.IngredienteNecesare[i];
                }
                this->nume = p.nume;
                this->esteBautura = p.esteBautura;
                this->esteMancare = p.esteMancare;
                this->pretUnitar = p.pretUnitar;
            }
            else {
                this->nrIngrediente = 0;
                this->IngredienteNecesare = nullptr;
                this->nume = p.nume;
                this->esteBautura = p.esteBautura;
                this->esteMancare = p.esteMancare;
                this->pretUnitar = p.pretUnitar;
            }

        }

        return *this;

    }

    bool getEsteMancare() const {
        return this->esteMancare;
    }

    const string getNumePreparat() {
        return this->nume;
    }

    float getPretUnitar() {
        return this->pretUnitar;

    }
    MateriePrima* getIngrediente() const {
        return IngredienteNecesare;
    }

    void setPretUnitar(float pretNou) {
        if (pretNou > 0) {
            this->pretUnitar = pretNou;
        }
    }

    /*
    void setNumePreparat(const string numeNou) {
        if (numeNou.size() >= 3) {
            this->nume = numeNou;
        }
    } */
    int getNrIngrediente() const {
        return this->nrIngrediente;
    }
    void adaugaMateriePrima(MateriePrima& m) {
        if (m.getNumeIngredient() != nullptr && m.getStoc() > 0) {
            MateriePrima* temp = new MateriePrima[this->nrIngrediente + 1];

            for (int i = 0; i < this->nrIngrediente; i++) {
                temp[i] = this->IngredienteNecesare[i];
            }

            temp[this->nrIngrediente] = m;

            delete[] this->IngredienteNecesare;
            this->IngredienteNecesare = nullptr;
            this->nrIngrediente++;
            //copiez inapoi in this
            this->IngredienteNecesare = new MateriePrima[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++) {
                this->IngredienteNecesare[i] = temp[i];
            }
            delete[] temp;
            temp = nullptr;
        }

    }



    MateriePrima operator[](int index)
    {
        if (index >= 0 && index < this->nrIngrediente) {
            if (this->IngredienteNecesare != nullptr) {
                return this->IngredienteNecesare[index];
            }
        }
    }

    friend ostream& operator<<(ostream& out, const Preparat& p)
    {
        out << "---- Reteta pentru " << p.nume << " ----\n";
        out << "Numar ingrediente: " << p.nrIngrediente << "\n";
        for (int i = 0; i < p.nrIngrediente; i++) {
            out << p.IngredienteNecesare[i] << "\n";
        }
        out << "Mancare sau baututura? ";
        if (p.esteMancare) {
            out << "Mancare" << endl;
        }
        else {
            out << "Bautura" << endl;
        }

        out << "Pret unitar: " << p.pretUnitar << endl;

        return out;
    }

    friend istream& operator>>(istream& in, Preparat& p) {
        cout << "Introduceti numele preparatului: ";
        getline(in, p.nume);

        int nrIngrediente;
        cout << "Introduceti numarul de ingrediente: ";
        in >> nrIngrediente;

        // Consuma newline-ul ramas in buffer
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nrIngrediente > 0) {
            delete[] p.IngredienteNecesare;
            p.nrIngrediente = nrIngrediente;
            p.IngredienteNecesare = new MateriePrima[nrIngrediente];

            cout << "Introduceti detaliile pentru fiecare ingredient:\n";
            for (int i = 0; i < p.nrIngrediente; i++) {
                cout << "Ingredient " << i + 1 << ":\n";
                in >> p.IngredienteNecesare[i];


            }
        }
        else {
            delete[] p.IngredienteNecesare;
            p.IngredienteNecesare = nullptr;
            p.nrIngrediente = 0;
        }

        cout << "Este bautura? (1 pentru bautura, 0 pentru mancare): ";
        in >> p.esteBautura;
        p.esteMancare = (p.esteBautura == 0) ? 1 : 0;

        cout << "Pret unitar al preparatului: ";
        in >> p.pretUnitar;


        return in;
    }




    bool poateFiServit(Depozit& d)

    {
        if (&d != nullptr)
        {
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                bool ingredientFound = false;

                for (int j = 0; j < d.getNrMateriiPrime(); j++)
                {
                    if (this->IngredienteNecesare[i] == d[j])
                    {
                        if (d[j] < this->IngredienteNecesare[i]) {
                            return false;
                        }

                        ingredientFound = true;
                    }
                }

                if (!ingredientFound) {
                    return false;
                }
            }

        }
        else {
            return false;
        }
        return true;
    }


    bool operator!=(Preparat& p) {
        bool diferite = false;
        if (this->nrIngrediente == p.nrIngrediente && this->IngredienteNecesare != nullptr) {
            for (int i = 0; i < this->nrIngrediente; i++) {
                if (this->IngredienteNecesare[i].getNumeIngredient() != p.IngredienteNecesare[i].getNumeIngredient() &&
                    this->IngredienteNecesare[i].getStoc() != p.IngredienteNecesare[i].getStoc()) {
                    diferite = true;
                }
            }

        }

        return this->nume != p.nume || this->nrIngrediente != p.nrIngrediente || this->esteBautura != p.esteBautura || diferite;

    }



    //operator == compara preparatele
    bool operator==(const Preparat& p) {
        bool lafel = true;
        if (this->nrIngrediente == p.nrIngrediente && this->IngredienteNecesare != nullptr) {
            for (int i = 0; i < this->nrIngrediente; i++) {
                if (this->IngredienteNecesare[i].getNumeIngredient() != p.IngredienteNecesare[i].getNumeIngredient() &&
                    this->IngredienteNecesare[i].getStoc() != p.IngredienteNecesare[i].getStoc()) {
                    lafel = false;
                }
            }

        }

        return this->nume == p.nume && this->nrIngrediente == p.nrIngrediente && this->esteBautura == p.esteBautura && lafel;
    }

    void afiseazaReteta() {
        cout << "--------------------" << "Reteta pentru " << this->nume << "-------------------------" << endl;
        for (int i = 0; i < this->nrIngrediente; i++) {
            cout << this->IngredienteNecesare[i] << "\n";
        }
        cout << endl;
    }




    ~Preparat() {

        delete[] this->IngredienteNecesare;
        this->IngredienteNecesare = nullptr;
    }

};

class Meniu {
private:
    int nrMancaruri;
    Preparat* mancaruri;
    int nrBauturi;
    Preparat* bauturi;


public:
    friend class Preparat;

    Meniu() {
        this->nrMancaruri = 0;
        this->mancaruri = nullptr;
        this->nrBauturi = 0;
        this->bauturi = nullptr;
    }




    Meniu(int nrMancaruri, Preparat* mancaruri, int nrBauturi, Preparat* bauturi) {
        if (nrMancaruri > 0 && mancaruri != nullptr) {
            this->nrMancaruri = nrMancaruri;
            this->mancaruri = new Preparat[this->nrMancaruri];
            for (int i = 0; i < this->nrMancaruri; i++) {
                this->mancaruri[i] = mancaruri[i];
            }
        }
        else {
            this->nrMancaruri = 0;
            this->mancaruri = nullptr;
        }

        if (nrBauturi > 0 && bauturi != nullptr) {
            this->nrBauturi = nrBauturi;
            this->bauturi = new Preparat[this->nrBauturi];
            for (int i = 0; i < this->nrBauturi; i++) {
                this->bauturi[i] = bauturi[i];
            }
        }
        else {
            this->nrBauturi = 0;
            this->bauturi = nullptr;
        }
    }

    void addPreparatMeniu(Preparat& p)
    {

        if (p.getEsteMancare()) {
            //adaug in vector mancaruri
            Preparat* temp = new Preparat[this->nrMancaruri + 1];
            if (this->mancaruri != nullptr) {
                for (int i = 0; i < this->nrMancaruri; i++) {
                    temp[i] = this->mancaruri[i];
                }
            }
            temp[this->nrMancaruri] = p;
            delete[] this->mancaruri;
            this->mancaruri = nullptr;
            this->mancaruri = temp;
            this->nrMancaruri++;

        }
        else {
            //adaug in vector bauturi
            Preparat* temp = new Preparat[this->nrBauturi + 1];
            if (this->bauturi != nullptr) {
                for (int i = 0; i < this->nrBauturi; i++) {
                    temp[i] = this->bauturi[i];
                }
            }
            temp[this->nrBauturi] = p;
            delete[] this->bauturi;
            this->bauturi = nullptr;
            this->bauturi = temp;
            this->nrBauturi++;
        }
    }
    int getNrMancaruri() {
        return this->nrMancaruri;
    }

    int getNrBauturi() {
        return this->nrBauturi;
    }
    const Preparat* getMancaruri() {
        return this->mancaruri;
    }


    const Preparat* getBauturi() {
        return this->bauturi;
    }

    Preparat& getIndexMancaruri(int index) {
        if (this->mancaruri != nullptr && this->nrMancaruri > 0) {
            if (index >= 0 && index < this->nrMancaruri) {
                return this->mancaruri[index];
            }
        }
    }
    Preparat& getIndexBauturi(int index) {
        if (this->bauturi != nullptr && this->nrBauturi > 0) {
            if (index >= 0 && index < this->nrBauturi) {
                return this->bauturi[index];
            }
        }
    }

    Meniu(const Meniu& m) {
        this->nrMancaruri = m.nrMancaruri;
        if (m.nrMancaruri > 0 && m.mancaruri != nullptr) {

            for (int i = 0; i < this->nrMancaruri; i++) {
                this->mancaruri[i] = m.mancaruri[i];
            }
        }
        else {
            this->mancaruri = nullptr;
        }

        this->nrBauturi = m.nrBauturi;
        if (m.nrBauturi > 0 && m.bauturi != nullptr) {
            for (int i = 0; i < this->nrBauturi; i++) {
                this->bauturi[i] = m.bauturi[i];
            }
        }
        else {
            this->bauturi = nullptr;
        }
    }

    Meniu& operator=(const Meniu& m) {
        if (this != &m) {
            delete[] this->mancaruri;
            this->mancaruri = nullptr;
            delete[] this->bauturi;
            this->bauturi = nullptr;
            this->nrMancaruri = m.nrMancaruri;
            if (m.nrMancaruri > 0 && m.mancaruri != nullptr) {

                for (int i = 0; i < this->nrMancaruri; i++) {
                    this->mancaruri[i] = m.mancaruri[i];
                }
            }
            else {
                this->mancaruri = nullptr;
            }

            this->nrBauturi = m.nrBauturi;
            if (m.nrBauturi > 0 && m.bauturi != nullptr) {
                for (int i = 0; i < this->nrBauturi; i++) {
                    this->bauturi[i] = m.bauturi[i];
                }
            }
            else {
                this->bauturi = nullptr;
            }
        }

        return *this;
    }


    int gasesteIndexPreparat(string& denumire) {

        for (int i = 0; i < this->nrBauturi; i++) {
            //cout << this->bauturi[i].getNumePreparat() << endl;
            if (denumire == this->bauturi[i].getNumePreparat()) {

                return i;

            }
        }


        for (int i = 0; i < this->nrMancaruri; i++) {
            //cout << this->mancaruri[i].getNumePreparat() << endl;
            if (denumire == this->mancaruri[i].getNumePreparat()) {
                return i + this->nrBauturi;
            }
        }

        return -1;
    }




    Meniu& operator+(Preparat& p) {
        this->addPreparatMeniu(p);
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Meniu& m)
    {
        out << "===========================Meniu==============================================" << endl;
        out << "------------Mancaruri-----------------------" << endl;
        if (m.mancaruri != nullptr && m.nrMancaruri > 0) {
            for (int i = 0; i < m.nrMancaruri; i++) {
                out << i + 1 << "." << m.mancaruri[i].getNumePreparat() << "----------------" << m.mancaruri[i].getPretUnitar() << " lei" << endl;
            }
        }
        else {
            out << "Nu exista mancaruri adaugate in meniu!" << endl;
        }

        cout << endl;
        out << "------------Bauturi-----------------------" << endl;
        if (m.bauturi != nullptr && m.nrBauturi > 0) {
            for (int i = 0; i < m.nrBauturi; i++) {
                out << i + 1 << "." << m.bauturi[i].getNumePreparat() << "-------" << m.bauturi[i].getPretUnitar() << " lei" << endl;
            }
        }
        else {
            out << "Nu exista inca bauturi in meniu!" << endl;
        }
        return out;
    }

    //afisare numai pt bauturi
    void afiseazaBauturi() {
        if (this->bauturi != nullptr) {
            for (int i = 0; i < this->nrBauturi; i++) {
                cout << i + 1 << "." << this->bauturi[i].getNumePreparat() << "-------" << this->bauturi[i].getPretUnitar() << "euro" << endl;
            }
        }
    }

    //asta pt afisare numai de mancaruri
    void afiseazaMancaruri() {
        if (this->mancaruri != nullptr) {

            for (int i = 0; i < this->nrMancaruri; i++) {
                cout << i + 1 << "." << this->mancaruri[i].getNumePreparat() << "----------------" << this->mancaruri[i].getPretUnitar() << "euro" << endl;
            }
        }
    }

    void afiseazaRetetaPreparat(string denumire) {
        bool found = false;
        if (this->bauturi != nullptr && this->nrBauturi > 0)
        {
            for (int i = 0; i < this->nrBauturi; i++) {
                if (denumire == this->bauturi[i].getNumePreparat()) {
                    found = true;
                    this->bauturi[i].afiseazaReteta();
                }
            }
        }
        if (this->mancaruri != nullptr && this->nrMancaruri > 0)
        {
            for (int i = 0; i < this->nrMancaruri; i++)
            {
                if (denumire == this->mancaruri[i].getNumePreparat()) {
                    found = true;
                    this->mancaruri[i].afiseazaReteta();

                }
            }
        }

        if (!found) {
            cout << "Preparatul introdus nu se afla in meniu!" << endl;
        }
    }


    bool existaInMeniu(string denumire) {
        for (int i = 0; i < this->nrMancaruri; i++) {
            if (denumire == this->mancaruri[i].getNumePreparat()) {
                return true;
            }
        }

        for (int i = 0; i < this->nrBauturi; i++) {
            if (denumire == this->bauturi[i].getNumePreparat()) {
                return true;
            }
        }
        return false;
    }



    ~Meniu() {
        delete[] this->mancaruri;
        this->mancaruri = nullptr;
        delete[] this->bauturi;
        this->bauturi = nullptr;
    }

};

//comanda cu mai multe preparate
class Comanda {
private:
    static int ultimulId;
    const int id;
    int nrPreparateComandate;
    Preparat* preparateComandate;
    float valoareComanda;
public:

    Comanda() :id(++ultimulId) {
        this->nrPreparateComandate = 0;
        this->preparateComandate = nullptr;
        this->valoareComanda = 0;
    }

    Comanda(int nrPreparateComandate, Preparat* preparateComandate) :id(++ultimulId) {
        if (nrPreparateComandate > 0 && preparateComandate != nullptr) {
            this->nrPreparateComandate = nrPreparateComandate;
            this->preparateComandate = new Preparat[this->nrPreparateComandate];
            for (int i = 0; i < this->nrPreparateComandate; i++) {
                this->preparateComandate[i] = preparateComandate[i];
                this->valoareComanda += preparateComandate[i].getPretUnitar();
            }
        }
        else {
            this->nrPreparateComandate = 0;
            this->preparateComandate = nullptr;
            this->valoareComanda = 0;
        }
    }

    Comanda(const Comanda& c) :id(++ultimulId) {
        this->nrPreparateComandate = c.nrPreparateComandate;
        if (this->nrPreparateComandate > 0) {
            this->preparateComandate = new Preparat[this->nrPreparateComandate];
            for (int i = 0; i < this->nrPreparateComandate; i++) {
                this->preparateComandate[i] = c.preparateComandate[i];
                this->valoareComanda += c.preparateComandate[i].getPretUnitar();
            }
        }
        else {
            this->preparateComandate = nullptr;
        }
    }

    Preparat& operator[](int index) {
        if (this->preparateComandate != nullptr && this->nrPreparateComandate > 0)
        {
            if (index >= 0 && index < this->nrPreparateComandate) {
                return this->preparateComandate[index];
            }
        }
    }

    void adaugaPreparatComanda(Preparat& p) {
        
        this->valoareComanda += p.getPretUnitar();
        Preparat* temp = new Preparat[this->nrPreparateComandate + 1];
        if (this->preparateComandate != nullptr) {
            for (int i = 0; i < this->nrPreparateComandate; i++) {
                temp[i] = this->preparateComandate[i];
            }

        }

        temp[this->nrPreparateComandate] = p;
        delete[] this->preparateComandate;
        this->preparateComandate = nullptr;
        this->preparateComandate = temp;
        this->nrPreparateComandate++;


    }
    //metoda pe care o voi folosi dupa ce adaug un preparat in comanda
    void eliminaDepozit(Preparat& p, Depozit& d) {
        if (p.getNrIngrediente() > 0 && p.getIngrediente() != nullptr) {
            for (int i = 0; i < p.getNrIngrediente(); i++) {
                const char* denumire = p.getIngrediente()[i].getNumeIngredient();
                float cantitate = p.getIngrediente()[i].getStoc();

                //scade din depozit cantitatea aferenta din reteta
                d.scadeDepozit(denumire, cantitate);
            }
        }
    }

    float getValoareComanda() {
        return this->valoareComanda;
    }

    int getNrPreparateComandate() {
        return this->nrPreparateComandate;
    }



    Comanda& operator+(Preparat& p) {

        this->adaugaPreparatComanda(p);

        return *this;
    }


    friend Comanda& operator+(Preparat& p, Comanda& c) {
        Comanda copie = c;
        copie.adaugaPreparatComanda(p);
        return copie;

    }

    friend ostream& operator<<(ostream& out, const Comanda& c) {
        out << "Comanda cu id " << c.id << endl;
        if (c.preparateComandate != nullptr) {
            for (int i = 0; i < c.nrPreparateComandate; i++) {
                out << i + 1 << "." << c.preparateComandate[i].getNumePreparat() << " " << c.preparateComandate[i].getPretUnitar() << " " << "lei" << endl;

            }
            out << "Total: " << c.valoareComanda << endl;
        }
        else {
            out << "Inca nu exista preparate in comanda" << endl;
        }

        return out;
    }
    friend istream& operator>>(istream& in, Comanda& c) {
        in >> c.nrPreparateComandate;

        in.ignore(numeric_limits<streamsize>::max(), '\n');

        if (c.nrPreparateComandate > 0) {
            delete[] c.preparateComandate;
            c.preparateComandate = new Preparat[c.nrPreparateComandate];

            for (int i = 0; i < c.nrPreparateComandate; i++) {
                in >> c.preparateComandate[i];
            }

            c.valoareComanda = 0;
            for (int i = 0; i < c.nrPreparateComandate; i++) {
                c.valoareComanda += c.preparateComandate[i].getPretUnitar();
            }
        }
        else {
            delete[] c.preparateComandate;
            c.preparateComandate = nullptr;
            c.valoareComanda = 0;
        }

        return in;
    }


    Comanda& operator=(const Comanda& c) {
        if (this != &c) {
            // Copy the id from the source object
            const_cast<int&>(this->id) = c.id;
            this->valoareComanda = c.valoareComanda;
            delete[] this->preparateComandate;
            this->preparateComandate = nullptr;
            this->nrPreparateComandate = c.nrPreparateComandate;
            if (this->nrPreparateComandate > 0) {
                this->preparateComandate = new Preparat[this->nrPreparateComandate];
                for (int i = 0; i < this->nrPreparateComandate; i++) {
                    this->preparateComandate[i] = c.preparateComandate[i];
                }
            }
            else {
                this->preparateComandate = nullptr;
            }
        }
        return *this;
    }


    bool operator==(const Comanda& c2) {
        if (this->nrPreparateComandate != c2.nrPreparateComandate) {
            return false;
        }

        for (int i = 0; i < this->nrPreparateComandate; i++) {
            if (this->preparateComandate[i] != c2.preparateComandate[i]) {
                return false;
            }
        }

        return true;
    }


    bool operator!=(Comanda& c) {
        bool diferite = false;
        if (this->preparateComandate != nullptr && c.preparateComandate != nullptr
            && this->nrPreparateComandate == c.nrPreparateComandate) {
            for (int i = 0; i < this->nrPreparateComandate; i++) {
                if (this->preparateComandate[i] != c.preparateComandate[i]) {
                    diferite = true;
                }
            }
        }

        return this->nrPreparateComandate != c.nrPreparateComandate || diferite;
    }


    int getId() {
        return this->id;
    }

    void anuleazaComanda(Depozit& d)
    {
        for (int i = 0; i < this->nrPreparateComandate; i++) {
            Preparat p = this->preparateComandate[i];
            for (int j = 0; j < p.getNrIngrediente(); j++) {
                const char* denumire = p.getIngrediente()[j].getNumeIngredient();

                float cantitate = p.getIngrediente()[j].getStoc();

                d.adaugaStoc(denumire, cantitate);
            }
        }

        if (this->preparateComandate != nullptr) {
            delete[] this->preparateComandate;
            this->preparateComandate = nullptr;
        }

        this->nrPreparateComandate = 0;
        this->valoareComanda = 0;
    }
    //elimina ultimul preparat comandat
    Comanda& operator--() {
        if (this->nrPreparateComandate > 1 && this->preparateComandate != nullptr) {
            Preparat* temp = new Preparat[this->nrPreparateComandate - 1];
            for (int i = 0; i < this->nrPreparateComandate - 1; i++) {
                temp[i] = this->preparateComandate[i];
            }
            delete[] this->preparateComandate;
            this->preparateComandate = nullptr;
            this->preparateComandate = temp;
        }
        else if (this->nrPreparateComandate == 1) {
            delete[] this->preparateComandate;
            this->preparateComandate = nullptr;
            this->nrPreparateComandate = 0;
        }
        return *this;
    }
    Comanda& operator--(int) {
        Comanda copie = *this;
        copie--;
        return copie;
    }

    ~Comanda() {
        delete[] this->preparateComandate;
        this->preparateComandate = nullptr;
    }

};
int Comanda::ultimulId = 0;

//client care poate avea mai multe comenzi
class Client {
private:
    static int ultimulId;
    const int id;
    string nume;
    float bugetMaxim;
    int nrComenzi;
    Comanda* comenzi;
    float valoareTotalaComenzi;

public:
    Client() : id(++ultimulId), valoareTotalaComenzi(0) {
        this->nume = "N/A";
        this->nrComenzi = 0;
        this->comenzi = nullptr;
        this->bugetMaxim = 0;
    }

    Client(string nume, float bugetMaxim) : id(++ultimulId), valoareTotalaComenzi(0) {
        if (nume.length() >= 2) {
            this->nume = nume;
        }
        else {
            this->nume = "N/A";
        }
        this->nrComenzi = 0;
        this->comenzi = nullptr;
        if (bugetMaxim > 0) {
            this->bugetMaxim = bugetMaxim;
        }
        else {
            this->bugetMaxim = 0;
        }
    }

    Client(string nume, int nrComenzi, Comanda* comenzi, float bugetMaxim) : id(++ultimulId) {
        if (nume.length() >= 2) {
            this->nume = nume;
        }
        else {
            this->nume = "N/A";
        }

        if (nrComenzi > 0 && comenzi != nullptr) {
            this->nrComenzi = nrComenzi;
            this->comenzi = new Comanda[this->nrComenzi];
            for (int i = 0; i < this->nrComenzi; i++) {
                this->comenzi[i] = comenzi[i];
                this->valoareTotalaComenzi += comenzi[i].getValoareComanda();
            }
        }
        else {
            this->nrComenzi = 0;
            this->comenzi = nullptr;
        }

        if (bugetMaxim > 0) {
            this->bugetMaxim = bugetMaxim;
        }
        else {
            this->bugetMaxim = 0;
        }
    }

    Client(const Client& c) : id(++ultimulId) {
        this->nume = c.nume;
        this->nrComenzi = c.nrComenzi;
        if (this->nrComenzi > 0) {
            this->comenzi = new Comanda[this->nrComenzi];
            for (int i = 0; i < this->nrComenzi; i++) {
                this->comenzi[i] = c.comenzi[i];
            }
            this->valoareTotalaComenzi = c.valoareTotalaComenzi;
        }
        else {
            this->nrComenzi = 0;
            this->comenzi = nullptr;
            this->valoareTotalaComenzi = 0;
        }
        this->bugetMaxim = c.bugetMaxim;
    }

    Client& operator=(const Client& c) {
        if (this != &c) {
            delete[] this->comenzi;
            this->comenzi = nullptr;
            this->nume = c.nume;
            this->nrComenzi = c.nrComenzi;
            if (this->nrComenzi > 0) {
                this->comenzi = new Comanda[this->nrComenzi];
                for (int i = 0; i < this->nrComenzi; i++) {
                    this->comenzi[i] = c.comenzi[i];
                }
                this->valoareTotalaComenzi = c.valoareTotalaComenzi;
            }
            else {
                this->nrComenzi = 0;
                this->comenzi = nullptr;
                this->valoareTotalaComenzi = 0;
            }
            this->bugetMaxim = c.bugetMaxim;
        }
        return *this;
    }

    void adaugaComanda(Comanda& c) {
        if (&c != nullptr && bugetMaxim - c.getValoareComanda() - valoareTotalaComenzi >= 0) {
            Comanda* aux = new Comanda[nrComenzi + 1];

            if (nrComenzi > 0 && comenzi != nullptr) {
                for (int i = 0; i < nrComenzi; i++) {
                    aux[i] = comenzi[i];
                }
            }

            aux[nrComenzi] = c;
            delete[] comenzi;
            comenzi = nullptr;
            comenzi = aux;
            nrComenzi++;
            valoareTotalaComenzi += c.getValoareComanda();
        }
        else {
            cout << "Buget insuficient!" << endl;
        }
    }


    Client& operator+=(Comanda& c) {
        if (&c != nullptr && bugetMaxim - c.getValoareComanda() - valoareTotalaComenzi >= 0) {
            Comanda* aux = new Comanda[nrComenzi + 1];

            if (nrComenzi > 0 && comenzi != nullptr) {
                for (int i = 0; i < nrComenzi; i++) {
                    aux[i] = comenzi[i];
                }
            }

            aux[nrComenzi] = c;
            delete[] comenzi;
            comenzi = nullptr;
            comenzi = aux;
            nrComenzi++;

            float totalValue = 0;
            for (int i = 0; i < nrComenzi; i++) {
                totalValue += comenzi[i].getValoareComanda();
            }

            valoareTotalaComenzi = totalValue;
        }

        return *this;
    }


    Client& operator-=(Comanda& c) {
        int index = -1;

        for (int i = 0; i < nrComenzi; i++) {
            if (comenzi[i] == c) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            Comanda* aux = new Comanda[nrComenzi - 1];

            for (int i = 0, j = 0; i < nrComenzi; i++) {
                if (i != index) {
                    aux[j++] = comenzi[i];
                }
            }

            delete[] comenzi;
            comenzi = nullptr;
            comenzi = aux;
            nrComenzi--;
            valoareTotalaComenzi -= c.getValoareComanda();
        }

        return *this;
    }

    float getTotalComenzi() {
        return valoareTotalaComenzi;
    }

    friend ostream& operator<<(ostream& out, const Client& client) {
        out << "Clientul " << ": " << client.nume << endl;
        out << " - Buget maxim: " << client.bugetMaxim << " lei";

        if (client.nrComenzi > 0) {
            out << " - Comenzi:";
            for (int i = 0; i < client.nrComenzi; i++) {
                out << "\n\t" << client.comenzi[i];
            }
        }
        else {
            out << " - Fara comenzi.";
        }
        out << "Total comenzi: " << client.valoareTotalaComenzi << endl;
        return out;
    }

    bool operator==(const Client& other) const {
        if (this == &other) {
            return true;
        }

        if (this->bugetMaxim != other.bugetMaxim ||
            this->nrComenzi != other.nrComenzi ||
            this->valoareTotalaComenzi != other.valoareTotalaComenzi) {
            return false;
        }

        for (int i = 0; i < this->nrComenzi; i++) {
            if (!(this->comenzi[i] == other.comenzi[i])) {
                return false;
            }
        }

        return true;
    }

    friend istream& operator>>(istream& in, Client& client) {
        cout << "Introduceti numele clientului: ";
        in >> ws;
        getline(in, client.nume);

        cout << "Introduceti bugetul maxim al clientului: ";
        in >> client.bugetMaxim;

        cout << "Introduceti numarul de comenzi ale clientului: ";
        in >> client.nrComenzi;

        if (client.nrComenzi > 0) {
            client.comenzi = new Comanda[client.nrComenzi];
            cout << "Introduceti comenzile clientului:";

            for (int i = 0; i < client.nrComenzi; i++) {
                cout << "\nComanda " << i + 1 << ":\n";
                in >> client.comenzi[i];
                client.valoareTotalaComenzi += client.comenzi[i].getValoareComanda();
            }
        }
        else {
            client.comenzi = nullptr;
        }

        return in;
    }

    ~Client() {
        delete[] this->comenzi;
        this->comenzi = nullptr;
    }
};


int Client::ultimulId = 0;
//restaurant care poate avea mai multi clienti
class ComenziRestaurant {
private:
    int nrClienti;
    Client* clienti;
    static int capacitateRestaurant;

public:
    friend class Client;

    ComenziRestaurant() {
        this->nrClienti = 0;
        this->clienti = nullptr;
    }

    ComenziRestaurant(int nrClienti, Client* clienti) {
        if (nrClienti > 0 && clienti != nullptr && nrClienti <= capacitateRestaurant) {
            this->nrClienti = nrClienti;
            this->clienti = new Client[this->nrClienti];
            for (int i = 0; i < this->nrClienti; i++) {
                this->clienti[i] = clienti[i];
            }
        }
        else {
            this->nrClienti = 0;
            this->clienti = nullptr;
        }
    }

    // Operator +=
    // Operator +=
    ComenziRestaurant& operator+=(const Client& client) {
        if (nrClienti < capacitateRestaurant) {
            Client* aux = new Client[nrClienti + 1];

            for (int i = 0; i < nrClienti; i++) {
                aux[i] = clienti[i];
            }

            aux[nrClienti] = client;
            delete[] clienti;
            clienti = aux;
            nrClienti++;
        }
        else {
            cout << "Capacitate depasita! Nu s-au adaugat clientii." << endl;
        }

        return *this;
    }

    // Operator -=
    ComenziRestaurant& operator-=(const Client& client) {
        int newNrClienti = nrClienti - 1;

        if (newNrClienti >= 0) {
            Client* aux = new Client[newNrClienti];

            int k = 0;
            for (int i = 0; i < nrClienti; i++) {
                if (!(clienti[i] == client)) {
                    aux[k++] = clienti[i];
                }
            }

            delete[] clienti;
            clienti = aux;
            nrClienti = newNrClienti;
        }
        else {
            cout << "Numarul de clienti este mai mic decat 1. Nu s-au eliminat clientii." << endl;
        }

        return *this;
    }


    // Operator -- (predecrementare)
    ComenziRestaurant& operator--() {
        if (this->nrClienti > 0) {
            Client* aux = new Client[this->nrClienti - 1];

            for (int i = 0; i < this->nrClienti - 1; i++) {
                aux[i] = this->clienti[i];
            }

            delete[] this->clienti;
            this->clienti = aux;
            this->nrClienti--;
        }
        else {
            cout << "Nu exista clienti de eliminat." << endl;
        }

        return *this;
    }

    // Operator -- (postdecrementare)
    ComenziRestaurant operator--(int) {
        ComenziRestaurant copy = *this;
        --(*this);
        return copy;
    }

    friend ostream& operator<<(ostream& out, const ComenziRestaurant& comenziRestaurant) {
        out << "ComenziRestaurant cu " << comenziRestaurant.nrClienti << " clienti";

        if (comenziRestaurant.nrClienti > 0) {
            out << ":\n";
            for (int i = 0; i < comenziRestaurant.nrClienti; i++) {
                out << comenziRestaurant.clienti[i] << "\n";
            }
        }
        else {
            out << " - Fara clienti.\n";
        }

        return out;
    }

    friend istream& operator>>(istream& in, ComenziRestaurant& comenziRestaurant) {
        cout << "Introduceti numarul de clienti: ";
        in >> comenziRestaurant.nrClienti;

        if (comenziRestaurant.nrClienti > 0 && comenziRestaurant.nrClienti <= ComenziRestaurant::capacitateRestaurant) {
            comenziRestaurant.clienti = new Client[comenziRestaurant.nrClienti];

            cout << "Introduceti clientii:";

            for (int i = 0; i < comenziRestaurant.nrClienti; i++) {
                cout << "\nClient " << i + 1 << ":\n";
                in >> comenziRestaurant.clienti[i];
            }
        }
        else {
            comenziRestaurant.nrClienti = 0;
            comenziRestaurant.clienti = nullptr;
        }

        return in;
    }

    ~ComenziRestaurant() {
        delete[] this->clienti;
        this->clienti = nullptr;
    }
};

// Initializare membru static
int ComenziRestaurant::capacitateRestaurant = 100;



int main()
{
    //stocul in depozit
    MateriePrima ingredienteDepozit[] = {
        MateriePrima("Faina", 'S', 2),
        MateriePrima("Oua", 'S', 1.2),
        MateriePrima("Carne", 'S', 2),
        MateriePrima("Pui", 'S', 0.8),
        MateriePrima("Salata", 'S', 0.8),
        MateriePrima("Ulei", 'L', 0.7),
        MateriePrima("Suc de portocale", 'L', 2),
        MateriePrima("Legume", 'S', 1),
        MateriePrima("Apa", 'L', 100),
        MateriePrima("Bere", 'L', 50),
        MateriePrima("Porc",'S',20),
        MateriePrima("Ceai",'S',2),
        MateriePrima("Ciuperci",'S',10),
        MateriePrima("Sunca",'S',12),
        MateriePrima("Pepperoni",'S',20),
        MateriePrima("Cascaval",'S',20),
        MateriePrima("Sprite",'L',50),
        MateriePrima("Sos de rosii",'L',2),
        MateriePrima("Mozzarella", 'S', 0.9),
        MateriePrima("Sunca", 'S', 0.4)

    };


    Depozit depozit(20, ingredienteDepozit);
    //cout << "Depozit initial:\n" << depozit << endl;
    MateriePrima m1("Suc de mere", 'L', 12);
    MateriePrima m2("Pere", 'S', 12);
    depozit += m1;
    depozit += m2;
    //cout << depozit;
    //depozit.scadeDepozit("Faina", 0.5);
    MateriePrima ingredientePaste[] = {
        MateriePrima("Faina", 'S', 1.0),
        MateriePrima("Apa", 'L', 0.5),
        MateriePrima("Sos de rosii",'L',0.3),
        MateriePrima("Cascaval",'S',0.2)
    };
    Preparat paste("Paste cu rosii si cascaval", 4, ingredientePaste, false, true, 10);

    MateriePrima ingredienteSalata[] = {
        MateriePrima("Salata", 'V', 0.8),
        MateriePrima("Ulei", 'L', 0.02),
        MateriePrima("Rosii",'S',0.5),
        MateriePrima("Castraveti",'S',0.5),
        MateriePrima("Ardei",'S',0.3)
    };
    Preparat salata("Salata Caesar", 5, ingredienteSalata, false, true, 15);

    MateriePrima ingredienteSuc[] = {
        MateriePrima("Suc de portocale", 'L', 1.0)
    };
    Preparat suc("Suc de portocale", 1, ingredienteSuc, true, false, 5);

    MateriePrima ingredienteBere[] = {
        MateriePrima("Bere", 'L', 0.5),

    };
    Preparat bere("Bere", 1, ingredienteBere, true, false, 7);

    MateriePrima ingredienteOmleta[] = {
        MateriePrima("Oua", 'S', 0.1),
        MateriePrima("Ulei", 'L', 0.02),
        MateriePrima("Legume", 'V', 0.2)
    };
    Preparat omleta("Omleta cu legume", 3, ingredienteOmleta, false, true, 12);

    MateriePrima ingredientePizza[] = {
        MateriePrima("Faina", 'S', 0.5),
        MateriePrima("Sos de rosii", 'L', 0.3),
        MateriePrima("Mozzarella", 'S', 0.2),
        MateriePrima("Sunca", 'S', 0.2)
    };
    Preparat pizza("Pizza Quatro Staggioni", 4, ingredientePizza, false, true, 20.0);

    MateriePrima ingredienteSmoothie[] = {
        MateriePrima("Fructe de padure", 'V', 1.2),
        MateriePrima("Iaurt", 'L', 0.5),
        MateriePrima("Miere", 'L', 0.3)
    };
    Preparat smoothie("Smoothie cu fructe de padure", 3, ingredienteSmoothie, true, false, 8.0);
    MateriePrima ingredienteMancarePui[] = {
        MateriePrima("Pui", 'S', 0.6),
        MateriePrima("Legume", 'V', 0.4),
        MateriePrima("Condimente", 'S', 0.02)
    };
    Preparat mancarePui("Pui cu legume", 3, ingredienteMancarePui, false, true, 15.0);
    MateriePrima ingredienteCafea[] = {
        MateriePrima("Cafea", 'L', 0.2),
        MateriePrima("Zahar", 'S', 0.01),
        MateriePrima("Lapte", 'L', 0.1)
    };
    Preparat cafea("Cafea", 3, ingredienteCafea, true, false, 8.0);

    MateriePrima ingredienteSucNatural[] = {
        MateriePrima("Suc de mere", 'L', 0.5),
        MateriePrima("Zahar", 'S', 0.02)
    };
    Preparat sucNatural("Suc Natural", 2, ingredienteSucNatural, true, false, 6.0);
    MateriePrima ingredienteTiramisu[] = {
        MateriePrima("Blat de biscuiti", 'S', 0.3),
        MateriePrima("Esenta de vanilie", 'S', 0.02),
        MateriePrima("Cafea", 'L', 0.2),
        MateriePrima("Cacao", 'S', 0.01),
        MateriePrima("Mascarpone", 'S', 0.3)
    };
    Preparat tiramisu("Tiramisu", 5, ingredienteTiramisu, false, true, 12.0);
    MateriePrima m4("Blat de biscuiti", 'S', 3);
    MateriePrima m5("Esenta de vanilie", 'S', 0.6);
    MateriePrima m6("Cafea", 'S', 12);
    MateriePrima m7("Cacao", 'S', 5);
    MateriePrima m8("Mascarpone", 'S', 30);
    depozit += m5;
    depozit += m6;
    depozit += m7;
    depozit += m8;
    depozit += m4;

    Meniu meniu;
    meniu = meniu + paste + salata + suc + bere + omleta + pizza + smoothie+mancarePui+cafea+sucNatural+tiramisu;
    //cout << meniu;
    /*Preparat p;
    cin >> p;
    cout << p;
   
    meniu = meniu + p;
    cout << meniu;*/
    Comanda comanda1;
    comanda1 = comanda1 + pizza;
    cout << comanda1 << endl;
    comanda1.eliminaDepozit(pizza, depozit);
    
    Comanda comanda2;
    comanda2 = comanda2 + pizza;
    comanda2.eliminaDepozit(pizza, depozit);
    cout << comanda2 << endl;
    Client client1("Marcel", 50);
    client1 += comanda1;
    client1 += comanda2;
    cout << client1 << endl;
    ComenziRestaurant restaurant;
    restaurant += client1;
    cout << restaurant;

    string comandaConsola;
    string raspuns;


    cout << "Cine esti?(manager/client)" << endl;
    getline(cin, raspuns);
    Client c2("Maria", 70);

    bool esteManager = (raspuns == "sunt manager" || raspuns == "manager");
    Comanda c;

    //pentru a vedea comenzile disponibile pentru fiecare rol dati comanda "comenzi" si vor aparea toate

    while (true) {

        cout << "$ ";
        getline(cin, comandaConsola);

        //schimb rolul intre manager al restaurantului si client 
        if (comandaConsola == "schimba rolul") {
            esteManager = !esteManager;
            cout << "Rolul a fost schimbat la " << (esteManager ? "manager" : "client") << endl;
        }
        else if (esteManager) {
            // Comenzi specifice managerului
            if (comandaConsola == "afiseaza stocuri") {
                cout << depozit << endl;
            }
            else if (comandaConsola == "comenzi") {
                cout << "\nLista de comenzi pe care le poate scrie un manager:\n";
                cout << " afiseaza stocuri\n";
                cout << " afiseaza stoc[denumire]\n";
                cout << " adauga stoc [denumire] [cantitate]\n";
                cout << " adauga depozit nou\n";
                cout << " afiseaza reteta [nume preparat]\n";
                cout << " afiseaza meniu\n";
                cout << " schimba rolul = va puteti comporta ca un client\n";
                cout << " adauga meniu(materii prime noi)\n";
                cout << " exit\n";
                cout << endl;
            }


            // adauga stoc [denumire] [cantitate]
            else if (comandaConsola.substr(0, 11) == "adauga stoc") {
                char text[100];
                strcpy(text, comandaConsola.substr(12).c_str());
                char* denumire = strtok(text, " ");
                char* cantitateStr = strtok(nullptr, " ");

                if (denumire != nullptr && atof(cantitateStr) > 0) {
                    // Convertim cantitatea la float
                    float cantitate = atof(cantitateStr);
                    if (depozit.exista(denumire)) {
                        depozit.adaugaStoc(denumire, cantitate);
                        cout << "Materia prima " << denumire << " in cantitate de " << cantitate << " a fost adaugata in depozit" << endl;
                    }
                }
                else {
                    if (!depozit.exista((denumire))) {
                        cout << "Nu exista aceasta materie prima in depozit!" << endl;
                    }
                    else {
                        cout << "Cantitatea trebuie sa fie un numar pozitiv!" << endl;
                    }
                }

            }
            //afiseaza stoc [cantitate]
            else if (comandaConsola == "afiseaza stoc") {
                cout << "Eroare: comanda corecta: afiseaza stoc [denumire]" << endl;
            }
            else if (comandaConsola.substr(0, 13) == "afiseaza stoc") {
                // Extrage denumirea începând cu indexul 14
                string denumire = comandaConsola.substr(14);

                if (!denumire.empty() && denumire.length() >= 2) {

                    depozit.afisareStoc(denumire.c_str());
                }

            }

            //afisare meniu
            else if (comandaConsola == "afiseaza meniu") {
                cout << meniu;
            }
            else if (comandaConsola == "adauga meniu") {
                Preparat p;
                cin >> p;

                meniu = meniu + p;
            }
            //introduc un ingredient inexistent in depozit
            else if (comandaConsola == "adauga depozit nou") {
                MateriePrima m;
                cin >> m;
                if (depozit.exista(m.getNumeIngredient())) {
                    cout << "Ingredient deja existent" << endl;
                }
                else {
                    depozit += m;
                }
            }
            //adauga meniu
            else if (comandaConsola.substr(0, 15) == "afiseaza reteta") {
                string numePreparat = comandaConsola.substr(16);  // Extrage numele preparatului
                meniu.afiseazaRetetaPreparat(numePreparat);
            }
            else if (comandaConsola == "exit") {
                cout << "Ai iesit din zona de comenzi!" << endl;
                break;
            }
            else {
                cout << "Comanda la consola invalida pentru manager!" << endl;
            }
        }
        else {
            // Comenzi specifice clientului

            if (comandaConsola == "afiseaza meniu") {
                cout << meniu << endl;
            }
            else if (comandaConsola == "comenzi") {
                cout << "\nLista de comenzi pe care le poate scrie un client:\n";
                cout << "afiseaza meniu\n";
                cout << "afiseaza mancaruri\n";
                cout << "afiseaza bauturi\n";
                cout << "schimba rolul= va puteti comporta ca un manager\n";
                cout << "afiseaza reteta [nume preparat]\n";
                cout << "comanda [denumire] [cantitate]\n";
                cout << "afiseaza comanda\n";
                cout << "anuleaza comanda\n";
                cout << "exit\n";
                cout << endl;

            }

            else if (comandaConsola == "afiseaza mancaruri") {
                meniu.afiseazaMancaruri();
            }
            else if (comandaConsola == "afiseaza bauturi") {
                meniu.afiseazaBauturi();
            }
            else if (comandaConsola == "schimba rolul") {
                esteManager = !esteManager;
                cout << "Rolul a fost schimbat la " << (esteManager ? "manager" : "client") << endl;
            }
            // afiseaza reteta [denumire preparat]
            else if (comandaConsola.substr(0, 15) == "afiseaza reteta") {
                string numePreparat = comandaConsola.substr(16);  // Extrage numele preparatului
                meniu.afiseazaRetetaPreparat(numePreparat);
            }
            else if (comandaConsola == "adauga meniu" || comandaConsola == "afiseaza stocuri" || comandaConsola == "afiseaza stoc") {
                cout << "Nu ai permisiunea de a manipula ce este in depozit!\nDaca vrei sa fi manager scrie comanda << schimba rolul >>!" << endl;
            }
            else if (comandaConsola == "exit") {
                cout << "Ai iesit din zona de comenzi!" << endl;
                break;
            }


            else if (comandaConsola.substr(0, 7) == "comanda") {
                string restComanda = comandaConsola.substr(8);
                size_t pos = restComanda.rfind(' ');

                if (pos != string::npos) {
                    string denumire = restComanda.substr(0, pos);
                    string cantitateStr = restComanda.substr(pos + 1);

                    if (cantitateStr.find_first_not_of("0123456789") == string::npos) {
                        int cantitate = stoi(cantitateStr);
                        int potFiServite = 0; // numarul care pot fi servite 
                        if (meniu.existaInMeniu(denumire)) {
                            int index = meniu.gasesteIndexPreparat(denumire);

                            for (int i = 0; i < cantitate; i++) {
                                if (index < meniu.getNrBauturi()) {
                                    Preparat p = meniu.getIndexBauturi(index);

                                    if (p.poateFiServit(depozit)) {
                                        potFiServite++;
                                        //cout << "Preparatul " << denumire << " poate fi servit!" << endl;
                                        c.adaugaPreparatComanda(p);
                                        //cout << c;
                                        c.eliminaDepozit(p, depozit);
                                    }
                                    else {
                                        cout << "Nu exista suficiente stocuri in depozit pentru acest preparat!" << endl;
                                        break;
                                    }
                                }
                                else if (index >= meniu.getNrBauturi() && index < (meniu.getNrBauturi() + meniu.getNrMancaruri())) {
                                    Preparat p = meniu.getIndexMancaruri(index - meniu.getNrBauturi());

                                    if (p.poateFiServit(depozit)) {
                                        potFiServite++;
                                        //cout << "Preparatul " << denumire << " poate fi servit!" << endl;
                                        c.adaugaPreparatComanda(p);
                                        //cout << c;
                                        c.eliminaDepozit(p, depozit);
                                    }
                                    else {
                                        cout << "Nu exista suficiente stocuri in depozit pentru acest(e) preparat(e)!" << endl;
                                        break;
                                    }
                                }
                            }
                            if (potFiServite < cantitate) {
                                cout << c;
                                cout << "Doriti sa anulati comanda pentru celelalte preparate? (da=1/nu=0) ";
                                bool anulat;
                                cin >> anulat;
                                if (anulat) {
                                    c.anuleazaComanda(depozit);
                                    cout << "Comanda cu id " << c.getId() << " a fost golita" << endl;
                                    //cout << c;
                                }
                                cout << endl;
                            }
                            else {
                                cout << "Comanda plasata cu succes!" << endl;
                            }
                        }
                        else {
                            cout << "Preparatul introdus nu exista in meniu!" << endl;
                        }
                    }
                    else {
                        cout << "Comanda invalida! Formatul corect: comanda [denumire] [cantitate]" << endl;
                    }
                }
            }
            else if (comandaConsola == "afiseaza comanda") {
                cout << c;
            }
            else if (comandaConsola == "anuleaza comanda") {
                c.anuleazaComanda(depozit);
                cout << "Comanda cu id " << c.getId() << " a fost golita" << endl;
            }



            else {
                cout << "Comanda la consola invalida pentru client!" << endl;
            }
        }
    }
    c2 += c;
    restaurant += c2;



    
    return 0;
    //sf main
}




