#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_DERS 5
#define MAX_OGRENCI 25

typedef struct Ogrenci {
    int numara;
    char tc[12];
    char ad[50];
    char soyad[50];
    char bolum[50];
    char dersler[MAX_DERS][50];
    struct Ogrenci* prev;
    struct Ogrenci* next;
} Ogrenci;

Ogrenci* Start = NULL;

// Ogrenci ekleme
void ogrenciEkle() {
    Ogrenci* New = (Ogrenci*)malloc(sizeof(Ogrenci));
    printf("OGRENCI EKLEME\n\n");
    printf("Numara: "); scanf("%d", &New->numara);
    printf("TC: "); scanf("%s", New->tc);
    printf("Ad: "); scanf("%s", New->ad);
    printf("Soyad: "); scanf("%s", New->soyad);
    printf("Bolum: "); scanf("%s", New->bolum);
    printf("En fazla %d ders girin:\n", MAX_DERS);
    int i;
    for (i = 0; i < MAX_DERS; i++) {
        printf("Ders %d (yoksa '-' yazin): ", i + 1);
        scanf("%s", New->dersler[i]);
        if (strcmp(New->dersler[i], "-") == 0) {
            strcpy(New->dersler[i], "");
        }
    }
    New->prev = NULL;
    New->next = NULL;

    if (Start == NULL) {
        Start = New;
    } else {
        Ogrenci* tmp = Start;
        while (tmp->next != NULL) tmp = tmp->next;
        tmp->next = New;
        New->prev = tmp;
    }
    printf("\n\n"); 
}

// Ogrencileri listele
void ogrencileriListele() {
    Ogrenci* tmp = Start;
    printf("OGRENCI LISTESI\n");
    if (tmp == NULL) {
        printf("Liste bos.\n");
        return;
    }
    while (tmp != NULL) {
        printf("\nNumara: %d\nAd: %s %s\nBolum: %s\nTC: %s\nDersler: ",
            tmp->numara, tmp->ad, tmp->soyad, tmp->bolum, tmp->tc);
            int i;
        for (i = 0; i < MAX_DERS; i++) {
            if (strlen(tmp->dersler[i]) > 0)
                printf("%s ", tmp->dersler[i]);
        }
        printf("\n");
        tmp = tmp->next;
    }
    printf("\n\n"); 
}

// Veri Yapilari alan ogrenciler
void veriYapilariAlanlar() {
    Ogrenci* tmp = Start;
    int bulundu = 0;
    printf("VERI YAPILARI ALAN OGRENCI SORGUSU\n\n");
    while (tmp != NULL) {
        int i;
        for (i = 0; i < MAX_DERS; i++) {
            if (strcmp(tmp->dersler[i], "VeriYapilari") == 0) {
                printf("Numara: %d, Ad: %s %s\n", tmp->numara, tmp->ad, tmp->soyad);
                bulundu = 1;
                break;
            }
        }
        tmp = tmp->next;
    }

    if (!bulundu) {
        printf("Bu dersi alan ogrenci bulunamadi.\n");
    }
    printf("\n\n");
}

// Isme gore sirala
void isimSirala() {
    if (Start == NULL) return;
    int swapped;
    Ogrenci* ptr1;
    Ogrenci* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = Start;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->ad, ptr1->next->ad) > 0) {
                int tempNumara = ptr1->numara;
                char tempTC[12], tempAd[50], tempSoyad[50], tempBolum[50], tempDers[MAX_DERS][50];
                strcpy(tempTC, ptr1->tc);
                strcpy(tempAd, ptr1->ad);
                strcpy(tempSoyad, ptr1->soyad);
                strcpy(tempBolum, ptr1->bolum);
                int i;
                for (i = 0; i < MAX_DERS; i++) {
                    strcpy(tempDers[i], ptr1->dersler[i]);
                }

                ptr1->numara = ptr1->next->numara;
                strcpy(ptr1->tc, ptr1->next->tc);
                strcpy(ptr1->ad, ptr1->next->ad);
                strcpy(ptr1->soyad, ptr1->next->soyad);
                strcpy(ptr1->bolum, ptr1->next->bolum);
                for (i = 0; i < MAX_DERS; i++) {
                    strcpy(ptr1->dersler[i], ptr1->next->dersler[i]);
                }

                ptr1->next->numara = tempNumara;
                strcpy(ptr1->next->tc, tempTC);
                strcpy(ptr1->next->ad, tempAd);
                strcpy(ptr1->next->soyad, tempSoyad);
                strcpy(ptr1->next->bolum, tempBolum);
                for (i = 0; i < MAX_DERS; i++) {
                    strcpy(ptr1->next->dersler[i], tempDers[i]);
                }

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("ISME GORE SIRALAMA TAMAMLANDI.\n\n\n");
}

