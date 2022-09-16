#!/usr/bin/python3

import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"

import pygame
from pygame.locals import *

import requests

pygame.init()

width = 600
height = width      # square
res = (width,height)

# initialize display environment
pygame.display.init()
pygame.display.set_caption('Draw')

# display surface
lcd = pygame.display.set_mode(res)

def map(value) :
    return int(value * 4095 / width)

posList = ""
lastPos = (0,0)
active = True
while active:
    events = pygame.event.get()
    for e in events:
        if ( e.type == MOUSEBUTTONUP) :
            pos = pygame.mouse.get_pos()
            # dot at position
            pygame.draw.circle(lcd, (255,0,0), pos, 5)
            # line from last pos
            if lastPos != (0,0) :
                pygame.draw.line(lcd, (255,0,0), lastPos, pos, 3)
            lastPos = pos
            #add to list
            posList = f"{posList}&{map(pos[0])},{map(width-pos[1])}"

            pygame.display.flip()

        if ( e.type == KEYUP) :
            if e.key == K_c :
                # clear
                lcd.fill((0,0,0))
                lastPos = (0,0)
                posList = ""

                pygame.display.flip()

            if e.key == K_s :
                print(posList)
                try:
                    r = requests.get(f"http://laserdemo.home/draw?{posList}")
                    print(r.status_code)
                    print(r.text)
                except:
                    print("HTTP GET error")

            if e.key == K_q :
                # quit
                active = False

                

