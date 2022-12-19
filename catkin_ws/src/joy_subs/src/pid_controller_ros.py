from re import L
import rospy
from std_msgs.msg import Int16
from std_msgs.msg import Int32

#reference speed.
set_speed_x=0         
set_speed_y=0


deltaT=0
eintegral_x=0
eintegral_y=0

#parameters for PID controller.
#can be canged according to tunning the system/
kp=5
ki=0.8


pub_x=rospy.Publisher('motor_x',Int16,queue_size=10)
pub_y=rospy.Publisher('motor_y',Int16,queue_size=10)

def callback_x(data):
    set_speed_x=data.data

def callback_y(data):
    set_speed_y=data.data

def deltaTime(data):
    deltaT=data.data

def pid_x(data):
    #pid control for motorX.
    e=set_speed_x-data.data               
    eintegral_x=eintegral_x+e*deltaT
    u=kp*e + ki*eintegral_x
    pub_x.publish(u)
    
def pid_y(data):
    #pid control for motorY.
    e=set_speed_y-data.data
    eintegral_x=eintegral_y+e*deltaT
    u=kp*e + ki*eintegral_y
    pub_y.publish(u)
    
def listner():
    rospy.init_node('publisher_node',anonymous=True)
    rospy.Subscriber('chatter_x',Int16,callback_x)
    rospy.Subscriber('chatter_y',Int16,callback_y)
    rospy.Subscriber('time_int',Int32,deltaTime)
    rospy.Subscriber('rpm_x',Int16,pid_x)
    rospy.Subscriber('rpm_y',Int16,pid_y)
    rospy.spin()
if __name__=='__main__':
    try:
        listner() 
    except rospy.ROSInterruptException:
        pass 