// Quick sort icin ders aliyor mu kontrolu
int dersAliyorMu(Ogrenci* ogr, const char* ders1, const char* ders2) {
    int v = 0, a = 0, i;
    for (i = 0; i < MAX_DERS; i++) {
        if (strcmp(ogr->dersler[i], ders1) == 0) v = 1;
        if (strcmp(ogr->dersler[i], ders2) == 0) a = 1;
    }
    return v && a;
}

// Quick sort fonksiyonu
void quickSort(Ogrenci** arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high]->numara;
        int i = low - 1, j;
        for (j = low; j < high; j++) {
            if (arr[j]->numara < pivot) {
                i++;
                Ogrenci* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Ogrenci* temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Quick sort yapildiktan sonra siralama
void quickSirala() {
    Ogrenci* tmp = Start;
    Ogrenci* filtreli[MAX_OGRENCI];
    int sayac = 0;

    while (tmp != NULL) {
        if (dersAliyorMu(tmp, "VeriYapilari", "AlgoritmaAnalizi")) {
            filtreli[sayac++] = tmp;
        }
        tmp = tmp->next;
    }
    printf("VERI YAPILARI VE ALGORITMA ANALIZI ALAN OGRENCILERI NUMARAYA GORE QUICK SORT ILE SIRALAMA\n\n");
    if (sayac == 0) {
        printf("Bu dersi alan ogrenci bulunamadi.\n");
        return;
    }

    quickSort(filtreli, 0, sayac - 1);

    printf("Quick Sort Sonucu :\n");
    int i;
    for (i = 0; i < sayac; i++) {
        printf("Numara: %d, Ad: %s %s\n", filtreli[i]->numara, filtreli[i]->ad, filtreli[i]->soyad);
    }  
    printf("\n\n\n");   
}

// Otomatik ogrenci ekleme
void otomatikOgrenciEkle() {
    char* isimler[10] = {"Ahmet", "Zeynep", "Mehmet", "Ayse", "Ali", "Elif", "Murat", "Deniz", "Can", "Sude"};
    char* soyadlar[10] = {"Yilmaz", "Demir", "Kaya", "Celik", "Aydin", "Tas", "Kaplan", "Gunes", "Yildiz", "Polat"};
    char* bolumler[5] = {"Bilgisayar", "Elektrik", "Makine", "Insaat", "Endustri"};
    char* dersler[] = {"VeriYapilari", "AlgoritmaAnalizi", "AyrikIslemsel", "VeriAnalizi", "Olasilik"};
    int i;
    for (i = 0; i < 25; i++) {
        Ogrenci* New = (Ogrenci*)malloc(sizeof(Ogrenci));
        New->numara = 1000 + i;
        snprintf(New->tc, sizeof(New->tc), "11111111%1d", i+100);
        strcpy(New->ad, isimler[i % 10]);
        strcpy(New->soyad, soyadlar[(i * 3) % 10]);
        strcpy(New->bolum, bolumler[i % 5]);
        int j;
        for (j = 0; j < MAX_DERS; j++) {
            strcpy(New->dersler[j], dersler[(i + j) % 5]);
        }

        New->prev = NULL;
        New->next = NULL;

        if (Start == NULL) {
            Start = New;
        } else {
            Ogrenci* tmp = Start;
            while (tmp->next != NULL) tmp = tmp->next;
            tmp->next = New;
            New->prev = tmp;
        }
    }
    printf("OTOMATIK OLARAK 25 OGRENCI EKLENDI!\n\n");
    printf("\n"); 
}

// Ana menu
int main() {
    int secim;
    do {
        printf("------------\n");
        printf("--- MENU ---\n\n");
        printf("1 - Ogrenci Ekle\n");
        printf("2 - Tum Ogrencileri Listele\n");
        printf("3 - Sadece VeriYapilari Alanlari Listele\n");
        printf("4 - Isimlere Gore Sirala (A-Z)\n");
        printf("5 - VeriYapilari ve AlgoritmaAnalizi Alanlari QuickSort (Numaraya Gore)\n");
        printf("6 - Otomatik 25 Ogrenci Ekle\n");
        printf("0 - Cikis\nSecim: ");
        scanf("%d", &secim);
        switch (secim) {
            case 1: system("cls"); ogrenciEkle(); break;
            case 2: system("cls"); ogrencileriListele(); break;
            case 3: system("cls"); veriYapilariAlanlar(); break;
            case 4: system("cls"); isimSirala(); ogrencileriListele(); break;
            case 5: system("cls"); quickSirala(); break;
            case 6: system("cls"); otomatikOgrenciEkle(); break;
        }
    } while (secim != 0);
    return 0;
}