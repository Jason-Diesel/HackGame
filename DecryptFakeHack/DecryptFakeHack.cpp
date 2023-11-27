#include <iostream>

std::string decrypt(const std::string& ciphertext, int shift) {
	std::string decryptmessage;
	decryptmessage.resize(ciphertext.size());
	for (int i = 0; i < ciphertext.size(); i++) {
		int a = ciphertext[i] - 65; // Make it from 0 - 25
		a -= shift;
		// Use modulo to ensure the result is within the range 0 to 25
		while (a < 0)
		{
			a += 25;
		}
		decryptmessage[i] = a + 65; // make it A-Z
	}
	return decryptmessage;
}

int main()
{
	std::string letters;
	std::string Decryption;
	int specialNumber;
	std::cout << "Write the first two digits" << std::endl;
	std::cin >> specialNumber;
	if(specialNumber > 99)
	{
		std::cout << "error cannot use that digit" << std::endl;
		getchar();
		return -1;
	}
	std::cout << "Write the rest of the characters" << std::endl;
	std::cin >> letters;

	Decryption.resize(letters.size());

	Decryption = decrypt(letters, specialNumber);

	std::cout << "The Decrypt message is:" << Decryption << std::endl;

	std::cout << "press any letter key + enter to exit (write a word or letter + enter)" << std::endl;
	std::cin >> letters;
	return 1;
}