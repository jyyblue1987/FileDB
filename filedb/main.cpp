#include <iostream>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_STRING_LENGTH 100
#define MAX_PARAM 10
struct Student {
	char last_name[MAX_STRING_LENGTH];
	char first_name[MAX_STRING_LENGTH];
	char phone[MAX_STRING_LENGTH];
};



int main ()
{
	list<Student> student_list = list<Student>();

	cout << "start program" << endl;

	string param;

	while(true)
	{
		getline(cin, param); 
		if( param.compare("q") == 0 )
			break;

		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM){
			ssin >> arr[param_count];
			++param_count;
		}


		if( param_count < 1 )
		{
			cout << "Please input correct value" << endl;
			continue;
		}

		if( arr[0].compare("a") == 0 )
		{
			if( param_count < 2 )
			{
				cout << "Please input correct value" << endl;
				continue;
			}

			if( arr[1].compare("s") == 0 )
			{
				Student stu1;
				strcpy(stu1.last_name, arr[2].c_str());
				strcpy(stu1.first_name, arr[3].c_str());
				strcpy(stu1.phone, arr[4].c_str());

				student_list.push_back(stu1);
			}
		}
		else if( arr[0].compare("l") == 0 )
		{

		}
		else if( arr[0].compare("t") == 0 )
		{

		}
		else
		{
			cout << "Please input a or l or t value" << endl;

		}

	}
	cout << "end program";
}