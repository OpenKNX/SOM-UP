### Allgemein

Das SOM-UP kann aktuell mit zwei verschieden Playern bestückt werden. Der alte Player (DY-SV17F) ist komplett Eingeständig und bringt daher einen eigenen Flashspeicher (4MB) mit und wird daher auch unabhängig über einen eigenen USB-Anschluss befüllt. Ich kann weder prüfen, ob eine Datei vorhanden ist, noch Dateien per KNX auf diesem ablegen.

Der neue Player hingegangen, ist eigentlich kein richtiger Player, sondern eher wie ein Verstärker zu betrachten. Hierbei werden die Audio-Signale per I2S übermittelt und ausgegeben. Das komplette Dekodieren der MP3, erledigt somit das SOM-UP selber. Dieser kann nicht nur MP3, WAV sondern auch RTTTL (Ringtones) abspielen und sogar eigene Töne (Buzzer) generieren. Die Daten können hierbei auf dem internen Speicher abgelegt werden (von bis zu 14MB nutzbar sind). Auch ein Übertagen der Dateien per KNX ist möglich, so dass ein Ausbauen nicht mehr nötig ist.

Alternativ können die Dateien auch per USB übertragen werden. Hierzu simuliert das SOM-UP einen virtuellen USB-Stick mit einem Eingangsordner. Nach dem Auswerfen werden die Dateien in diesem Ordner auf den internen Speicher verschoben. Dieser Modus kann per Doppelklick auf die PROG-Taste gestartet, wie auch beendet werden (Alternativ über das Betriebssystem auswerfen).
Hinweis: Da der virtuelle Speicher auf ca. 1MB limitiert ist, kann es nötig sein, die Daten in mehreren Tranchen zu kopieren. Anhand des Blinkens, kann geprüft werden, ob der Kopiervorgang abgeschlossen wurde und man erneut USB-Modus starten kann.

### Sounddateien

Die Sounddateien werden immer im Namensschema (00000.XXX) abgespeichert. Dabei ist der kleinste Wert die 00001 und der größte Wert die 09999. Die Dateiendung ist beim Hardwareplayer immer .MP3. Beim Softwareplayer sind auch .WAV und .RTT erlaubt. Während MP3- und WAV-Dateien selbsterklärend sein sollte, enthalten RTT-Dateien sogenannte RTTTL-Daten auch bekannt als Ringtones. Im Internet findet man entsprechende RTTTLs die man aber selbst in eine Textdatei mit der Endung RTT packen muss.
Bei den MP3 Dateien gibt es einige Hinweise die zu beachten sind. Da der Hardware-Player meistens doch recht leise ist, kann es nötig sein, MP3-Dateien zu verstärken (auf Kosten der Ton-Qualität). Beim Softwareplayer ist es genau andersherum. Hier kann es nötig sein, die Lautstärke zu begrenzen (Normalisieren), da der Player sonst übersteuert wird und der Ton abgehackt abgespielt wird.

Darüber hinaus ist die Leistung des Software-Player begrenzt, so dass die Leistung nicht für das Dekodieren der MP3 reicht. Hier kann es nötigt sein, die MP3 zu konvertieren. Ich empfehlen hier eine Abtastrate von 32000Hz mit einer Konstanten Bitrate von 128kbps. Es dürften aber je nach Sound auch höre Werte funktionieren.
Um Speicherplatz zu sparen, kann man die Sounddateien als Mono speichern und ggf. auch direkt die MP3 Tags entfernen.

### Lautstärke

Die Lautstärke ist je nach Player unterschiedlich. Während der Hardwareplayer nur Werte von 1-30 erlaubt, kann der Softwareplayer 1-255 nutzen. Dennoch sollte man mit niedrigem Wert (25) anfangen, um so nicht den Lautsprecher zu überlasten. Auch ist die maximale Lautstärke abhängig von dem abgespielten Sound. Die Leistung ist aufgrund der Stromversorgung per BUS eingeschränkt.

### Auslöser

Es gibt 10 verschiedene Auslöser, um das Abspielen eines Sounds zu steuern. Über ein Schaltobjekt (EIN) kann das Abspielen gestartet und über (AUS) beendet werden. Das Objekt kann auch im Triggermodus arbeiten, so dass ein AUS den Abspielvorgang nicht unterbricht. Das kann je nach Konfiguration des Tasters nötig sein.

### Externe Logik

Das SOM-UP kann auf Wunsch auch über eine externe Logik direkt angesteuert werden. Hierfür stehen 3 Eingänge für Lautstärke, Priorität sowie das Soundfile zur Verfügung. Der Eingang für das Soundfile triggert gleichzeitig den Abspielvorgang, der ebenfalls mittels 0 vorzeitig beendet werden kann.
Beispiel: Du betreibst eine zentrale Visu-/Logik-Engine wo mittels HomeConnect die Waschmaschine oder der Trockner angebunden ist. Jetzt kannst du direkt diverse Meldungen wie „Wäsche ist fertig“ auslösen. Somit brauchst du keinen Umweg über die begrenzten 1bit-Auslöser zu gehen.
Tipp: Auf der Seite ttsmp3.com kannst du dir schnell passende Statusmeldungen als MP3 erstellen lassen.

