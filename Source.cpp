#include<iostream>
#include "Location.h"
using namespace std;
int main() {

	Location location1;
	cin >> location1;
	cout << location1;
	cout << endl;
	Location::printLocation(location1);

	return 0;
}