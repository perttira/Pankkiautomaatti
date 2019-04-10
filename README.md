
# C-ohjelmointi -kurssin harjoitustyö

Ohjelman kuvaus: Ohjelma luo .tili päätteiset tiedostot jotka
sisältävä 'pankkitilien' tunnusluvut sekä saldon (oletuksena 0).
Tunnusluku on aina sama kuin tilin nimi. Luotavat tilit ovat
nimeltään 1234.tili, 4321.tili, 5678.tili ja 8765.tili. Ohjelma
kysyy käynnistäessä tilin nimen ja kysyy sitä uudestaan jos tili
ei löydy. Tilin löydyttyä ohjelma tulostaa toiminnot jotka ovat
Nosto, Talleta, Saldo ja Lopeta. Noston ja talletuksen yhteydessä
ohjelma kysyy halutun nosto/talletus -summan. Noston yhteydessä
kysytään myöskin tilinumero. Saldo tulostaa tilillä olevan
rahamäärän ruudulle.


![scrrenshot](https://github.com/perttira/pankkiautomaatti/blob/master/pankkiautomaatti.gif)

## Use

```
$ Ohjelman kuvaus ja käyttöohjeet löytyvät "Lopullinen" -kansiosta readme.txt tiedostosta.
```

### Locally

```
$ go get https://github.com/perttira/pankkiautomaatti
$ open C-pankkiautomaatti or ./C-pankkiautomaatti
```
