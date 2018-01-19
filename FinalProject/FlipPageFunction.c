#include "EV3Servo-lib-UW.c"

/*
void flipPage ()
{
	setGripperPosition(S1, 1, 0)

	wait1Msec(500);
	if (getButtonPress(buttonEnter))
	{
		shutdown();
	}

	else
	{
		move (forward);

		while (sensorValue [S2] == 0)
		{}

		move (0, 0);

		setGripperPosition(S1, 1, 70);

		wait1Msec(200);

		move (backwards);

		while (sensorValue[S3] <= 22 && sensorValue[S3] >= 20)
		{}

		move (0, 0);
	}
}
*/

task main()
{
	//SensorType[S1] = sensorI2CCustom9V;

	//setGripperPosition (S1, 1, 70);

	//wait1Msec (5000);

	//resetGripper (S1, 1);

	SensorType[S3] = sensorEV3_Ultrasonic;

	displayString(0, "Distance: %d", SensorValue[S3]);

	wait1Msec(5000);

}
