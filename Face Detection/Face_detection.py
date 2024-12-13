import cv2
from scipy.spatial import distance as dist
from imutils import face_utils
import numpy as np
import imutils

def eye_aspect_ratio(eye):
    # Compute the euclidean distances between the two sets of
    # vertical eye landmarks (x, y)-coordinates
    A = dist.euclidean(eye[1], eye[5])
    B = dist.euclidean(eye[2], eye[4])

    # Compute the euclidean distance between the horizontal
    # eye landmark (x, y)-coordinates
    C = dist.euclidean(eye[0], eye[3])

    # Compute the eye aspect ratio
    ear = (A + B) / (2.0 * C)

    # Return the eye aspect ratio
    return ear

# Load the cascade
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')

# To capture video from webcam.
cap = cv2.VideoCapture(0)
# To use a video file as input
# cap = cv2.VideoCapture('filename.mp4')

# Define constants for eye closure detection
EAR_THRESHOLD = 0.3
CONSECUTIVE_FRAMES = 3
frame_counter = 0
closed_frames = 0

while True:
    # Read the frame
    _, img = cap.read()
    img = imutils.resize(img, width=450)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detect faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)

    # Detect eyes and check for closure
    for (x, y, w, h) in faces:
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex, ey, ew, eh) in eyes:
            eye = roi_gray[ey:ey+eh, ex:ex+ew]
            eye = cv2.resize(eye, (24, 24))
            ear = eye_aspect_ratio(eye)
            if ear < EAR_THRESHOLD:
                closed_frames += 1
            else:
                if closed_frames >= CONSECUTIVE_FRAMES:
                    print("Eye is close")
                closed_frames = 0
            cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)

    # Display
    cv2.imshow('img', img)
    # Stop if escape key is pressed
    k = cv2.waitKey('q') & 0xff
    if k == 'q':
        break

# Release the VideoCapture object
cap.release()
