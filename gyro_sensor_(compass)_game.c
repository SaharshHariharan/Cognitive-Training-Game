void rand_degAndDirec(string & direction, int & degree)
{

	string directions[2] = {"right", "left"};
	int dir_index = 0;

	dir_index = random(1);

	direction = directions[dir_index];

	int degrees[3] = {20, 40, 60};
	int deg_index = 0;

	deg_index = random(2);

	degree = degrees[deg_index];
}

void gyro_game (int & current_degrees)
{
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Angle;
	wait1Msec(50);

	resetGyro(S4);

	const int TOL = 7;
	string direction = " ";
	int degrees = 0;
	int input_degrees = 0;

	rand_degAndDirec(direction, degrees);

	while(current_degrees + degrees < -60 || current_degrees + degrees > 60)
		rand_degAndDirec(direction, degrees);

	displayString(2,"turn the dial %s", direction);
	displayString(4,"%d degrees", degrees);

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	eraseDisplay();
	input_degrees = SensorValue[S4];
	if (fabs(input_degrees - degrees) > TOL)
	{
		displayString(2,"you done fucked up!");
		wait1Msec(2000);
	}
	else
	{
		displayString(4,"Well done NIGGGAAA");
		wait1Msec(2000);
	}
	current_degrees = current_degrees + degrees;
}
task main()
{
	int current_degrees = 0;
	gyro_game(current_degrees);
}





