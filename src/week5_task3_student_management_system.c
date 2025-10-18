#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATA_FILE "students.txt"
#define MAX_STUDENTS 1000
#define MAX_NAME_LEN 128
#define LINE_BUF 256

typedef struct {
    char name[MAX_NAME_LEN];
    int id;
    double gpa;
} Student;

/* in-memory storage */
static Student students[MAX_STUDENTS];
static int student_count = 0;

/* helper prototypes */
static void trim_newline(char *s);
static void clear_stdin_line(void);

/* TODO: load_students() - read students from DATA_FILE into students[] */
void load_students(void)
{
    FILE *f = fopen(DATA_FILE, "r");
    if (!f) {
        /* No file yet or cannot open -> treat as empty dataset */
        student_count = 0;
        return;
    }

    char line[LINE_BUF];
    student_count = 0;
    while (fgets(line, sizeof(line), f) != NULL && student_count < MAX_STUDENTS) {
        trim_newline(line);
        if (line[0] == '\0') continue; /* skip empty lines */

        /* Expect format: name|id|gpa
           Use manual parsing to be tolerant to malformed lines. */
        char *p = line;
        char *sep = strchr(p, '|');
        if (!sep) continue;
        *sep = '\0';
        /* copy name (may contain spaces) */
        strncpy(students[student_count].name, p, MAX_NAME_LEN - 1);
        students[student_count].name[MAX_NAME_LEN - 1] = '\0';

        p = sep + 1;
        sep = strchr(p, '|');
        if (!sep) continue;
        *sep = '\0';

        /* parse id */
        char *endptr = NULL;
        long idl = strtol(p, &endptr, 10);
        if (p == endptr) continue; /* parse failed */
        students[student_count].id = (int)idl;

        /* parse gpa */
        p = sep + 1;
        double g = strtod(p, &endptr);
        if (p == endptr) continue;
        students[student_count].gpa = g;

        student_count++;
    }

    fclose(f);
}

/* TODO: save_students() - write students[] into DATA_FILE (one record per line) */
int save_students(void)
{
    FILE *f = fopen(DATA_FILE, "w");
    if (!f) {
        perror("Failed to open data file for writing");
        return -1;
    }

    for (int i = 0; i < student_count; ++i) {
        /* write as: name|id|gpa */
        /* use two decimal places for GPA (matches example) */
        if (fprintf(f, "%s|%d|%.2f\n",
                    students[i].name,
                    students[i].id,
                    students[i].gpa) < 0) {
            fclose(f);
            perror("Failed while writing data file");
            return -1;
        }
    }

    if (fclose(f) != 0) {
        perror("Failed to close data file");
        return -1;
    }
    return 0;
}

/* TODO: add_student() - prompt user and append to students[] in memory */
void add_student(void)
{
    if (student_count >= MAX_STUDENTS) {
        puts("Student list is full. Cannot add more students.");
        return;
    }

    char buf[MAX_NAME_LEN];
    int id = 0;
    double gpa = 0.0;

    printf("Enter name: ");
    if (!fgets(buf, sizeof(buf), stdin)) {
        puts("Input error.");
        clear_stdin_line();
        return;
    }
    trim_newline(buf);
    if (buf[0] == '\0') {
        puts("Name cannot be empty.");
        return;
    }

    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) {
        puts("Invalid ID.");
        clear_stdin_line();
        return;
    }

    printf("Enter GPA: ");
    if (scanf("%lf", &gpa) != 1) {
        puts("Invalid GPA.");
        clear_stdin_line();
        return;
    }
    clear_stdin_line(); /* remove leftover newline */

    /* store (safe copy) */
    strncpy(students[student_count].name, buf, MAX_NAME_LEN - 1);
    students[student_count].name[MAX_NAME_LEN - 1] = '\0';
    students[student_count].id = id;
    students[student_count].gpa = gpa;
    student_count++;

    puts("Student added successfully!");
}

/* TODO: list_students() - print all students to stdout */
void list_students(void)
{
    if (student_count == 0) {
        puts("No students available.");
        return;
    }

    puts("List of students:");
    for (int i = 0; i < student_count; ++i) {
        printf("%d. Name: %s | ID: %d | GPA: %.2f\n",
               i + 1,
               students[i].name,
               students[i].id,
               students[i].gpa);
    }
}

/* helper: trim newline and carriage returns */
static void trim_newline(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        --len;
    }
}

/* helper: discard rest of stdin line */
static void clear_stdin_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* main menu loop */
int main(void)
{
    load_students();

    for (;;) {
        puts("1. List students");
        puts("2. Add student");
        puts("3. Save and Exit");
        printf("Select an option: ");

        int opt = 0;
        if (scanf("%d", &opt) != 1) {
            puts("Invalid selection.");
            clear_stdin_line();
            continue;
        }
        clear_stdin_line();

        switch (opt) {
            case 1:
                list_students();
                break;
            case 2:
                add_student();
                break;
            case 3:
                if (save_students() == 0) {
                    puts("Data saved. Goodbye!");
                } else {
                    puts("Failed to save data. Exiting anyway.");
                }
                return 0;
            default:
                puts("Unknown option. Please try again.");
                break;
        }
    }

    return 0;
}2