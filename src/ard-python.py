import serial

# Configure the serial port
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Replace '/dev/ttyUSB0' with the appropriate port and baud rate

# Read and print serial data in real-time
while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode().rstrip()
        print(data)