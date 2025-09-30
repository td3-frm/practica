from flask import Flask, request
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
    # return jsonify(data)
    return data, 200


# Endpoint para configurar el sensor con una petición POST
@app.route('/sensor/configure', methods=['POST'])
def configure_sensor():
    if request.is_json:
        # Obtenemos los datos de la solicitud
        config_data = request.get_json()

        # Ejemplo de procesamiento de los datos
        sensor_id = config_data.get('sensor_id')
        new_limit = config_data.get('temperature_limit')

        # Simulamos la configuración del sensor
        response_data = {
            'message': f"Configuración recibida para el sensor {sensor_id}.",
            'new_temperature_limit': new_limit
        }

        # Devolvemos una respuesta con el código 200 y los datos de confirmación
        return response_data, 201
    else:
        # Si la solicitud no es JSON, devolvemos un error 400
        return {'error': 'La solicitud debe ser en formato JSON'}, 400


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
