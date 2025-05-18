import requests
import time

API_KEY = "RS62YUB4CN5C6NZH"  # Your Write API Key
url = "https://api.thingspeak.com/update"

temperature = 25.0  # Starting temperature

while True:
    # Send current temperature to ThingSpeak
    payload = {
        "api_key": API_KEY,
        "field1": round(temperature, 2)
    }

    response = requests.post(url, data=payload)
    print(f"Sent -> Temperature: {temperature}°C | Response: {response.status_code} | Entry ID: {response.text}")

    # Wait 15 seconds before sending next data
    time.sleep(15)

    # Increase temperature by 1°C
    temperature += 1.0

    # Reset after 50°C
    if temperature > 50:
        temperature = 25.0
