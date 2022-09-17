#!/usr/bin/python3

import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"

import pygame
from pygame.locals import *

import requests

# initialize display environment
pygame.init()
pygame.display.init()
pygame.display.set_caption('Draw')

WHITE = (255,255,255)
BLACK = (0,0,0)

requestRes = (1024,768)
#width = width + width % 16      # must be a multiple of 16
#height = width      # square

# camera surface
import pygame.camera
pygame.camera.init()
cam = pygame.camera.Camera("/dev/video2",requestRes)
cam.start()
camRes = cam.get_size()
print(cam.get_size())
font = pygame.font.Font(None, 25)

# picamera ... sort of...
#from picamera import PiCamera
#camera = PiCamera()
#camera.resolution = requestRes
#camBuffer = bytearray(3*width*width)

print("cam initialized")

# display surface
lcdRes = (camRes[1], camRes[1])         # the laser is square, so the display should be too
lcd = pygame.display.set_mode(lcdRes)      
lcdRect = lcd.get_rect()

# laser 'surface'
laserRes = (4095,4095)

# overlay surface
overlay = pygame.surface.Surface(lcdRes)
overlay.set_colorkey((0,0,0))

# active surfact
laserSurf = pygame.surface.Surface(lcdRes)
laserSurf.set_colorkey((0,0,0))

# menu surface
menu1 = pygame.surface.Surface(lcdRes)
menu1.set_colorkey((0,0,0))
menu1Text = font.render('Calibrate, TL, TR, BR',True,WHITE)
menu1TextPos = menu1Text.get_rect(center=lcdRect.center)
menu1.blit(menu1Text, menu1TextPos)
pygame.Rect.inflate_ip(menu1TextPos, 25, 25)
pygame.draw.rect(menu1,WHITE, menu1TextPos,3)

# rectangles
TLrect = pygame.Rect((0          ,0          ),(lcdRes[0]/2,lcdRes[1]/2))
TL = (0,0)
TRrect = pygame.Rect((lcdRes[0]/2,0          ),(lcdRes[0]/2,lcdRes[1]/2))
TR = (lcdRes[0],0)
BRrect = pygame.Rect((lcdRes[0]/2,lcdRes[1]/2),(lcdRes[0]/2,lcdRes[1]/2))
BR = (lcdRes[0],lcdRes[1])

def map(value) :
    return int(value * laserRes[0] / lcdRes[0])

def mapToLaser(pos) :
    Mx = pos[0]
    My = pos[1]

    # translate
    Lx = Mx - TL[0]
    Ly = My - TL[1]
    # scale
    Lx *= (laserRes[0]/(TR[0]-TL[0]))
    Ly *= (laserRes[1]/(BR[1]-TL[1]))

    #return f"{int (Lx)},{int(laserRes[1]- Ly)}"
    return f"{int (Lx)},{int(laserRes[1] - Ly)}"

posList = ""
lastPos = (0,0)
active = True
calibrate = False
while active:
    #camera.capture(camBuffer, format='rgb')
    #camImage = pygame.image.frombuffer(camBuffer,res, 'RGB')
    #lcd.blit(camImage,(0,0))
    #pygame.display.flip()
    if cam.query_image():
        camImage = cam.get_image()
        camRect = camImage.get_rect(center=lcdRect.center)

        lcd.blit(camImage, camRect)

    events = pygame.event.get()
    for e in events:
        if ( e.type == KEYUP) :
            if e.key == K_q :
                # quit
                active = False

            if e.key == K_b:
                # calibrate
                overlay.fill((0,0,0))
                lastPos = (0,0)
                posList = ""
                calibrate = not calibrate

                if calibrate:
                    # clear boundary
                    laserSurf.fill(BLACK)
                    # send calibrate dots to laser
                    try:
                        r = requests.get("http://laserdemo.home/serverConfig?lq=75")
                        cal = f"0,{laserRes[1]}&{laserRes[0]},{laserRes[1]}&{laserRes[0]},0&0,0"
                        r = requests.get(f"http://laserdemo.home/draw?{cal}")
                    except:
                        print("Calibrate Dots error")
                        #print(r.status_code)
                        #print(r.text)

                else:
                    # turn off the calibrate dots
                    try:
                        r = requests.get(f"http://laserdemo.home/draw?")
                    except:
                        print("Calibrate Dots error")
                        #print(r.status_code)
                        #print(r.text)
                

        if calibrate:
            # do calibrate stuff   
            if e.type == MOUSEBUTTONDOWN :
                pos =pygame.mouse.get_pos()
                if TLrect.collidepoint(pos):
                    TL = pos
                    overlay.fill(BLACK,TLrect)
                    pygame.draw.circle(overlay, (0,255,0), pos, 5)
                if TRrect.collidepoint(pos):
                    TR = pos
                    overlay.fill(BLACK,TRrect)
                    pygame.draw.circle(overlay, (0,255,0), pos, 5)
                if BRrect.collidepoint(pos):
                    BR = pos
                    overlay.fill(BLACK,BRrect)
                    pygame.draw.circle(overlay, (0,255,0), pos, 5)

                laserSurf.fill(BLACK)
                pygame.draw.rect(laserSurf, WHITE, pygame.Rect(TL[0], TL[1],TR[0]-TL[0],BR[1]-TL[1]),3)
            
                print (f"TL: {TL}, TR: {TR}, BR: {BR}")

        else:
            # do draw stuff
            if ( e.type == MOUSEBUTTONDOWN) :
                pos = pygame.mouse.get_pos()
                # dot at position
                pygame.draw.circle(overlay, (255,0,0), pos, 5)
                # line from last pos
                if lastPos != (0,0) :
                    pygame.draw.line(overlay, (255,0,0), lastPos, pos, 3)
                lastPos = pos
                #add to list
                # mapToLaser(pos)
                #posList = f"{posList}&{map(pos[0])},{map(lcdRes[1]-pos[1])}"
                posList = f"{posList}&{mapToLaser(pos)}"

            if ( e.type == KEYUP) :
                if e.key == K_c :
                    # clear
                    overlay.fill((0,0,0))
                    lastPos = (0,0)
                    posList = ""

                if e.key == K_s :
                    print(posList)
                    try:
                        r = requests.get(f"http://laserdemo.home/draw?{posList}")
                        print(r.status_code)
                        print(r.text)
                    except:
                        print("Send List error")

    if calibrate:
        lcd.blit(menu1,(0,0))
    lcd.blit(laserSurf,(0,0))
    lcd.blit(overlay,(0,0))
    pygame.display.flip()


