# Formula LED

See the project on Hackster.io: https://www.hackster.io/xing-hackweek/formula-led-b4cd78

## Team Members

### Dev Team

* [jesus-lopez](https://github.com/jesuslg123)
* [aaron-ciaghi](https://github.com/aaronsama)
* [sarah-seitz](https://github.com/SarahNox)
* [isobel-smith](https://github.com/IzzySmith)

### Special thanks to contributors

* jordi-manuel
* [helios-aliaga](https://github.com/heliosam)

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
  * Controllers ([Player 1](https://source.xing.com/hackweek/arduino-led-racing/blob/master/3D/Player%201.stl), [Player 2](https://source.xing.com/hackweek/arduino-led-racing/blob/master/3D/Player%202.stl))
  * Base
* Software:
  * Arduino IDE
  * Fritzing (http://fritzing.org/download/)

Follow the designs in: [Schemas](./Schemas)

## A real-time race event board

We want to display the race progress in real time on a race board. To do this we are using Flask, (http://flask.pocoo.org/), and mqtt-messages.

##### Requirements

`Python3` and `pip` are installed.

Create your virtual environment.

`<venv>` in this case is the path to your virtual environment. (For simplicity, this can just be `venv`)

```
python3 -m venv <venv>
```

##### Local Development

##### Local, Local

To activate the virtual environment:

```
source <venv>/bin/activate
```

To run the application:

```
export FLASK_APP=race_events
export FLASK_ENV=development
pip install -e .
flask run
```
