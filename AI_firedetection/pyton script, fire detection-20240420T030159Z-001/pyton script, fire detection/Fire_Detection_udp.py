import numpy as np
import cv2
import socket
from threading import Thread

# IP address and port for the ESP32
ip_address = '192.168.1.5'
aport = 5555

url = f'http://{ip_address}:{aport}/video'

host = "192.168.1.2"
port = 4446
UDP_SRC_PORT = 4445
imH = 480
imW = 640
txbuff = bytearray(20)
lock = 0

def send_UDP(host, port, data_send):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    destination = (host, port)

    try:
        udp_socket.sendto(data_send.encode(), (host, port))
        print(f"data sent success to {host}:{port}")
    except Exception as e:
        print(f"Error sending data{e}")
    finally:
        udp_socket.close()

def send_udp_packet(data):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
        udp_socket.sendto(data, (host, port))

class VideoStream:
    def __init__(self, resolution=(640, 480), framerate=30, source=None):
        if source is None:
            source = url
        self.stream = cv2.VideoCapture(source)
        self.stream.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))
        self.stream.set(3, resolution[0])
        self.stream.set(4, resolution[1])
        self.grabbed, self.frame = self.stream.read()
        self.stopped = False

    def start(self):
        Thread(target=self.update, args=()).start()
        return self

    def update(self):
        while True:
            if self.stopped:
                self.stream.release()
                return
            self.grabbed, self.frame = self.stream.read()

    def read(self):
        return self.frame

    def stop(self):
        self.stopped = True
flag = False

# Load the trained cascade classifier XML file
custom_cascade = cv2.CascadeClassifier('fire_detection.xml')

# Open the default camera (usually 0)
videostream = VideoStream(resolution=(imW, imH)).start()

# Loop to capture frames from the camera
while True:
    # Capture frame-by-frame
    frame = videostream.read()

    # Check if frame is not None
    if frame is not None:
        # Convert frame to grayscale
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect custom objects (fire)
        custom_objects = custom_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=3, minSize=(30, 30))
        
        # Draw rectangles around the detected objects
        for (x, y, w, h) in custom_objects:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
            print("BOX")
            lock = 1
            txbuff[0] = lock
            send_udp_packet(bytes(txbuff))
            flag = True
##        if len(custom_objects) == 0:
##            print(" NO detection")
##            lock = 0
##            txbuff[0] = lock
##            send_udp_packet(bytes(txbuff))
            
##        if flag == False:
##            lock = 0
##            txbuff[0] = lock
##            send_udp_packet(bytes(txbuff))
##            print("out")
##        else:
##            print("Else")
##            flag = False

        # Display the resulting frame
        cv2.imshow('frame', frame)

    # Check for 'q' key press to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera
videostream.stop()

# Close all OpenCV windows
cv2.destroyAllWindows()
