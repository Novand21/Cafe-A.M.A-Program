#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <ctype.h>
#include "header.h"

#define LENGTH_MEJA 6




// variabel global
struct Admin* headadmin = NULL;
struct Order* headmenu = NULL;
struct Customer* headcustomer = NULL;
struct Tables* headtables = NULL;

const int durasiPesanan = 20;
int customerOrder = 1;
int Mejap[LENGTH_MEJA] = {0,0,0,0,0,0};
int tables = 0;


//Modul Admin



/*Nama Modular : Admin*/
/*Deskripsi : Untuk mengecek username dan password admin*/
/*Pembuat : Arman Yusuf Rifandi*/

void Admin(){
    char username[20], password[20];
    printf("\n\n======== ADMIN LOGIN ========");
    printf("\n\n Masukan Username: ");
    scanf("%19s", username);
    printf("\n Masukan Sandi: ");
    scanf("%19s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin@a.m.a") == 0) {
        printf("\n\n==========Anda Telah Login===========\n\n");
        AdminMenu();
    }else{
        printf("Login gagal. Username atau Sandi Salah");
    }
}






/*Nama Modular : MainMenu*/
/*Deskripsi : Untuk menampilkan pilihan menu untuk admin dan customer*/
/*Pembuat : Arman Yusuf Rifandi*/

// Tampilan Menu
int MainMenu() {
    int choice;
    printf("\n\n======== A.M.A CAFE ========\n\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
    printf("3. Exit\n\n");
    printf("Masukan Pilihannmu: ");
    scanf("%d", &choice);
    return choice;
}





/*Nama Modular : AdminMenu*/
/*Deskripsi : Untuk menampilkan tampilan menu untuk admin*/
/*Pembuat : Arman Yusuf Rifandi*/

//Tampilan admin ketika sudah login
void AdminMenu(){
    int condition = 1;
    int ID, choice;
    char menu[50];
    float price;
    while(condition){
        printf("\n\n======== ADMIN MENU ========\n\n");
        printf("\n1. View Sales");
        printf("\n2. Add Item From Menu");
        printf("\n3. Delete Item From Menu");
        printf("\n4. View Items Menu");
        printf("\n5. Menu Order Pelanggan");
        printf("\n6. View Order Pelanggan");
        printf("\n7. Delete Order Pelanggan");
        printf("\n8. Exit");
        printf("\n\nMasukan Pilihan : ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                viewSales();
                break;
            case 2:
                ViewItems(headadmin);
                printf("\nMasukan ID [0] untuk exit : ");
                scanf("%d", &ID);
                if (ID == 0){
                    break;
                }else{ 
                    printf("Masukan Nama Menu, [0] untuk cancel: ");
                    scanf(" %[^\n]s", menu);
                    if (strcmp(menu, "0") == 0){
                        break;
                    }
                    printf("Masukan harga, [0] Untuk cancel: ");
                    scanf("%f", &price);
                    if(price == 0){
                        break;
                    }
                    headadmin = AddItems(headadmin, ID, menu, price);
                    break;
                }
            case 3:
                if(headadmin == NULL){
                    printf("Tidak Ada Item");
                    break;
                }
                ViewItems(headadmin);
                printf("Put ID, [0] untuk cancel: ");
                scanf("%d", &ID);
                if (ID == 0)
                {   
                    break;
                }
                
                headadmin = DeleteItems(ID);
                break;
            case 4:
                ViewItems(headadmin);
                break;
            
            case 5:
                headmenu = OrderMenu(headmenu, headadmin);
                break;
            
            case 6:
                ViewOrder(headmenu);
                break;
            
            case 7:
                if (headmenu == NULL){
                    printf("No Items");
                    break;
                }
                ViewOrder(headmenu);
                headmenu = DeleteOrder();        
                break;
            case 8:
                condition = 0;
                break;
            default:
                printf("Input anda salah");
                break;
        }
    }
}




/*Nama Modular : CustomerMenu*/
/*Deskripsi : Untuk menampilkan tampilan menu untuk customer*/
/*Pembuat : Arman Yusuf Rifandi*/

//Tampilan untuk customer
void CustomerMenu(){
    int condition = 1;
    int choice;

    while(condition){
        printf("\n======== CUSTOMER MENU ========\n\n");
        printf("1. View Menu\n");
        printf("2. Reservasi Meja\n");
        printf("3. Status Pesanan\n");
        printf("4. Pembayaran Pelanggan\n");
        printf("5. Exit\n\n");
        printf("Masukan Pilihan:");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                ViewItems(headadmin);
                break;
            case 2:
                ReservasiMeja(Mejap);        
                break;
            case 3:
                StatusPesanan();
                break;
            case 4:
                Pembayaran();
                break;
            case 5:
                condition = 0;
                break;
        }
    }
}




