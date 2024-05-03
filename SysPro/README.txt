Προγραμματισμός Συστήματος

Σχολιασμός Εργασίας 1



Στοιχεία

Όνομα φοιτητή : Ακκογιούνογλου Γεώργιος
Αριθμός Μητρώου : 1115 2014 00258

Σχολιασμός

Η εργασία είναι υλοποιημένη σύμφωνα με όλες τις προδιαγραφές που αναφέρονται στην εκφώνηση. Πιο συγκεκριμένα, έχω υλοποιήσει τις δομές Bloom Filter και Skip List όπως ακριβώς 
αναγράφονται στην εκφώνηση της εργασίας. Έχω δημιουργήσει ένα δέντρο να τρέχει με την βοήθεια templates, και αναλόγως την περίπτωση δημιουργεί και ανατρέχει το εκάστοτε δέντρο, είτε αυτό ειναι για citizen, country, diseases. Τέλος, χρησιμοποιώ μία μονά συνδεδεμένη λίστα εκτέλεσης, όπου ολα εισέρχονται με pointer και προσθέτονται στην αρχή ή στο τέλος για καλύτερη απόδοση. Επίσης, εχω υλοποιήσει το bash script όπως ακριβώς ζητείται.

Για την υλοποιήση τους, έχω μια κλάση για κάθε δομή, ώστε να είναι πιο ευδιάκριτο ποια συνάρτηση χρησιμοποιεί η καθεμία. Πιο συγκεκριμένα, ανάλογα την εντολή που πληκτρολογεί ο χρήστης καλείται η εκάστοτε διεργασία και με τη σειρά της οδηγείται στην δομή που αντιστοιχεί.
Πιο συγκεκριμένα έχω οργανώσει ένα μενού που ο χρήστης μπορεί είτε να πληκτρολογήσει την εντολή που επιθυμεί είτε τον εκάστοτε αριθμό που αναγράφεται στο μενού για να τον οδηγήσει εκεί που επιθυμεί.

Για την οργάνωση του μενού αυτού με βοήθησε το αρχείο operations.cpp που γράφονται και αναπτύσονται όλες οι συναρτήσεις που κατευθύνονται από το μενού της main μου. Με την εντολή που εκτελείται κάθε φορά, ανατρέχω στην δομή που ζητείται, είτε αυτή είναι το Bloom Filter είτε η Skip List. Έχω αναπαράγει το bloom filter σαν έναν πίνακα 256 bits θέσεων, και συνοδεύεται απο 16 hash functions. Επίσης, για την διευκόλυνση μου έχω φτιάξει 2 Skip Lists για κάθε ασθένεια, στην μία εισάγονται μόνο όσοι έχουν εμβολιαστεί και στην άλλη όσοι δεν έχουν εμβολιαστεί.

Πιο συγκεκριμένα το μενού που με βοήθησε στην υλοποιήση αυτή είναι το εξής : 

WELCOME
Press 10 to check if this citizen has been vaccinated to this virus(Bloom Filter)
Press 20 to check if this citizen has been vaccinated to this virus (skip list)
Press 30 to check if this citizen has been vaccinated at all viruses (skip list)
Press 41 to check population status about a virus during 2 dates for country
Press 42 to check population status about a virus during 2 dates
Press 43 to check population status about a virus
Press 44 to check population status about a virus for a country 
Press 51 to check population status about a virus during 2 dates sorted by ages for country
Press 52 to check population status about a virus during 2 dates sorted by ages
Press 53 to check population status about a virus sorted by ages
Press 54 to check population status about a virus sorted by ages for a country
Press 60 to insert a Citizen to the vaccination programm
Press 70 to vaccinate now a citizen
Press 80 to check which citizens hasn't been vaccinated to this virus
Press 90 to exit
Ο χρήστης μπορεί να πληκτρολογήσει είτε τον αριθμό της εντολής όπως αυτός αναγράφεται στο μενού είτε την εντολή οπώς αυτη αναγράφεται στην εκφώνηση της άσκησης.


Ορίσματα

Ο χρήστης δίνει τα εξής ορίσματα:
	
$ ./diseaseMonitor -c Input_File -b BloomSize
	
    • Input_File : Αρχείο εισόδου
    • BloomSize : Μέγεθος του Bloom Filter

 Στο παραδοτέο αρχείο,  έχω συμπεριλάβει και το Makefile για ευκολότερη μεταγλώττιση του προγράμματος..

Εκτέλεση
Ενδεικτικές εκτελέσεις φαίνονται στη συνέχεια:

$ ./diseaseMonitor -c inputFile -b 256

