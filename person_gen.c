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
    
};


struct person // Студент
{
    char fullname[100];
    struct tm birth;        // Крч тут принцип записи в структуру {число, месяц - 1, год -1900} потом буду фиксить
    char number_of_group[20];
    struct subject lesson;
    attestation status;

};

void generation(int n){

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