/*Nama Modular : viewSales*/
/*Deskripsi : Untuk menampilkan hasil rekaptulasi penjualan*/
/*Pembuat : M Raditya Novandrian*/

void viewSales(){
    int sales;
    FILE* list = fopen("earnings.txt", "r");
    if(list == NULL){
        fclose(list);
        list = fopen("earnings.txt", "w");
        fclose(list);
        return;
    }
    while(!feof(list)){
        sales = fgetc(list);
        printf("%c", sales);
    }
    fclose(list);
}





/*Nama Modular : AddSales*/
/*Deskripsi : Untuk menyimpan hasil penjualan/bon*/
/*Pembuat : M Raditya Novandrian*/

void addSales(){
    FILE *file;
    int numTransactions, i;
    double amount, total = 0;
    char filename[50] = "earnings.txt";
    char currentDate[11];       
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    struct Order* ptrMenu = headmenu;
    int no = 1;

    
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", t);


    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) > 0) {
        fprintf(file, "\n"); 
    }
    fprintf(file, "\n%s\n", currentDate);
    fprintf(file, "Order no %d \n", customerOrder);
    fprintf(file, "-----------------------------\n");
    fprintf(file, "%-15s%-25s%-15s%-15s\n", "Transaction", "Menu", "Jumlah", "Total Harga");
    while (ptrMenu != NULL) {
        // Save transaction to file
        fprintf(file, "%-15d%-25s%-15d%-15.2f\n", no, ptrMenu->namemenu, ptrMenu->kuantitas, ptrMenu->totalPrice);
        total += ptrMenu->totalPrice; // Add to total
        no += 1;
        ptrMenu = ptrMenu->next;
    }

    
    fprintf(file, "-----------------------------\n");
    fprintf(file, "Total Harga: %.2lf\n", total);


    fclose(file);

    // menghapus list menu
    ptrMenu = headmenu;
    struct Order* ptrNextMenu =  headmenu->next;
    while(ptrNextMenu != NULL){
        free(ptrMenu);
        ptrMenu = ptrNextMenu;
        ptrNextMenu = ptrNextMenu->next;        
    }
    free(ptrMenu);
    headmenu = NULL;
    customerOrder += 1;
}







/*Nama Modular : AddItems*/
/*Deskripsi : Untuk menambahkan menu baru untuk customer*/
/*Pembuat : M Raditya Novandrian*/

struct Admin* AddItems(struct Admin* heada, int ID, char namemenu[], float price){
    struct Admin* temp1 = malloc(sizeof(struct Admin));
    struct Admin* pCheckID = heada;

    if (temp1 == NULL) {
        printf("Error: Alokasi memori gagal.\n");
        return heada;
    }
    
    temp1->ID = ID;
    strcpy(temp1->namemenu, namemenu);
    temp1->price = price;
    temp1->next = NULL;

    while(pCheckID != NULL && pCheckID->ID != ID){
        pCheckID = pCheckID->next;
    } 

    if(heada==NULL){
        heada = temp1;
    }
    else{
        struct Admin* temp2 = heada;
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }  
        if(pCheckID != NULL && pCheckID->ID == ID){
            printf("\nID Sama Dengan Menu Lainnya");
            return headadmin;
        }
        temp2->next = temp1;
    }
    FILE* pOpen = fopen("menu.txt", "a");
    fprintf(pOpen, "\n%d\n%s\n%.2f", ID, namemenu, price);
    fclose(pOpen);  
    printf("Item Berhasil Ditambahkan");
    return heada;
}




