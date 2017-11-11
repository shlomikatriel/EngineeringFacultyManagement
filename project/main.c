#include "project.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define ADD_COURSE 1
#define ADD_STUDENT 2
#define REMOVE_STUDENT 3
#define CANCEL_COURSE 4
#define UPDATE_STATUS 5
#define PRINT_COURSES 6
#define PRINT_STUDENTS_BY_FAMILY 7
#define PRINT_STUDENTS_BY_GRADE 8
#define PRINT_COURSE_SERIAL_MAX_AVERAGE_GRADE 9
#define PRINT_COURSE_SERIAL_MAX_PASS 10
#define PRINT_TESTED_B_STUDENTS 11
#define QUIT 12
#define NO_OPTION 1
void main()
{
	int option, i;
	List L;
	printf("%c", 201);
	for (i = 0; i < 52; i++)
		printf("%c", 205);
	printf("%c\n", 187);
	printf("%c Welcome to Engineering Faculty management software %c\n", 186, 186);
	printf("%c", 200);
	for (i = 0; i < 52; i++)
		printf("%c", 205);
	printf("%c\nBy Shlomi Katriel\n\n", 188);
	L.head = NULL;
	L.tail = NULL;
	option = main_menu();
	while (option != QUIT)
	{
		switch (option)
		{
		case ADD_COURSE:
			printf("Main Menu=>Add empty course\n");
			for (i = 0; i < 27; i++)
				printf("%c", 205);
			printf("\n\n");
			add_course(&L);
			break;
		case ADD_STUDENT:
			printf("Main menu=>Add student to specific course\n");
			for (i = 0; i < 41; i++)
				printf("%c", 205);
			printf("\n\n");
			add_student(L);
			break;
		case REMOVE_STUDENT:
			printf("Main Menu=>Remove student from specific course\n");
			for (i = 0; i < 46; i++)
				printf("%c", 205);
			printf("\n\n");
			remove_student(L);
			break;
		case CANCEL_COURSE:
			printf("Main Menu=>Cancel course\n");
			for (i = 0; i < 24; i++)
				printf("%c", 205);
			printf("\n\n");
			cancel_course(&L);
			break;
		case UPDATE_STATUS:
			printf("Main menu=>Update student status and grade\n");
			for (i = 0; i < 42; i++)
				printf("%c", 205);
			printf("\n\n");
			update_status(L);
			break;
		case PRINT_COURSES:
			printf("Main menu=>Print Courses and serial numbers\n");
			for (i = 0; i < 43; i++)
				printf("%c", 205);
			printf("\n\n");
			print_courses(L);
			break;
		case PRINT_STUDENTS_BY_FAMILY:
			printf("Main menu=>Print student list sorted by family name\n");
			for (i = 0; i < 51; i++)
				printf("%c", 205);
			printf("\n\n");
			print_student_by_family(L);
			break;
		case PRINT_STUDENTS_BY_GRADE:
			printf("Main menu=>Print student list sorted by grade\n");
			for (i = 0; i < 45; i++)
				printf("%c", 205);
			printf("\n\n");
			print_student_by_grade(L);
			break;
		case PRINT_COURSE_SERIAL_MAX_AVERAGE_GRADE:
			printf("Main menu=>Print the serial number of the course with the highest average\n");
			for (i = 0; i < 73; i++)
				printf("%c", 205);
			printf("\n\n");
			print_course_serial_max_average_grade(L);
			break;
		case PRINT_COURSE_SERIAL_MAX_PASS:
			printf("Main menu=>Print the serial number of the course with the most passed grades\n");
			for (i = 0; i < 76; i++)
				printf("%c", 205);
			printf("\n\n");
			print_course_serial_max_pass(L);
			break;
		case PRINT_TESTED_B_STUDENTS:
			printf("Main menu=>Print all students which tested B term\n");
			for (i = 0; i < 49; i++)
				printf("%c", 205);
			printf("\n\n");
			print_tested_B_students(L);
			break;
		default:
			error(NO_OPTION);
		}
		option = main_menu();
	}
	freeall(L);
}