#include <iostream>
#include <sstream>
#include "mysql\mysql.h"

#pragma comment (lib,"libmysql.lib")

using namespace std;

#define MAX_PARAM 10

// define mysql connection variabl
MYSQL *conn;	
MYSQL_RES *res;
MYSQL_ROW row;

int main ()
{
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
		if( param_count < 4 )	// if not provide sufficient information about connection
		{
			cout << "Please input correct value" << endl;
			continue;
		}

		hostname = arr[0];
		port = stoi(arr[1]);
		username = arr[2];
		password = "";
		dbname = "";
		if( param_count < 5 ) // empty password
			dbname = arr[3];
		else // non empty password
		{
			password = arr[3];
			dbname = arr[4];
		}

		// connect mysql
		if (!mysql_real_connect(conn, hostname.c_str(), username.c_str(), password.c_str(), "", port, NULL, 0))
		{
			cout << "Can not connect db!!!, Please input again:" << endl;
			continue;
		}

		cout << "db is connected successfully" << endl;
		break;
	}
	
	char query[1000];

	// create database
	sprintf(query, "CREATE DATABASE IF NOT EXISTS %s", dbname.c_str()); 				
	mysql_query(conn, query);

	sprintf(query, "USE %s", dbname.c_str()); 				
	mysql_query(conn, query);

	cout << "db is created successfully" << endl;

	// create tables
	sprintf(query, "CREATE TABLE IF NOT EXISTS `course` ( "
		"`id` int(11) unsigned NOT NULL AUTO_INCREMENT, "
		"`prefix` varchar(20) DEFAULT NULL, "
		"`number` int(11) DEFAULT NULL, "
		"`title` varchar(40) DEFAULT NULL, "
		"`credit` int(10) DEFAULT '0', "
		"PRIMARY KEY (`id`) "
		") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
	mysql_query(conn, query);
	cout << "`course` table is created successfully" << endl;

	sprintf(query, "CREATE TABLE IF NOT EXISTS `grade` ( "
		"`id` int(11) unsigned NOT NULL AUTO_INCREMENT, "
		"`type` varchar(30) DEFAULT NULL, "
		"`score` float DEFAULT '0', "
		"PRIMARY KEY (`id`) "
		") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
	mysql_query(conn, query);
	cout << "`grade` table is created successfully" << endl;

	sprintf(query, "CREATE TABLE IF NOT EXISTS `semester` ( "
		"`id` int(11) unsigned NOT NULL AUTO_INCREMENT, "
		"`code` varchar(20) DEFAULT NULL, "
		"`year` int(11) DEFAULT NULL, "
		"`desc` text, "
		"PRIMARY KEY (`id`) "
		") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
	mysql_query(conn, query);
	cout << "`semester` table is created successfully" << endl;

	sprintf(query, "CREATE TABLE IF NOT EXISTS `student` ( "
		"`id` int(11) unsigned NOT NULL AUTO_INCREMENT, "
		"`last_name` varchar(30) DEFAULT NULL, "
		"`first_name` varchar(30) DEFAULT NULL, "
		"`phone` varchar(30) DEFAULT NULL, "
		"PRIMARY KEY (`id`) "
		") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
	mysql_query(conn, query);
	cout << "`student` is created successfully" << endl;

	sprintf(query, "CREATE TABLE IF NOT EXISTS `take` ( "
		"`id` int(11) unsigned NOT NULL AUTO_INCREMENT, "
		"`student_id` int(11) DEFAULT NULL, "
		"`course_id` int(11) DEFAULT NULL, "
		"`grade_id` int(11) DEFAULT NULL, "
		"`semester_id` int(11) DEFAULT NULL, "
		"PRIMARY KEY (`id`) "
		") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
	mysql_query(conn, query);
	cout << "`take` table is created successfully" << endl;

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

			if( arr[1].compare("g") == 0 ) // add greade mode
			{
				sprintf(query, "INSERT INTO grade (type, score) VALUES ('%s', %f)", arr[2].c_str(), stof(arr[3])); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("m") == 0 )	// add semester
			{
				sprintf(query, "INSERT INTO semester (code, year, `desc`) VALUES ('%s', %d, '%s')", arr[2].c_str(), stoi(arr[3]), arr[4].c_str()); 				
				mysql_query(conn, query);
			}

			if( arr[1].compare("t") == 0 ) // add course taken
			{
				// find student id using last name and first name
				sprintf(query, "SELECT id FROM student WHERE last_name = '%s' AND first_name = '%s' LIMIT 1", arr[2].c_str(), arr[3].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);
				int student_id = 0;
				if (row)
					student_id = atoi(row[0]);
				mysql_free_result(res);		
				
				// find course id using prefix and number				
				sprintf(query, "SELECT id FROM course WHERE prefix = '%s' AND number = %d LIMIT 1", arr[4].c_str(), stoi(arr[5])); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int course_id = 0;
				if (row)
					course_id = atoi(row[0]);
				mysql_free_result(res);

				
				// find grade id using grade type
				sprintf(query, "SELECT id FROM grade WHERE type = '%s' LIMIT 1", arr[6].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int grade_id = 0;
				if (row)
					grade_id = atoi(row[0]);
				mysql_free_result(res);

				// find semester id using code
				sprintf(query, "SELECT id FROM semester WHERE code = '%s' LIMIT 1", arr[7].c_str()); 				
				mysql_query(conn, query);
				res = mysql_use_result(conn);
				row = mysql_fetch_row(res);				
				int semester_id = 0;
				if (row)
					semester_id = atoi(row[0]);
				mysql_free_result(res);

				// insert course taken using ids
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
				sprintf(query, "SELECT a.id, b.last_name, b.first_name, c.code, d.prefix, d.number, d.title, e.type FROM take as a " 
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
		else if( arr[0].compare("d") == 0 ) // course list group by semester
		{
			// delete student for selected last name and first name			
			sprintf(query, "DELETE FROM student "
				"WHERE last_name = '%s' AND first_name = '%s' ", 				
				arr[1].c_str(), arr[2].c_str()
				);

			mysql_query(conn, query);
		}
		else if( arr[0].compare("t") == 0 ) // course list group by semester
		{
			int hours = 0;
			float gpa = 0.0f;

			// find course take list for selected last name and first name
			// and order by semester
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

			// read query ressult one by one
			while((row=mysql_fetch_row(res))!=NULL)
			{
				int course_id = atoi(row[0]);
				if( course_id != prev_id )	// if new semester, print semenster information.
					cout << endl << "=========== Semester: " << row[1] << " " << row[2] << " ===========" << endl;

				// print course information
				cout << row[3] << row[4] << " " << row[5] << "(" << row[6] << ") " << row[7] << endl;

				// calucate hours and gpa
				hours += atoi(row[6]);
				gpa += (float)atof(row[8]);

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

