import numpy as np
import cv2
import serial
import time
import socket

# IP address and port for the ESP32
ip_address = '192.168.1.4'
port = '5555'
url = f'http://{ip_address}:{port}//video'

##host ="192.168.0.50"
##port = 4444
##UDP_SRC_PORT = 4445
##
##def send_UDP(host, port,data_send):
##    udp_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
##    destination = (host,port)
##
##    try:
##        udp_socket.sendto(data_send.encode(), (host, port))
##        print(f"data sent success to {host}:{port}")
##    except Exception as e:
##        print(f"Error sending data{e}")
##    finally:
##        udp_socket.close()
##
##
##
##def print_debug_hex_string(header, data_buf, length):
##    log_info = f"{header} : "
##    for idx in range(length):
##        log_info += f"{data_buf[idx]:02X},"
##    print(log_info)
##
##def send_udp_packet(data):
##    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
##        udp_socket.sendto(data, (host, port))

# Open serial connection to the ESP32
siri = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the connection to establish

# Load the trained cascade classifier XML file
custom_cascade = cv2.CascadeClassifier('fire_detection.xml')

# Open the default camera (usually 0)
cap = cv2.VideoCapture(url)

# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()
flag = False
# Loop to capture frames from the camera
while True:
    # Capture frame-by-frame
    ret, frame = cap.read()

    # If frame is read correctly ret is True
    if not ret:
        print("Error: Can't receive frame (stream end?). Exiting...")
        break

    # Convert frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect custom objects (fire)
    custom_objects = custom_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=3, minSize=(30, 30))

    # Draw rectangles around the detected objects
    for (x, y, w, h) in custom_objects:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
        siri.write(b'a')
        print("BOX")
        
    

    # Display the resulting frame
    cv2.imshow('frame', frame)

    # Check for 'q' key press to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera
cap.release()

# Close serial connection
siri.close()

# Close all OpenCV windows
cv2.destroyAllWindows()
