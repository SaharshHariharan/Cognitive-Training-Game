void button_game()
{
	SensorType[S2] = sensorEV3_Touch;
	SensorType[S1] = sensorEV3_Touch;

	int red_button = 0;
	int yellow_button = 0;
	int red_count = 0;
	int yellow_count = 0;

	red_button = random(5);
	yellow_button = random(5);

	displayString(2,"press red button %d times", red_button);
	displayString(4,"when done");
	displayString(6,"press the left button on EV3");


	motor[motorA] = 25;
	motor[motorB] = -25;

	while(!getButtonPress(buttonLeft))
	{
		while(SensorValue[S2] == 0 & !getButtonPress(buttonLeft))
			{}
		while(SensorValue[S2] == 1 & !getButtonPress(buttonLeft))
			{}
		red_count++;
	}

	eraseDisplay();
	displayString(2,"press yellow button %d times", yellow_button);
	displayString(4,"when done");
	displayString(6,"press the right button on EV3");


	while(!getButtonPress(buttonRight))
	{
		while(SensorValue[S1] == 0 & !getButtonPress(buttonRight))
			{}
		while(SensorValue[S1] == 1 & !getButtonPress(buttonRight))
			{}
		yellow_count++;
	}

	motor[motorA] = motor[motorB] = 0;

	eraseDisplay();

	if(red_count-1 != red_button || yellow_count-1 != yellow_button)
	{
		displayString(2, "you done fucked up nigga");
		wait1Msec(5000);
	}
	else
	{
		displayString(2, "well done NIGGA");
		wait1Msec(5000);
	}
}
task main()
{
	button_game();

}
