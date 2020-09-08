#include <iostream>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_STRING_LENGTH 100
#define MAX_PARAM 10
struct Student {
	int id;
	string last_name;
	string first_name;
	string phone;
};

struct Course {
	int id;
	string prefix;
	int number;
	string title;
	int credit;
};

struct Grade {
	int id;
	string type;
	float score;	
};

struct Semester {
	int id;
	string code;
	int year;	
	string desc;
};



int main ()
{
	list<Student> student_list = list<Student>();
	list<Course> course_list = list<Course>();
	list<Grade> grade_list = list<Grade>();
	list<Semester> semester_list = list<Semester>();

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
				int last_id = 0;
				if( student_list.size() > 0 )
				{
					Student last = student_list.back();
					last_id = last.id;
				}
				Student data;
				data.id = last_id + 1;
				data.last_name = arr[2];
				data.first_name = arr[3];
				data.phone = arr[4];

				student_list.push_back(data);
			}

			if( arr[1].compare("c") == 0 )
			{
				int last_id = 0;
				if( course_list.size() > 0 )
				{
					Course last = course_list.back();
					last_id = last.id;
				}

				Course data;
				data.id = last_id + 1;
				data.prefix = arr[2];
				data.number = stoi(arr[3]);
				data.title = arr[4];
				data.credit = stoi(arr[5]);

				course_list.push_back(data);
			}

			if( arr[1].compare("g") == 0 )
			{
				int last_id = 0;
				if( grade_list.size() > 0 )
				{
					Grade last = grade_list.back();
					last_id = last.id;
				}

				Grade data;
				data.id = last_id + 1;
				data.type = arr[2];
				data.score = stof(arr[3]);
				
				grade_list.push_back(data);
			}

			if( arr[1].compare("m") == 0 )
			{
				int last_id = 0;
				if( semester_list.size() > 0 )
				{
					Semester last = semester_list.back();
					last_id = last.id;
				}

				Semester data;
				data.id = last_id + 1;
				data.code = arr[2];
				data.year = stoi(arr[3]);
				data.desc = arr[4];

				semester_list.push_back(data);
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