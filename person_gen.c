#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include <windows.h>


typedef enum { // Формат аттестации
    exam,           // Экзамен 0
    test,           // зачет 1
    coursework      // курсовая 2
} attestation;


struct subject  // Предмет
{
    char name_of_subject[30];               
    unsigned int number_of_lectures:8;      
    unsigned int number_of_laboratory:8;    
    unsigned int lesson_sum:8;              
    attestation status;
};


struct person // Студент
{
    char fullname[100];
    struct tm birth;        // Крч тут принцип записи в структуру {число, месяц - 1, год -1900} 
    char number_of_group[20];
    struct subject* lesson;
    size_t number_of_items;

};

// Функция для генерации случайного числа в диапазоне [min, max]
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}


// Функция для генерации случайного ФИО
void random_fio(char *fio) {
    const char *names[] = { "Никита", "Лев", "Виталий", "Раджаб", "Юрий", "Мухамед", "Алексей", "Андрей", "Александр" };
    const char *surnames[] = { "Клыгин", "Попов", "Гужавин" };
    const char *lastnames[] = { "Александрович", "Алексеевич", "Сергеевич" };

    // Случайный выбор имени, фамилии и отчества
    sprintf(fio, "%s %s %s", surnames[random_int(0, 2)], names[random_int(0, 2)], lastnames[random_int(0, 2)]);
}

// Функция для генерации случайной группы
void random_group(char group[20]){
    
    group[0] = (char)random_int(65,90);
    for (int i = 1; i < 20; i++)
    {
        if (i ==17){
            group[17] = '_';
        }
        else if (i>17){
            group[i] = (char)random_int(10,99);
        }
        else{
            group[i] = (char)random_int(65, 90);
        }

        
        
        
    }
    
}

// Функция для генерации случайного предмета
void random_lesson(struct subject* lesson, size_t n) {
    const char *lessons_names[] = { "Выш.мат", "Физика", "Аип" , "Англ.яз", "Физ.культ", "Философия", "Впд"};

    
    // lesson = (struct subject*)calloc(n, sizeof(struct subject));// прикольная строка я вроде понял, вроде не понял
    
    for (size_t i = 0; i < n; i++)
    {
        strncpy(lesson[i].name_of_subject, lessons_names[random_int(0,2)], 21);
        lesson[i].name_of_subject[21] = '\0';
        lesson[i].number_of_lectures = (unsigned char)random_int(0,255);
        lesson[i].number_of_laboratory = (unsigned char)random_int(0,255);
        lesson[i].lesson_sum = (unsigned char)random_int(0,255);
        lesson[i].status = random_int(0,2);
    }
}


void generation(size_t n, struct person* arr, int min_disciplines, int max_disciplines){
    for (size_t i = 0; i < n; i++)
    {
        random_fio(arr[i].fullname);
        arr[i].birth.tm_mon = random_int(2, 13);// -1 тк time
        
        if (arr[i].birth.tm_mon == 2){
            arr[i].birth.tm_mday = random_int(1, 28);

        }else if (arr[i].birth.tm_mon == 4 || arr[i].birth.tm_mon == 6 || arr[i].birth.tm_mon == 9 || arr[i].birth.tm_mon == 11 ){
            arr[i].birth.tm_mday = random_int(1, 30); 

        }else{
            arr[i].birth.tm_mday = random_int(1, 31); 
        }
        arr[i].birth.tm_year = random_int(85, 110); //-1900 тк time

        random_group(arr[i].number_of_group);
        arr[i].number_of_items = (size_t)random_int(min_disciplines, max_disciplines);

        arr[i].lesson = (struct subject*)calloc(arr[i].number_of_items, sizeof(struct subject));
        if (arr[i].lesson == NULL) {
            printf("Ошибка выделения памяти для предметов.\n");
            return;
        }


        random_lesson(arr[i].lesson, arr[i].number_of_items);
    }
    
}




