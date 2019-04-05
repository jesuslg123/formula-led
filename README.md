# arduino-led-racing

## Team Members

### Dev Team

* [@jesus-lopez](https://source.xing.com/jesus-lopez)
* [@aaron-ciaghi](https://source.xing.com/aaron-ciaghi)
* [@sarah-seitz](https://source.xing.com/sarah-seitz)

### Special thanks to contributors

* [@helios-aliaga](https://source.xing.com/helios-aliaga)
* [@jordi-manuel](https://source.xing.com/jordi-manuel)

## Rules

* There are two players: red and blue
* The race begins with a random countdown
* Keep pressing the button on the controller to accelerate
* When a player goes too fast it changes color to green or yellow
* Keep going too fast to be "thrown off the track". When this happens the player's speed is reset to 0 and the player blinks until it accelerates back to speed 1
* There are 5 laps in a race
* The first player to cross the line at the end of the 4th lap wins
* Press the reset button to start again

## Build your own

You will need:

* Hardware:
  * 1x Arduino Nano (or any Arduino)
  * 1x LED Strip (WS2813)
  * 2x Buttons
  * 1x 1000 µF capacitor
  * 2x 10kΩ resistors (for the buttons)
  * 1x 470Ω resistor (for the LED strip) but change it according to your power supply
  * Optional: 5V 2A power supply (you may have to change the resistors and the capacitor)
  * All the necessary cables to connect all the stuff above
* Components you can 3d-print:
  * Controllers
  * Base
* Software:
  * Arduino IDE
  * Fritzing (http://fritzing.org/download/)

Follow the designs in: [Schemas](./Schemas)
