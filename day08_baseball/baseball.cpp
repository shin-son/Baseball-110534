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
			if (guessNumber[0] == question[0])
				result.strikes++;
			else if (guessNumber[0] == question[1] || guessNumber[0] == question[2])
				result.balls++;

			if (guessNumber[1] == question[1])
				result.strikes++;
			else if (guessNumber[1] == question[0] || guessNumber[1] == question[2])
				result.balls++;


			if (guessNumber[2] == question[2])
				result.strikes++;
			else if (guessNumber[2] == question[0] || guessNumber[2] == question[1])
				result.balls++;
		}
		return result;
	}

private:
	string question;
};