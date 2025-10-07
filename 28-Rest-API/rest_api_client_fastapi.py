import requests
import json
import time
from typing import Optional

class SensorClient:
    """Cliente para interactuar con la API de sensores"""
    
    def __init__(self, base_url: str = "http://localhost:8000"):
        self.base_url = base_url
        self.session = requests.Session()
        
    def _handle_response(self, response: requests.Response) -> dict:
        """Maneja la respuesta del servidor y errores comunes"""
        try:
            data = response.json()
        except json.JSONDecodeError:
            return {
                "error": "Invalid JSON",
                "message": "Server returned invalid JSON response",
                "status_code": response.status_code
            }
        
        if response.status_code == 404:
            print(f"❌ ERROR 404 - Endpoint no encontrado")
            print(f"   Mensaje: {data.get('message', 'Recurso no disponible')}")
            return None
            
        elif response.status_code == 500:
            print(f"❌ ERROR 500 - Error interno del servidor")
            print(f"   Mensaje: {data.get('message', 'Error inesperado')}")
            return None
            
        elif response.status_code >= 400:
            print(f"❌ ERROR {response.status_code}")
            print(f"   Detalle: {data.get('detail', 'Error desconocido')}")
            return None
            
        return data
    
    def get_temperature(self) -> Optional[dict]:
        """Obtiene la lectura actual del sensor de temperatura"""
        try:
            response = self.session.get(f"{self.base_url}/sensors/temperature")
            return self._handle_response(response)
        except requests.exceptions.ConnectionError:
            print("❌ Error de conexión: No se puede conectar al servidor")
            return None
        except Exception as e:
            print(f"❌ Error inesperado: {e}")
            return None
    
    def update_temperature_unit(self, unit: str) -> Optional[dict]:
        """Actualiza la unidad del sensor de temperatura"""
        try:
            response = self.session.put(
                f"{self.base_url}/sensors/temperature",
                json={"unit": unit}
            )
            return self._handle_response(response)
        except requests.exceptions.ConnectionError:
            print("❌ Error de conexión: No se puede conectar al servidor")
            return None
        except Exception as e:
            print(f"❌ Error inesperado: {e}")
            return None
    
    def get_humidity(self) -> Optional[dict]:
        """Obtiene la lectura actual del sensor de humedad"""
        try:
            response = self.session.get(f"{self.base_url}/sensors/humidity")
            return self._handle_response(response)
        except requests.exceptions.ConnectionError:
            print("❌ Error de conexión: No se puede conectar al servidor")
            return None
        except Exception as e:
            print(f"❌ Error inesperado: {e}")
            return None
    
    def update_humidity_unit(self, unit: str) -> Optional[dict]:
        """Actualiza la unidad del sensor de humedad"""
        try:
            response = self.session.put(
                f"{self.base_url}/sensors/humidity",
                json={"unit": unit}
            )
            return self._handle_response(response)
        except requests.exceptions.ConnectionError:
            print("❌ Error de conexión: No se puede conectar al servidor")
            return None
        except Exception as e:
            print(f"❌ Error inesperado: {e}")
            return None
    
    def test_404_error(self):
        """Prueba el manejo de error 404"""
        try:
            response = self.session.get(f"{self.base_url}/sensors/nonexistent")
            return self._handle_response(response)
        except Exception as e:
            print(f"❌ Error inesperado: {e}")
            return None

def print_sensor_data(data: dict, sensor_type: str):
    """Imprime los datos del sensor de forma legible"""
    if data:
        print(f"\n📊 {sensor_type.upper()}")
        print(f"   Sensor ID: {data.get('sensor_id')}")
        print(f"   Valor: {data.get('value')} {data.get('unit')}")
        print(f"   Timestamp: {data.get('timestamp')}")
        print(f"   Estado: {data.get('status')}")

def main():
    """Función principal de demostración"""
    print("=" * 60)
    print("🌡️  CLIENTE DE SENSORES REST API")
    print("=" * 60)
    
    client = SensorClient()
    
    # 1. Consultar temperatura en Celsius
    print("\n1️⃣  Consultando temperatura (Celsius por defecto)...")
    temp_data = client.get_temperature()
    print_sensor_data(temp_data, "Temperatura")
    
    time.sleep(1)
    
    # 2. Cambiar a Fahrenheit
    print("\n2️⃣  Cambiando unidad de temperatura a Fahrenheit...")
    temp_data = client.update_temperature_unit("fahrenheit")
    print_sensor_data(temp_data, "Temperatura")
    
    time.sleep(1)
    
    # 3. Volver a Celsius
    print("\n3️⃣  Cambiando unidad de temperatura a Celsius...")
    temp_data = client.update_temperature_unit("celsius")
    print_sensor_data(temp_data, "Temperatura")
    
    time.sleep(1)
    
    # 4. Consultar humedad en porcentaje
    print("\n4️⃣  Consultando humedad (Porcentaje por defecto)...")
    hum_data = client.get_humidity()
    print_sensor_data(hum_data, "Humedad")
    
    time.sleep(1)
    
    # 5. Cambiar a humedad absoluta
    print("\n5️⃣  Cambiando unidad de humedad a absoluta (g/m³)...")
    hum_data = client.update_humidity_unit("absolute")
    print_sensor_data(hum_data, "Humedad")
    
    time.sleep(1)
    
    # 6. Volver a porcentaje
    print("\n6️⃣  Cambiando unidad de humedad a porcentaje...")
    hum_data = client.update_humidity_unit("percentage")
    print_sensor_data(hum_data, "Humedad")
    
    time.sleep(1)
    
    # 7. Probar error 404
    print("\n7️⃣  Probando error 404 (endpoint inexistente)...")
    client.test_404_error()
    
    time.sleep(1)
    
    # 8. Múltiples consultas para provocar error 500
    print("\n8️⃣  Realizando múltiples consultas (puede aparecer error 500)...")
    for i in range(10):
        print(f"\n   Intento {i+1}/10...")
        temp_data = client.get_temperature()
        if temp_data:
            print(f"   ✅ Temperatura: {temp_data.get('value')} {temp_data.get('unit')}")
        time.sleep(0.5)
    
    print("\n" + "=" * 60)
    print("✅ Demostración completada")
    print("=" * 60)

if __name__ == "__main__":
    main()
