import serial
import time
import matplotlib.pyplot as plt
import csv


def set_usb(baudrate):
    return serial.Serial('/dev/ttyUSB0', baudrate)

def log_data(start, ser):

    # Read and record the data
    log_dat =[]                       # empty list to store the data
    log_time=[]
    # while True:
    print("START")
    # t_end = time.time() + 2.5
    for i in range(3000):
        # print("ready")
        b = ser.readline()         # read a byte string
        if(i==0):
            continue

        log_dat.append(float(b.decode('ISO-8859-1'))) # add to the end of data list

        log_time.append(time.time()-start)

    return log_dat, log_time

def write_to_file(log_dat, log_time):

    with open("arpit.csv","w") as f:
        wr = csv.writer(f,delimiter="\n")
        wr.writerows((log_dat,log_time))

    plt.plot(log_time,log_dat)

    plt.show()


def main():
    ser = set_usb(115200)
    start=time.time()
    log_dat, log_time = log_data(start,ser)
    write_to_file(log_dat, log_time)
    ser.close()


if __name__ == '__main__':
    main()