/*Nama Modular : DeleteItems*/
/*Deskripsi : Untuk menghapus menu pilihan dari list menu*/
/*Pembuat : Arman Yusuf Rifandi*/


struct Admin* DeleteItems(int ID){
    struct Admin* ptrPrev = headadmin;
    struct Admin* ptr = headadmin->next;
    if (ptrPrev->ID == ID){
        headadmin = ptr;
        free(ptrPrev);
        printf("\nItem Berhasil Dihapus");
        deletelistItem();
        return headadmin;
    }
    while(ptr != NULL && ptr->ID != ID){
        ptrPrev = ptrPrev->next;
        ptr = ptr->next;
    }
    if (ptr != NULL){
        ptrPrev->next = ptr->next;
        printf("\nItem Berhasil Dihapus");
        free(ptr);
    }
    else{
        printf("Item Tidak Ada");
    }
    deletelistItem();
    return headadmin;
}






/*Nama Modular : deletItem*/
/*Deskripsi : Untuk mengupdate file menu.txt supaya menu yang dihapus hilang*/
/*Pembuat : M Raditya Novandrian*/

void deletelistItem(){
    FILE* pDelete = fopen("menu.txt", "w");
    struct Admin* pAdmin = headadmin;

    while(pAdmin !=NULL){
        fprintf(pDelete,"\n%d\n%s\n%.2f", pAdmin->ID, pAdmin->namemenu, pAdmin->price);
        pAdmin = pAdmin->next;
    }
    fclose(pDelete);
}


/*Nama Modular : viewItems*/
/*Deskripsi : Untuk menampilkan list menu*/
/*Pembuat : M Raditya Novandrian*/

void ViewItems(struct Admin* head){
    printf("==========MENU==========\n\n");
    printf("%-15s%-25s%-15s\n", "Id Menu", "Menu", "Harga");
    while(head != NULL){
        printf("\n %-15d%-25s%s%-.2f\t\n", head->ID, head->namemenu, "Rp. ", head->price);
        head = head->next;
    }
}





/*Nama Modular : OrderMenu*/
/*Deskripsi : Untuk memesan menu customer*/
/*Pembuat : M Raditya Novandrian*/


struct Order* OrderMenu(struct Order* headmenu, struct Admin* headadmin){
    int currId;
    int kuantitas;
    ViewItems(headadmin);
    if (headadmin == NULL){
        printf("Menu Kosong");
        return headmenu;
    }
    printf("Masukkan ID, [0] untuk cancel: ");
    scanf("%d", &currId);
    if (currId == 0){
        return headmenu;
    }
    printf("Masukkan kuantitas, [0] untuk cancel: ");
    scanf("%d", &kuantitas);
    if (kuantitas == 0){
        return headmenu;
    }
    
    struct Admin* temp4 = headadmin;
    while(temp4 != NULL && temp4->ID != currId){
        temp4 = temp4->next;
    }
    if (temp4 == NULL){
        printf("Tidak Terdapat Menu");
        return headmenu;
    }
    struct Order* temp6 = malloc(sizeof(struct Order));
    struct Order* temp5 = headmenu;
    temp6->id = temp4->ID;
    temp6->kuantitas = kuantitas;
    temp6->price = temp4->price;
    temp6->totalPrice = temp4->price * kuantitas;
    strcpy(temp6->namemenu, temp4->namemenu);
    temp6->next = NULL;
    if(headmenu == NULL){
        temp5 = temp6;
        return temp5;
    }
    else{
        while(temp5->next != NULL){
            temp5 = temp5->next;
        }
        temp5->next = temp6;
    }
    printf("\nMenu Ditambahkan");
    return headmenu;
}





/*Nama Modular : ViewOrder*/
/*Deskripsi : Untuk melihat menu pesanan yang telah diorder*/
/*Pembuat : M Raditya Novandrian*/

