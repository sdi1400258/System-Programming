Προγραμματισμός Συστήματος

Σχολιασμός Εργασίας 2


Στοιχεία

Όνομα φοιτητή : Ακκογιούνογλου Γεώργιος
Αριθμός Μητρώου : 1115 2014 00258

Σχολιασμός

Η εργασία είναι υλοποιημένη σύμφωνα με όλες τις προδιαγραφές που αναφέρονται στην εκφώνηση. Για αρχή πάμε στην βάση δεδομένων μας και διαβάζω από τον δωσμένο φάκελο τις χώρες και ταξινομώ τις εγγραφές στις εκάστοτε δομές που έχω φτιάξει από την 1η εργασία . Στην συνέχεια δημιουργώ τόσα pipes όσα ζητάει ο χρήστης κατά την εκτέλεση του προγράμματος. Ένα παράδειγμα εκτέλεσης είναι: 
	./travelMonitor –m numMonitors -b bufferSize -s sizeOfBloom -i input_dir
Μέτα τη δημιουργία των pipes, ο πατέρας μοίραζει τις εγγραφές απο κάθε χώρα στα παιδιά με τη διαδικασία του Round Robin. Το κάθε παιδί δημιουργεί δομές Bloom Filter και Skip List για τις εγγραφές κάθε χώρας ξεχωριστά. 
Αναλόγως την εντολή από τον πατέρα το κάθε παίδι στέλνει στον πατέρα τις απαντήσεις που χρειάζονται.

	/travelRequest citizenID date countryFrom countryTo virusName
Σε περίπτωση απάντησης No από το BloomFilter, που σημαίνει οτί ο πολίτης δεν μπόρει να ταξιδέψει , εμφανίζεται μήνυμα :
	Rejected by parent because of bloom filter: No
Σε περίπτωση απάντησης Maybe , ελέγχεται εαν ο πόλιτης έχει εμβολιαστεί μέσα στο τελευταίο εξάμηνο και μπορεί να ταξιδέψει.
Αντίστοιχα μηνύματα Rejected εμφανίζονται σε περίπτωση που δεν υπάρχει η χώρα countryFrom από την οποία προέρχεται ο πόλιτης, είτε από ιο που δεν υπάρχει καταγεγραμένος στη βάση δεδομένων μας. Για να υπολογιστεί εαν ο πολίτης είναι εμβολιασμένος το τελευταίο εξάμηνο δημιουργήθηκε το αρχείο datevacc.cpp .

	/travelStats virusName date1 date2 [country]
Η εντολή  travelStats εκτελείται μόνο στον πατέρα καθώς είναι αυτός που κρατάει στην μνήμη του τα log files, και πόσα requests έχουμε καθώς accepted και rejected.


	/addVaccinationRecords country
Αυτή η εντολή στέλνει σήμα στο παιδί που διαχειρίζεται το εκάστοτε country μέσω της SIGUSR1, και έτσι το παιδί διάβαζει ότι νέο αρχείο βρει και ενημερώνει τις δομές δεδομένων μας και  στις στέλνει πίσω στον πατέρα μεσω pipe.

	/searchVaccinationStatus citizenID
Ο πατέρας με broadcasting προωθεί το αίτημα να βρεθεί η κατάσταση εμβολιασμού για τον συγκεκριμένο πολίτη σε όλα τα παιδιά. Όταν βρεθεί τυπώνει το Vaccination Status του πολίτη καθώς και την ηλικία του και τη χώρα καταγωγής του.

Για την ομαλή χρήση του προγράμματος μου έχω δημιουργήσει ένα μενού για την διευκόλυνση τη δική μου αλλά και τη δική σας.

WELCOME

Press [ /travelRequest citizenID date countryFrom CountryTo virusName ] to check if a citizen is vaccinated and allowed to travel !
Press [ /travelStats virusName date1 date2 ] to check Total Requests for traveling, accepted and rejected Requests too!
Press [ /travelStats virusName date1 date2 country ] to check Total Requests for traveling for a specific country, accepted and rejected Requests too!
Press [ /addVaccinationRecords country ] to add a country file for processing !
Press [ /searchVaccinationStatus citizenID ] to check the vaccination status of this citizen !
Press [ /exit ] to exit !

Type  [ /menu ] to print menu again !  
Press a command to run: 


Ορίσματα:

Ο Χρήστης δίνει τα εξής ορίσματα:
	πχ.
	./travelMonitor -m  numMonitors -b buffersize -s sizeOfBloom -i InputDir/
	όπου
	-numMonitors : ο αριθμός των Monitors - Παιδίων που θα δημιουργήσει η εφαρμογή
	-buffersize : το μέγεθος του buffer για δίαβασμα και εγγραφή σε κάθε pipe
	-sizeOfBloom : το μέγεθος του BloomFilter σε byte
	-InputDir : Ο φάκελος με του υποφακέλους, που εκεί μέσα είναι όλες οι εγγραφές κάθε χώρας.



