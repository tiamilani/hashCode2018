#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;

string nomeTest = "kittens";
string nomeFileinput = "input.txt";     //File da cui ottenere le info
string nomeFileOutput = "output.txt";   //File su cui salvare il risultato da dare a google
int MAX_EQUALS_RESULT = 20;             //Numero massimo di punteggi uguali
vector<int> v;                          //Struttura dati su cui salvare le info
ofstream LOG;                           //File di log
string nomeFileMaxPoints = "output";          //Nome del file con il punteggio massimo al termine dell'esecuzione

void inserimentoOggetti(ifstream*);     //Funzione per inserire gli oggetti nella struttura dati
int execute(int,int&);                  //Funzione che dalla struttura dati calcola il risultato e lo salva sul file da dare a google
int getRandomNumber(int);               //Funzione per ottenere un numero random
int calculatePoints(string);            //Funzione per calcolare il punteggio di una soluzione

int main(){
    srand (time(NULL)); //Imposto il seme per la generazione di numeri random

    LOG.open("LOG_" + nomeTest);    //Apro il file di log per la scrittura

    ifstream input;
    input.open(nomeFileinput);  //Apro il file di (*input) per la lettura

    LOG << "File di (*input) aperto" << endl;

    string line;
    while (getline(input, line))    //Ottengo la linea
    {
        istringstream iss(line);
        int a;  //Variabile su cui salverò il valore della linea
        if (!(iss >> a)) {  //Per questa linea ottengo il valore richiesto, se la linea avesse due valori avrei potuto fare 'iss >> a >> b' in modo da salvare il primo su a ed il secondo su b
            break; //Errore
        }
        v.push_back(a); //Inserisco il valore ottenuto nella struttura dati
    }

    LOG << "Oggetti inseriti nella struttura dati" << endl;

    input.close();  //Chiudo il file di (*input) non più necessario

    int maxPoints = 0;      //Massimo punteggio ottenuto fino ad ora
    int counterEquals = 0;  //Contatore di quante volte ottengo un determinato punteggio massimo
    int i = 1;              //Contatore dei tentativi

    while(counterEquals < MAX_EQUALS_RESULT){   //Continuo a fare tentativi finche il contatore dei risultati uguali al massimo non raggiunge il massimo settato
        LOG << "Tentativo -> " << i << endl;
        //cout << "Tentativo -> " << i << endl;

        int value = execute(i,maxPoints); //Ottengo il responso dalla funzione che genera il risultato

        if(value == 1){ //Caso di nuovo punteggio massimo
            LOG << "Trovato nuovo punteggio massimo -> " << maxPoints << endl;
            cout << "Trovato nuovo punteggio massimo -> " << maxPoints << endl;
            counterEquals = 0;  //Resetto il contatore per farlo ricominciare
            MAX_EQUALS_RESULT--;    //Dato che ottenre un punteggio sempre più elevato è più difficile, diminuisco il massimo di punteggi uguali da ottenere per considerare concluso il test
        } else if(value == 0){  //Caso di punteggio uguale al massimo attuale
            counterEquals++;
            LOG << "Il punteggio è uguale al precedente " << counterEquals << endl;
            //cout << "Il punteggio è uguale al precedente " << counterEquals << endl;
        } else {    //Caso di punteggio inferiore al massimo attuale
            LOG << "Il punteggio è inferiore al massimo" << endl;
            //cout << "Il punteggio è inferiore al massimo" << endl;
        }
        i++;
        //usleep(500000); //Sleep per il seme del random del prossimo tentativo
    }

    return 0;
}

void inserimentoOggetti(ifstream* input){ //Funzione che andrà modificata in base alla struttura del file di (*input)
    string line;
    while (getline((*input), line))    //Ottengo la linea
    {
        istringstream iss(line);
        int a;  //Variabile su cui salverò il valore della linea
        if (!(iss >> a)) {  //Per questa linea ottengo il valore richiesto, se la linea avesse due valori avrei potuto fare 'iss >> a >> b' in modo da salvare il primo su a ed il secondo su b
            break; //Errore
        }
        v.push_back(a); //Inserisco il valore ottenuto nella struttura dati
    }
}