void ViewOrder(struct Order* head){
    float totalHarga = 0.0;
    struct Order* temp10 = head;
    struct Admin* menuAdmin = headadmin;
    if (temp10 != NULL){
        printf("==========================MENU ORDER PELANGGAN===============================\n\n");
        printf("%-15s%-25s%-15s%-15s%-15s\n", "ID", "Menu", "Harga", "Kuantitas", "Total");
        while(temp10 != NULL){
            printf("\n%-15d%-25s%s%-15.2f%-15d%s%-15.2f", temp10->id, temp10->namemenu, "Rp.", temp10->price, temp10->kuantitas, "Rp.", temp10->totalPrice);
            totalHarga +=  temp10->totalPrice;
            temp10 = temp10->next;
        }
        printf("\n==============================================================================\n");
         
        printf("\n\nTotal Harga: Rp.%.2f", totalHarga);
    } else 
        printf("Anda Belum Memesan apapun");
}





/*Nama Modular : DeleteOrder*/
/*Deskripsi : Untuk melihat menu pesanan yang telah diorder*/
/*Pembuat : Arman Yusuf Rifandi*/

struct Order* DeleteOrder(){
    struct Order* ptrPrev = headmenu;
    struct Order* ptr = headmenu->next;
    int id, kuantitas;
    printf("\nPut ID, [0] untuk cancel : ");
    scanf("%d", &id);
    if (id == 0){
        return headmenu;
    }
    printf("\nMasukan Jumlah, [0] untuk cancel : ");
    scanf("%d", &kuantitas);
    if (kuantitas == 0){
        return headmenu;
    }

    
    if(headmenu->id == id && headmenu->kuantitas <= kuantitas){
        headmenu = headmenu->next;
        printf("\nItem Berhasil Dihapus");
        free(ptrPrev);
        return headmenu;
    }
    else if(headmenu->id == id && headmenu->kuantitas > kuantitas){
        headmenu->totalPrice = (headmenu->totalPrice / headmenu->kuantitas) * kuantitas;
        headmenu->kuantitas = headmenu->kuantitas - kuantitas;
        printf("\nItem Berhasil Dikurang");
        return headmenu;
    }

    while(ptr != NULL && ptr->id != id){
        ptrPrev = ptrPrev->next;
        ptr = ptr->next;
    }
    if (ptr != NULL && ptr->kuantitas <= kuantitas){
        ptrPrev->next = ptr->next;
        printf("\nItem Berhasil Dihapus");
        free(ptr);
    }
    else if (ptr != NULL && ptr->kuantitas > kuantitas){
        ptr->totalPrice = (ptr->totalPrice / ptr->kuantitas) * kuantitas;
        ptr->kuantitas = ptr->kuantitas - kuantitas;
        printf("\nItem Berhasil Dikurang");
    }
    else{
        printf("Item Tidak Ada");
    }
    
    return headmenu;
}


/*Nama Modular : tampilkanMeja*/
/*Deskripsi : Untuk melihat list meja yang ada*/
/*Pembuat : M Raditya Novandrian*/

void tampilkanMeja(int input[]){
    char status[2][15] = {"Available", "Unavailable"};
    printf("===================        ====================\n");
    printf("[1](%s)             [2](%s)\n\n", status[input[0]], status[input[1]]);
    printf("        [3](%s)[4](%s)\n\n", status[input[2]], status[input[3]]);
    printf("[5](%s)             [6](%s)", status[input[4]], status[input[5]]);
}

/*Nama Modular : checkMeja*/
/*Deskripsi : Untuk mengecek list meja yang tersedia*/
/*Pembuat : M Raditya Novandrian*/

void checkMeja(int input[]){
    if(headtables == NULL){
        //printf("\nKosong");
        return;
    }
    struct Tables* prevPointer = headtables;
    struct Tables* pointer = headtables->next;
    time_t current_time = time(NULL);
    int waktuBerlalu, sisaWaktu;

    waktuBerlalu = (int)(current_time - prevPointer->startTime);
    sisaWaktu = prevPointer->durasi - waktuBerlalu;
    //printf("\n%d", sisaWaktu); // buat debuging
    
    if (sisaWaktu < 0 && prevPointer->readytoCheck){
        input[headtables->mejaID-1] = 0;
        headtables = pointer;
        free(prevPointer);
        prevPointer = headtables;
        if (prevPointer == NULL){
            pointer = headtables;
        }
        else{
            pointer = headtables->next;
        }
    }
    while(pointer != NULL){
        waktuBerlalu = (int)(current_time - pointer->startTime);
        sisaWaktu = pointer->durasi - waktuBerlalu;
        //printf("\n%d", sisaWaktu); // buat debugging
        if(sisaWaktu <= 0 && pointer->readytoCheck){
            input[pointer->mejaID-1] = 0;
            prevPointer->next = pointer->next;
            free(pointer);
            pointer = prevPointer->next;
        }
        if(pointer == NULL){
            break;
        }
        pointer = pointer->next;
    }
}


