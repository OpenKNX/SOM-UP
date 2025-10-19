# **Soundmodul**

<!-- DOC HelpContext="Doc" -->
## **Dokumentation**

<!-- DOCCONTENT
Eine vollständige Applikationsbeschreibung ist unter folgendem Link verfügbar: https://github.com/openknx/SOM-UP/blob/v1/doc/Applikationsbeschreibung-Soundmodul.md
DOCCONTENT -->

Das SOM-UP kann aktuell mit zwei verschieden Playern bestückt werden. Der alte Player (DY-SV17F) ist komplett Eingeständig und bringt daher einen eigenen Flashspeicher (4MB) mit und wird daher auch unabhängig über einen eigenen USB-Anschluss befüllt. Ich kann weder prüfen, ob eine Datei vorhanden ist, noch Dateien per KNX auf diesem ablegen.

Der neue Player hingegangen, ist eigentlich kein richtiger Player, sondern eher wie ein Verstärker zu betrachten. Hierbei werden die Audio-Signale per I2S übermittelt und ausgegeben. Das komplette Dekodieren der MP3, erledigt somit das SOM-UP selber. Dieser kann nicht nur MP3, WAV sondern auch RTTTL (Ringtones) abspielen und sogar eigene Töne (Buzzer) generieren. Die Daten können hierbei auf dem internen Speicher abgelegt werden (von bis zu 14MB nutzbar sind). Auch ein Übertagen der Dateien per KNX ist möglich, so dass ein Ausbauen nicht mehr nötig ist.

Alternativ können die Dateien auch per USB übertragen werden. Hierzu simuliert das SOM-UP einen virtuellen USB-Stick mit einem Eingangsordner. Nach dem Auswerfen werden die Dateien in diesem Ordner auf den internen Speicher verschoben. Dieser Modus kann per Doppelklick auf die PROG-Taste gestartet, wie auch beendet werden (Alternativ über das Betriebssystem auswerfen).
Hinweis: Da der virtuelle Speicher auf ca. 1MB limitiert ist, kann es nötig sein, die Daten in mehreren Tranchen zu kopieren. Anhand des Blinkens, kann geprüft werden, ob der Kopiervorgang abgeschlossen wurde und man erneut USB-Modus starten kann.

### **Features**

- Variante: MP3-Player (DY-SV17F)
	- 4MB großer Speicher, welcher per USB befüllt wird. (Wird als USB-Stick angesprochen)
	- Onboard 5W Class D Verstärker (ca 3~5W an 4Ω Lautsprecher)
- Variante: Software-Player (I2S)
    - Verwendung des internen Flashspeichers ca 10MB frei zur Nutzung
    - Tongenerator bis 9 Tonsequenzen
    - Support MP3-, WAV-, RTT-Dateien
- Grundlautstärke (auch Tag/Nachtabhängig)
- Globale Sperrmöglichkeit
- 20 konfigurierbare Szenen
- 5 stufiges Prioritätensystem
- 10 Auslöser (1bit-Trigger)
	- Sperrmöglichkeit (z.B. Klingelsperre)
	- Abweichende Laustärke (auch Tag/Nachtabhängig)
	- Wiederholgen (z.B. für Sirene)
	- Maximale Abspieldauer
	- Retrigger-Schutz

<!-- DOCEND -->

## **Allgemein**

Hier werden Einstellungen vorgenommen, die für das gesamte Soundmodul und alle Auslöser gelten.

<!-- DOC HelpContext="AvailableTriggers" -->
### **Verfügbare Auslöser**

Um die Applikation übersichtlicher zu gestalten, kann hier ausgewählt werden, wie viele Auslöser in der Applikation verfügbar und editierbar sind. Die Maximalanzahl der Auslöser beträgt 10.

Die ETS ist auch schneller in der Anzeige, wenn sie weniger (leere) Auslöser darstellen muss. Insofern macht es Sinn, nur so viele Auslöser anzuzeigen, wie man wirklich braucht.

<!-- DOC HelpContext="PlayerVariant" -->
### **Player-Variante**

Wähle die Player-Variante, die im SOM-UP verbaut wurde. Diese Auswahl dient dazu, die Einstellungen in der ETS anzupassen sowie zu dokumentarischen Zwecken. Die Firmware erkennt automatisch, welche Variante tatsächlich verbaut wurde, und steuert diese entsprechend an.

<!-- DOC HelpContext="DayNight" -->
### **Tag/Nacht-Objekt**

Über das Tag/Nacht-Objekt kann die Standardlautstärke tagesabhängig gesteuert werden. Die Lautstärke zusätzlich je Auslöser separat abweichend konfiguriert werden.

<!-- DOC HelpContext="Volume" -->
### **Lautstärke**

Wähle die gewünschte Lautstärke aus. Beachte, dass die Lautstärke nicht beliebig eingestellt werden kann, da sie durch die begrenzte Stromversorgung über den Bus begrenzt ist.

