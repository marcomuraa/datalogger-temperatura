## Introduzione

Il progetto RadioLab offre agli studenti delle scuole superiori di avvicinarsi al mondo della radioattività, studiando come funziona e offrendo un’esperienza di laboratorio che si conclude con la misurazione di gas Radon tramite rilevatori al CR-39. 

Uno dei passaggi iniziali della prova di laboratorio è, dopo aver esposto i rilevatori per 6 mesi, di sottoporli ad un bagno ad alta temperatura in una soluzione di soda caustica; questo rende visibili le tracce lasciate dalle particelle alpha al microscopio ottico, rendendo possibile proseguire con l’esperimento. 

L’INFN fornisce alle scuole, oltre ai rilevatori stessi, una semplice friggitrice da cucina per eseguire questo passaggio dell’esperimento. La nostra scuola ha però a disposizione un bagno termostatico, ovvero un dispositivo creato appositamente per portare liquidi o sostanze chimiche ad alta temperatura, mantenendola. 

Abbiamo deciso quindi di usare il bagno termostatico al posto della friggitrice, però abbiamo anche deciso di controllare quanto fosse preciso questo dispositivo.

## Il datalogger di temperatura

Un datalogger è un dispositivo che raccoglie dati o misurazioni a intervalli di tempo definiti e li salva per essere utilizzati successivamente. I dati misurati possono essere di qualunque tipo: temperatura, pressione, umidità ma anche vibrazioni, come nei sismografi; anche il supporto sul quale i dati vengono salvati può essere di vario tipo, digitale o analogico (un rotolo di carta ad esempio, o una scheda di memoria).

Arduino è una piattaforma hardware con microcontrollore, semplice da programmare e con infinite possibilità per interfacciarsi con motori, sensori e una miriade di altri componenti elettronici. E’ quindi possibile interfacciare Arduino con un sensore di temperatura e un dispositivo di memorizzazione per creare un semplice ma affidabile datalogger di temperatura. 

Il sensore di temperatura scelto è il DS18B20: può essere collegato ad Arduino con 3 fili, alimentazione, massa e linea dati. Il protocollo di comunicazione si chiama appunto "One Wire" perchè ha bisogno di un solo conduttore per trasmettere dati in modo bidirezionale. Un altro vantaggio del protocollo è il fatto che ogni dispositivo possiede un indirizzo e quindi il master (in questo caso Arduino, il dispositivo principale che comanda tutti gli altri sul bus) può comunicare con più di un dispositivo; al dispositivo finale sono collegati due sensori di temperatura, in modo tale da poter registrare la temperatura ambiente e la temperatura dell’acqua nel bagno termostatico. 

Per poter salvare i dati ho optato per una semplice SD breakout board; si tratta di una scheda elettronica con uno slot per scheda microSD (la stessa usata per cellulari e macchine fotografiche) e un microcontrollore per rendere più semplice interfacciarsi con Arduino o altri microcontrollori. Anche questo si collega con pochi fili all’Arduino.

A questo punto ho caollegato tutti i componenti tramite breadboard (una scheda con dei buchi collegati elettricamente tra loro per provare velocemente un circuito senza saldare permenentemente i componenti).

Dopo aver testato i singoli componenti con i rispettivi "sketch" di prova (lo sketch è il file che contiene il codice che Arduino esegue) e aver controllato che i singoli componenti funzionavano correttamente, ho cominciato a scrivere il codice finale per farli funzionare insieme. Come dicevo prima i sensori di temperatura hanno un loro indirizzo, quindi ho utilizzato uno sketch creato appositamente per trovare gli indirizzi di tutti i dispositivi collegati al bus OneWire; dopo averli trovati ho potuto aggiungere il codice per scrivere sulla scheda di memoria i dati raccolti. Ho aggiunto un ritardo di 30 secondi tra una misura e l’altra, valore che può essere modificato abbastanza semplicemente avendo accesso ad un computer e qualche minuto di tempo. Ho anche aggiunto un led colorato che si illumina quando i dati di temperatura raccolti vengono scritti correttamente sulla scheda SD. 

A questo punto funzionava tutto correttamente, ho saldato permanenetementi i componenti su una scheda perforata e abbiamo utilizzato il dispositivo per misurare la temperatura nel bagno termostatico. Abbiamo osservato che sia il datalogger sia il bagno termostatico funzionavano correttamente.

## Miglioramenti

Dopo la fine della scuola ho avuto più tempo libero a disposizione e ho potuto migliorare il datalogger: ho ridotto le dimensioni della scheda perforata con i componenti e ho utilizzato un Arduino nano al posto dell’Arduino Uno che avevo usato originariamente. Ho poi creato con Autodesk Fusion 360 una scatola su misura che ho stampato con la stampante 3D. In questo modo non ci sono componenti esposti ed è tutto più compatto e sinceramente un pò meno brutto esteticamente.

Un ulteriore miglioramento sarebbe aggiungere un potenziometro (una manopola) per regolare il ritardo tra le misure; a questo punto sarebbe necessario un piccolo schermo per vedere il valore attuale del ritardo, sarebbe quindi possibile usare lo stesso schermo anche per far vedere le ultime 2 o 3 misure registrate.

Infine sarebbe utile aggiungere un modulo RTC (real time clock), lo stesso che usano tutti i computer per ricordarsi data e ora. Al momento l’unico modo per conoscere l’orario delle misure è segnare separatamente l’orario della prima misura, ovvero quando si attacca il datalogger alla corrente; una volta terminata la misura, importare i dati in excel e creare una colonna aggiuntiva per l’orario; segnare nella prima cella l’orario di inizio, e nella casella sotto aggiungere 30 secondi; a questo punto si può usare la funzione di autocompletamente di excel trascinando dall’angolo la seconda casella fino in fondo. 

## Istruzioni

1. Procurarsi un cavo da USB A a USB micro B (tipo per navigatore satellitare);

2. Procurarsi un alimentatore USB da almeno 500mA (quello dell’iPhone ad esempio) o un powerbank;

3. inserire una scheda microSD nell’apposito slot; consiglio una scheda da massimo 4gb visto che comunque il file del datalog pesa pochi kb; inoltre la scheda deve essere formattata come FAT16 o FAT32;

4. alimentare il datalogger.

Nota: non scollegare l’alimentazione mentre la luce di scrittura è accesa, altrimenti la scheda SD potrebbe corrompersi. Consiglio di aspettare la luce, quando si accende aspettare che si spenga, aspettare 5 secondi e poi scollegare l’alimentazione. 

## Come riprogrammare il ritardo tra le misure

1. Installare Arduino IDE;

2. aprire lo sketch "datalog_no_rtc"

3. cambiare il valore alla riga 76 delay(30000); nota: è espresso in millisecondi, quindi 30 secondi = 30000

4. collegare il datalogger con il cavo USB al computer; in Arduino IDE selezionare tools > board > arduino nano; poi tools > port e selezionare la porta a cui è connesso Arduino (in questo elenco dovrebbe esserci una sola porta). Ora sketch > upload.

