#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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
    struct tm birth;        // Крч тут принцип записи в структуру {число, месяц - 1, год -1900} потом буду фиксить
    char number_of_group[20];
    struct subject* lesson;

};

// Функция для генерации случайного числа в диапазоне [min, max]
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Функция для генерации случайной даты рождения
// struct tm random_date() {
//     int month = random_int(1, 12);
//     int day = 0;
//     if (month == 28){
//         person.birth. = random_int(1, 28);
//     }else if (month == 4 || month == 6 || month == 9 || month == 11 ){
//         int day = random_int(1, 30); 
//     }else{
//         int day = random_int(1, 31); 
//     }
//     int year = random_int(1990, 2005); // Год
//     return 
//     // sprintf(date, "%02d.%02d.%04d", day, month, year); // Формат: ДД.ММ.ГГГГ
// }

// Функция для генерации случайного ФИО
void random_fio(char *fio) {
    const char *names[] = { "Никита", "Лев", "Виталий" };
    const char *surnames[] = { "Клыгин", "Попов", "Гужавин" };
    const char *lastnames[] = { "Александрович", "Алексеевич", "Сергеевич" };

    // Случайный выбор имени, фамилии и отчества
    sprintf(fio, "%s %s %s", surnames[random_int(0, 2)], names[random_int(0, 2)], lastnames[random_int(0, 2)]);
}


void random_group(char group[20]){
    group[0] = random_int(65,90);
    for (int i = 1; i < 17; i++)
    {
        group[i] = random_int(65, 90);
    }
    group[17] = '_';
    group[18] = random_int(10,99);    
}

// Функция для генерации случайного предмета
void random_lesson(struct person* student, int min_disciplines, int max_disciplines) {
    const char *lessons_names[] = { "Рыганье", "Пуканье", "Сраканье" };

    if(min_disciplines == NULL && max_disciplines == NULL){
        min_disciplines = 10, max_disciplines = 20;
    }
    
    int count_of_lessons = random_int(min_disciplines , max_disciplines);
    student->lesson = (struct Lesson*)calloc(count_of_lessons, sizeof(struct subject));// прикольная строка я вроде понял, вроде не понял
    
    for (int i = 0; i < count_of_lessons; i++)
    {
        // student->lesson[i].name_of_subject = lessons_names[random_int(0,2)]; Фикс не знаю почему
        student->lesson[i].number_of_lectures = random_int(0,255);
        student->lesson[i].number_of_laboratory = random_int(0,255);
        student->lesson[i].lesson_sum = random_int(0,255);
        student->lesson[i].status = random_int(0,2);
    }
   
}


void generation(int n){
    struct person arr[10];

    for (int i = 0; i < n; i++)
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
        random_lesson(arr[i].lesson, NULL, NULL);
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

    printf("Data size %lld %s", total_mem, format[index_size]);
}



//Работает коректно
void print_students(size_t n, struct person *students, size_t max_count){
    if (n == 1){n = max_count;}

    for (size_t i = 0; i < n; i++){
        printf("%lld %s %02d.%02d.%04d %s\n", i+1, students[i].fullname, students[i].birth.tm_mday, students[i].birth.tm_mon+1, students[i].birth.tm_year+1900,students[i].number_of_group);
    }

}





int main(){
    // Проверка работы  двух функций 


    // struct person students[] = { {"xYzAbC", {.tm_mday = 15, .tm_mon = 7, .tm_year = 95}, "Group-101", {"math", 30, 10, 40}, exam},
    //                                 {"tyjej", {.tm_mday = 21, .tm_mon = 2, .tm_year = 106}, "Group-102", {"english", 65, 23, 67}, test},
    //                                 {"etykkuk", {.tm_mday = 23, .tm_mon = 7, .tm_year = 109}, "Group-103", {"physics", 123, 54, 122}, coursework}};
    // size_t n = sizeof(students) / sizeof(students[0]);
    // print_students(1, students, n);
    // printf("\n");
    // get_size(n);

    
    return 0;

}