int getRandomNumber(int MAX){   //Il numero random generato sarà tra 0 e MAX compresi
    return rand() % MAX;
}

int calculatePoints(string fileinput){ //Funzione che andrà modificata in base a come andrà effettuato il calcolo del punteggio sul risultato
    int points;
    ifstream input;
    input.open(fileinput);

    string line;
    while (getline(input, line))    //Ottengo la linea
    {
        istringstream iss(line);
        int a,b,c;  //Variabili su cui salverò il valore della linea
        if (!(iss >> a >> b >> c)) {  //Per questa linea ottengo il valore richiesto, se la linea avesse due valori avrei potuto fare 'iss >> a >> b' in modo da salvare il primo su a ed il secondo su b
            LOG << "ERROR" << endl;
            break; //Errore
        }
        points = a+b+c;
    }
    return points;
}

string tentativoRandom(int nTentativo){
    int a,b,c;

    //In questa parte genero la possibile soluzione del problema
    //***************************************
    a = v.at(getRandomNumber(v.size()));
    b = v.at(getRandomNumber(v.size()));
    c = v.at(getRandomNumber(v.size()));
    //***************************************

    //In questa parte scrivo la soluzione trovata su di un file di output secondo le specifiche fornite
    //**************************************
    string fileOutput = "output_" + to_string(nTentativo);
    ofstream output;
    output.open(fileOutput);   //Apro il file contenente il risultato da dare poi a google
    output << a << " " << b << " " << c << endl;    //Scrivo il risultato che andrà dato a google
    output.close();
    //**************************************

    return fileOutput;
}

int execute(int nTentativo,int& maxPoints){

    //****************PARTE 1****************
    //Eseguo il tentativo random e ottengo il nome del file di output prodotto
    string fileOutputTemporaneo = tentativoRandom(nTentativo);
    //**********************************************

    //***************PARTE 2*****************
    //Calcolo il punteggio dato dal file di output generato randomicamente
    int points = calculatePoints(fileOutputTemporaneo);    //Calcolo il punteggio dato dalla soluzione che ho trovato
    //**************************************************

    LOG << "Punteggio trovato: " << points << endl;

    //*****************PARTE 3******************
    //In questa parte confronto il punteggio con il massimo attuale
    if(points > maxPoints){ //Caso in cui io abbia trovato una soluzione migliore della precedente
        maxPoints = points; //Imposto il nuvo punteggio massimo attuale

        //Ho trovato un nuovo punteggio massimo, quindi elimino il file di output che dava il vecchio punteggio massimo
        if( remove( nomeFileMaxPoints.c_str() ) != 0 )
            LOG << "Error deleting file" << endl;
        else
            LOG << "File " << fileOutputTemporaneo << " successfully deleted" << endl;

        //Sostituisco il nome del file di output che genera il punteggio massimo
        nomeFileMaxPoints = fileOutputTemporaneo;
        return 1;
    } else if(points == maxPoints){ //Caso in cui il punteggio calcolato sia uguale al massimo attuale
        //Dando lo stesso punteggio elimino il file generato randomicamente in questo tentativo
        if( remove( fileOutputTemporaneo.c_str() ) != 0 )
            LOG << "Error deleting file" << endl;
        else
        LOG << "File " << fileOutputTemporaneo << " successfully deleted" << endl;
        return 0;
    } else {    //Caso in cui il punteggio calcolato sia inferiore al precedente
        //Punteggio inferiore al massimo, elimino il file generato in questo tentativo
        if( remove( fileOutputTemporaneo.c_str() ) != 0 )
            LOG << "Error deleting file" << endl;
        else
            LOG << "File " << fileOutputTemporaneo << " successfully deleted" << endl;
        return -1;
    }
    //*****************************************
}