* **Player-Variante: Hardware**
Hier kann die Lautstärke im Bereich von 1-30 eingestellt werden. Sollte die Lautstärke einer Datei dennoch als zu leise empfunden werden, besteht die Möglichkeit, sie mithilfe eines Audioprogramms wie Audacity zu verstärken. Beachte jedoch, dass dies den Dynamikumfang beeinträchtigen kann.
* **Player-Variante: Software**
Die Lautstärke kann hier zwischen 1-255 eingestellt werden. In der Regel ist jedoch aufgrund der begrenzten Stromversorgung 60-80 das Maximum.

Es wird empfohlen, mit einem niedrigen Wert, etwa 25, zu starten. Ein zu lautes Abspielen kann den Lautsprecher beschädigen. 

<!-- DOC HelpContext="GlobalLock" -->
### **Zentrale Sperre**

Über die zentrale Sperre kann das Abspielen der Sounds vollständig unterbunden werden. In der Regel empfiehlt es sich jedoch, die Sperre auf den Auslösern zu nutzen.

<!-- DOC HelpContext="Scenes" -->
## **Szenen**

Über die Steruerung per Szenen können Trigger und Sperren gesteuert werden.

<!-- DOC HelpContext="External" -->
### **Externe Logik**

Das Modul bietet die Möglichkeit einer direkten Ansteuerung durch eine externe Logik. Dafür stehen drei Eingänge zur Verfügung: Lautstärke, Priorität und Soundfile. Der Eingang für das Soundfile löst den Abspielvorgang aus, welcher auch mittels einer 0 vorzeitig beendet werden kann.

Beispiel: Du betreibst eine zentrale Visu/Logik-Engine wo mittels HomeConnect die Waschmaschine oder der Trockner angebunden ist. Jetzt kannst du direkt diverse Meldungen wie „Wäsche ist fertig“ auslösen, ohne den Umweg über die begrenzten 1bit-Auslöser zu gehen.

Tipp: Auf der Seite ttsmp3.com kannst du dir schnell passende Statusmeldungen als MP3 erstellen lassen.

<!-- DOC HelpContext="Sequences" -->
## **Tongenerator**

Der Tongenerator ermöglicht die Erstellung einfacher und komplexer Tonabfolgen, sofern die Hardware einen I2S-Ausgabechip verwendet.

Dies ist nicht nur platzsparender, sondern auch deutlich einfacher als das Erstellen von MP3- oder WAV-Dateien. Mit dem Tongenerator lassen sich problemlos Ton-Rückmeldungen wie Dauertöne oder einfaches Piepen erzeugen. Es können bis zu neun verschiedene Tonfolgen gespeichert werden, die über die Pseudodateien 10001 bis 10009 angesteuert werden.
<!-- DOCEND -->

<!-- DOC HelpContext="SequenceMode" -->
### **Modus**

Im Ton-Generator-Modus stehen zwei verschiedene Modi zur Verfügung:

* **Simple-Modus**: Hier können Frequenz und Dauer angegeben werden. In Kombination mit einer Wiederholungsanzahl und der Länge der Pause, können bereits einfache Statuscodes zurückgegeben werden. (wie zum Beispiel 3x schnelles Piepen)
* **Komplex-Modus**: In diesem Modus kannst du komplexere Tonabfolgen generieren. Für jede Tonabfolge können die Dauer und die Frequenz angegeben werden. Einträge mit einer Dauer von 0 werden dabei ignoriert, und Frequenzen mit 0 werden stumm abgespielt.

<!-- DOC HelpContext="SequenceRepeat" -->
### **Wiederholung**

Mit dieser Option kann die Tonabfolge x-mal wiederholt werden. Der Abspielvorgang erfolgt "gapless", kann aber durch die Angabe eine Pausedauer verzögert werden.

**Achtung**: Ein Wert von 3 für die Wiederholungen bedeutet, dass die Tonabfolge insgesamt 4x abgespielt wird, da die erste Wiedergabe nicht als Wiederholung zählt.

<!-- DOC HelpContext="Trigger" -->
## **Auslöser**

Es gibt 10 verschiedene Auslöser, um das Abspielen eines Sounds zu steuern. Über ein Schaltobjekt (EIN) kann das Abspielen gestartet und über (AUS) beendet werden. Das Objekt kann auch im Triggermodus arbeiten, so dass ein AUS den Abspielvorgang nicht unterbricht. Das kann je nach Konfiguration des Tasters nötig sein.

<!-- DOC HelpContext="TriggerName" -->
### **Beschreibung**

Der hier angegebene Name wird an verschiedenen Stellen verwendet, um diesen Kanal wiederzufinden.

* Seitenbeschreibung des Kanals
* Name vom Kommunikationsobjekt

