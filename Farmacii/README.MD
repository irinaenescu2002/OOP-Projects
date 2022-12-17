# Farmacii

Se dorește implementarea unei aplicații OOP care sa permita gestionarea activității
unor farmacii apartinand proprietarului X. Pentru fiecare farmacie se cunoaște cel puțin
denumirea, numărul de angajați și profiturile pe fiecare luna. Farmaciile pot fi și online. În
acest caz se cunoaște doar adresa web, numărul de vizitatori și discountul utilizat.

Cerința suplimentară:
- Să se adauge toate campurile relevante pentru modelarea acestei probleme (Am adaugat campul locatie pentru farmaciile fizice)
- Să se construiască clasa template GestionareFarmacii care sa conțină informații despre
diversele tipuri de farmacii. Clasa conține indexul farmaciei (incrementat automat la
adaugarea unei noi file), id-ul lanțului (constant) și o structura de obiecte, alocată dinamic.
Sa se supraincarce operatorul += pentru inserarea unei noi farmacii online în structura.
- Să se construiască o specializare pentru tipul Farmacie_online care sa conțină și să afișeze
doar numărul total de vizitatori ai farmaciilor online.

Structura de date: vector sau list <tuple<web, nr_vizitatori, discount>> pentru a se reține farmaciile online

