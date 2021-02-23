// Hunnain Atif
// Code for autonomous robot game
// Game is designed to help user improve reflexes and memory
// Look at readMe file for further description

int how_many_rounds(int & rounds) // used to allow user to choose how many rounds they want to play
{
	displayBigTextLine(2, "ENTER");
	displayBigTextLine(5, "ROUNDS");
	displayBigTextLine(7, "MAX 4");
	wait1Msec(1000);

	while(!getButtonPress(buttonEnter)) // rounds are counted with right button and enter is confirm
	{
		while(!getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		while(getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		while(!getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		rounds++;
	}

	if(rounds >=4) // check in place to make sure a maximum of four rounds
		rounds = 4;
		
	if(rounds ==0) // check to make sure minimum of one round 
		rounds = 1;

	return rounds;
}

void shutdown_procedure(bool lose, float score_time) // function called when game is complete or player loses
{
	float score = 0;
	const int CONVERSION = 100000000; // converts time into a more traditional score

	if (lose == true)
	{
		eraseDisplay();
		displayBigTextLine(3, "YOU LOSE");
		displayBigTextLine(7, "PRESS BACK");
		wait1Msec(70000000000000000000); // delay keeps game from continuing
	}
	else
	{
		eraseDisplay();
		displayBigTextLine(3, "YOU WIN");
		score = (1/score_time) * CONVERSION;
		displayBigTextLine(6, "Score:");
		displayBigTextLine(9, "%f", score);
		wait1Msec(70000000000000000000);
	}
}

void rand_degAndDirec(string & direction, int & degree) // used to randomize an angle and direction for gyro sensor (compass) game
{ // pass by reference used as more than one variable is being manipulated

	string directions[2] = {"right", "left"};
	int dir_index = 0;

	dir_index = random(1);

	direction = directions[dir_index];

	int degrees[3] = {20, 40, 60};
	int deg_index = 0;

	deg_index = random(2);

	degree = degrees[deg_index];
}

void gyro_game() // implmentation of gyro sensor (compass) game
{
	SensorType[S4] = sensorEV3_Gyro; // sensor configuration
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

	while(getGyroRate(S4) != 0)
	{}
	resetGyro(S4);

	const int TOL = 13;
	string direction = " ";
	int degrees = 0;
	int input_degrees = 0;
	int check_degrees = 0;

	rand_degAndDirec(direction, degrees); // recieves a random angle and direction from previous function

	eraseDisplay();
	displayBigTextLine(2,"COMPASS");
	displayBigTextLine(4,"TURN %d", degrees);
	displayBigTextLine(6, "%s", direction);

	while(!getButtonPress(buttonEnter))
	{}
	while(getButtonPress(buttonEnter))
	{}

	eraseDisplay();
	input_degrees = getGyroDegrees(S4); // gyro sensor input is used to check if activity was completed correctly
	check_degrees = fabs(input_degrees);
	if (fabs(check_degrees - degrees) > TOL) // tolerance was added to make game more reliable and account for evironmental factors
	{
		int score = 0;
		shutdown_procedure(1, score);
	}
	if ((direction == "right") && (input_degrees < 0))
	{
		int score = 0;
		shutdown_procedure(1, score);
	}
	if ((direction == "left") && (input_degrees > 0))
	{
		int score = 0;
		shutdown_procedure(1, score);
	}
}
void randomize_colour(string & side, int & side_number) // randomizer function for colour game
{
	int colour_num[3] = {5, 3, 1};
	string colours[3] = {"red", "green", "black"}; // creates an array of colours and another array of their associated sensor imput
	int index = 0;

	index = random(2);

	side = colours[index];
	side_number = colour_num[index];
}

void colour_game() // implementation of colour game
{
	SensorType[S3] = sensorEV3_Color; // sensor configuration
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	const int CHECK_SPEED = -10; 
	const int RIGHT_LOCATN = -29; // motor moves sensor to check placeholders, the constants are the motor encoder values
	const int TOP_LOCATN = -88;
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

	randomize_colour(left_side, left_side_num); // calls randomizer function to generate a random colour to plae in each placeholder
	randomize_colour(top, top_num);
	randomize_colour(right_side, right_side_num);

	while (top == left_side || top == right_side) // check in place to make sure no colours repeat
		randomize_colour(top, top_num);
	while (right_side == left_side || right_side == top)
		randomize_colour(right_side, right_side_num);

	displayBigTextLine(2, "COLOUR");
	displayBigTextLine(4, "LEFT: %s", left_side);
	displayBigTextLine(6, "TOP: %s", top);
	displayBigTextLine(8, "RIGHT: %s", right_side);
	wait1Msec(5000);

	while(!getButtonPress(buttonEnter)) // waits for the user to press the enter button to signal they have completed activity
	{}
	while(getButtonPress(buttonEnter))
	{}

	nMotorEncoder[motorC] = 0;
	motor[motorC] = CHECK_SPEED;
	while(nMotorEncoder[motorC] > RIGHT_LOCATN) // motor is moved to all locations and colour sensor is used to check if acitivy was completed correctly
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
	if((right_check != right_side_num && right_check != 2)
		|| (left_check != left_side_num && left_check != 2)
		|| (top_check != top_num && top_check != 2))
	{
		int score = 0;
		shutdown_procedure(1,score);
	}

	motor[motorC] = -CHECK_SPEED;
	while(nMotorEncoder[motorC] < 110)
	{}
	motor[motorC] = 0;
}
void button_game() // button game requires users to press moving buttons a certain number of times
{
	SensorType[S2] = sensorEV3_Touch; // sensor configuration
	SensorType[S1] = sensorEV3_Touch;

	int red_button = 0;
	int yellow_button = 0;
	int red_count = 0;
	int yellow_count = 0;

	red_button = random(3);
	yellow_button = random(3);

	eraseDisplay();
	displayBigTextLine(2, "BUTTON");
	displayBigTextLine(4,"RED: %d ", red_button);
	displayBigTextLine(6,"PRESS LEFT");
	displayBigTextLine(8,"EV3 BUTTON");


	motor[motorA] = 25; // motor is used to move the buttons around
	motor[motorB] = -25;

	while(!getButtonPress(buttonLeft)) // counts times button is pressed by touch sensor input
	{
		while(SensorValue[S2] == 0 & !getButtonPress(buttonLeft))
			{}
		while(SensorValue[S2] == 1 & !getButtonPress(buttonLeft))
			{}
		red_count++;
	}

	eraseDisplay();
	displayBigTextLine(4,"YELLOW: %d", yellow_button);
	displayBigTextLine(6,"PRESS RIGHT");
	displayBigTextLine(8,"EV3 BUTTON");


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
		int score = 0;
		shutdown_procedure(1, score);
	}

}
task main()
{
	int score = 0;
	const int ROUND1_TIME = 600000; // time limits set for each round to test test user speed 
	const int ROUND2_TIME = 150000; // if not completed in time game shutsdown
	const int ROUND3_TIME = 210000;
	const int ROUND4_TIME = 240000;
	int user_input = 0;
	int num_of_rounds = 0;

	num_of_rounds = how_many_rounds(user_input);

	eraseDisplay();
	displayBigTextLine(5, "PLAYING %d", num_of_rounds);
	displayBigTextLine(7, "ROUNDS");
	wait1Msec(2000);

	eraseDisplay();
	displayBigTextLine(2, "ROUND 1");
	eraseDisplay();
	displayBigTextLine(8, "3");
	wait1Msec(1000);
	displayBigTextLine(8, "2");
	wait1Msec(1000);
	displayBigTextLine(8, "1");
	wait1Msec(1000);

	time1[T1] = 0;
	time1[T2] = 0; // timers used to set score and implement round time limits

	gyro_game(); // main just calls the functions of each individual activity to establish a round


	if (time1[T2] > ROUND1_TIME)
		shutdown_procedure(1,score);

	if (num_of_rounds == 1)
	{
		score = time1[T1];
		shutdown_procedure(0,score);
	}

	time1[T2] = 0;

	button_game();


	colour_game();

	if (time1[T2] > ROUND2_TIME)
		shutdown_procedure(1,score);

	if (num_of_rounds == 2)
	{
		score = time1[T1];
		shutdown_procedure(0,score);
	}

	time1[T2] = 0;

	button_game();

	gyro_game();

	colour_game();


	if (time1[T2] > ROUND3_TIME)
		shutdown_procedure(1,score);

	if (num_of_rounds == 3)
	{
		score = time1[T1];
		shutdown_procedure(0,score); // a win condition is produced if the user has played all rounds successfully
	}

	time1[T2] = 0;

	button_game();

	gyro_game();

	button_game();

	colour_game();

	if (time1[T2] > ROUND4_TIME)
		shutdown_procedure(1,score);

	score = time1[T1];
	shutdown_procedure(0,score);

}
