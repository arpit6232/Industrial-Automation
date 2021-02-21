import numpy as np 
import matplotlib.pyplot as plt


def main():
    temp = [90, 95, 100, 105, 110, 115, 120, 125]
    x = [e*e for e in temp]
    y = [-59.86, -56.57, -52.55, -50.54, -46.88, -43.23, -39.75, -35.55]

    y = [np.sin(np.radians(e)) for e in y]

    # fig, axs = plt.subplots(nrows=1, ncols=1)
    # fig.suptitle('C3 Constant - Angle Vs Input Signal')
    plt.title('C3 Constant - Angle Vs Input Signal -> 3.696e-05 x - 1.17')
    plt.plot(x,y)
    plt.xlabel('Input Signal')
    plt.ylabel('Angle')

    z = np.poly1d(np.polyfit(x,y,1))
    y_p = z(x)

    # slope = ((x*y_p).mean(axis=1) - x.mean()*y_p.mean(axis=1)) / ((x**2).mean() - (x.mean())**2)
    
    print(z)
    plt.plot(x,y_p)

    plt.show()

if __name__ == '__main__':
    main()
