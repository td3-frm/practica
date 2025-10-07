from fastapi import FastAPI, HTTPException, status
from pydantic import BaseModel
from typing import Literal
import random
from datetime import datetime

app = FastAPI(title="Sensor API", version="1.0.0")

# Modelos de datos
class TemperatureConfig(BaseModel):
    unit: Literal["celsius", "fahrenheit"] = "celsius"

class HumidityConfig(BaseModel):
    unit: Literal["percentage", "absolute"] = "percentage"

class TemperatureResponse(BaseModel):
    sensor_id: str
    value: float
    unit: str
    timestamp: str
    status: str

class HumidityResponse(BaseModel):
    sensor_id: str
    value: float
    unit: str
    timestamp: str
    status: str

class ErrorResponse(BaseModel):
    error: str
    message: str
    status_code: int

# Estado interno de los sensores
sensors_config = {
    "temperature": {"unit": "celsius", "status": "active"},
    "humidity": {"unit": "percentage", "status": "active"}
}

# Función auxiliar para simular fallo del servidor
def simulate_server_error():
    """Simula aleatoriamente un error del servidor (5% de probabilidad)"""
    if random.random() < 0.05:
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail="Internal server error: Sensor communication failure"
        )

# Función para convertir temperatura
def convert_temperature(celsius_value: float, unit: str) -> float:
    if unit == "fahrenheit":
        return (celsius_value * 9/5) + 32
    return celsius_value

# Función para convertir humedad
def convert_humidity(percentage_value: float, unit: str, temp_celsius: float = 20) -> float:
    if unit == "absolute":
        # Conversión simplificada a humedad absoluta (g/m³)
        return percentage_value * 0.173 * (temp_celsius + 273.15) / 273.15
    return percentage_value

# Endpoint raíz - Lista todos los endpoints disponibles
@app.get("/")
def root():
    return {
        "message": "Sensor API v1.0",
        "endpoints": {
            "temperature": "/sensors/temperature",
            "humidity": "/sensors/humidity",
            "documentation": "/docs"
        }
    }

# GET /sensors/temperature - Obtener lectura del sensor de temperatura
@app.get("/sensors/temperature", response_model=TemperatureResponse)
def get_temperature():
    """
    Obtiene la lectura actual del sensor de temperatura.
    La unidad de medida se configura mediante PUT.
    """
    simulate_server_error()
    
    if sensors_config["temperature"]["status"] != "active":
        raise HTTPException(
            status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
            detail="Temperature sensor is not active"
        )
    
    # Simular lectura del sensor (valor base en Celsius)
    celsius_value = round(random.uniform(18.0, 28.0), 2)
    unit = sensors_config["temperature"]["unit"]
    
    value = convert_temperature(celsius_value, unit)
    
    return TemperatureResponse(
        sensor_id="TEMP-001",
        value=round(value, 2),
        unit=unit,
        timestamp=datetime.now().isoformat(),
        status="ok"
    )

# PUT /sensors/temperature - Actualizar configuración del sensor de temperatura
@app.put("/sensors/temperature", response_model=TemperatureResponse)
def update_temperature_config(config: TemperatureConfig):
    """
    Actualiza la configuración del sensor de temperatura.
    Permite cambiar la unidad de medida entre Celsius y Fahrenheit.
    """
    simulate_server_error()
    
    sensors_config["temperature"]["unit"] = config.unit
    
    # Retornar lectura actual con la nueva configuración
    return get_temperature()

# GET /sensors/humidity - Obtener lectura del sensor de humedad
@app.get("/sensors/humidity", response_model=HumidityResponse)
def get_humidity():
    """
    Obtiene la lectura actual del sensor de humedad.
    La unidad de medida se configura mediante PUT.
    """
    simulate_server_error()
    
    if sensors_config["humidity"]["status"] != "active":
        raise HTTPException(
            status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
            detail="Humidity sensor is not active"
        )
    
    # Simular lectura del sensor (valor base en porcentaje)
    percentage_value = round(random.uniform(40.0, 70.0), 2)
    unit = sensors_config["humidity"]["unit"]
    
    value = convert_humidity(percentage_value, unit)
    
    return HumidityResponse(
        sensor_id="HUM-001",
        value=round(value, 2),
        unit=unit,
        timestamp=datetime.now().isoformat(),
        status="ok"
    )

# PUT /sensors/humidity - Actualizar configuración del sensor de humedad
@app.put("/sensors/humidity", response_model=HumidityResponse)
def update_humidity_config(config: HumidityConfig):
    """
    Actualiza la configuración del sensor de humedad.
    Permite cambiar la unidad entre porcentaje relativo y humedad absoluta.
    """
    simulate_server_error()
    
    sensors_config["humidity"]["unit"] = config.unit
    
    # Retornar lectura actual con la nueva configuración
    return get_humidity()

# Manejador de error 404
@app.exception_handler(404)
async def not_found_handler(request, exc):
    return {
        "error": "Not Found",
        "message": f"The endpoint {request.url.path} does not exist",
        "status_code": 404
    }

# Manejador de error 500
@app.exception_handler(500)
async def internal_error_handler(request, exc):
    return {
        "error": "Internal Server Error",
        "message": "An unexpected error occurred on the server",
        "status_code": 500
    }

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
