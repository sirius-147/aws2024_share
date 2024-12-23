import serial
import csv
import os
from datetime import datetime, timedelta
import pandas as pd
import matplotlib.pyplot as plt
from time import sleep


SERIAL_PORT = '/dev/ttyACM0' # arduino port
BAUD_RATE = 9600


DATA_DIR = '/home/aws2024/aws2024_code/aws2024_csv_data' # data in this path

def get_csv_file_path():
    now = datetime.utcnow()
    first_day = now.replace(day=1)
    last_day = (first_day + timedelta(days=31)).replace(day=1) - timedelta(days=1)
    file_name = f"temp_moist_{first_day.strftime('%Y%m%d')}_{last_day.strftime('%Y%m%d')}.csv"
    file_path = os.path.join(DATA_DIR, file_name)

    if not os.path.exists(file_path):
        with open(file_path, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['Date (YYYY-MM-DD)', 'Time (GMT)', 'Temperature (C)', 'Humidity (%)'])

    return file_path

def save_data_to_csv(temperature, humidity):
    file_path = get_csv_file_path()
    now = datetime.utcnow()
    date_str = now.strftime('%Y-%m-%d')
    time_str = now.strftime('%H:%M:%S')

    with open(file_path, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([date_str, time_str, temperature, humidity])

    print(f"Data saved: {date_str} {time_str}, Temp: {temperature} C, Humidity: {humidity} %")


def plot_graph():
    file_path = get_csv_file_path()
    if not os.path.exists(file_path):
        print("No data available to plot.")
        return

    data = pd.read_csv(file_path)
    data['Datetime'] = pd.to_datetime(data['Date (YYYY-MM-DD)'] + ' ' + data['Time (GMT)'])
    data.set_index('Datetime', inplace=True)

    plt.figure(figsize=(12, 6))
    plt.plot(data.index, data['Temperature (C)'], label='Temperature (C)', color='red')
    plt.plot(data.index, data['Humidity (%)'], label='Humidity (%)', color='blue')
    plt.title('Temperature and Humidity Over Time')
    plt.xlabel('Time (GMT)')
    plt.ylabel('Values')
    plt.legend()
    plt.grid()
    plt.tight_layout()
    graph_path = os.path.join(DATA_DIR, 'temp_moist_graph.png')
    plt.savefig(graph_path)
    plt.close()
    print(f"Graph saved: {graph_path}")

def read_arduino_data():
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=10) as ser:
            while True:
                line = ser.readline().decode('utf-8').strip()
                if line.startswith("Temperature:"):
                    parts = line.split(", ")
                    temp_str = parts[0].split(": ")[1].strip()
                    hum_str = parts[1].split(": ")[1].strip(" %")
                    temperature = float(temp_str)
                    humidity = float(hum_str)

                    save_data_to_csv(temperature, humidity)
                    plot_graph()

                    sleep(60) 
    except Exception as e:
        print(f"Error reading data: {e}")

if __name__ == '__main__':
    if not os.path.exists(DATA_DIR):
        os.makedirs(DATA_DIR)

    read_arduino_data()
