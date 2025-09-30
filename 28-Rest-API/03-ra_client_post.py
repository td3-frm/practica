import requests

# URL del servidor (sensor)
sensor_url = 'http://localhost:5000/sensor/configure'

# Datos de configuración a enviar al sensor
config_data = {
    'sensor_id': 'sensor_002',
    'temperature_limit': 25.5
}

# Enviamos la petición POST con los datos JSON
response = requests.post(sensor_url, json=config_data)

# Verificamos si la solicitud fue exitosa (código 200)
if response.status_code == 201:
    data = response.json()
    print(f"Respuesta del servidor: {data}")
else:
    print(f"Error al configurar el sensor. Código de estado: {response.status_code}")
