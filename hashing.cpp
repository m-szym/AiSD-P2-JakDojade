#include "hashing.h"

long long hash_string(char* key)
{
	int i = 0;
	//int limiter = 10151;
	int limiter = 15485863;
	//int prime = 67;
	int prime = 67;
	int prime_power = prime;
	long long hash = 0;	//uwaga na rozmiar

	while (i < MAX_KEY_SIZE)
	{
		if (key[i] == '\0') return hash;

		hash = (hash + (key[i] - '0' + 1) * prime_power) % limiter;
		prime_power = (prime_power * prime) % limiter;
		++i;
	}


	//std::cout << key << " == " << hash;
	return hash;
}