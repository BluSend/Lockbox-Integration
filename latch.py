from gpiozero import OutputDevice, Button
from time import sleep

lock = OutputDevice(17)
sensor = Button(27, pull_up=True)

print("Locked: ", sensor.is_pressed)
#INITIAL RUN DO NOT PUT LATCH BACK IN
lock.on()
sleep(0.3)

print("Unlocked: ", not sensor.is_pressed)
sleep(1.7)
lock.off()
sleep(0.5)
print("Locked: ", sensor.is_pressed)
#PUT LATCH BACK IN QUICK!!!!
sleep(5)
#New RUN
print("Locked: ", sensor.is_pressed)

lock.on()
sleep(0.3)

print("Unlocked: ", not sensor.is_pressed)
sleep(1.7)
lock.off()
sleep(3)
#Look, now its locked in again!
print("Locked: ", sensor.is_pressed)