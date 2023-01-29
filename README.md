
# SOM-UP

Das OpenKNX SOM-UP ist ein KNX-MP3-Player mit integriertem Verstärker zum direkten Anschluss an einen UP-Lautsprecher. Es wurde zur Nutzung als Klingel bzw. Signalgeber konzipiert.
Die Platine wurde klein und rund gehalten, so dass diese mit Nylon M2-Abstanshalter z.B. direkt auf einen Gira-Lautsprecher geklebt werden kann und somit in eine tiefe Unterputzdose passt. Die Stromversorgung erfolgt dabei komplett aus dem KNX-Bus. Hierdurch ist aber die maximale Lautstärke limitiert (abhängig von der Sounddatei und dem verwendeten Lautsprecher).

## Features
- MP3-Player (DY-SV17F)
	- 4MB großer Speicher, welcher per USB befüllt wird. (Wird als USB-Stick angesprochen)
	- Onboard 5W Class D Verstärker (ca 3~5W an 4Ω Lautsprecher)
- Grundlautstärke (auch Tag/Nachtabhängig)
- Globale Sperrmöglichkeit
- 20 konfigurierbare Szenen
- 5 stufiges Prioritätensystem
- 10 Auslöser (1bit-Trigger)
	- Sperrmöglichkeit (z.B. Klingelsperre)
	- Abweichende Laustärke (auch Tag/Nachtabhängig)
	- Wiederholgen (z.B. für Sirene)
	- Maximale Abspieldauer
- Zusätzliche Steuerung durch externe Logik möglich
- 4 gepulste Binäreingäng
	- Entprell-Möglichkeit
	- Zyklisches Senden (z.B. für Verschlusskontakte)
	- Direkte Nutzung im VIrtualButton-Modul
- 20 Kanäle des [VirtualButton-Modul](https://knx-user-forum.de/forum/projektforen/openknx/1841539-firmware-openknx-virtualbutton-release-vbm)
- 30 Kanäle des [Logik-Modul](https://knx-user-forum.de/forum/projektforen/openknx/1765082-openknx-logikmodul-release)

## Installation

Die Installation erfolgt wie bei OpenKNX üblich, über PowerShell-Skripte im Installationspaket. Dazu muss der SOM-UP über den USB-Port von der Grundplatine (der auf der Ecke) angeschlossen sein. Der USB-Port auf der Rückseite der Platine (vom MP3 Player) dient zum Aufspielen der MP3 und wird wie ein normaler USB-Stick genutzt.
In der beigelegten „knxprod“-Datei für die ETS, findet sich auch eine ausführliche Dokumentation mit einigen wichtigen Hinweisen zur Nutzung. Daher sollte man sich diese Doku genau durchlesen.
