import rospy
from std_msgs.msg import String

def callback(data):
    rospy.loginfo("Recieved Data is : %s", data.data)
def listner():
    rospy.init_node("Subscriber_node",anonymous=True)
    rospy.Subscriber('talking_topic',String,callback)
    rospy.spin()
if __name__=='__main__':
    try:
        listner() 
    except rospy.ROSInterruptException:
        pass