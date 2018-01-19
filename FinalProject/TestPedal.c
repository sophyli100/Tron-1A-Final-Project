
task main()
{
	SensorType[S2] = sensorEV3_Touch;



	do
	{
		while (SensorValue[S2] == 0)
		{}

		displayString (0, "It worked!");
		wait1Msec(5000);

	}while (!getButtonPress(buttonAny));

}
