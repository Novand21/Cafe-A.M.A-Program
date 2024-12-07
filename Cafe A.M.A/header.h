#ifndef HEADER_H
#define HEADER_H
#include <time.h>

//Kamus Admin

struct Admin {
    int ID;
    char namemenu[50];
    float price;
    struct Admin* next;
};


struct Order{
    int id;
    char namemenu[50];
    float price;
    float totalPrice;
    int kuantitas;  
    struct Order* next;
};


struct Customer{
    int statusMakanan;
    int mejaID;
    int idBayar;
    time_t startTime;
    int durasi;
    struct Customer* next;
};


struct Tables{
    int mejaID;
    int startTime;
    int durasi;
    int readytoCheck;
    struct Tables* next;
};




// deklarasi tipe Admin
extern struct Admin* headadmin;  // buat menu admin
extern struct Order* headmenu; // untuk order customer
extern struct Customer* headcustomer; // untuk identitas customer
extern struct Time waktuPesanan; // untuk mengukur waktu pesanan


//Deklarasi Modul
int MainMenu(); //Arman
void checkMeja(); //Raditya
void startTimeMeja(int);//Raditya


//Admin Modular
void Admin(); //Arman
void AdminMenu(); //Arman
struct Admin* DeleteItems(int); //Arman
void viewSales();//Raditya
struct Order* DeleteOrder(); //Arman
void addSales();//Raditya
struct Admin* AddItems(struct Admin*, int, char[20], float); // Raditya
void ViewItems(struct Admin*); //Raditya
struct Order* OrderMenu(struct Order*, struct Admin*); //Raditya
void menuInit();//Raditya
void ViewOrder(struct Order*); //Raditya


//Customer Modular
void CustomerMenu(); //Arman
void StatusPesanan();// Raditya
void ReservasiMeja();//Raditya
struct Customer* addCustomerStatus(); // Raditya
void tampilkanMeja();//Raditya
void hitungTotalHarga(float*);//Raditya
void Pembayaran();//Arman
void cash();//Arman
void debit();//Arman
void eWallet();//Arman
void deletelistItem(); //Raditya
#endif


/*Nama Modular : */
/*Dekripsi : */
/*Pembuat :*/