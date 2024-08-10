#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

std::string convert_to_lowercase(std::string input);

int main()
{
	std::string rawCode, rawMessage;
	std::cout << "Give me the word code: ";
	std::getline(std::cin, rawCode);
	std::cout << "Give me the message to encrypt: ";
	std::getline(std::cin, rawMessage);	

    std::string code = convert_to_lowercase(rawCode);
    std::string message = convert_to_lowercase(rawMessage);

	message.erase(std::remove_if(message.begin(), message.end(), ::isspace), message.end());

	int codeLength = code.length(), messageLength = message.length();
	int index = 0;

	std::string finalMessage("");

	for(int i = 0; i < messageLength / codeLength; ++i)
	{
		for(int j = 0; j < codeLength; ++j)
		{
			char character = static_cast<char>((((
					static_cast<int>(message.at(index)) - 97 +
					static_cast<int>(code.at(j)) - 97) % 26) + 97));
			finalMessage.push_back(character);
			++index;
		}
	}

    for(int i = 0; i < messageLength % codeLength; ++i)
    {
        char character = static_cast<char>((((
                            static_cast<int>(message.at(index)) - 97 +
                            static_cast<int>(code.at(i)) - 97) % 26) + 97));
        finalMessage.push_back(character);
        ++index;
    }

    std::cout << "The encrypted message is: " << std::endl;
	std::cout << finalMessage << std::endl;
	
	return 0;
}

std::string convert_to_lowercase(std::string input)
{
    std::string output("");
    for(char ch : input)
    {
        output += std::tolower(ch);
    }
    return output;
}
