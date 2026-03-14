uint8 mode  #运动模式 1、位置控制；3、速度控制；4、力控模式；8、csp模式；10、cst模式
uint8 num   #从站的站号
float32 q	#关节位置，rad	
float32 dq	#速度，rad/s
float32 current	#电流		
int16[2] temperature	#电机绕组温度和驱动器温度		
uint32 motorstate	#电机错误码	