WELCOME
Press 10 to check if this citizen has been vaccinated to this virus(Bloom Filter)
Press 20 to check if this citizen has been vaccinated to this virus (skip list)
Press 30 to check if this citizen has been vaccinated at all viruses (skip list)
Press 41 to check population status about a virus during 2 dates for country
Press 42 to check population status about a virus during 2 dates
Press 43 to check population status about a virus 
Press 44 to check population status about a virus for a country 
Press 51 to check population status about a virus during 2 dates sorted by ages for country
Press 52 to check population status about a virus during 2 dates sorted by ages
Press 53 to check population status about a virus sorted by ages
Press 54 to check population status about a virus sorted by ages for a country
Press 60 to insert a Citizen to the vaccination programm
Press 70 to vaccinate now a citizen
Press 80 to check which citizens hasn't been vaccinated to this virus
Press 90 to exit
Press a number or anything else to run the command directly: 54

Type the country and the virus : Greece H1N1
Command: popStatusByAge with arguments: Greece/H1N1
Greece [ 0-20] 0 7 0%
Greece [20-40] 1 8 12.5%
Greece [40-60] 1 4 25%
Greece [60+  ] 0 7 0%

Press a number or anything else to run the command directly: /popStatusByAge Greece H1N1
Command: popStatusByAge with arguments: Greece/H1N1
Greece [ 0-20] 0 7 0%
Greece [20-40] 1 8 12.5%
Greece [40-60] 1 4 25%
Greece [60+  ] 0 7 0%
Press a number or anything else to run the command directly: 10  
Type the id and the virus: 8 EVD
Command: vaccineStatusBloom with arguments: 8/EVD
No

Press a number or anything else to run the command directly: vaccineStatusBloom 8 EVD
Command: vaccineStatusBloom with arguments: 8/EVD
No

Press a number or anything else to run the command directly: 20
Type the id and the virus: 84 SARS-1
Command: vaccineStatus with arguments: 84/SARS-1
Vaccinated at Sunday, 26 October 2013

Press a number or anything else to run the command directly: vaccineStatus 84 SARS-1 
POSTFIX: 32
Command: vaccineStatus with arguments: 84/SARS-1
Vaccinated at Sunday, 26 October 2013

Press a number or anything else to run the command directly: exit


Τα αποτέλεσματα είναι ενδεικτικά καθώς χρησιμοποίησα το δικό μου inputFile που εφτιάξε το Bash script μου

Bash script :

Όσο αναφορά το bash script, έχω υλοποιήσει όλα τα ερωτήματα που αναγράφονται στην εκφώνηση 
όπως : τον έλεγχο για νούμερα εισόδο, το διάβασμα των αρχείων virusesFile και countriesFile, όπως επίσης και τη δημιουργία του inputFile ανάλογα με τα number of lines που πληκτρολογεί ο χρήστης. Έτσι, αμέσως μετά την πληκτρολόγηση του numlines , το bash script μου φτιάχνει το προφίλ κάθε ασθενή όπως ζητείται : 
    • CitizenId : Από 1-4 ψηφία με τυχαίο και μοναδικό αριθμό.
    • Όνομα και επίθετο με τυχαίο μήκος από 3 έως 12 χαρακτήρες.
    • Χώρα διαμονής, όπως αύτη επιλέγεται τυχαία από το αρχείο countriesFile.
    • Ασθένεια,  όπως αύτη επιλέγεται τυχαία από το αρχείο virusesFile.
    • Σε περίπτωση που είναι εμβολιασμένος αναγράφεται δίπλα τον ιό “YES”
σε περίπτωση που είναι εμβολιασμένος και “NO” εάν δεν είναι.(υπάρχει μία πιθανότητα 1/10, δίπλα από το “ΝΟ” (δηλαδή ο ασθενής δεν είναι εμβολιασμένος), να υπάρχει ημερομηνία εμβολιασμού και αυτό για να απορρίπτεται από το προγραμμά μας όταν εμφανίζεται .
    • Τέλος, όταν ενεργοποιείται το Dublicates Allowed, δίνοντας απο το πληκτρολόγιο τον αριθμό 1 διπλα από το numLines, τότε έχουμε για τον ίδιο ασθένη πληροφορίες και για άλλες ασθένιες και τυχόν εμβολιασμούς και τις ημερομηνίες τους.

./testFile virusesFile countriesFile [numlines= 1-9999] [dublicates = 0 or 1]


Η εργασία γράφτηκε και ανπτύχθηκε σε Sublime Text 3 , και έτρεξε σε περιβάλλον Linux Ubuntu 
με τη βοήθεια του Terminal.

