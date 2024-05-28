from flask import Flask, request, jsonify
from flask_cors import CORS

# just added a simple comment to see the changes
app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})

# Global variable to store the pump state
pump_state = "OFF"

@app.route('/')
def control_pump():
    global pump_state
    return pump_state

@app.route('/toggle', methods=['POST'])
def toggle_pump():
    global pump_state
    if pump_state == "OFF":
        pump_state = "ON"
    else:
        pump_state = "OFF"
    return jsonify({"status": pump_state})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