/*Nama Modular : StatusPesanan*/
/*Deskripsi : Untuk mengecek status pesanan customer*/
/*Pembuat : M Raditya Novandrian*/

void StatusPesanan(){
    if (headcustomer == NULL){              //Belum Diproses, Sedang Diproses, Selesai
        printf("\n[Tidak Ada Status]");
        return;
    }
    time_t current_time = time(NULL);
    int waktuBerlalu, sisaWaktu, putId;
    struct Customer* pointer = headcustomer;
    while(pointer != NULL){
        waktuBerlalu = (int)(current_time - pointer->startTime);
        sisaWaktu = pointer->durasi - waktuBerlalu;
        if(sisaWaktu <= 0){
            printf("Id: %d Status: [Selesai]: 0 detik\n", pointer->idBayar);
        }
        else if(sisaWaktu > pointer->durasi - 30){
            printf("\nId: %d Status: [Belum Di Proses]: %d detik", pointer->idBayar, sisaWaktu);
        }
        else if(sisaWaktu > 0){
            printf("\nId: %d Status: [Sedang Di Proses]: %d detik", pointer->idBayar, sisaWaktu);
        }
        pointer = pointer->next;
    }
    struct Customer* prevPointer = headcustomer;
    pointer = headcustomer->next;
    printf("\nMasukkan id Pesanan: ");
    scanf("%d", &putId);
    waktuBerlalu = (int)(current_time - prevPointer->startTime);
    sisaWaktu = prevPointer->durasi - waktuBerlalu;

    if(headcustomer->idBayar == putId && sisaWaktu <= 0){
        printf("\nPesanan Selesai Untuk Id(%d)", headcustomer->idBayar);
        Sleep(3000);
        startTimeMeja(putId);
        headcustomer = pointer;
        free(prevPointer);
        return;
    }
    else if(headcustomer->idBayar != putId){
        while(pointer != NULL && pointer->idBayar != putId){
            prevPointer = prevPointer->next;
            pointer = pointer->next;
        }
        if(pointer == NULL){
            printf("Tidak ada id");
            return;
        }
        waktuBerlalu = (int)(current_time - pointer->startTime);
        sisaWaktu = pointer->durasi - waktuBerlalu;
        if (pointer->idBayar == putId && sisaWaktu <= 0){
            printf("\nPesanan Selesai untuk Id(%d)", pointer->idBayar);
            Sleep(3000);
            startTimeMeja(putId);
            prevPointer->next = pointer->next;
            free(pointer);
        }   
        else{
            printf("\n Pesanan Belum Selesai");
        }
    }
    else{
        printf("Pesanan Belum Selesai");
    }
}


/*Nama Modular : addCustomerStatus*/
/*Deskripsi : Untuk menambahkan data customer setelah proses pembayaran*/
/*Pembuat : M Raditya Novandrian*/

struct Customer* addCustomerStatus(){
    int totalOrder = 0;
    struct Customer* customer = malloc(sizeof(struct Customer));
    struct Customer* pointerC = headcustomer;
    struct Order* pointerO = headmenu;
    while(pointerO != NULL){
        totalOrder += pointerO->kuantitas;
        pointerO = pointerO->next;
    }

    customer->idBayar = customerOrder;
    customer->mejaID = tables;
    customer->statusMakanan = 1;
    customer->startTime = time(NULL);
    customer->durasi = totalOrder * durasiPesanan;
    customer->next = NULL;
    if (headcustomer == NULL){
        headcustomer = customer;
        return headcustomer;
    }
    while(pointerC->next != NULL){
        pointerC = pointerC->next;
    }
    pointerC->next = customer;
    return headcustomer;
}


