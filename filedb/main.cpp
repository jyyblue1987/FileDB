#include <iostream>

using namespace std;

int main ()
{
	cout << "start program" << endl;

	char param[500];

	while(true)
	{
		cin >> param;
		if( strcmp(param, "q") == 0 )
			break;

	}
	cout << "end program";
}