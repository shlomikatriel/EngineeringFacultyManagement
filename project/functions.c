#include "project.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX_LENGTH 100
#define NOT_TESTED 1
#define TESTED_A 2
#define TESTED_B 3
#define BREAK 0
#define CONTINUE 1
#define NO_OPTION 1
#define NO_EMPTY_COURSE 2
#define NO_COURSES_LISTED 3
#define NO_STUDENTS_LISTED 4
#define NO_ROOM_IN_COURSE 5
#define WRONG_SERIAL 6
#define NO_STUDENTS_LISTED_IN_COURSE 7
#define WRONG_ID 8
#define CANT_CHANGE_STATUS_A 9
#define CANT_CHANGE_STATUS_B 10
#define NO_ROOM_IN_COURSES 11
#define NO_STUDENTS_PASSED 12
#define NO_STUDENTS_TESTED 13
int main_menu()
{
	int option = 0, i;
	printf("Main Menu\n");
	for (i = 0; i < 9; i++)
		printf("%c", 205);
	printf("\nWhat would you like to do?\n\n1 - Add empty course.\n2 - Add student to specific course.\n");
	printf("3 - Remove student from specific Course.\n4 - Cancel course.\n5 - Update student's status and grade.\n");
	printf("6 - Print the list of courses ans serial numbers.\n7 - Print student list of specific course sorted by family name.\n");
	printf("8 - Print student list of specific course sorted by grades.\n9 - Print serial number of the course with the highest average grade.\n");
	printf("10 - Print serial number of the course with the most passed grades.\n");
	printf("11 - Print all students that made the term B test.\n12 - Quit.\n");
	scanf("%d", &option);
	return option;
}
void add_course(List *L)
{
	int i;
	Course *c;
	char name[MAX_LENGTH], lecturer[MAX_LENGTH];
	c = (Course *)malloc(sizeof(Course));
	printf("Please enter the name of the course:");
	flushall();
	gets(name);
	c->name = (char *)malloc(sizeof(char)*(strlen(name) + 1));
	strcpy(c->name, name);
	printf("Please enter the name of the lecturer:");
	flushall();
	gets(lecturer);
	c->name_lecturer = (char *)malloc(sizeof(char)*(strlen(lecturer) + 1));
	strcpy(c->name_lecturer, lecturer);
	printf("Please enter the course's serial number:");
	scanf("%d", &c->serial_number);
	do
	{
		printf("Please insert the student capacity:");
		scanf("%d", &c->num_students);
		if (c->num_students <= 0)
			error(NO_EMPTY_COURSE);
	} while (c->num_students <= 0);
	c->arr = (Student *)malloc(sizeof(Student)*c->num_students);
	for (i = 0; i < c->num_students; i++)
	{
		c->arr[i].first = NULL;
		c->arr[i].last = NULL;
		c->arr[i].grade = 0;
		c->arr[i].id = 0;
		c->arr[i].status=0;
	}
	if (L->head == NULL)
	{
		L->head = (Item *)malloc(sizeof(Item));
		L->head->course = c;
		L->head->next = NULL;
		L->head->prev = NULL;
		L->tail = L->head;
	}
	else
	{
		L->tail->next = (Item *)malloc(sizeof(Item));
		L->tail->next->prev = L->tail;
		L->tail = L->tail->next;
		L->tail->next = NULL;
		L->tail->course = c;
	}
	printf("\nCourse Added.\n\n");
}
void add_student(List L)
{
	int i, count, flag = BREAK;
	Item *p;
	Course *c;
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0, count = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
			count++;
		if (count < p->course->num_students)
		{
			flag = CONTINUE;
			break;
		}
	}
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (flag == BREAK)
	{
		error(NO_ROOM_IN_COURSES);
		return;
	}
	do
	{
		c = find_course(L);
		for (i = 0, count = 0; c->arr[i].first != NULL&&i < c->num_students; i++)
			count++;
		if (count == c->num_students)
			error(NO_ROOM_IN_COURSE);
	} while (count == c->num_students);
	for (i = 0; c->arr[i].first != NULL; i++);
	c->arr[i] = get_student();
	printf("\nStudent Added.\n\n");
}
Course *find_course(List L)
{
	int ser;
	Item *p;
	do
	{
		print_courses(L);
		printf("Please insert the serial number of the requested course:\n");
		scanf("%d", &ser);
		for (p = L.head; p != NULL; p = p->next)
			if (p->course->serial_number == ser)
				break;
		if (p == NULL)
			error(WRONG_SERIAL);
	} while (p == NULL);
	return p->course;
}
Student get_student()
{
	Student s;
	char first_tmp[MAX_LENGTH], last_tmp[MAX_LENGTH];
	printf("Please insert first name:");
	flushall();
	gets(first_tmp);
	s.first = (char *)malloc(sizeof(char)*(strlen(first_tmp) + 1));
	strcpy(s.first, first_tmp);
	printf("Please insert last name:");
	flushall();
	gets(last_tmp);
	s.last = (char *)malloc(sizeof(char)*(strlen(last_tmp) + 1));
	strcpy(s.last, last_tmp);
	printf("Please insert ID:");
	scanf("%d", &s.id);
	s.grade = 260;
	s.status = NOT_TESTED;
	return s;
}
void remove_student(List L)
{
	int flag = BREAK, ind, i;
	Item *p;
	Course *c;
	for (p = L.head; p != NULL; p = p->next)
	{
		if (p->course->arr[0].first != NULL)
		{
			flag = CONTINUE;
			break;
		}
	}
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (flag == BREAK)
	{
		error(NO_STUDENTS_LISTED);
		return;
	}
	do
	{
		c = find_course(L);
		if (c->arr[0].first == NULL)
			error(NO_STUDENTS_LISTED_IN_COURSE);
	} while (c->arr[0].first == NULL);
	ind = find_student_ind(c);
	free(c->arr[ind].first);
	free(c->arr[ind].last);
	for (i = ind; i + 1 < c->num_students; i++)
		c->arr[i] = c->arr[i + 1];
	if (c->arr[c->num_students - 1].first != NULL)
	{
		c->arr[c->num_students - 1].first = NULL;
		c->arr[c->num_students - 1].last = NULL;
		c->arr[c->num_students - 1].grade = 0;
		c->arr[c->num_students - 1].id = 0;
		c->arr[c->num_students - 1].status = 0;
	}
	printf("\nStudent Removed.\n\n");
}
int find_student_ind(Course *c)
{
	int i, id;
	do
	{
		for (i = 0; c->arr[i].first != NULL && i < c->num_students; i++)
			printf("%s %s - %d\n", c->arr[i].first, c->arr[i].last, c->arr[i].id);
		printf("Please enter the requested student's ID:");
		scanf("%d", &id);
		for (i = 0; c->arr[i].first != NULL; i++)
			if (c->arr[i].id == id)
				break;
		if (c->arr[i].first == NULL)
			error(WRONG_ID);
	} while (c->arr[i].first == NULL);
	return i;
}
void cancel_course(List *L)
{
	int i;
	Course *c;
	Item *p, *p_prev, *p_next;
	if (L->head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	c = find_course(*L);
	for (p = L->head; p->course != c; p = p->next);
	for (i = 0; i < c->num_students&&c->arr[i].first != NULL; i++)
	{
		free(c->arr[i].first);
		free(c->arr[i].last);
	}
	free(c->arr);
	free(c->name);
	free(c->name_lecturer);
	free(c);
	if (L->head == L->tail)
	{
		free(L->head);
		L->head = NULL;
		L->tail = NULL;
	}
	else if (p == L->tail)
	{
		p = p->prev;
		free(p->next);
		p->next = NULL;
		L->tail = p;
	}
	else if (p == L->head)
	{
		p = p->next;
		free(p->prev);
		p->prev = NULL;
		L->head = p;
	}
	else
	{
		p_next = p->next;
		p_prev = p->prev;
		free(p_prev->next);
		p_prev->next = p_next;
		p_next->prev = p_prev;
	}
}
void update_status(List L)
{
	int index, flag = BREAK, new_status;
	Course *c;
	Item *p;
	for (p = L.head; p != NULL; p = p->next)
	{
		if (p->course->arr[0].first != NULL)
		{
			flag = CONTINUE;
			break;
		}
	}
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (flag == BREAK)
	{
		error(NO_STUDENTS_LISTED);
		return;
	}
	do
	{
		c = find_course(L);
		if (c->arr[0].first == NULL)
			error(NO_STUDENTS_LISTED_IN_COURSE);
	} while (c->arr[0].first == NULL);
	index = find_student_ind(c);
	printf("\n%s %s:\nGrade - %d.\nCurrent status - ", c->arr[index].first, c->arr[index].last, c->arr[index].grade);
	switch (c->arr[index].status)
	{
	case NOT_TESTED:
		printf("Not tested.\n\n");
		break;
	case TESTED_A:
		printf("Tested A term.\n\n");
		break;
	case TESTED_B:
		printf("Tested B term.\n\n");
	}
	do
	{
		printf("Please choose the new status:\n1.Tested A term.\n2.Tested B term.\n");
		scanf("%d", &new_status);
		new_status++;//to fit with the constant value
		if (new_status == TESTED_A&&c->arr[index].status == TESTED_B)
			error(CANT_CHANGE_STATUS_A);
		else if (new_status == TESTED_B&&c->arr[index].status == NOT_TESTED)
			error(CANT_CHANGE_STATUS_B);
	} while (new_status == TESTED_A&&c->arr[index].status == TESTED_B || new_status == TESTED_B&&c->arr[index].status == NOT_TESTED);
	c->arr[index].status = new_status;
	printf("Please enter the new grade:");
	scanf("%d", &c->arr[index].grade);
	printf("\nStatus updated.\n\n");
}
void print_courses(List L)
{
	Item *p;
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	for (p = L.head; p != NULL; p = p->next)
		printf("%s - %d\n", p->course->name, p->course->serial_number);
	printf("\n");
	
}
void print_student_by_family(List L)
{
	Course *c;
	int i, j, count;
	Item *p;
	Student *tmp_arr, stmp;
	for (p = L.head; p != NULL; p = p->next)
		if (p->course->arr[0].first!=NULL)
			break;
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (p == NULL)
	{
		error(NO_STUDENTS_LISTED);
		return;
	}
	do
	{
		c = find_course(L);
		if (c->arr[0].first == NULL)
			error(NO_STUDENTS_LISTED_IN_COURSE);
	} while (c->arr[0].first == NULL);
	for (i = 0, count = 0; c->arr[i].first != NULL&&i < c->num_students; i++)
		count++;
	tmp_arr = (Student *)malloc(sizeof(Student)*count);
	for (i = 0; i < count; i++)
		tmp_arr[i] = c->arr[i];
	for (j = count - 1; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (strcmp(tmp_arr[i].last, tmp_arr[i + 1].last) == 1)
			{
				stmp = tmp_arr[i];
				tmp_arr[i] = tmp_arr[i + 1];
				tmp_arr[i + 1] = stmp;
			}
		}
	}
	for (i = 0; i < count; i++)
	{
		printf("Name: %s %s - Grade: %d - ID: %d - Status: ", tmp_arr[i].last, tmp_arr[i].first, tmp_arr[i].grade, tmp_arr[i].id);
		if (tmp_arr[i].status == NOT_TESTED)
			printf("Not tested.\n");
		else if (tmp_arr[i].status == TESTED_A)
			printf("Tested A term.\n");
		else
			printf("Tested B term.\n");
	}
	free(tmp_arr);
	printf("\n\n");
}
void print_student_by_grade(List L)
{
	Course *c;
	int i, j, count;
	Item *p;
	Student *tmp_arr, stmp;
	for (p = L.head; p != NULL; p = p->next)
		if (p->course->arr[0].first != NULL)
			break;
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (p == NULL)
	{
		error(NO_STUDENTS_LISTED);
		return;
	}
	do
	{
		c = find_course(L);
		if (c->arr[0].first == NULL)
			error(NO_STUDENTS_LISTED_IN_COURSE);
	} while (c->arr[0].first == NULL);
	for (i = 0, count = 0; c->arr[i].first != NULL&&i < c->num_students; i++)
		count++;
	tmp_arr = (Student *)malloc(sizeof(Student)*count);
	for (i = 0; i < count; i++)
		tmp_arr[i] = c->arr[i];
	for (j = count - 1; j > 0; j--)
	{
		for (i = 0; i < j; i++)
		{
			if (tmp_arr[i].grade > tmp_arr[i + 1].grade)
			{
				stmp = tmp_arr[i];
				tmp_arr[i] = tmp_arr[i + 1];
				tmp_arr[i + 1] = stmp;
			}
		}
	}
	for (i = 0; i < count; i++)
	{
		printf("Grade: %d - Name: %s %s - ID: %d - Status: ", tmp_arr[i].grade, tmp_arr[i].last, tmp_arr[i].first, tmp_arr[i].id);
		if (tmp_arr[i].status == NOT_TESTED)
			printf("Not tested.\n");
		else if (tmp_arr[i].status == TESTED_A)
			printf("Tested A term.\n");
		else
			printf("Tested B term.\n");
	}
	free(tmp_arr);
	printf("\n\n");
}
void print_course_serial_max_average_grade(List L)
{
	float max_average = 0, average;
	int sum, i, max_serial, flag = BREAK, count;
	Item *p;
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
		{
			if (p->course->arr[i].status != NOT_TESTED)
			{
				flag = CONTINUE;
				break;
			}
		}
		if (flag == CONTINUE)
			break;
	}
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (flag == BREAK)
	{
		error(NO_STUDENTS_TESTED);
		return;
	}
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0, sum = 0, count = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
		{
			if (p->course->arr[i].status != NOT_TESTED)
			{
				sum += p->course->arr[i].grade;
				count++;
			}

		}
		average = (float)sum / (float)count;
		if (average>max_average)
		{
			max_average = average;
			max_serial = p->course->serial_number;
		}
	}
	printf("The serial number of the course with the highest average grade is: %d.\n\n", max_serial);
}
void print_course_serial_max_pass(List L)
{
	int i, max_pass = 0, pass, max_serial, flag = BREAK;
	Item *p;
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
		{
			if (p->course->arr[i].grade >= 60 && p->course->arr[i].status != NOT_TESTED)
			{
				flag = CONTINUE;
				break;
			}
		}
		if (flag == CONTINUE)
			break;
	}
	if (L.head == NULL)
	{
		error(NO_COURSES_LISTED);
		return;
	}
	if (flag == BREAK)
	{
		error(NO_STUDENTS_PASSED);
		return;
	}
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0, pass = 0; i < p->course->num_students&&p->course->arr[0].first != NULL; i++)
			if (p->course->arr[i].grade >= 60 && p->course->arr[i].status != NOT_TESTED)
				pass++;
		if (max_pass < pass)
		{
			max_pass = pass;
			max_serial = p->course->serial_number;
		}
	}
	printf("The serial number of the course with the most passed grade is: %d.\n\n", max_serial);
}
void print_tested_B_students(List L)
{
	int i, count;
	Item *p;
	if (L.head == NULL)
		return;
	for (p = L.head; p != NULL; p = p->next)
	{
		printf("Students in course '%s' which tested the B term:\n", p->course->name);
		for (i = 0, count = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
		{
			if (p->course->arr[i].status == TESTED_B)
			{
				printf("	%s %s - ID: %d - Grade: %d\n", p->course->arr[i].first, p->course->arr[i].last, p->course->arr[i].id, p->course->arr[i].grade);
				count++;
			}
			if (count == 0)
				printf("	There are no students in this course which testes B term.\n");
		}
	}
}
void error(int whaterr)
{
	switch (whaterr)
	{
	case NO_OPTION:
		printf("Invalid choice, number must be between 1 to 12, please try again.\n");
		break;
	case NO_EMPTY_COURSE:
		printf("Student capacity must be more then 0.\n");
		break;
	case NO_COURSES_LISTED:
		printf("There are no courses listed at all.\n\n");
		break;
	case NO_STUDENTS_LISTED:
		printf("There are no students listed at all.\n\n");
		break;
	case NO_ROOM_IN_COURSE:
		printf("There is no room for new student in the selected course.\n");
		break;
	case WRONG_SERIAL:
		printf("Serial doesn't exist, please insert correct serial.\n");
		break;
	case NO_STUDENTS_LISTED_IN_COURSE:
		printf("The selected course has no students listed, please try again.\n");
		break;
	case WRONG_ID:
		printf("The student with the id entered is not listed in this course.\n");
		break;
	case CANT_CHANGE_STATUS_A:
		printf("Student tested B term, can't update to A term, please try again.\n");
		break;
	case CANT_CHANGE_STATUS_B:
		printf("Student is not tested, can't update to B term, please try again.\n");
		break;
	case NO_ROOM_IN_COURSES:
		printf("There is no room for new students in the available courses.\n\n");
		break;
	case NO_STUDENTS_TESTED:
		printf("There are no students,in the available courses, that tested A or B term.\n\n");
		break;
	case NO_STUDENTS_PASSED:
		printf("There are no students with passed grade in the available courses.\n\n");
		break;
	}
}
void freeall(List L)
{
	Item *p;
	int i;
	for (p = L.head; p != NULL; p = p->next)
	{
		for (i = 0; i < p->course->num_students&&p->course->arr[i].first != NULL; i++)
		{
			free(p->course->arr[i].first);
			free(p->course->arr[i].last);
		}
		free(p->course->name);
		free(p->course->name_lecturer);
		free(p->course->arr);
		free(p->course);
	}
	if (L.head != NULL)
	{
		while (L.head != L.tail)
		{
			L.head = L.head->next;
			free(L.head->prev);
		}
		free(L.head);
	}
}