// SHUT DOWN FUNCTION 
// assume user won't press any other button other than enter

void shutDown(int gripPower)
{
	int userTime = 5000; // 5 seconds hold enter

	while (!getButtonPress(buttonEnter))
	{}

	buttonTimer[T1] = 0;

	while (getButtonPress(buttonEnter))
	{}

	if (buttonTimer[T1] >= userTime)
	{
		clawTimer[T2] = 0;
		setGripperPosition(S1, SV_GRIPPER, gripPower);
		while (clawTimer[T2] < 3000)
		{}
		setServoSpeed(S1, SV_CSERVO1, 0);
		setServoSpeed(S1, SV_CSERVO2, 0);
	}

	wait1Msec(10000); // wait 10 seconds before function ends

}


