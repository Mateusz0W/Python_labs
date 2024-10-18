#!/usr/bin/env python3.11
import sys
import random
# Write a module that will simulate autonomic car.
# The simulation is event based, an example:
# car1 = Car()
# car1.act(event)
# print(car1.wheel_angle, car1.speed)
# where event can be anything you want, i.e. :
# `('obstacle', 10)` where `10` is a duration (time) of the event.
##The program should:
# - act on the event
# - print out current steering wheel angle, and speed
# - run in infinite loop
# - until user breaks the loop

#The level of realism in simulation is of your choice, but more sophisticated solutions are better.
#If you can think of any other features, you can add them.
#Make intelligent use of pythons syntactic sugar (overloading, iterators, generators, etc)
#Most of all: CREATE GOOD, RELIABLE, READABLE CODE.
#The goal of this task is for you to SHOW YOUR BEST python programming skills.
#Impress everyone with your skills, show off with your code.
#
#Your program must be runnable with command "python task.py".
#Show some usecases of your library in the code (print some things)
#
#When you are done upload this code to github repository. 
#
#Delete these comments before commit!
#Good luck.

class Car:
    def __init__(self):
        self.wheel_angle=0
        self.speed=100
    
    def go_right(self):
        self.speed=50
        self.wheel_angle=-45
    
    def go_left(self):
        self.speed=50
        self.wheel_angle=45
    def go_straight(self,time):
        if time%2==0:
            self.speed=100
            self.wheel_angle=0

    def act(self,event):
        if event == 'obstacle on right':
            self.go_left()
        elif event == 'obstacle on left':
            self.go_right()
        elif event == 'obstacle in front':
            if random.randint(0,1):
                self.go_right()
            else:
                self.go_left()
        



time=1
i=0
car1=Car()
event=['obstacle on right','no obstacle','obstacle on left','no obstacle','obstacle in front']
while(True):
    car1.act(event[i])
    car1.go_straight(time)
    print(event[i],car1.wheel_angle, car1.speed)
    time+=1
    if time%3==0:
        i+=1
    if len(event)<=i:
        i=0
    
    


        