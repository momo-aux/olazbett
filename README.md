#Code um ein NANO CNC shield für das z-bett des K40 zu verwenden.


z-bett hier: https://www.thingiverse.com/thing:3051286

hab mir selber pulleys gemacht: https://www.thingiverse.com/thing:4815530
und abstandhalter damit die Kugellager drehen: https://www.thingiverse.com/thing:4822071

Die billigen Nano shields sind komplett verpfuscht, daher funktionieren sie nicht mit GRBL aber für sowas reichts :-)

![Aufbau](images/bett_montiert.jpg?raw=true "Montiert")

![Board](images/shield.jpg?raw=true "Shield")

![Display](images/oled.jpg?raw=true "Display")

Auf Pin 5 und 6 liegen die pushbuttons. 
Beide zu irgendeinem GND.

Auf der 9 (Auf dem Shield als X- bezeichnet) liegt der encoder pushbutton.

Für den Encoder verwende ich die DIR pins der X/Y Motoren, also 2 und 3. 
Da wir hier interrupts brauchen, damit der richtig funktioniert und die sind beim Nano auf 2 und 3.

Das Display ist über die SCL/SDA Leiste angeschlossen. Auf beschriftung achten, bei mir war die reihenfolge anders als auf dem Displayboard.

Ich betreibe das board mit 12V


