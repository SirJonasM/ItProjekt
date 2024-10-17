import requests
from dotenv import load_dotenv
import os
def make_api_call():
    load_dotenv()
    # The URL of the API (ESP8266 server)
    url = os.getenv("API_URL")
    if not url:
        print("API_URL not found in .env file.")
        return
    # Send a GET request to the API
    response = requests.get(url)

    # Check if the request was successful
    if response.status_code == 200:
        # Write the content to a local file
        with open("task8.csv", "w", newline='') as file:
            file.write(response.text)
        print("File 'task8.csv' successfully downloaded and saved.")
    else:
        print(f"Failed to retrieve the file. Status code: {response.status_code}")

if __name__ == "main":
    make_api_call()
