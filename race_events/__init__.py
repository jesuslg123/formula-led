from flask import Flask

app = Flask(__name__)

import race_events.process_messages
