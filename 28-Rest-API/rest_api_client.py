import requests

# El cliente hace una petición GET al sensor para obtener la temperatura
sensor_url = 'http://localhost:5000/sensor/temperature'

response = requests.get(sensor_url)

if response.status_code == 200:
    data = response.json()
    print(f"Sensor ID: {data['sensor_id']}")
    print(f"Temperature: {data['temperature']} {data['unit']}")
else:
    print(f"Failed to retrieve data from sensor. Status code: {response.status_code}")
