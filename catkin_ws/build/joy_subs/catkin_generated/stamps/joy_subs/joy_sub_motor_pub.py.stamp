from re import L
import rospy
from std_msgs.msg import Int16

pub_x=rospy.Publisher('motor_x',Int16,queue_size=10)
pub_y=rospy.Publisher('motor_y',Int16,queue_size=10)

def callback_x(data):
    pub_x.publish(data.data)

def callback_y(data):
    pub_y.publish(data.data)

def listner():
    rospy.init_node('publisher_node',anonymous=True)
    rospy.Subscriber('chatter_x',Int16,callback_x)
    rospy.Subscriber('chatter_y',Int16,callback_y)
    rospy.spin()
if __name__=='__main__':
    try:
        listner() 
    except rospy.ROSInterruptException:
        pass 