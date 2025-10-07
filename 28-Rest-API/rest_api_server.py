from flask import Flask, jsonify
import random

app = Flask(__name__)

# Simulamos el sensor, que devuelve datos de temperatura
@app.route('/sensor/temperature', methods=['GET'])
def get_temperature():
    # Generamos un valor de temperatura aleatorio
    temperature = round(random.uniform(20.0, 30.0), 2)
    data = {
        'sensor_id': 'sensor_001',
        'temperature': temperature,
        'unit': 'Celsius'
    }
    return jsonify(data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
