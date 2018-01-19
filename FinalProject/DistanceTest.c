
task main()
{
	SensorType[S3] = sensorEV3_Ultrasonic;

	displayString(0, "Distance: %d", SensorValue[S3]);

	wait1Msec(5000);

}
