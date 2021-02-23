void randomize_colour(string & side)
{

	string colours[3] = {"red", "blue", "green"};
	int index = 0;

	index = random(2);

	side = colours[index];
}



task main()
{
	string left_side = " ";
	string top = " ";
	string right_side = " ";

	randomize_colour(left_side);
	randomize_colour(top);
	randomize_colour(right_side);

	while (top == left_side || top == right_side)
		randomize_colour(top);

	while (right_side == left_side || right_side == top)
		randomize_colour(right_side);


	displayString(2, "left is %s", left_side);
	displayString(4, "top is %s", top);
	displayString(6, "right side is %s", right_side);

	wait1Msec(5000);

}
