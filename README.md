<h1>Submit to grader from home!</h1>
<h2>Οδηγίες χρήσης:</h2>
<ol>
<li>Είσοδος στο grader με το username και το password σου</li>
<li>Πήγαινε στην σελίδα με την εκφώνηση της άσκησης, πχ: <a href="http://grader.softlab.ntua.gr/index.php?page=problem&id=9">http://grader.softlab.ntua.gr/index.php?page=problem&id=9</a></li>
<li>Κάνε login στο putty με τα στοιχεία σου στο putty</li>
<li>
Πληκτρολόγησε:

`edit formsubmit.c`

και στην γραμμη εντολών του vi εκτέλεσε την εντολή:
`:set paste`. Έπειτα αντίγραψε το περιεχόμενο του αρχείου formsubmit.c πάνω και επικόλησε το στο vi με το command: `Shift+Ins`. Τέλος, κλείσε το vi αποθηκεύοντας με `:wq` και κάνε compile το αρχείο με την εντολή: `cc formsubmit.c`

</li>
<li>Πληκτρολόγησε:

`edit config.txt` και αντίγραψε το `config.txt` πάνω αντικαθιστώντας τα εξής:

  <ul>
    <li>Θέσε το filename ίσο με το όνομα του αρχείου που θες να υποβάλεις</li>
    <li>Θέσε το task ίσο με τον αριθμό που έπεται του id= στο link της εκφώνησης (στο παραπάνω παράδειγμα είναι το: 9 )</li>
    <li>Θέσε το cookie ίσο με την τιμή του cookie με όνομα PHPSESSID στο site του grader (Για να το βρεις πατάς δεξί κλικ στην σελίδα, μετά Inspect, και πλοηγείσαι στο tab με όνομα Application και τέλος επιλέγοντας στην αριστερή μπάρα τα cookies)</li>
  </ul>
 </li>
 <li>
  Τρέξε την εντολή:

  ``run formsubmit.exec``
 </li>
</ol>
