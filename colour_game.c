void randomize_colour(string & side, int & side_number)
{
	int colour_num[3] = {5, 3, 7};
	string colours[3] = {"red", "green", "yellow"};
	int index = 0;

	index = random(2);

	side = colours[index];
	side_number = colour_num[index];
}

void colour_game()
{
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	const int CHECK_SPEED = -10;
	const int RIGHT_LOCATN = -29;
	const int TOP_LOCATN = -90;
	const int LEFT_LOCATN = -90;

	int right_check = 0;
	int top_check = 0;
	int left_check = 0;
	int left_side_num = 0;
	int top_num = 0;
	int right_side_num = 0;
	string left_side = " ";
	string top = " ";
	string right_side = " ";

	randomize_colour(left_side, left_side_num);
	randomize_colour(top, top_num);
	randomize_colour(right_side, right_side_num);

	while (top == left_side || top == right_side)
		randomize_colour(top, top_num);
	while (right_side == left_side || right_side == top)
		randomize_colour(right_side, right_side_num);

	displayString(2, "left is %s", left_side);
	displayString(4, "top is %s", top);
	displayString(6, "right is %s", right_side);
	wait1Msec(5000);

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	nMotorEncoder[motorC] = 0;
	motor[motorC] = CHECK_SPEED;
	while(nMotorEncoder[motorC] > RIGHT_LOCATN)
	{}
	motor[motorC] = 0;
	wait1Msec(2000);
	right_check = SensorValue[S3];

	nMotorEncoder[motorC] = 0;
	motor[motorC] = CHECK_SPEED;
	while(nMotorEncoder[motorC] > TOP_LOCATN)
	{}
	motor[motorC] = 0;
	wait1Msec(2000);
	top_check = SensorValue[S3];

	nMotorEncoder[motorC] = 0;
	motor[motorC] = -7;
	while(nMotorEncoder[motorC] > LEFT_LOCATN)
	{}
	motor[motorC] = 0;
	wait1Msec(2000);
	left_check = SensorValue[S3];

	eraseDisplay();
	displayString(2, "%d, %d, %d", right_check, top_check, left_check);
	wait1Msec(2000);

	if(right_check != right_side_num || left_check != left_side_num || top_check != top_num)
	{
		displayString(8, "you done fucked up");
		wait1Msec(2000);
	}

	else
	{
		displayString(9, "well done NIGGGAAAA");
		wait1Msec(2000);
	}
	// replace with end function

	motor[motorC] = -CHECK_SPEED;
	while(nMotorEncoder[motorC] > 0)
	{}
	motor[motorC] = 0;

}

task main()
{
	colour_game();


}