/*Nama Modular : ReservasiMeja*/
/*Deskripsi : Untuk mengambil input dari user untuk reservasi meja*/
/*Pembuat : M Raditya Novandrian*/

void ReservasiMeja(int input[]){
    char confirm;
    int localTable;
    tampilkanMeja(Mejap);
    if(tables != 0){
        printf("\nAnda Telah Reservasi");
        checkMeja(Mejap);
        return;
    }
    printf("\n\nMasukkan Meja no Berapa, [0] untuk cancel: ");
    scanf(" %d", &localTable);
    if (localTable > LENGTH_MEJA || localTable <= 0 || input[localTable-1] == 1){
        printf("\nMeja Tidak Tersedia");
        checkMeja(Mejap);
        localTable = 0;
        return;
    }
    while(1){
        printf("\nApakah Anda Yakin (Y/N): ");
        scanf(" %c", &confirm);
        if(tolower(confirm) == 'y'){
            //struct Tables* IDmeja = malloc(sizeof(struct Tables));
            input[localTable-1] = 1;
            tables = localTable;
            printf("\nOke");
            struct Tables* temp = malloc(sizeof(struct Tables));
            struct Tables* pointer = headtables;

            temp->mejaID = localTable;
            temp->readytoCheck = 0;
            temp->next = NULL;
            if (pointer == NULL){
                headtables = temp;
                break;
            }
            while(pointer->next != NULL){
                pointer = pointer->next;
            }
            pointer->next = temp;
            break;
        }
        else if(tolower(confirm) == 'n'){
            break;
        }
        printf("\nCoba Lagi");
    }
    checkMeja(Mejap);
}


/*Nama Modular : startTimeMeja*/
/*Deskripsi : Untuk memulai timer meja setelah customer mengambil pesanannya*/
/*Pembuat : M Raditya Novandrian*/

void startTimeMeja(int putId){
    struct Tables* pointer = headtables;
    srand(time(NULL));
    if(headtables == NULL){
        return;
    }
    while(pointer->next != NULL && pointer->mejaID != putId){
        pointer = pointer->next;
    }
    if (pointer->mejaID <= LENGTH_MEJA && pointer->mejaID > 0){
        pointer->startTime = time(NULL);
        pointer->durasi= (rand() % 60) + 20;
        pointer->readytoCheck = 1;
    }
}








/*Nama Modular : menuInit*/
/*Deskripsi : Untuk mengambil list menu dari file menu.txt*/
/*Pembuat : M Raditya Novandrian*/

void menuInit(){
    int id;
    char menus[25];
    float harga;
    struct Admin* ptrMenu = NULL;
    FILE* pOpen = fopen("menu.txt", "r");
    fseek(pOpen, 0, SEEK_END);
    int size = ftell(pOpen);
    if(size == 0){
        fclose(pOpen);
        return;
    }
    fclose(pOpen);
    pOpen = fopen("menu.txt", "r");
    while(fscanf(pOpen, "%d %[^\n] %f", &id, menus, &harga) != EOF){    
        struct Admin* temp = malloc(sizeof(struct Admin));
        temp->ID = id;
        strcpy(temp->namemenu, menus);
        temp->price = harga;
        temp->next = NULL;
        if (headadmin == NULL){
            headadmin = temp;
            ptrMenu = headadmin;
        }
        else{
            ptrMenu->next = temp;
            ptrMenu = ptrMenu->next;
        }
    }
    fclose(pOpen);
}

/*Nama Modular : Pembayaran*/
/*Deskripsi : Untuk menampilkan menu pembayaran*/
/*Pembuat : Arman Yusuf Rifandi*/

void Pembayaran(){
    int input;
    int condition = 1;
    while(condition){
        printf("============ Menu Pembayaran ============\n\n");
        printf("1. Cash\n");
        printf("2. Debit\n");
        printf("3. E-Wallet\n");
        printf("4. Exit\n");
        printf("\nMasukkan Input Angka: ");
        scanf("%d", &input);

        switch(input){
            case 1:
                cash();
                condition = 0;                
                break;
            case 2:
                debit();
                condition = 0;                
                break;
            case 3:
                eWallet();
                condition = 0;                
                break;
            case 4:
                condition = 0;
                break;    
            default:
                printf("Nilai di input salah");
                break;
        }
    }    
}


