import sensor, image, time
from pyb import Pin
from pyb import Servo


tile_servo=Servo(1)#上
pan_servo=Servo(2)#下
pan_servo.angle(-2)
pan_servo.angle(0)
s = Pin('P5', Pin.IN, Pin.PULL_DOWN)
s_8 = Pin('P1',Pin.OUT_PP)
s_4 = Pin('P2',Pin.OUT_PP)
s_2 = Pin('P3',Pin.OUT_PP)
s_1 = Pin('P4',Pin.OUT_PP)

red_threshold  = (18, 55, 23, 90, -3, 80)
k = 2479
list_num = []
data = 0
i = 0
fire = 0
num = 0
sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

s.low()
s_8.low()
s_4.low()
s_2.low()
s_1.low()

def d_output(val1):
    if val1 >= 200 and val1 <= 205:
        s_8.low()
        s_4.low()
        s_2.low()
        s_1.high()#1
    elif val1 >= 206 and val1 <= 215:
        s_8.low()
        s_4.low()
        s_2.high()
        s_1.low()#2
    elif val1 >= 216 and val1 <= 225:
        s_8.low()
        s_4.low()
        s_2.high()
        s_1.high()#3
    elif val1 >= 226 and val1 <= 235:
        s_8.low()
        s_4.high()
        s_2.low()
        s_1.low()#4
    elif val1 >= 236 and val1 <= 245:
        s_8.low()
        s_4.high()
        s_2.low()
        s_1.high()#5
        print(5)
    elif val1 >= 246 and val1 <= 255:
        s_8.low()
        s_4.high()
        s_2.high()
        s_1.low()#6
        print(6)
    elif val1 >= 256 and val1 <= 265:
        s_8.low()
        s_4.high()
        s_2.high()
        s_1.high()#7
    elif val1 >= 266 and val1 <= 275:
        s_8.high()
        s_4.low()
        s_2.low()
        s_1.low()#8
    elif val1 >= 276 and val1 <= 285:
        s_8.high()
        s_4.low()
        s_2.low()
        s_1.high()#9
    elif val1 >= 286 and val1 <= 295:
        s_8.high()
        s_4.low()
        s_2.high()
        s_1.low()#10
    elif val1 >= 296 and val1 <= 300:
        s_8.high()
        s_4.low()
        s_2.high()
        s_1.high()#11

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # Take a picture and return the image.

    blobs = img.find_blobs([red_threshold])
    if blobs :
        max_blob = find_max(blobs)
        pan_error = max_blob.cx()-80
        img.draw_rectangle(max_blob.rect()) # rect
        img.draw_cross(max_blob.cx(), max_blob.cy()) # cx, cy

        if abs(pan_error) >= 10:
            #fire = 0
            if pan_error < 0:
                pan_servo.angle(pan_servo.angle()+2)
            else:
                 pan_servo.angle(pan_servo.angle()-2)
        elif abs(pan_error) < 10 and fire == 0:

            print("目标已瞄准!")
            s_8.high()
            s_4.high()
            s_2.high()
            s_1.high()
            if i < 50:
                list_num.append(k/((blobs[0][2]+blobs[0][3])/2))
            else:
                data=(sum(list_num)/len(list_num)+10)-30-30
                list_num = []
                i = 0
            i+=1
            if int(data) != 0:
                #uart.write(str(int(data)))

                d_output(int(data))
                time.sleep(10)
                print(int(data))
                #fire = 1

                s_8.low()
                s_4.low()
                s_2.low()
                s_1.low()
            #list_data = []
        #print(max_blob.pixels())
        #print((blobs[0][2]+blobs[0][3])/2)
        #print("pan_error: ", pan_error)

        #print(list_num)
