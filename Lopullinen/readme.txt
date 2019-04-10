Ohjelman kuvaus: Ohjelma luo .tili päätteiset tiedostot jotka
sisältävä 'pankkitilien' tunnusluvut sekä saldon (oletuksena 0).
Tunnusluku on aina sama kuin tilin nimi. Luotavat tilit ovat
nimeltään 1234.tili, 4321.tili, 5678.tili ja 8765.tili. Ohjelma
kysyy käynnistäessä tilin nimen ja kysyy sitä uudestaan jos tili
ei löydy. Tilin löydyttyä ohjelma tulostaa toimimmot jotka ovat
Nosto, Talleta, Saldo ja Lopeta. Noston ja talletuksen yhteydessä
ohjelma kysyy halutun nosto/talletus -summan. Noston yhteydessä
kysytään myöskin tilinumero. Saldo tulostaa tilillä olevan
rahamäärän ruudulle.

Ohjelman ajo syötteillä 'väärä tili': 2323
oikea tili: 1234
-> saldon tulostus: 3
nosto väärällä syötteellä: w
tunnusluku: 1234
-> nosto: 3
tunnusluku: 1234
-> talleta: 2
talleta: 32
-> saldo: 3
-> ohjelman lopetus: 0

Anna nelinumeroinen tilinumero: 
2323
Tilia ei loytynyt!
Anna tilinumero uudestaan :1234
Tili loytyi...

Valise toiminto:
 1 - Nosto
 2 - Talleta
 3 - Saldo
 0 - Lopeta

 Valitasi: 3
Tililläsi ei ole rahaa!
Valise toiminto:
 1 - Nosto
 2 - Talleta
 3 - Saldo
 0 - Lopeta

 Valitasi: 1
Paljonko haluat nostaa? 
: w
Anna tunnusluku: 1234
Syötä vain kokonaislukuja
3
Anna tunnusluku: 1234
Tilillä ei tarpeeksi rahaa
Valise toiminto:
 1 - Nosto
 2 - Talleta
 3 - Saldo
 0 - Lopeta

 Valitasi: 2
Paljonko haluat tallettaa? 
: 34
Talletetaan tulosValise toiminto:
 1 - Nosto
 2 - Talleta
 3 - Saldo
 0 - Lopeta

 Valitasi: 3
Tilisi saldo on: 34
	Valise toiminto:
 1 - Nosto
 2 - Talleta
 3 - Saldo
 0 - Lopeta

 Valitasi: 0
Ohjelma lopetetaan, tervetuloa uudelleen! 