-Όσο αναφορά τα buffersize , σε περίπτωση που ένα μήνυμα που πρέπει να περάσει από το pipe, είναι μεγαλύτερο από το buffersize ( message > buffersize ) , τότε σπάω το μήνυμα σε επιμέρους μηνύματα ώστε να χωράνε στα buffersize του pipe.

-Σε περίπτωση που το μήνυμα είναι μικρότερο από  το buffersize ( message < buffersize ) , τοτε στέλνω μόνο  το μήνυμα σαν size και δεν δεσμεύω όλο το buffersize, παρά μόνο όσο χρειάζεται.

-Σε περίπτωση που ένα παιδί λαμβάνει SIGUSR1 κατά τη διάρκεια αποστολής δεδομένων του προς τον πατέρα, εχώ φτιάξει το πρόγραμμα μου έτσι ώστε να μπλοκάρει οποιοδήποτε άλλο σήμα κατά τη διάρκεια αποστολής. (main_vaccinemonitor.cpp  *150* *154* , main_travelmonitor.cpp  *405* *409*)

-Στο πρόγραμμα μου δεν έχω υλοποιήση την select() κατά την οποία ο parent process δεν μπλοκάρει περιμένοντας ένα παιδί να καθυστερεί στο να στείλει πίσω δεδομένα που του έχουν ζητηθεί και συνεχίζει να λαμβάνει από ολα τα παιδιά οσα δεδομένα έχουν έτοιμα για αποστολή. Αυτό που κάνω, είναι να στέλνω με for loop τις εντολές στα παιδιά και περιμένω απάντηση στον πατέρα. 

-Χρησιμοποιώ blocking pipes, καθώς έτσι ένα παιδί ενημερώνεται αμέσως εάν ο πατέρας θέλει να του μεταβιβάσει κάποια εντολή.

-Το πρωτόκολλο επικοινωνίας ανάμεσα σε πατέρα και παιδία το έχω αναπτύξει στο αρχείο readerwriter.cpp , εκεί είναι εμφανείς όλες οι εντολές εγγραφής και ανάγνωσης μέσω pipes, για parent processes και monitors. Πριν γίνει η εγγραφή ή η ανάγνωση μέσω pipe, ο πατέρας ή το παιδί , στέλνει πρώτα το messagesize (σειρά *14*), για το μήνυμα που θα ακολουθήσει, για να σιγουρευτούμε ότι θα σταλθεί ολοκληρωμένο το μήνυμα.

-Στο αρχείο readerwriter_all.cpp έχω χρησιμοποιήσει και τροποποιήσει τις συναρτήσεις read_all - write_all από τις διαφάνειες. 

-Στο αρχείο main_travelmonitor.cpp έχω τη συνάρτηση reviveChildren, που σε περίπτωση που γίνει kill ενός παιδιού αναλαμβάνει να ξαναδημιουργήσει το παιδί και να στείλει τις εγγραφές και τα BloomFilters που είχε και πριν.


Στο φάκελο μου υπάρχει Makefile και με την εντολή make μεταγλωττίζεται το πρόγραμμα, και με make clean , διαγραφή .o files & exec file.


Bash Script : 
		./create_infiles.sh inputFile input_dir [ numFilesPerDirectory >= 1 ]	

Όσο αναφορά το bash script, έχω υλοποιήσει όλα τα ερωτήματα που αναγράφονται στην εκφώνηση 
όπως :  1) Τον έλεγχο εισόδου για νούμερα.
	2) Τη δημιουργία καταλόγου με όνομα που δίνεται κατά την εκτέλεση στο δεύτερο όρισμα input_dir. Σε περίπτωση που ο κατάλογος 
	   υπάρχει, εκτυπώνει κατάλληλο μήνυμα και τερματίζει το πρόγραμμα.
	3) Διαβάζει το inputFile, το οποίο δίνεται και αυτό στο πρώτο όρισμα κατά την εκτέλεση.
	4) Μετά την ανάγνωση του inputFile, αποθηκεύει τις χώρες σε ένα array, για να καταφέρει να δημιουργήσει subdirectories μέσα 
		στο Input_dir
	5) Σε κάθε subdirectory δημιουργεί αριθμό αρχείων , όσων έχουν ζητηθεί κατά την εκτέλεση στο τρίτο και τελευταίο όρισμα.
		Έτσι δημιουργεί εκάστοτε αριθμό αρχείων για κάθε χώρα και μοιράζει τις εγγραφές με τη βοήθεια Round Robin. 
		Έτσι λοιπόν έχουμε κάθε χώρα από ένα φάκελο με number files per directory , όσα έχουν ζητηθεί , και μέσα σε κάθε 
		αρχείο ισομοιρασμένες εγγραφές για την αντίστοιχη χώρα.


