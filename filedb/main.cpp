#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>

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

struct Take {
	int student_id;
	int course_id;
	int grade_id;	
	int semester_id;
};


int main ()
{
	list<Student> student_list = list<Student>();
	list<Course> course_list = list<Course>();
	list<Grade> grade_list = list<Grade>();
	list<Semester> semester_list = list<Semester>();
	list<Take> take_list = list<Take>();

	//char a[100] = "";
	//char b[100] = "";
	//fgets(a, 100, stdin);

	//char c;
	//while(true) {
	//	scanf("%c", &c);
	//	if( c == '\n' )
	//		break;
	//}

	string param;

	cout << "start program" << endl;
	
	// read student list
	std::ifstream infile("student.txt");	
	while (std::getline(infile, param))
	{
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM)
		{
			ssin >> arr[param_count];
			++param_count;
		}

		Student data;
		data.id = stoi(arr[0]);
		data.last_name = arr[1];
		data.first_name = arr[2];
		data.phone = arr[3];

		student_list.push_back(data);
	}

	// read course list
	std::ifstream infile1("course.txt");	
	while (std::getline(infile1, param))
	{
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM)
		{
			ssin >> arr[param_count];
			++param_count;
		}

		Course data;
		data.id = stoi(arr[0]);
		data.prefix = arr[1];
		data.number = stoi(arr[2]);
		data.title = arr[3];
		data.credit = stoi(arr[4]);

		course_list.push_back(data);
	}

	// read grade list
	std::ifstream infile2("grade.txt");	
	while (std::getline(infile2, param))
	{
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM)
		{
			ssin >> arr[param_count];
			++param_count;
		}

		Grade data;
		data.id = stoi(arr[0]);
		data.type = arr[1];
		data.score = stof(arr[2]);

		grade_list.push_back(data);
	}

	// read semester list
	std::ifstream infile3("semester.txt");	
	while (std::getline(infile3, param))
	{
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM)
		{
			ssin >> arr[param_count];
			++param_count;
		}

		Semester data;
		data.id = stoi(arr[0]);
		data.code = arr[1];
		data.year = stoi(arr[2]);
		data.desc = arr[3];

		semester_list.push_back(data);
	}
	
	// read take list
	std::ifstream infile4("take.txt");	
	while (std::getline(infile4, param))
	{
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM)
		{
			ssin >> arr[param_count];
			++param_count;
		}

		Take data;
		data.student_id = stoi(arr[0]);
		data.course_id = stoi(arr[1]);
		data.grade_id = stoi(arr[2]);
		data.semester_id = stoi(arr[3]);

		take_list.push_back(data);
	}


	while(true)
	{
		// read command line
		getline(cin, param); 
		if( param.compare("q") == 0 )
			break;

		// split command string
		string arr[MAX_PARAM];
		int param_count = 0;
		stringstream ssin(param);
		while (ssin.good() && param_count < MAX_PARAM){
			ssin >> arr[param_count];
			++param_count;
		}

		// check param count
		if( param_count < 1 )
		{
			cout << "Please input correct value" << endl;
			continue;
		}

		if( arr[0].compare("a") == 0 ) // add mode
		{
			if( param_count < 2 )
			{
				cout << "Please input correct value" << endl;
				continue;
			}

			if( arr[1].compare("s") == 0 ) // add student mode
			{	
				// get last id of student
				int last_id = 0;
				if( student_list.size() > 0 )
				{
					Student last = student_list.back();
					last_id = last.id;
				}
				Student data;
				data.id = last_id + 1; // auto increment id
				data.last_name = arr[2];
				data.first_name = arr[3];
				data.phone = arr[4];

				// add student to list
				student_list.push_back(data);

				// save student data to table
				std::ofstream outfile;
				outfile.open("student.txt", std::ios_base::app); // append instead of overwrite
				outfile << data.id << " " << data.last_name << " " << data.first_name << " " << data.phone << endl; 
			}

			if( arr[1].compare("c") == 0 ) // add course mode
			{
				// get last id of course
				int last_id = 0;
				if( course_list.size() > 0 )
				{
					Course last = course_list.back();
					last_id = last.id;
				}

				Course data;
				data.id = last_id + 1; // auto increment id
				data.prefix = arr[2];
				data.number = stoi(arr[3]);
				data.title = arr[4];
				data.credit = stoi(arr[5]);

				// add course to list
				course_list.push_back(data);

				// save course data to table
				std::ofstream outfile;
				outfile.open("course.txt", std::ios_base::app); // append instead of overwrite
				outfile << data.id << " " << data.prefix << " " << data.number << " " << data.title << " " << data.credit << endl; 
			}

			if( arr[1].compare("g") == 0 )
			{
				// get last id of grade
				int last_id = 0;
				if( grade_list.size() > 0 )
				{
					Grade last = grade_list.back();
					last_id = last.id;
				}

				Grade data;
				data.id = last_id + 1; // auto increment id
				data.type = arr[2];
				data.score = stof(arr[3]);
				
				// add grade to list
				grade_list.push_back(data);

				// save grade data to table
				std::ofstream outfile;
				outfile.open("grade.txt", std::ios_base::app); // append instead of overwrite
				outfile << data.id << " " << data.type << " " << data.score << endl; 
			}

			if( arr[1].compare("m") == 0 )
			{
				// get last id of semester
				int last_id = 0;
				if( semester_list.size() > 0 )
				{
					Semester last = semester_list.back();
					last_id = last.id;
				}

				Semester data;
				data.id = last_id + 1; // auto increment id
				data.code = arr[2];
				data.year = stoi(arr[3]);
				data.desc = arr[4];

				// add semester to list
				semester_list.push_back(data);

				// save semster data to table
				std::ofstream outfile;
				outfile.open("semester.txt", std::ios_base::app); // append instead of overwrite
				outfile << data.id << " " << data.code << " " << data.year << " " << data.desc << endl; 
			}

			if( arr[1].compare("t") == 0 )
			{
				// find student id
				int student_id = 0;
				std::list<Student>::iterator it;
				for (it = student_list.begin(); it != student_list.end(); ++it)
				{
					if( it->last_name.compare(arr[2]) == 0 && it->first_name.compare(arr[3]) == 0 )
						student_id = it->id;
				}

				// find course id
				int course_id = 0;
				std::list<Course>::iterator it1;
				for (it1 = course_list.begin(); it1 != course_list.end(); ++it1)
				{
					if( it1->prefix.compare(arr[4]) == 0 && it1->number == stoi(arr[5]) )
						course_id = it1->id;
				}

				// find grade id
				int grade_id = 0;
				std::list<Grade>::iterator it2;
				for (it2 = grade_list.begin(); it2 != grade_list.end(); ++it2)
				{
					if( it2->type.compare(arr[6]) == 0)
						grade_id = it2->id;
				}

				// find semester id
				int semester_id = 0;
				std::list<Semester>::iterator it3;
				for (it3 = semester_list.begin(); it3 != semester_list.end(); ++it3)
				{
					if( it3->code.compare(arr[7]) == 0)
						semester_id = it3->id;
				}

				// add student to list
				Take data;
				data.student_id = student_id;
				data.course_id = course_id;
				data.grade_id = grade_id;
				data.semester_id = semester_id;
			
				take_list.push_back(data);

				// save student data to table
				std::ofstream outfile;
				outfile.open("take.txt", std::ios_base::app); // append instead of overwrite
				outfile << data.student_id << " " << data.course_id << " " << data.grade_id << " " << data.semester_id << endl; 				
			}
		}
		else if( arr[0].compare("l") == 0 )	// list mode
		{
			if( arr[1].compare("c") == 0 ) // course list 
			{
				std::list<Course>::iterator it1;
				for (it1 = course_list.begin(); it1 != course_list.end(); ++it1)
					cout << it1->prefix << " " << it1->number << " " << it1->title << " " << it1->credit << endl;				
			}

			if( arr[1].compare("g") == 0 ) // grade list
			{
				std::list<Grade>::iterator it1;
				for (it1 = grade_list.begin(); it1 != grade_list.end(); ++it1)
					cout << it1->type << " " << it1->score << endl;				
			}

			if( arr[1].compare("m") == 0 ) // semester list
			{
				std::list<Semester>::iterator it1;
				for (it1 = semester_list.begin(); it1 != semester_list.end(); ++it1)
					cout << it1->code << " " << it1->desc << " " << it1->year << endl;				
			}

			if( arr[1].compare("s") == 0 ) // student list
			{
				std::list<Student>::iterator it1;
				for (it1 = student_list.begin(); it1 != student_list.end(); ++it1)
					cout << it1->last_name << " " << it1->first_name << " " << it1->phone << endl;				
			}

			if( arr[1].compare("t") == 0 ) // take course list
			{
				std::list<Take>::iterator it1;
				for (it1 = take_list.begin(); it1 != take_list.end(); ++it1)	// iterate taken course list
				{
					std::list<Student>::iterator it2; // find student by student_id
					for (it2 = student_list.begin(); it2 != student_list.end(); ++it2)
					{
						if( it1->student_id == it2->id )
							cout << it2->last_name << " " << it2->first_name << " ";
					}

					std::list<Semester>::iterator it4; // find semester by semester_id
					for (it4 = semester_list.begin(); it4 != semester_list.end(); ++it4)
					{
						if( it1->semester_id == it4->id )
							cout << it4->code << " ";
					}

					std::list<Course>::iterator it3; // find course by course_id
					for (it3 = course_list.begin(); it3 != course_list.end(); ++it3)
					{
						if( it1->course_id == it3->id )
							cout << it3->prefix << " " << it3->number << " " << it3->title << " ";
					}

					std::list<Grade>::iterator it5; // find grade by grade_id
					for (it5 = grade_list.begin(); it5 != grade_list.end(); ++it5)
					{
						if( it1->grade_id == it5->id )
							cout << it5->type;
					}
					cout << endl;
				}
			}
		}
		else if( arr[0].compare("t") == 0 )
		{
			// find student id
			int student_id = 0;
			std::list<Student>::iterator it;
			for (it = student_list.begin(); it != student_list.end(); ++it)
			{
				if( it->last_name.compare(arr[1]) == 0 && it->first_name.compare(arr[2]) == 0 )
					student_id = it->id;
			}

			if( student_id < 1 )
			{
				cout << "Invalid Student" << endl;
				continue;
			}

			int hours = 0;
			float gpa = 0.0f;

			std::list<Semester>::iterator it3;
			for (it3 = semester_list.begin(); it3 != semester_list.end(); ++it3) // group by semester
			{
				int semester_id = it3->id;

				std::list<Take>::iterator it4;
				int count = 0;

				for (it4 = take_list.begin(); it4 != take_list.end(); ++it4)
				{
					if( it4->student_id != student_id )
						continue;

					if( it4->semester_id != semester_id )
						continue;

					if( count == 0 )
						cout << "=========== Semester: " << it3->desc << " " << it3->year << " ===========" << endl;
					
					// find course id
					std::list<Course>::iterator it1;
					for (it1 = course_list.begin(); it1 != course_list.end(); ++it1)
					{
						if( it1->id == it4->course_id )
						{
							cout << it1->prefix << it1->number << " " << it1->title << "(" << it1->credit << ") ";
							hours += it1->credit;
						}
					}

					// find grade id					
					std::list<Grade>::iterator it2;
					for (it2 = grade_list.begin(); it2 != grade_list.end(); ++it2)
					{
						if( it2->id == it4->grade_id )
						{
							cout << it2->type << endl;
							gpa += it2->score;
						}
					}

					count++;
				}
			}


			cout << "SUTDENT HOURS COMPLETED:" << hours << endl;
			cout << "SUTDENT GPA:" << gpa << endl;
		}
		else
		{
			cout << "Please input a or l or t value" << endl;

		}

	}
	cout << "end program";
}

