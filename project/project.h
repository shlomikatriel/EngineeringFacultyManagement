
typedef struct Student
{
	char *first;
	char *last;
	int id;
	int status;
	int grade;
}Student;
typedef struct Course
{
	char *name;
	char *name_lecturer;
	int serial_number;
	int num_students;
	Student *arr;
}Course;
typedef struct Item
{
	Course *course;
	struct Item *next;
	struct Item *prev;
}Item;
typedef struct List
{
	Item *head;
	Item *tail;
}List;
int main_menu();
void add_course(List *L);
void add_student(List L);
Course *find_course(List L);
Student get_student();
void remove_student(List L);
int find_student_ind(Course *c);
void cancel_course(List *L);
void update_status(List L);
void print_courses(List L);
void print_student_by_family(List L);
void print_student_by_grade(List L);
void print_course_serial_max_average_grade(List L);
void print_course_serial_max_pass(List L);
void print_tested_B_students(List L);
void error(int whaterr);
void freeall(List L);