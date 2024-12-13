import cv2
import dlib
import math
import socket
BLINK_RATIO_THRESHOLD = 5.7


host ="192.168.1.1"
port = 4444
UDP_SRC_PORT = 4446


txbuff = bytearray(50)
lock = 0
lock_count = 0
error2deg = 0
error2deg_count = 0

def send_UDP(host, port,data_send):
    udp_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    destination = (host,UDP_SRC_PORT)

    try:
        udp_socket.sendto(data_send.encode(), (host, UDP_SRC_PORT))
        print(f"data sent success to {host}:{port}")
    except Exception as e:
        print(f"Error sending data{e}")
    finally:
        udp_socket.close()

def send_udp_packet(data):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
        udp_socket.sendto(data, (host, UDP_SRC_PORT))


def print_debug_hex_string(header, data_buf, length):
    log_info = f"{header} : "
    for idx in range(length):
        log_info += f"{data_buf[idx]:02X},"
    print(log_info)

def send_udp_packet(data):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_socket:
        udp_socket.sendto(data, (host, UDP_SRC_PORT))





#-----Step 5: Getting to know blink ratio

def midpoint(point1 ,point2):
    return (point1.x + point2.x)/2,(point1.y + point2.y)/2

def euclidean_distance(point1 , point2):
    return math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

def get_blink_ratio(eye_points, facial_landmarks):
    
    #loading all the required points
    corner_left  = (facial_landmarks.part(eye_points[0]).x, 
                    facial_landmarks.part(eye_points[0]).y)
    corner_right = (facial_landmarks.part(eye_points[3]).x, 
                    facial_landmarks.part(eye_points[3]).y)
    
    center_top    = midpoint(facial_landmarks.part(eye_points[1]), 
                             facial_landmarks.part(eye_points[2]))
    center_bottom = midpoint(facial_landmarks.part(eye_points[5]), 
                             facial_landmarks.part(eye_points[4]))

    #calculating distance
    horizontal_length = euclidean_distance(corner_left,corner_right)
    vertical_length = euclidean_distance(center_top,center_bottom)

    ratio = horizontal_length / vertical_length

    return ratio

#livestream from the webcam 
cap = cv2.VideoCapture(0)

'''in case of a video
cap = cv2.VideoCapture("__path_of_the_video__")'''

#name of the display window in OpenCV
cv2.namedWindow('BlinkDetector')

#-----Step 3: Face detection with dlib-----
detector = dlib.get_frontal_face_detector()

#-----Step 4: Detecting Eyes using landmarks in dlib-----
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
#these landmarks are based on the image above 
left_eye_landmarks  = [36, 37, 38, 39, 40, 41]
right_eye_landmarks = [42, 43, 44, 45, 46, 47]
flag = True

while True:
    
    if flag == True:
        HEADER = 0x11
        LOCK_1 = 0x66
        lock =  0
        error2deg = 0
        txbuff[0] = HEADER
        txbuff[1] = LOCK_1
        txbuff[2] = lock
        txbuff[3] = error2deg
        # Print debug information
        print_debug_hex_string("SENT", txbuff, 20)

        # Send t    he UDP packet
        send_udp_packet(bytes(txbuff))
    else:
        flag = True
        
    #capturing frame
    retval, frame = cap.read()

    #exit the application if frame not found
    if not retval:
        print("Can't receive frame (stream end?). Exiting ...")
        break 

    #-----Step 2: converting image to grayscale-----
##    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    #-----Step 3: Face detection with dlib-----
    #detecting faces in the frame 
    faces,_,_ = detector.run(image = frame, upsample_num_times = 0, 
                       adjust_threshold = 0.0)

    #-----Step 4: Detecting Eyes using landmarks in dlib-----
    for face in faces:
        
        landmarks = predictor(frame, face)

        #-----Step 5: Calculating blink ratio for one eye-----
        left_eye_ratio  = get_blink_ratio(left_eye_landmarks, landmarks)
        right_eye_ratio = get_blink_ratio(right_eye_landmarks, landmarks)
        blink_ratio     = (left_eye_ratio + right_eye_ratio) / 2

        if blink_ratio > BLINK_RATIO_THRESHOLD:
            flag = False
            cv2.putText(frame,"Abnomal",(10,50), cv2.FONT_HERSHEY_SIMPLEX,
                        2,(0,0,255),2,cv2.LINE_AA)
            print("Blinking")
            HEADER = 0x11
            LOCK_1 = 0x66
            lock =  1
            error2deg = 0
            txbuff[0] = HEADER
            txbuff[1] = LOCK_1
            txbuff[2] = lock
            txbuff[3] = error2deg
            # Print debug information
            print_debug_hex_string("SENT", txbuff, 20)

            # Send t    he UDP packet
            send_udp_packet(bytes(txbuff))
##        else:
##            HEADER = 0x11
##            LOCK_1 = 0x66
##            lock =  0
##            error2deg = 0
##            txbuff[0] = HEADER
##            txbuff[1] = LOCK_1
##            txbuff[2] = lock
##            txbuff[3] = error2deg
##            # Print debug information
##            print_debug_hex_string("SENT", txbuff, 20)
##
##            # Send t    he UDP packet
##            send_udp_packet(bytes(txbuff))
            
            
            #Blink detected! Do Something!

    cv2.imshow('BlinkDetector', frame)
    key = cv2.waitKey(1)
    if key == ord('r'):
        print("Blinking")
        HEADER = 0x11
        LOCK_1 = 0x66
        lock =  0
        error2deg = 1
        txbuff[0] = HEADER
        txbuff[1] = LOCK_1
        txbuff[2] = lock
        txbuff[3] = error2deg
        # Print debug information
        print_debug_hex_string("SENT", txbuff, 20)

        # Send t    he UDP packet
        send_udp_packet(bytes(txbuff))
        
    if key == ord('q'):
        break

#releasing the VideoCapture object
cap.release()
cv2.destroyAllWindows()
