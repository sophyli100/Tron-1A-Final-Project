#include "EV3Servo-lib-UW.c"
#include "EV3_FileIO.c"
//These libraries were provided by the teaching team

const int STOP_MOVING = -12;
const int FORWARDS = 25;
const int BACKWARDS = -25;
const int MOTORG = 1;
const int MOTORY = 2;
const int GRIPPER = 4;
const int TRACK_END = 42;
const int TRACK_BEG = 18;

/*
Assigns a power to the motors. If the robot is not stopping, it accounts for 
deadband to ensure the two motors are moving at the same speed. The motors 
were also mechanically positioned in opposite directions so they had to receive
opposite power values.
Coded by Shafin Shahriar
*/
void robotDrive(int motorPow)
{
	if (motorPow == STOP_MOVING)
	{
		setServoSpeed(S1, MOTORG, motorPow);
		setServoSpeed(S1, MOTORY, motorPow);
	}
	else
	{
		setServoSpeed(S1, MOTORG, motorPow, -3, -17);
		setServoSpeed(S1, MOTORY, -motorPow, -11, -22);
	}

}

/*
Stops robot, opens claw, and waits 5 seconds
Coded by Jean De Jesus
*/
void pause ()
{
	robotDrive (STOP_MOVING);
	setGripperPosition(S1, GRIPPER, 70);
	wait1Msec(5000);
}

/*
This function grabs a page, moves the page to the end location, releases the 
page, and returns to its start location. It also has checks to see if the user
has hit the pause button throughout. If the user chooses to pause the function
while it is flipping a page, the claw grasps the page again afterwards before 
continuing.
Coded by Hannah Rosenberg
*/
void flipPage ()
{
	setGripperPosition(S1, GRIPPER, 70);

	wait1Msec(500);

	setGripperPosition(S1, GRIPPER, 0);

	wait1Msec(500);

	if (getButtonPress(buttonEnter))
	{
		pause();
	}

	  robotDrive (FORWARDS);

		while (SensorValue[S3] <= TRACK_END)
		{
			if (getButtonPress(buttonEnter))
			{
				pause();
				robotDrive(BACKWARDS);
				wait1Msec(50);
				robotDrive(STOP_MOVING);
				setGripperPosition (S1, GRIPPER, 0);
				wait1Msec(500);
				robotDrive(FORWARDS);
			}
		}

		robotDrive(STOP_MOVING);

		setGripperPosition(S1, GRIPPER, 70);

		wait1Msec(500);

    robotDrive (BACKWARDS);

		while (SensorValue[S3] >= TRACK_BEG)
		{
			if (getButtonPress(buttonEnter))
			{
				pause();
				robotDrive (BACKWARDS);
			}
		}

	robotDrive(STOP_MOVING);

}

/*
This function first calculates the average volume played over the course of a 
second by dividng the sum of the readings by the number of readings taken. It
then checks if the average volume fits into the piano, mezzo forte, or forte 
range (or if no sound was made). It then outputs the range and the time the 
range was played at to a file.
Coded by Sophy Li
*/
void outputVolume(int numReadings, int sum, TFileHandle & fout)
{
	float volume = 0;
	volume = (float)sum/(float)numReadings;
	string volRange = "Pause";

	if (volume <= 1)
	{
		volRange = "No sound";
	}
	else if(volume <= 15)
	{
		volRange = "Piano";
	}

	else if(volume <=55)
	{
		volRange = "Mezzo Forte";
	}

	else
	{
		volRange = "Forte";
	}

	writeLongPC(fout, time1[T3]/1000);
	writeTextPC(fout, volRange);
	writeEndlPC(fout);
}

/*
This function takes sound readings continuously for a second and adds them 
together. It also counts the number of readings taken. 
Coded by Jean De Jesus
*/
int collectReadings(int & numReadings)
{
	int sum = 0;
	time1[T2] = 0;
	while (time1[T2] <= 1000)
	{
		sum += SensorValue[S4];
		numReadings++;
	}

	return sum;
}

/*
This function finds the sum of all the readings taken in one second and the 
number of readings taken using the Collect Readings function. It then passes
them to the Output Volume function. 
Coded by Sophy Li
*/
void measureVolume(TFileHandle & fout)
{
	int numReadings = 0;
	int sum = 0;

	sum = collectReadings(numReadings);
	outputVolume(numReadings, sum, fout);
}

//Coded by Hannah Rosenberg
task main()
{
	SensorType[S1] = sensorI2CCustom9V;
	SensorType[S2] = sensorEV3_Touch;
	SensorType[S3] = sensorEV3_Ultrasonic;
	SensorType[S4] = sensorSoundDBA;

	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "soundReadings.txt");

	robotDrive (STOP_MOVING);

	displayString (0,"Push centre button to start");

	while (!getButtonPress(buttonEnter))
	{}

	while (getButtonPress(buttonEnter))
	{}

	eraseDisplay();

	displayString (0,"Hold centre button during");
	displayString (1,"page flip to pause");
	displayString (3,"Else, hold centre button");
	displayString (4,"to end program");

//moves robot to correct start location

	if (SensorValue[S3] > TRACK_BEG)
	{

		robotDrive(BACKWARDS);

		while (SensorValue[S3] > TRACK_BEG)
		{}

		robotDrive (STOP_MOVING);
	}

	time1[T1] = 0;

	time1[T3] = 0;

/*
Continuously checks to see if user has hit foot pedal or if 1 second has
passed. If the user has hit the foot pedal, the Flip Page function is called.
If one second has passed, the Measure Volume function is called.
*/
	while (!getButtonPress(buttonEnter))
	{
		if (SensorValue[S2] != 0)
		{
			flipPage ();
		}

		if (time1[T1] >= 1000)
		{
			measureVolume(fout);
			clearTimer(T1);
		}

	}

	robotDrive(STOP_MOVING);

	writeTextPC(fout, "Duration of session: ");
	writeLongPC(fout, time1[T3]/1000);
	writeEndlPC(fout);

	closeFilePC(fout);
}
