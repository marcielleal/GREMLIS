#include "Random.hpp"
#include <iostream>
#include <ctime>

Random::Random (int i) {srand ((int)(time(NULL)+i)); }

int Random::getInt(int low, int high) {
	int k;
	double d;
	d=(double) rand()/((double) RAND_MAX + 1);
	k=(int) (d*(high-low+1));
	return (low+k );
}
