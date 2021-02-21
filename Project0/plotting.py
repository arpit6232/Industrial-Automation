import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt


def main():
    angle = pd.read_csv('angle.csv')
    time = pd.read_csv('time.csv')
    frames = [time, angle]
    result = pd.concat(frames, axis=1)
    result = result.iloc[:-2]
    df = result
    df.columns = pd.RangeIndex(df.columns.size)
    df.rename(columns = {0:'time', 1:'angle'}, inplace = True) 

    # df.drop(['time'],axis=1,inplace=True)
    # df.columns = pd.RangeIndex(df.columns.size)
    # df.rename(columns = {0:'time', 1:'angle'}, inplace = True)

    ll = list(df['time'])
    ll = [(e-ll[0]) for e in ll]
    df['time'] = pd.DataFrame(ll)

    ll = list(df['angle'])
    ll = [(np.cos(np.radians(e))) for e in ll]
    df['angle'] = pd.DataFrame(ll)

    z = np.poly1d(np.polyfit(df['time'],df['angle'],9))
    y_p = z(df['time'])
    df['fit'] = pd.DataFrame(y_p)
    grad1 = list(df['fit'])

    diff_1 = np.gradient(df['fit'])
    z = np.poly1d(np.polyfit(df['time'],diff_1,9))
    y_p = z(df['time'])
    df['fit2'] = pd.DataFrame(y_p)
    df['grad_1'] = pd.DataFrame(diff_1)

    diff_2 = np.gradient(df['fit2'])
    z = np.poly1d(np.polyfit(df['time'],diff_2,3))
    y_p = z(df['time'])
    df['fit3'] = pd.DataFrame(y_p)
    df['grad_2'] = pd.DataFrame(diff_2)
    

    x = df['time']
    ang = df['angle']
    theta = df['fit']
    thetaDot = df['fit2']
    thetaDotDot = df['fit3']
    

    fig, axs = plt.subplots(nrows=4, ncols=1)
    fig.suptitle('Transient Response')

    # axs[0].set_title('Raw Serial Data')
    axs[0].plot(x,ang)
    axs[0].set(ylabel='Raw Sensor Readings', xlabel='Time')

    # axs[1].set_title('Theta')
    axs[1].plot(x,theta)
    axs[1].set(ylabel='Theta', xlabel='Time')

    # axs[2].set_title('Theta_Dot')
    axs[2].plot(x,thetaDot)
    axs[2].plot(x,df['fit2'])
    axs[2].set(ylabel='Theta_Dot', xlabel='Time')
    
    # axs[3].set_title('Theta_Dot_Dot')
    axs[3].plot(x,thetaDotDot)
    axs[3].plot(x,df['fit3'])
    axs[3].set(ylabel='Theta_Dot_Dot', xlabel='Time')

    # plt.show()
    # plt.savefig()
    
    grad1 = list(df['fit'])
    grad2 = list(df['grad_1'])
    grad3 = list(df['grad_2'])

    grad1 = np.array(grad1)
    grad2 = np.array(grad2)
    grad3 = np.array(grad3)

    # gradd = np.vstack((grad1,grad2))

    new_df = pd.DataFrame(grad1)
    new_df.to_csv('named1.csv', index=False)

    new_df = pd.DataFrame(grad2)
    new_df.to_csv('named2.csv', index=False)

    new_df = pd.DataFrame(grad3)
    new_df.to_csv('named3.csv', index=False)

if __name__ == '__main__':
    main()
