from re import L
import rospy
from std_msgs.msg import Int16

l=[0,0]

def callback_x(data):
    #rospy.loginfo("Recieved Data for X is : %d", data.data)
    global l
    l[0]=data.data

def callback_y(data):
    #rospy.loginfo("Recieved Data for Y is : %d", data.data)
    global l
    l[1]=data.data
    rospy.loginfo("Recieved Data for X and Y is : [ %d , %d ]", l[0],l[1])


def listner():
    rospy.init_node("Subscriber_node",anonymous=True)
    global l
    l=[0,0]
    rospy.Subscriber('chatter_x',Int16,callback_x)
    rospy.Subscriber('chatter_y',Int16,callback_y)
    rospy.spin()
if __name__=='__main__':
    try:
        listner() 
    except rospy.ROSInterruptException:
        pass 