/*Nama Modular : cash*/
/*Deskripsi : Untuk metode pembayaran cash*/
/*Pembuat : Arman Yusuf Rifandi*/


void cash(){
    float uang;
    float totalHarga = 0;

    hitungTotalHarga(&totalHarga);
    ViewOrder(headmenu);
    if(totalHarga == 0){
        return;
    }
    while(1){
        printf("\n\n Masukan uang anda, Ketik [0] jika ingin exit : ");
        scanf("%f", &uang);
        if (uang == 0)
        {
            break;
        }
        else if (totalHarga <= uang)
        {
            uang = uang - totalHarga;
            printf("\nKembalian uang anda: Rp.%.2f", uang);
            printf("\nPembayaran Selesai\n");
            Sleep(2000);
            printf("\nSilakan Tunggu :) (cek di status pesanan)");
            Sleep(3000);
            headcustomer = addCustomerStatus();
            addSales();
            tables = 0;
            break;                
        } else if (totalHarga > uang)
        {
            uang = uang - totalHarga;
            uang = fabs(uang);
            printf("\nAnda membutuhkan Rp%.2f lagi, Ketik [0] jika ingin exit\n", uang);          
        } 
    }
            
}  
        

/*Nama Modular : debit*/
/*Deskripsi : Untuk metode pembayaran debit*/
/*Pembuat : Arman Yusuf Rifandi*/


void debit(){
    float totalHarga = 0;
    int pin;
    printf("Proses...\n");
    Sleep(3000);
    hitungTotalHarga(&totalHarga);
    ViewOrder(headmenu);
    if(totalHarga == 0){
        return;
    }
    while(1){
        printf("\nMasukan Pin Debit, [0] Untuk cancel :");
        scanf("%d", &pin);
            if (pin == 0){
                break;
            }
            if(pin == 112358){
                totalHarga = 0;
                printf("\nPembayaran Selesai\n");
                Sleep(2000);
                printf("\nSilakan Tunggu :) (cek di status pesanan)");
                Sleep(3000);
                headcustomer = addCustomerStatus();
                addSales();
                tables = 0;
                break;
            }else if (pin != 112358){
                printf("\nPin anda salah\n");
            } 
        }
    
}

/*Nama Modular : eWallet*/
/*Deskripsi : Untuk metode pembayaran eWallet*/
/*Pembuat : Arman Yusuf Rifandi*/

void eWallet(){
    float saldo;
    float totalHarga = 0;
    int pin;
    hitungTotalHarga(&totalHarga);
    ViewOrder(headmenu);
    if(totalHarga == 0){
        return;
    }
    while(1){
        printf("\n\n Input saldo anda untuk pembayaran, [0] untuk cancel : ");
        scanf("%f", &saldo);
        if(saldo == 0){
            break;
        }
        else if(saldo == totalHarga){
            break;
        }
        else if (saldo >= totalHarga)
        {
            float tip = saldo - totalHarga;
            printf("\nTerima kasih atas tip %.2f nya", tip);
            break;
        }
        printf("\nSaldo Anda Kurang\n");
    }
    
    while(1){
        printf("\nMasukan Pin E-Wallet, [0] Untuk cancel: ");
        scanf("%d", &pin);
        if(pin == 0){
            break;
        }
            if(pin == 112358){
                printf("\nPembayaran Selesai\n");
                Sleep(2000);
                printf("\nSilakan Tunggu :) (cek di status pesanan)");
                Sleep(3000);
                headcustomer = addCustomerStatus();
                addSales();
                tables = 0;
                break;
            }else if (pin != 112358){
                printf("\nPin anda salah\n");
            } 
        }
}


/*Nama Modular : hitungTotalHarga*/
/*Deskripsi : Untuk menghitung total harga menu yang diorder customer */
/*Pembuat : M Raditya Novandrian*/

void hitungTotalHarga(float* harga){
    struct Order* tempHarga = headmenu;
    while(tempHarga != NULL){
        *harga += tempHarga->totalPrice;
        tempHarga = tempHarga->next;
    }
}


