# hashCode2018

## Fase 1 - Ottengo la struttura dati necessaria
Per ottenere la struttura dati apro il file in input e poi inserisco i valori all'interno della struttura dati.

## Fase 2 - Genero un risultato
Genero un risultato attraverso la struttura dati, in modo random che poi andrà affinato in modo da tentare di raggiungere il massimo più velocemente.

## Fase 3 - Calcolo il punteggio secondo le specifiche di google
In base a ciò che ha scritto google nella parte in cui spiega come verrà calcolato il punteggio dal file del risultato ed in base al risultato che abbiamo appena ottenuto calcoliamo una previsione sul punteggio dato dal risultato.

## Fase 4 - Controllo del punteggio
Controllo il punteggio ottenuto con il punteggio massimo trovato fino ad ora

### Punteggio calcolato > punteggio massimo attuale
In questo caso dovremo sostituire il massimo attuale ed in più modificare il file da consegnare poi a google con il risulato che ha generato il nuvo massimo attuale
Diminuisco di uno il MASSIMO di punteggi uguali da ottenere per terminare il test, dato che raggiungere nuovamente punteggi sempre più alti diventa sempre più difficile

### Punteggio calcolato = punteggio massimo attuale
Avendo raggiunto nuovamente il massimo attuale aumento il contatore delle volte in cui l'ho raggiunto
se il contatore ha raggiunto il massimo prefissato terminare il programma

### Punteggio calcolato < punteggio massimo attuale
Ignorare il risultato ed il punteggio

## fase 5 - ripetizione
Ripetere dalla fase 2 fino a che non si raggiunge un ipotetico punteggio massimo, a quel punto il programma termina e bisogna caricare il file contente il risultato su google
