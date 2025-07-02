#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question) 
		: question(question) {
	}
	
	bool isDuplicatedNumber(const string& guessNumber) {
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

	bool isEqualNumber(const string& guessNumber, int number) {
		return guessNumber[number] == question[number];
	}

	void assertIllegalArgument(const string& guessNumber) {
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		GuessResult result = {false, 0, 0};
		
		if (guessNumber == question) {
			return { true , 3, 0 };
		}
		else {
			for (int number = 0; number < 3; ++number) {
				if (isEqualNumber(guessNumber, number))
					result.strikes++;
				else if (guessNumber[number] == question[(number + 1) % 3] || guessNumber[(number + 1) % 3] == question[2])
					result.balls++;			
			}
		}
		return result;
	}

private:
	string question;
};