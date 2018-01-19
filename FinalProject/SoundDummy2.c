
task main()
{

	SensorValue[S4] = sensorSoundDBA;

	time1[T1] = 0;
	time1[T2] = 0;
	int counter1 = 0;
	int sum = 0;
	int counter2 = 0;
	float avg = 0;

	while (!getButtonPress(buttonEnter))
	{

		while (time1[T1] >=1000)
		{
			sum=0;
			counter2=0;
			avg=0;
			time1[T2]=0;
			while (time1[T2] <=1000)
			{
				sum += SensorValue[S4];
				counter2++;
			}
			avg = (float)sum/(float)counter2;
			displayString(counter1, "Volume: %f", avg);
			counter1++;
			time1[T2]=0;
			time1[T1]=0;

		}

	}


}
