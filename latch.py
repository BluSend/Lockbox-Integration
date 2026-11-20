from gpiozero import OutputDevice, Button
from time import sleep

lock1 = OutputDevice(17)
lock2 = OutputDevice(22)
feedback1 = Button(27, pull_up=True)
feedback2 = Button(26, pull_up=True)


def trigger(lock, feedback):
    print('Initial Lock Status: ', feedback.is_pressed)
    lock.on()
    
    sleep(3)
    lock.off()

    sleep(0.3)
    print("Lock status: ", feedback.is_pressed)  #if there the latch isnt put back into the solenoid this will be false so it has its own fail safe to make sure the latch has been reinsterted
    print('place latch in to show locked status')
    sleep(2)
    print("Lock status: ", feedback.is_pressed)

trigger(lock1, feedback1)
sleep(1)
#trigger(lock2, feedback2)
''' Sample testing initially
print("Locked: ", not feedback1.is_pressed)

lock1.on()
sleep(1.5)
lock1.off()

sleep(0.3)
print("Locked: ", not feedback1.is_pressed)
'''