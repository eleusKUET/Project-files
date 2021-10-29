/*
author: Eleus Ahammad
roll : 1907005

admin username:admin
admin password:1234
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <conio.h>
#define N 1005 ///Maximum string length

int fileopen(char *path, char *name, char *info, char *mode); ///it opens a file, writes or appends some information.
int retrive(char *path, char *name, char *data); /// retrieve information from e file.
void _delete(char *path);

typedef struct student ///student structure
{
    char roll[N];
    char name[N];
    char phone_number[N];
    char address[N];
    char password[N];
} student;

void student_input(student *stud); ///input student information
void student_output(student *stud); ///output student information
void student_create(student *stud); ///create student account with default password 1234
void student_update(student *stud); /// update student account
void student_removeAccount(student *stud); /// remove student account
void student_fetchInfo(char *roll, student *stud); ///fetching student information from a file

typedef struct teacher ///teacher structure
{
    char name[N];
    char phone_number[N];
    char password[N];
} teacher;

void teacher_input(teacher *tutor); ///input teacher information
void teacher_output(teacher *tutor); ///output teacher information
void teacher_create(teacher *tutor); ///create teacher account with default password 1234
void teacher_update(teacher *tutor); ///update teacher account
void teacher_removeAccount(teacher *tutor); ///delete teacher account
void teacher_fetchInfo(teacher *tutor); ///fetching teacher information from a file and retrieve it to a teacher structure
void teacher_countOfStudent(); ///count how many students are there
void teacher_findByName(char *_name); ///Find all the students information with the given first name
student teacher_findByRoll(char *roll); ///Find a student by the given roll number.

typedef struct classTest ///Class test structure
{
    char course[N]; ///class test for a given course
} classTest;

void classTest_input(classTest *test); ///input the specific course
int classTest_valid_teacher(classTest *ass_course, classTest *test); ///check the teacher is valid to assign marks for a specific course
void classTest_setIndividualMark(char *roll, classTest *test); ///Helper function to give mark to a specific student
void classTest_provideMark(classTest *test);  ///with this function teacher can provide mark to all students for the assigned course of the teacher
void classTest_update(classTest *test); ///update mark of a student with his/her roll number
void classTest_myClassTestMark(char *roll); ///a student can find his/her all class test mark by this function

typedef struct log_in  ///log in structure
{
    char name[N];
    char roll[N];
    char password[N];
} log_in;

int student_log_in(log_in *person); ///student log in
int teacher_log_in(log_in *person); ///teacher log in
int admin_log_in(log_in *person); ///admin log in

typedef struct courseManager ///course structure for assigning courses to teachers
{
    char course_name[N];
} courseManager;

void assign_course(courseManager *man); ///assign courses to the teachers
void update_course(courseManager *man); ///update their courses

void adminPanel(); /// admin panel
void studentPanel(char *roll); ///student panel
void teacherPanel(char *name); ///teacher panel

int main()
{
    while (1) {
        //system("cls");
        puts("KUET Management system by 1907005");
        puts("Enter:");
        puts("1 to log in as an admin.");
        puts("2 to log in as a teacher.");
        puts("3 to log in as a student.");
        puts("Any key to quit");

        char regulation[N];
        gets(regulation);
        system("cls");

        switch (atoi(regulation)) {
            case 1:
            {
                log_in person;
                if (adminLogIn(&person)) {
                    adminPanel();
                }
                break;
            }
            case 2:
            {
                log_in person;
                if (teacherLogIn(&person)) {
                    teacherPanel(person.name);
                }
                break;
            }
            case 3:
            {
                log_in person;
                if (studentLogIn(&person)) {
                    studentPanel(person.roll);
                }
                break;
            }
            default:
            {
                return 0;
                break;
            }
        }
        //sleep(1);
    }
}

void student_input(student *stud)
{
    puts("student roll:");
    gets(stud->roll);
    puts("name:");
    gets(stud->name);
    puts("phone_number:");
    gets(stud->phone_number);

    puts("address:");
    gets(stud->address);
}

void student_output(student *stud)
{
    puts("student information:");
    printf("name        : %s\n", stud->name);
    printf("roll        : %s\n", stud->roll);
    printf("phone number: %s\n", stud->phone_number);
    printf("address     : %s\n", stud->address);
}

void student_create(student *stud)
{
    strcpy(stud->password, "1234");

    char path[N];
    strcpy(path, "students/");
    strcat(path, stud->roll);

    int cnt = 0;

    cnt += fileopen(path, "roll.txt", stud->roll, "w");
    cnt += fileopen(path, "name.txt", stud->name, "w");
    cnt += fileopen(path, "address.txt", stud->address, "w");
    cnt += fileopen(path, "phone_number.txt", stud->phone_number, "w");
    cnt += fileopen(path, "password.txt", stud->password, "w");

    if (cnt == 5) {
        puts("student account created.");
        puts("default password: 1234");
    }
    else {
        puts("account creation malfunctioned.");
    }
}

void student_update(student *stud)
{
    char path[N];
    strcpy(path, "students/");
    strcat(path, stud->roll);

    DIR *dir;
    dir = opendir(path);
    if (!dir) {
        printf("No account found for %s.\n", stud->roll);
        return;
    }
    else {
        closedir(dir);
    }
    puts("Update Key: name, address, phone_number, password");

    char key[N];
    gets(key);
    printf("%s:\n", key);
    strcat(key, ".txt");

    char info[N];
    gets(info);

    if (fileopen(path, key, info, "w")) puts("Updated successfully.");
}

void student_removeAccount(student *stud)
{
    char path[N];
    strcpy(path, "students/");
    strcat(path, stud->roll);
    _delete(path);
    puts("Deletion successful if no error is shown.");
}

void student_fetchInfo(char *roll, student *stud)
{
    char path[N];
    strcpy(path, "students/");
    strcat(path, stud->roll);

    DIR *dir;
    dir = opendir(path);
    if (!dir) {
            printf("%s is not found.\n", stud->roll);
            return;
    }
    else closedir(dir);

    retrive(path, "roll.txt", stud->roll);
    retrive(path, "name.txt", stud->name);
    retrive(path, "address.txt", stud->address);
    retrive(path, "phone_number.txt", stud->phone_number);
    retrive(path, "password.txt", stud->password);
}

void teacher_input(teacher *tutor)
{
    puts("name:");
    gets(tutor->name);

    puts("phone_number:");
    gets(tutor->phone_number);
}

void teacher_output(teacher *tutor)
{
    puts("teacher information:");
    printf("name        : %s\n", tutor->name);
    printf("phone_number: %s\n", tutor->phone_number);
}

void teacher_create(teacher *tutor)
{
    strcpy(tutor->password, "1234");

    char path[N];
    strcpy(path, "teachers/");
    strcat(path, tutor->name);

    int cnt = 0;

    cnt += fileopen(path, "name.txt", tutor->name, "w");
    cnt += fileopen(path, "phone_number.txt", tutor->phone_number, "w");
    cnt += fileopen(path, "password.txt", tutor->password, "w");

    if (cnt == 3) {
        puts("teacher account created.");
        puts("default password: 1234");
    }
    else {
        puts("account creation malfunctioned.");
    }
}

void teacher_update(teacher *tutor)
{
    char path[N];
    strcpy(path, "teachers/");
    strcat(path, tutor->name);

    DIR *dir;
    dir = opendir(path);
    if (!dir) {
        printf("No account found for %s.\n", tutor->name);
        return;
    }
    else {
        closedir(dir);
    }

    puts("Update Key: phone_number, password");

    char key[N];
    gets(key);
    printf("%s:\n", key);
    strcat(key, ".txt");

    char info[N];
    gets(info);

    if (fileopen(path, key, info, "w")) puts("Updated successfully.");
}

void teacher_removeAccount(teacher *tutor)
{
    char path[N];
    strcpy(path, "teachers/");
    strcat(path, tutor->name);
    _delete(path);
}

void teacher_fetchInfo(teacher *tutor)
{
    char path[N];
    strcpy(path, "teachers/");
    strcat(path, tutor->name);

    DIR *dir;
    dir = opendir(path);
    if (!dir) {
        printf("%s is not found.\n", tutor->name);
        return;
    }
    else closedir(dir);

    retrive(path, "name.txt", tutor->name);
    retrive(path, "phone_number.txt", tutor->phone_number);
    retrive(path, "password.txt", tutor->password);
}

void teacher_countOfStudent()
{
    DIR *dir;
    dir = opendir("students");
    if (dir == NULL) {
        puts("0 students.");
        return;
    }
    struct dirent *stud;
    int cnt = 0;
    while ((stud = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; stud->d_name[i]; i++) {
            if (stud->d_name[i] != '.') all_dot = 0;
        }
        cnt += !all_dot;
    }
    printf("%d students.\n", cnt);
}

void teacher_findByName(char *_name)
{
    student target;
    DIR *dir;
    dir = opendir("students");
    if (dir == NULL) {
        puts("student not found.");
        strcpy(target.name, "NULL");
        return;
    }
    struct dirent *stud;

    int matched = 0;

    while ((stud = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; stud->d_name[i]; i++) {
            if (stud->d_name[i] != '.') all_dot = 0;
        }
        if (all_dot) continue;

        char path[N];
        strcpy(path, "students/");
        strcat(path, stud->d_name);

        memset(target.name, 0, sizeof target.name);
        retrive(path, "name.txt", target.name);

        int space = 0;
        for (i = 0; target.name[i]; i++) {
            if (target.name[i] == ' ') space = 1;
            if (space) target.name[i] = '\0';
        }

        if (strcmp(target.name, _name) == 0) {
            retrive(path, "name.txt", target.name);
            retrive(path, "roll.txt", target.roll);
            retrive(path, "address.txt", target.address);
            retrive(path, "phone_number.txt", target.phone_number);
            retrive(path, "password.txt", target.password);
            matched = 1;
            student_output(&target);
        }
    }
    if (!matched) puts("student not found.\n");
}

student teacher_findByRoll(char *roll)
{
    student target;
    DIR *dir;
    dir = opendir("students");
    if (dir == NULL) {
        strcpy(target.name, "NULL");
        return target;
    }
    struct dirent *stud;

    while ((stud = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; stud->d_name[i]; i++) {
            if (stud->d_name[i] != '.') all_dot = 0;
        }
        if (all_dot) continue;

        char path[N];
        strcpy(path, "students/");
        strcat(path, stud->d_name);

        if (strcmp(stud->d_name, roll) == 0) {
            retrive(path, "name.txt", target.name);
            retrive(path, "roll.txt", target.roll);
            retrive(path, "address.txt", target.address);
            retrive(path, "phone_number.txt", target.phone_number);
            retrive(path, "password.txt", target.password);
            return target;
        }
    }
    strcpy(target.name, "NULL");
    return target;
}

void classTest_input(classTest *test)
{
    puts("course:");
    gets(test->course);
}

int classTest_validTeacher(char *ass_course,classTest *test)
{
    return (strcmp(test->course, ass_course) == 0);
}

void classTest_setIndividualMark(char *roll, classTest *test)
{
    char path[N];
    strcpy(path, "students/");
    strcat(path, roll);
    strcat(path, "/");
    strcat(path, "result");

    char tmp[N];
    strcpy(tmp, test->course);
    strcat(test->course, ".txt");

    char mark[N];
    printf("mark for roll %s:\n", roll);
    gets(mark);

    if (fileopen(path, test->course, mark, "w")) printf("mark assigned for roll %s.\n", roll);
    strcpy(test->course, tmp);
}

void classTest_provideMark(classTest *test)
{
    DIR *dir;
    dir = opendir("students");
    if (dir == NULL) {
        puts("student not found.");
        return;
    }
    struct dirent *stud;

    while ((stud = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; stud->d_name[i]; i++) {
            if (stud->d_name[i] != '.') all_dot = 0;
        }
        if (all_dot) continue;
        classTest_setIndividualMark(stud->d_name, test);
    }
}

void classTest_update(classTest *test)
{
    char roll[N];
    puts("roll:");
    gets(roll);

    classTest_setIndividualMark(roll, test);
}

void classTest_myclassTestMark(char *roll)
{
    char path[N];
    strcpy(path, "students/");
    strcat(path, roll);
    strcat(path, "/");
    strcat(path, "result");

    DIR *dir;
    dir = opendir(path);
    if (dir == NULL) {
        printf("No result found for %s.\n", roll);
        return;
    }

    printf("result for roll %s:\n", roll);
    int not_found = 1;
    struct dirent *stud;

    while ((stud = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; stud->d_name[i]; i++) {
            if (stud->d_name[i] != '.') all_dot = 0;
        }
        if (all_dot) continue;

        char mark[N];

        retrive(path, stud->d_name, mark);
        char *name = strtok(stud->d_name, ".");
        printf("%s: %s\n", name, mark);
        not_found = 0;
    }
    if (not_found) printf("no result for roll %s.\n", roll);
}

int studentLogIn(log_in *person)
{
    puts("roll:");
    gets(person->roll);

    puts("password:");
    gets(person->password);

    teacher tutor;
    student stud = teacher_findByRoll(person->roll);

    if (strcmp(stud.name, "NULL") == 0) {
        puts("roll number is incorrect.");
        return 0;
    }
    else if (strcmp(stud.password, person->password) != 0) {
        puts("password is incorrect.");
        return 0;
    }
    else {
        puts("Log in successful.");
        return 1;
    }
}

int teacherLogIn(log_in *person)
{
    puts("name:");
    gets(person->name);

    puts("password:");
    gets(person->password);

    teacher tutor;
    strcpy(tutor.name, person->name);

    teacher_fetchInfo(&tutor);

    if (strcmp(tutor.password, person->password) != 0) {
        puts("teacher name or password is incorrect.");
        return 0;
    }
    else {
        puts("Log in successful.");
        return 1;
    }
}

int adminLogIn(log_in *person)
{
    puts("name:");
    gets(person->name);

    puts("password:");
    gets(person->password);

    if (strcmp(person->name, "admin") != 0) {
        puts("name is incorrect.");
        return 0;
    }
    else if (strcmp(person->password, "1234") != 0) {
        puts("password is incorrect.");
        return 0;
    }
    else {
        puts("Log in successful.");
        return 1;
    }
}

void assignCourse(courseManager *man)
{
    DIR *dir;
    dir = opendir("teachers");
    if (!dir) {
        puts("teachers are not found.");
        return;
    }

    struct dirent *tutors;
    while ((tutors = readdir(dir)) != NULL) {
        int all_dot = 1, i;
        for (i = 0; tutors->d_name[i]; i++) {
            if (tutors->d_name[i] != '.') all_dot = 0;
        }
        if (all_dot) continue;
        char path[N];
        strcpy(path, "teachers/");
        strcat(path, tutors->d_name);
        strcat(path, "/course");

        printf("course name for %s:\n", tutors->d_name);
        gets(man->course_name);

        if (fileopen(path, "course.txt", man->course_name, "w")) {
            printf("%s is assigned for course %s.\n", tutors->d_name, man->course_name);
        }
    }
}

void updateCourse(courseManager *man)
{
    assignCourse(man);
}

void adminPanel()
{
    while (1) {
        //system("cls");
        puts("WELCOME TO ADMIN PANEL");
        puts("Enter: ");
        puts("1 To create student account");
        puts("2 To create teacher account");
        puts("3 To update student account");
        puts("4 to update teacher account");
        puts("5 to delete student account");
        puts("6 to delete teacher account");
        puts("7 to assign courses to teachers");
        puts("8 to update courses to teachers");
        puts("Any key to log out");

        int command;

        char tmp[N];
        gets(tmp);
        command = atoi(tmp);

        system("cls");

        switch (command)
        {
            case 1:
            {
                student new_stud;

                student_input(&new_stud);
                student_create(&new_stud);
                break;
            }
            case 2:
            {
                teacher new_tutor;

                teacher_input(&new_tutor);
                teacher_create(&new_tutor);
                break;
            }
            case 3:
            {
                student stud;
                char roll[N];

                puts("roll:");
                gets(roll);

                strcpy(stud.roll, roll);
                student_update(&stud);
                break;
            }
            case 4:
            {
                teacher tutor;
                char name[N];

                puts("name:");
                gets(name);

                strcpy(tutor.name, name);
                teacher_update(&tutor);
                break;
            }
            case 5:
            {
                student stud;
                char roll[N];

                puts("roll:");
                gets(roll);
                strcpy(stud.roll, roll);
                student_removeAccount(&stud);
                break;
            }
            case 6:
            {
                teacher tutor;
                char name[N];

                puts("name:");
                gets(name);
                strcpy(tutor.name, name);
                teacher_removeAccount(&tutor);
                break;
            }
            case 7:
            {
                courseManager manager;
                assignCourse(&manager);
                break;
            }
            case 8:
            {
                courseManager manager;
                updateCourse(&manager);
                break;
            }
            default:
            {
                puts("Logged out successfully.");
                return;
                break;
            }
        }
        //sleep(1);
    }
}

void studentPanel(char *roll)
{
    while (1) {
        //system("cls");
        puts("WELCOME TO STUDENT PANEL");
        puts("Enter:");
        puts("1 to check your class test mark");
        puts("Any key to log out");

        int command;

        char tmp[N];
        gets(tmp);
        command = atoi(tmp);

        system("cls");

        switch (command)
        {
            case 1:
            {
                classTest exam;
                classTest_myclassTestMark(roll);
                break;
            }
            default:
            {
                puts("Logged out successfully.");
                return;
                break;
            }
        }
        //sleep(1);
    }
}

void teacherPanel(char *name)
{
    while (1) {
        //system("cls");
        puts("WELCOME TO TEACHER PANEL");
        puts("Enter:");
        puts("1 to provide class test mark");
        puts("2 to update class test mark");
        puts("3 to find the student by the given roll number");
        puts("4 to find the student by the given first name");
        puts("5 to count total students");
        puts("Any key to log out");

        int command;

        char tmp[N];
        gets(tmp);
        command = atoi(tmp);
        system("cls");

        switch (command)
        {
            case 1:
            {
                classTest exam;
                classTest_input(&exam);

                char path[N];
                strcpy(path, "teachers/");
                strcat(path, name);
                strcat(path, "/course");

                char ass_course[N];

                if (retrive(path, "course.txt", ass_course)) {
                    if (classTest_validTeacher(ass_course, &exam)) {
                        classTest_provideMark(&exam);
                    }
                    else {
                        printf("you can provide marks for %s course only.\n", ass_course);
                    }
                }
                break;
            }
            case 2:
            {
                classTest exam;
                classTest_input(&exam);

                char path[N];
                strcpy(path, "teachers/");
                strcat(path, name);
                strcat(path, "/course");

                char ass_course[N];

                if (retrive(path, "course.txt", ass_course)) {
                    if (classTest_validTeacher(ass_course, &exam)) {
                        classTest_update(&exam);
                    }
                    else {
                        printf("you can provide marks for %s course only.\n", ass_course);
                    }
                }
                break;
            }
            case 3:
            {
                char roll[N];
                puts("roll:");
                gets(roll);

                student stud = teacher_findByRoll(roll);
                if (strcmp(stud.name, "NULL") == 0) {
                    puts("student not found.\n");
                }
                else {
                    student_output(&stud);
                }
                break;
            }
            case 4:
            {
                char name[N];
                puts("name:");
                gets(name);

                teacher_findByName(name);
                break;
            }
            case 5:
            {
                teacher_countOfStudent();
                break;
            }
            default:
            {
                puts("Logged out successfully.");
                return;
                break;
            }
        }
        //sleep(1);
    }
}

int fileopen(char *path, char *name, char *info, char *mode)
{
    char hold[N];
    int i;
    for (i = 0; path[i]; i++) {
        if (path[i] == '/') {
            hold[i] = '\0';
            DIR *dir;
            dir = opendir(hold);
            if (!dir) mkdir(hold);
            else closedir(dir);
        }
        hold[i] = path[i];
    }

    DIR *dir;
    dir = opendir(path);
    if (!dir) mkdir(path);
    else closedir(dir);

    char tmp[N];
    strcpy(tmp, path);

    strcat(path, "/");
    strcat(path, name);

    FILE *file;

    file = fopen(path, mode);

    strcpy(path, tmp);

    if (file == NULL) {
        printf("Error opening %s.\n", name);
        fclose(file);
        return 0;
    }
    fputs(info, file);
    fclose(file);
    return 1;
}

void _delete(char *path)
{
    DIR *dir;
    dir = opendir(path);

    if (!dir) {
        if (unlink(path) != 0) printf("Error in deleting %s.\n", path);
        return;
    }
    else {
        struct dirent *tree;
        while ((tree = readdir(dir)) != NULL) {
            char tmp[N];
            strcpy(tmp, path);
            strcat(tmp, "/");
            strcat(tmp, tree->d_name);

            int i, all_dot = 1;
            for (i = 0; tree->d_name[i]; i++) {
                if (tree->d_name[i] != '.') all_dot = 0;
            }

            if (!all_dot) _delete(tmp);
        }
        if (rmdir(path)) printf("Error in deleting %s.\n", path);
    }
}

int retrive(char *path, char *name, char *data)
{
    char tmp[N];
    strcpy(tmp, path);

    strcat(path, "/");
    strcat(path, name);

    FILE *file;

    file = fopen(path, "r");

    strcpy(path, tmp);

    if (file == NULL) {
        printf("Error opening %s.\n", name);
        fclose(file);
        return 0;
    }
    fgets(data, N - 2, file);
    fclose(file);
    return 1;
}
