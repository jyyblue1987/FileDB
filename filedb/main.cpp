#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include "mysql\mysql.h"

#pragma comment (lib,"libmysql.lib")

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

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int main ()
{
	list<Student> student_list = list<Student>();
	list<Course> course_list = list<Course>();
	list<Grade> grade_list = list<Grade>();
	list<Semester> semester_list = list<Semester>();
	list<Take> take_list = list<Take>();

	string param;

	cout << "start program" << endl;
	
	// read mysql connection	
	cout << "Please input mysql information hostname, port, username, password, database: " << endl;

	string hostname = "localhost";
	int port = 3306;
	string username = "root";
	string password = "";
	string dbname = "school";
	
	conn = mysql_init(NULL);

	while(true)
	{		
		// read command line
		//getline(cin, param); 
		//if( param.compare("q") == 0 )
		//	break;

		//// split command string
		//string arr[MAX_PARAM];
		//int param_count = 0;
		//stringstream ssin(param);
		//while (ssin.good() && param_count < MAX_PARAM){
		//	ssin >> arr[param_count];
		//	++param_count;
		//}

		//// check param count
		//if( param_count < 4 )
		//{
		//	cout << "Please input correct value" << endl;
		//	continue;
		//}

		//hostname = arr[0];
		//port = stoi(arr[1]);
		//username = arr[2];
		//password = "";
		//dbname = "";
	//	if( param_count < 5 )			
	//		dbname = arr[3];
	//	else
	//	{
	//		password = arr[3];
	//		dbname = arr[4];
	//	}

		if (!mysql_real_connect(conn, hostname.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, NULL, 0))
		{
			cout << "Can not connect db!!!, Please input again:" << endl;
			continue;
		}
		break;
	}
	
	char query[1000];
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
				sprintf(query, "INSERT INTO student (last_name, first_name, phone) VALUES ('%s', '%s', '%s')", arr[2].c_str(), arr[3].c_str(), arr[4].c_str()); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("c") == 0 ) // add course mode
			{
				sprintf(query, "INSERT INTO course (prefix, number, title, credit) VALUES ('%s', %d, '%s', %d)", arr[2].c_str(), stoi(arr[3]), arr[4].c_str(), stoi(arr[5])); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("g") == 0 )
			{
				sprintf(query, "INSERT INTO grade (type, score) VALUES ('%s', %f)", arr[2].c_str(), stof(arr[3])); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("m") == 0 )
			{
				sprintf(query, "INSERT INTO semester (code, year, `desc`) VALUES ('%s', %d, '%s')", arr[2].c_str(), stoi(arr[3]), arr[4].c_str()); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("t") == 0 )
			{
				// find student id
				sprintf(query, "SELECT id FROM student WHERE last_name = '%s' AND first_name = '%s' LIMIT 1", arr[2].c_str(), arr[3].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);
				int student_id = 0;
				if (row)
					student_id = atoi(row[0]);
				mysql_free_result(res);		
				
				// find course id				
				sprintf(query, "SELECT id FROM course WHERE prefix = '%s' AND number = %d LIMIT 1", arr[4].c_str(), stoi(arr[5])); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int course_id = 0;
				if (row)
					course_id = atoi(row[0]);
				mysql_free_result(res);

				
				// find grade id
				sprintf(query, "SELECT id FROM grade WHERE type = '%s' LIMIT 1", arr[6].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int grade_id = 0;
				if (row)
					grade_id = atoi(row[0]);
				mysql_free_result(res);

				// find semester id
				sprintf(query, "SELECT id FROM semester WHERE code = '%s' LIMIT 1", arr[7].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int semester_id = 0;
				if (row)
					semester_id = atoi(row[0]);
				mysql_free_result(res);

				sprintf(query, "INSERT INTO take (student_id, course_id, grade_id, semester_id) VALUES (%d, %d, %d, %d)", student_id, course_id, grade_id, semester_id); 				
				mysql_query(conn, query);
			}
		}
		else if( arr[0].compare("l") == 0 )	// list mode
		{
			if( arr[1].compare("c") == 0 ) // course list 
			{
				sprintf(query, "SELECT * FROM course"); 	
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				
				while((row=mysql_fetch_row(res))!=NULL)
					cout << row[1] << " " << row[2] << " " << row[3] << " " << row[4] << endl;				
				
				mysql_free_result(res);
			}

			if( arr[1].compare("g") == 0 ) // grade list
			{
				sprintf(query, "SELECT * FROM grade"); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);

				while((row=mysql_fetch_row(res))!=NULL)
					cout << row[1] << " " << row[2] << endl;				
				
				mysql_free_result(res);
			}

			if( arr[1].compare("m") == 0 ) // semester list
			{
				sprintf(query, "SELECT * FROM semester"); 	
				mysql_query(conn, query);
				res = mysql_use_result(conn);

				while((row=mysql_fetch_row(res))!=NULL)
					cout << row[1] << " " << row[2] << " " << row[3] << endl;				
				
				mysql_free_result(res);
			}

			if( arr[1].compare("s") == 0 ) // student list
			{
				sprintf(query, "SELECT * FROM student"); 
				mysql_query(conn, query);
				res = mysql_use_result(conn);

				while((row=mysql_fetch_row(res))!=NULL)
					cout << row[1] << " " << row[2] << " " << row[3] << endl;				

				mysql_free_result(res);
			}

			if( arr[1].compare("t") == 0 ) // take course list
			{
				sprintf(query, "SELECT b.last_name, b.first_name, c.code, d.prefix, d.number, d.title, e.type FROM take as a " 
									"JOIN student as b ON a.student_id = b.id "  
									"JOIN semester as c ON a.semester_id = c.id "  
									"JOIN course as d ON a.course_id = d.id "  
									"JOIN grade as e ON a.grade_id = e.id "
									); 
				mysql_query(conn, query);
				res = mysql_use_result(conn);

				while((row=mysql_fetch_row(res))!=NULL)
					cout << row[1] << " " << row[2] << " " << row[3] << " " << row[4] << " " << row[5] << " " << row[6] << " " << row[7] << endl;				

				mysql_free_result(res);
			}
		}
		else if( arr[0].compare("t") == 0 )
		{
			int hours = 0;
			float gpa = 0.0f;

			sprintf(query, "SELECT c.id, c.desc, c.year, d.prefix, d.number, d.title, d.credit, e.type, e.score FROM take as a " 
				"JOIN student as b ON a.student_id = b.id "  
				"JOIN semester as c ON a.semester_id = c.id "  
				"JOIN course as d ON a.course_id = d.id "  
				"JOIN grade as e ON a.grade_id = e.id " 
				"WHERE b.last_name = '%s' AND b.first_name = '%s' " 
				"ORDER BY c.id ", 
				arr[1].c_str(), arr[2].c_str()
				); 

			mysql_query(conn, query);
			res = mysql_use_result(conn);

			int prev_id = -1;

			while((row=mysql_fetch_row(res))!=NULL)
			{
				int course_id = atoi(row[0]);
				if( course_id != prev_id )
					cout << endl << "=========== Semester: " << row[1] << " " << row[2] << " ===========" << endl;

				cout << row[3] << row[4] << " " << row[5] << "(" << row[6] << ") " << row[7] << endl;

				hours += atoi(row[6]);
				gpa += atof(row[8]);

				prev_id = course_id;
			}
			mysql_free_result(res);
			
			cout << "SUTDENT HOURS COMPLETED:" << hours << endl;
			cout << "SUTDENT GPA:" << gpa << endl;
		}
		else
		{
			cout << "Please input a or l or t value" << endl;
		}

	}

	mysql_close(conn);

	cout << "end program";
}

