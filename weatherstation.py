import requests
import random
import time

API_KEY = "E7VS53P9FZWZF9QF"  # Correct Write API Key
url = "https://api.thingspeak.com/update"

while True:
    temperature = round(random.uniform(25.0, 35.0), 2)
    humidity = round(random.uniform(50.0, 70.0), 2)

    payload = {
        "api_key": API_KEY,
        "field1": temperature,
        "field2": humidity
    }

    response = requests.post(url, data=payload)
    print(f"Sent -> Temp: {temperature}°C, Humidity: {humidity}% | Response: {response.status_code} | Entry: {response.text}")
    
    time.sleep(15)
