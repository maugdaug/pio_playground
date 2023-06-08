'''
Axis 0: left joystick left/right
Axis 1: left joystick up/down
Axis 2: L2
Axis 3: right joystick left/right
Axis 4: right joystick up/down
Axis 5: R2

Button 0: X
Button 1: O
Button 2: Square
Button 3: Triangle
Button 4: "Share"
Button 5: PS
Button 6: "Options"
Button 7: L3
Button 8: R3
Button 9: L1
Button 10: R1
Button 11: D-pad up
Button 12: D-pad down
Button 13: D-pad left
Button 14: D-pad right
Button 15: Touch pad
''' 

import pygame, os, sys, serial, time, struct
from pygame.locals import *

# os.environ["SDL_VIDEODRIVER"] = "dummy"

pygame.init()
pygame.joystick.init()

# joysticks = {}

joysticks = [pygame.joystick.Joystick(i) for i in range(pygame.joystick.get_count())]

FTDI = serial.Serial('/dev/ttyUSB0', 2000000)

print("Starting...")

def main():

    # def __init__(self):

    pad_input_X = 0.0       # axis 0
    pad_input_Y = 0.0       # axis 1
    pad_input_Z = 0.0       # axis 3
    pad_input_E = 0.0       # axis 4
    pad_input_L2 = 0.0      # axis 2
    pad_input_R2 = 0.0      # axis 5

    deadband = 0.2

    print_interval = 0.1
    print_index = 1

    start_byte = b"\x2C"
    TX_interval = 0.1
    TX_index = 1

    done = False

    start_time = time.time()

    while True:
        for event in pygame.event.get():
            # print(event)

            if event.type == pygame.QUIT:
                print("Quitting...")
                done = True

            if event.type == pygame.JOYAXISMOTION:
                # print(event.axis, ": ", event.value)
                match event.axis:
                    case 0:
                        if(abs(event.value)<deadband):
                            pad_input_X = 0.0
                        else:
                            pad_input_X = -round(event.value, 4)

                    case 1:
                        if(abs(event.value)<deadband):
                            pad_input_Y = 0.0
                        else:
                            pad_input_Y = round(event.value, 4)

                    case 2:
                        if(abs(event.value+1)<deadband):
                            pad_input_L2 = 0.0
                        else:
                            pad_input_L2 = round(event.value, 4)
                        
                    case 3:
                        if(abs(event.value)<deadband):
                            pad_input_Z = 0.0
                        else:
                            pad_input_Z = round(event.value, 4)
                    
                    case 4:
                        if(abs(event.value)<deadband):
                            pad_input_E = 0.0
                        else:
                            pad_input_E = round(event.value, 4)

                    case 5:
                        if(abs(event.value+1)<deadband):
                            pad_input_R2 = 0.0
                        else:
                            pad_input_R2 = round(event.value, 4)
                        

            # if event.type == pygame.JOYBUTTONDOWN:
            #     print(event)


        if(time.time() - start_time > print_interval * print_index):
            # print(time.time() - start_time)

            print_index += 1
            print(pad_input_X,
                  "\t", pad_input_Y,
                  "\t", pad_input_Z,
                  "\t", pad_input_E,
                  "\t", pad_input_L2,
                  "\t", pad_input_R2)
            
        if(time.time() - start_time > TX_interval * TX_index):
            TX_index += 1
            Xpacked = struct.pack('f', pad_input_X)
            Ypacked = struct.pack('f', pad_input_Y)
            Zpacked = struct.pack('f', pad_input_Z)
            Epacked = struct.pack('f', pad_input_E)
            L2packed = struct.pack('f', pad_input_L2)
            R2packed = struct.pack('f', pad_input_R2)

            FTDI.write(start_byte)
            FTDI.write(Xpacked)
            FTDI.write(Ypacked)
            FTDI.write(Zpacked)
            FTDI.write(Epacked)
            FTDI.write(L2packed)
            FTDI.write(R2packed)
            

if __name__ == "__main__":
    main()
    pygame.quit()