//Работает коректно
void get_size(size_t n){
    size_t total_mem = sizeof(struct person) * n;
    char format[][3] = {"B", "Kb", "Mb", "Gb"};
    short index_size = 0;
    while (total_mem >= 1024 && index_size < 4) {
        total_mem /= 1024;
        index_size++;
    }

    printf("Data size %zu %s\n", total_mem, format[index_size]);
}



//Работает коректно
void print_students(size_t n, struct person *students, size_t max_count){
    if (n < 1){
        printf("N не может быть меньше 1");
        return;
    }
    if (n == 1){n = max_count;}

    for (size_t i = 0; i < n; i++){
        printf("%zu %s %02d.%02d.%04d %s\n", i+1, students[i].fullname, students[i].birth.tm_mday, students[i].birth.tm_mon+1, students[i].birth.tm_year+1900,students[i].number_of_group);
    }

}

void print_lesson(struct person student){
    printf("%s\n", student.fullname);
    for (size_t i = 0; i < student.number_of_items; i++){
        printf("%zu %s %u %u %u %d\n", i+1, student.lesson[i].name_of_subject, student.lesson[i].number_of_lectures, student.lesson[i].number_of_laboratory, student.lesson[i].lesson_sum ,student.lesson[i].status);
    }
}

void clean_data(struct person* student, size_t *n){
    if (student != NULL){
        for (size_t i = 0; i < *n; i++){
            if(student[i].lesson != NULL){
                free(student[i].lesson); // тк мы выделяем динамич память для предметов
            }   
        }
        free(student);
        *n = 0;
        printf("Все данные очищены.\n");
    }else{
        printf("Нет данных для очистки.\n");
    }
    
}

void print_menu() {
    printf("\x1b[2J\x1b[H");// Очистка экрана
    printf("+----------------------------------------------+\n");
    printf("|                МЕНЮ ПРОГРАММЫ                |\n");
    printf("+----------------------------------------------+\n");
    printf("|       1. gen N - Генерация данных            |\n");
    printf("|       2. get_size - Размер данны             |\n");
    printf("|       3. print_students N (default - all)    |\n");
    printf("|       4. lesson N (N - number_of_student)    |\n");
    printf("|       5. clean - Очистка данных              |\n");
    printf("|       6. exit - Выход                        |\n");
    printf("+----------------------------------------------+\n");


    printf("Command:\n");
}


int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    bool d = true;
    size_t n = 0;
    struct person* student = 0;
    char command[20];
    print_menu();
    while (d) {
        
        fgets(command, sizeof(command), stdin);

        // Удаляем символ новой строки
        command[strcspn(command, "\n")] = '\0';

        // Разделяем команду и аргументы
        char* token = strtok(command, " ");
        if (token == NULL) continue; // Пропустить пустой ввод

        if (strcmp(token, "gen") == 0) { // Генерация данных
            char* arg = strtok(NULL, " ");
            if (arg != NULL) {
                n = (size_t)strtol(arg, NULL, 10);
                student = (struct person*)calloc(n, sizeof(struct person));
                generation(n, student, 10, 20);
                printf("Данные сгенерированы.\n");
            } else {
                printf("Неверный аргумент для команды gen.\n");
            }

        } else if (strcmp(token, "get_size") == 0) { // Получить размер данных
            get_size(n);

        } else if (strcmp(token, "print_students") == 0) { // Печать студентов
            char* arg = strtok(NULL, " ");
            print_students((size_t)strtol(arg, NULL, 10), student, n);

        } else if (strcmp(token, "lesson") == 0) { // Печать студентов
            char* arg = strtok(NULL, " ");
            print_lesson(student[(size_t)strtol(arg, NULL, 10)-1]);
        
        }else if (strcmp(token, "clean") == 0) { // Очистка данных
            clean_data(student, &n);
            student = NULL; 

        } else if (strcmp(token, "exit") == 0) { // Выход
            d = false;

        } else {
            printf("Неизвестная команда: %s\n", token);
        }
    }

    // Освобождаем память перед выходом
    if (student != NULL) {
        free(student);
    }
    
    return 0;

}