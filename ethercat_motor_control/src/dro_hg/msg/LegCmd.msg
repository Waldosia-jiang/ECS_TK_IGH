std_msgs/Header header
uint8 begin	#起始关节	
uint8 end	#终止关节	
MotorCmd[<=15] motor_cmd	#0-5左腿（ID:1-6），6-11右腿（ID:7-12）12-14腰（ID:13-15）
