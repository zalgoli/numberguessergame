#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <string>

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void feedback(double guess, double outer_bound, double solution)
{
	std::vector<std::pair<int, std::string>> feedback_list = {
		{5, "I am an ice cube."},
		{20, "Ice cold.. "},
		{40, "Quite chilly. "},
		{60, "Lukewarm. "},
		{80, "Warm! We are heating up! "},
		{90, "Boiling hot!! "},
		{95, "Woah! I just burned my hand, dude!! "}
	};

	if (abs(guess - solution) < 10)
	{
		std::cout << "Boiling hot!! ";
	}
	else
	{
		double proximity = 100.0 * (1.0 - (abs(solution - guess)) / abs(outer_bound - solution));

		for (auto it = feedback_list.rbegin(); it != feedback_list.rend(); ++it)
		{
			if (it->first <= proximity)
			{
				std::cout << it->second;
				break;
			}
		}
	}
}


int main()
{
	std::vector<int> levels{ 100, 500, 1000, 2000 };

	for (int i = 0; i < levels.size() - 1; i++)
	{

		int r_lower, r_upper;
		std::cout << "Level " << i + 1 << ". Your range has to be at least " << levels[i] << " wide.\n";
		std::cout << "Define a lower and upper limit for the range:\n";
		std::cin >> r_lower;
		std::cin >> r_upper;

		if (r_lower > r_upper)
		{
			swap(r_lower, r_upper);
		}

		while (abs(r_upper - r_lower) < levels[i])
		{
			std::cout << "The range is smaller than  " << levels[i] << ". Define new ranges:\n";
			std::cin >> r_lower;
			std::cin >> r_upper;
			if (r_lower > r_upper) swap(r_lower, r_upper);
		}

		// Generating random number
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> range(r_lower, r_upper);
		int solution = range(gen);
		int guess;
		int nr_guesses = 1;
		int upper_last = r_upper;
		int lower_last = r_lower;

		std::cout << "Let's go, guess the number!\n";
		std::cin >> guess;

		while (guess != solution)
		{
			++nr_guesses;
			feedback(guess, guess > solution ? lower_last : upper_last, solution);
			if (guess > solution)
			{
				upper_last = guess;
				std::cout << "Lower!\n";
			}
			else
			{
				lower_last = guess;
				std::cout << "Higher!\n";
			}
			std::cin >> guess;
		}

		system("cls");

		std::cout << "Congratulations, you won! The correct answer was " << solution << " and it took you " << nr_guesses << " guesses.\n";
		std::cout << "Moving on to next level..\n\n\n";
	}

	std::cout << "You finished the game!! Congrats!\n";

	return 0;
}