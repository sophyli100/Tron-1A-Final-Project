void moveForward()
{

motor[motorC]=100;
motor[motorB]=100;

wait1Msec(1000);

}

task main()
{
	moveForward();
}
