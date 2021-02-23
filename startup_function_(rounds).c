int how_many_rounds(int & rounds)
{
	displayString(1, "Enter number of rounds");
	displayString(2, "with right button");
	displayString(3, "press enter when done");
	displayString(5, "maximum 4 rounds");
	wait1Msec(1000);

	while(!getButtonPress(buttonEnter))
	{
		while(!getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		while(getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		while(!getButtonPress(buttonRight)& !getButtonPress(buttonEnter))
			{}
		rounds++;
	}

	if(rounds >=4)
		rounds = 4;

	return rounds;
}

task main()
{
	int user_input = 0;
	int num_of_rounds = 0;

	num_of_rounds = how_many_rounds(user_input);

	eraseDisplay();
	displayString(5, "playing for, %d rounds", num_of_rounds);
	wait1Msec(5000);

}