Eine aussagekräftige Benennung erlaubt eine einfachere Orientierung innerhalb der Applikation, vor allem wenn man viele Kanäle nutzt.

<!-- DOC HelpContext="TriggerStatus" -->
### Status

Der Trigger kann bei Bedarf aktiviert und konfiguriert werden.

<!-- DOC HelpContext="TriggerLock" -->
### **Sperrobjekt**

Durch Verwendung des Sperrobjekts kannst du vorübergehend den Auslöser deaktivieren. Wenn der Auslöser beispielsweise als Haustürklingel genutzt wird, fungiert das Sperrobjekt als klassische Klingelsperre. Dies kann beispielsweise sinnvoll sein, wenn es Nachwuchs im Haus gibt.

<!-- DOC HelpContext="TriggerPriority" -->
### **Priorität**

Durch die Verwendung von Prioritäten kann verhindert werden, dass wichtige Sounds von weniger wichtigen übersteuert werden. Ein Beispiel hierfür wäre eine Alarmsirene, die Vorrang vor anderen Sounds haben sollte. Es ist wichtig zu beachten, dass eine gleiche Priorität als höhere Priorität gewertet wird, um sicherzustellen, dass beispielsweise eine Haustürklingel auch mehrfach betätigt werden kann, selbst wenn der Sound noch nachklingt.

<!-- DOC HelpContext="TriggerControl" -->
### **Steuerung**

Mit dieser Option können Sie die Steuerung des Auslösers nach Ihren Bedürfnissen anpassen. Standardmäßig wird der Auslöser wie ein Schaltobjekt für Start/Stop behandelt. Als Alternative kann er durch einen Trigger mit den Optionen EIN oder AUS ausgelöst werden, wobei der jeweils andere Wert unbeachtet bleibt.

<!-- DOC HelpContext="TriggerDayNight" -->
### **Tag/Nacht-Objekt**

Das Tag/Nacht-Objekt ermöglicht eine tagesabhängige Steuerung der Standardlautstärke. Darüber hinaus kann zusätzlich die Lautstärke für jeden Auslöser individuell konfiguriert werden.

<!-- DOC HelpContext="TriggerDurartion" -->
### **Wiedergabedauer begrenzen**

Der Abspielvorgang kann zeitlich begrenzt werden, um eine automatische Unterbrechung sicherzustellen. Durch Kombination mit der Funktion „Wiederholungen“ kann beispielsweise ein Alarm für 3 Minuten ausgegeben werden, indem der Abspielvorgang entsprechend begrenzt wird.

<!-- DOC HelpContext="TriggerFile" -->
### **Sounddatei**

Um die Sounddateien abspielen zu können, müssen sie im 5-stelligen Format 00001.MP3 (Großbuchstaben) und im MP3-Format gespeichert sein.
Dabei ist aber nur 00001-09999 erlaubt, da die >10000 reserviert sind. Wenn ein SW-Player (I2S) verbaut wurde, kann der Tongenerator genutzt und über 10001 bis 10009 angesprochen werden. Außerdem können dann auch WAV und RTT Dateien abgespielt werden.

* Tipp 1: Um den Überblick zu behalten, kann eine zusätzliche Datei mit der gleichen Nummer angelegt werden, beispielsweise „00001 Klingel 1.txt“ oder „00002 Innensirene.txt“.
* Tipp 2: Um optimale Ergebnisse zu erzielen, können Sie die Sounddatei vorher in Audacity (Kostenfrei) bearbeiten.
  * Lautstärke verstärken (bei HW-Player relevant, da dieser recht leise ist) um die maximale Lautstärke zu erreichen (auf Kosten der Dynamik & Qualität)
  * Beim SW-Player (I2S) ist es je nach MP3 nötig, die Samplerate und/oder Bitrate zu reduzieren, da die CPU Leistung nur sehr schwach ist. 
  * Exportiere als Mono und entferne MP3-Tags um Speicherplatz zu sparen.

<!-- DOC HelpContext="TriggerRepeat" -->
### **Wiederholung**

Mit dieser Option kann der Abspielvorgang x-mal wiederholt werden. Dadurch kann der Speicherplatz für große MP3-Dateien eingespart werden. Allerdings erfolgt der Abspielvorgang nicht "gapless", was bedeutet, dass z.B. kein Dauerton simuliert werden kann. Diese Funktion ist nicht mit WAV-Dateien oder dem Tongenerator kompatibel.

**Achtung**: Ein Wert von 3 für die Wiederholungen bedeutet, dass die Sounddatei insgesamt 4x abgespielt wird, da die erste Wiedergabe nicht als Wiederholung zählt.

<!-- DOC HelpContext="TriggerRetrigger" -->
### **Retrigger-Schutz**

Der Retrigger-Schutz verhindert, dass der Auslöser erneut ausgeführt wird, solange er noch aktiv ist. Dies ist besonders nützlich bei Anwendungen wie einer Haustürklingel.

