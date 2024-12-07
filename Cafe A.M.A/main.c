#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main(){    
    int condition = true;
    int choice;
    menuInit();
    while(condition){
        choice = MainMenu();
        switch(choice){
            case 1:
                Admin();
                break;
            case 2:
                CustomerMenu();
                break;
            case 3:
                condition = false;
                break;
            default:
                printf("Input anda salah");
                break;
        } 
    }
    return 0;

}
    
