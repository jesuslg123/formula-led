# data: {'topic': 'track', 'payload': '{command: start}'}
# data: {'topic': 'player', 'payload': '{command: end, player: 1, loop: 1}'}
# data: {'topic': 'track', 'payload': '{command: end, winner: 1 }'}

from flask_socketio import SocketIO, emit
from flask_mqtt import Mqtt
from flask import Flask, render_template, url_for, copy_current_request_context
from race_events import app
from time import sleep
import time
import json

app.config['DEBUG'] = True
app.config['MQTT_BROKER_URL'] = '127.0.0.1'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_USERNAME'] = ''
app.config['MQTT_PASSWORD'] = ''
app.config['MQTT_KEEPALIVE'] = 5
app.config['MQTT_TLS_ENABLED'] = False

#turn the flask app into a socketio app
mqtt = Mqtt(app)
socketio = SocketIO(app)

race_start_time = []

@app.route('/')
def index():
    #only by sending this page first will the client be connected to the socketio instance
    mqtt.subscribe('mqtt_message')
    mqtt.subscribe('player')
    mqtt.subscribe('track')

    return render_template('asycn_index.html')

@socketio.on('connect')
def test_connect():
    print('Client connected')

@socketio.on('disconnect')
def test_disconnect():
    print('Client disconnected')

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    # every time we pass in a new message we overwrite variables from here
    data = dict(
        topic=message.topic,
        payload=message.payload.decode()
    )

    if data['topic'] == "track":
        process_track_message(data)

    elif data['topic'] == "player":
        process_player_message(data)

def process_track_message(data):
    command = json.loads(data['payload'])
    command_value = command['command']

    if command_value == "start":
        start = time.time()
        race_start_time.append(start)
        data['command_value'] = command_value
        data['start_time'] = start
        socketio.emit('track', {'data': data})
        return race_start_time

    if command_value == "end":
        end = time.time()
        # we stored the start time as the first element of the array start_time
        elapsed = round(end - race_start_time[0], 2)
        winner = command['winner']

        data['command_value'] = command_value
        data['winner'] = winner
        data['elapsed'] = elapsed

        socketio.emit('track', {'data': data})

    else:
        socketio.emit('track', {'data': data})

def process_player_message(data):

    command = json.loads(data['payload'])
    player_value = command['player']
    data['player_value'] = player_value

    if 'loop' in command:
        loop_value = command['loop']
        loop_end_time = time.time()
        elapsed_loop_time = round(loop_end_time - race_start_time[0], 2)
        data['loop_value'] = loop_value
        data['loop_time'] = elapsed_loop_time
        socketio.emit('player', {'data': data})

    if 'speed' in command:
         speed_value = command['speed']
         data['speed_value'] = speed_value
         socketio.emit('player', {'data': data})

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, use_reloader=True, debug=True)
