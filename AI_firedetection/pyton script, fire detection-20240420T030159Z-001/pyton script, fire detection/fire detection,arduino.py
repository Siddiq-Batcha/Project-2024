#code written by Shubham Shinganapure date 13/4/2018 _______
#S-TROniX Technologies ____________Nagpur, MH, INDIA

import numpy as np
import cv2
import serial
import time


ip_address = '192.168.1.3'
port = '5555'

url = f'http://{ip_address}:{port}//video'

fire_cascade = cv2.CascadeClassifier('fire_detection.xml')
#fire_detection.xml file & this code should be in the same folder while running the code

##ser1 = serial.Serial('COM14',9600)#change COM port number on which your arduino is connected

cap = cv2.VideoCapture(url)
while 1:
    #ser1.write('0')
    ret, img = cap.read()
    #cv2.imshow('imgorignal',img)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    fire = fire_cascade.detectMultiScale(img, 1.2, 5)
    for (x,y,w,h) in fire:
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        print ('Fire is detected..!')
##        ser1.write('p')
        time.sleep(0.2)
        
    cv2.imshow('img',img)
    ser1.write('s')
    
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
