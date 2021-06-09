import os
import requests

USERNAME = os.getenv("USERNAME")
IP = os.getenv("IP")

URL = f"http://{IP}/api/{USERNAME}/lights/1/state"

# put adds information to server, using a dict with key 'on' value 'false'
requests.put(URL, json={"on": False})

while True:
    requests.put(URL, json={"bri": 254, "on": True}

