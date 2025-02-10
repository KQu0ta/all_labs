#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//БД пока не будет тк хз че и как там
//БД поступлений товаров на склад
//comes:date; 		// Дата поступления
//sender:string; 	// Грузоотправитель
//name:string;		// Наименование товара
//weight:int; 		// Масса товара
//count:int; 		// Поступило в количестве
//images:set of ['fragile','toxic','perishable','acrid','inflammable','frozen']		// Значки на коробке
//worker:string; 	// Принял работник (фамилия)



void insert_to_base(char *str){
    while (strtok_r(str, ",", &str))
    {
        //field=value
        
    }
    
    
}

void select_in_base(char *str){

}

void delete_in_base(char *str){

}

void update_to_base(char *str){

}

void uniq_to_base(char *str){

}

void check_command(char str){
    char *token = strtok_r(str, " ", &str);
    if(strcmp(token, "insert") == 0){// INSERT 
        insert_to_base(strtok_r(NULL, " ", &str));

    }else if (strcmp(token, "select") == 0){// SELCET 
        select_in_base(strtok_r(NULL, " ", &str));

    }else if (strcmp(token, "delete") == 0){// DELETE 
        delete_in_base(strtok_r(NULL, " ", &str));

    }else if (strcmp(token, "update") == 0){// UPDATE 
        update_to_base(strtok_r(NULL, " ", &str));

    }else if (strcmp(token, "uniq ") == 0){// UNIQ 
        uniq_to_base(strtok_r(NULL, " ", &str));
    }
    
}

int main(){
    char *input;
    printf("Введите команду: ");
    fgets(input, sizeof(input), stdin);
    check_command(input);
    return 0;
}