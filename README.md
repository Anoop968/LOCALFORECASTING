# LOCALFORECASTING
This Edge AI project uses an ESP8266 and DHT11 sensor to predict rain offline. It features a Logistic Regression model trained on Kaggle weather data and deployed as a C++ header using TinyML techniques. Designed for localized event monitoring, it provides real-time "Rain/No Rain" predictions on an LCD without needing a cloud connection.Key Features
Offline Intelligence: No cloud APIs or Wi-Fi required. The prediction logic is baked into the hardware.

Real-time Monitoring: Continuous data acquisition via the DHT11 sensor.

TinyML Implementation: Uses scikit-learn for training and micromlgen to convert the model into a lightweight C++ header (model.h).

Visual Output: Real-time feedback via Serial Monitor and I2C LCD (16x2).

🛠️ Tech Stack
Hardware: ESP8266 (NodeMCU), DHT11 Sensor, I2C LCD 16x02.

Firmware: C++ (Arduino Framework), SimpleDHT Library.

Data Science: Python, Pandas (Data Cleaning), Scikit-Learn (ML Modeling).

Deployment: Micromlgen (Python-to-C++ porting).

📂 How it Works
Data Collection: Collected 1,000+ rows of weather data (Temperature, Humidity, RainToday) from Kaggle.

Preprocessing: Cleaned raw data using Pandas to handle missing values and convert categorical labels ("Yes/No") to binary (1/0).

Training: Trained a Logistic Regression classifier in Python.

Export: Ported the trained model weights into a C++ header file (model.h).

Inference: The ESP8266 reads live sensor data, feeds it into the model.h algorithm, and predicts "Rain" or "No Rain" every 5 seconds.

📊 Data Preview
The model was trained on the following features:

Temperature (°C): Captured as a float from the DHT11.

Humidity (%): Captured as a float from the DHT11.

Label: Binary classification where 1 = Rain and 0 = No Rain.

Future Enhancements
Add a Barometric Pressure sensor (BMP280) for higher prediction accuracy.

Implement deep sleep modes for battery-powered event monitoring.

Add a buzzer alarm to notify the event team when the rain probability exceeds a threshold.
