#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>
#include <string>

const std::vector<std::pair<int, std::string>> feedback_list = {
		{5, "I am an ice cube."},
		{20, "Ice cold.. "},
		{40, "Quite chilly. "},
		{60, "Lukewarm. "},
		{80, "Warm! We are heating up! "},
		{90, "Boiling hot!! "},
		{95, "Woah! I just burned my hand, dude!! "}
};

int guess_base = 7;

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void feedback(double guess, double outer_bound, double solution)
{
	
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

int validated_input()
{
	int input{};
	while (true)
	{
		std::cin >> input;
		if (!std::cin.fail())
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return input;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please try again.\n";
	}
}


int main()
{
	std::vector<int> levels{ 100, 500, 1000, 2000 };
	bool lost_game = false;
	int guesses_avail = guess_base;

	for (int i = 0; i < levels.size(); i++)
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

		std::cout << "You have " << guesses_avail << " guesses in total.\n";
		std::cout << "Let's go, guess the number!\n";
		guess = validated_input();


		while (guess != solution)
		{
			if (guesses_avail > 1)
			{
				--guesses_avail;
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
				std::cout << guesses_avail << " guesses left!\n";
				guess = validated_input();
			}
			else
			{
				lost_game = true;
				break;
			}
		}

		system("cls");

		if (!lost_game)
		{

			++guesses_avail;

			std::cout << "Congratulations, you won! The correct answer was " << solution << " and it took you " << nr_guesses << " guesses.\n";
			std::cout << "Moving on to next level..\n\n\n";
			guess_base += 2;
			guesses_avail = guess_base;
		}
		else
		{
			std::cout << "Sorry! You lost. The correct answer was " << solution << ".\n";
			std::cout << "Better luck next time!\n";
			break;
		}
	}

	std::cout << "Game over. Press any key to quit.\n";

	return 0;
}