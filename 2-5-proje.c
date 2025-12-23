#include <stdio.h>
#include <stdlib.h>

struct Ogrenci
{
    char ad[30];
    char soyad[30];
    float ort;
    float ales;
    float uds;
    float toplam; 
};

int main(){
    struct Ogrenci *ogr = NULL; //Ogrenci türünde dinamik bir dizi oluşturmak için pointer tanımladık. Henüz öğrenci yok. Ogrenci sayısı başta bilinmediği için dinamik bellek yöntemi kullanıldı. 
    struct Ogrenci gecici;
    int n = 0; //Dizide 0 eleman var.
    
    FILE *dosya1 = fopen("ogrenci.txt", "r");
    if (dosya1 == NULL)
    {
        printf("ogrenci.txt dosyasi acilamadi!\n");
        return 1;
    }

    FILE *dosya2 = fopen("kazanan.txt", "w");
    if (dosya2 == NULL)
    {
        printf("kazanan.txt dosyasi olusturulamadi!\n");
        return 1;
    }

    while (fscanf(dosya1, "%s %s %f %f %f",
         gecici.ad, 
         gecici.soyad, 
         &gecici.ort, 
         &gecici.ales, 
         &gecici.uds) != EOF) //fscanf ile struct diziyi oku. EOF=End Of File
    {
        if (n == 0)
        {
            ogr = (struct Ogrenci *)malloc(sizeof(struct Ogrenci)); //Struct Ogrenci * => malloc'un dönderdiği adres struct Ogrenci * olarak kullanılır.
        }

        else
        {
            ogr = (struct Ogrenci *)realloc(ogr, (n+1) * sizeof(struct Ogrenci));
        }

        if (ogr == NULL)
        {
            printf("Bellek ayirma hatasi!\n");
            fclose(dosya1);
            fclose(dosya2);
            return 1;
        }

        ogr[n] = gecici;
        n++;
    }

    if (n == 0)
    {
        printf("Dosyada ogrenci bulunamadi\n");
        fclose(dosya1);
        fclose(dosya2);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        ogr[i].toplam = (ogr[i].ort * 0.25) + (ogr[i].ales * 0.50) + (ogr[i].uds * 0.25);
    }

    for (int i = 0; i < (n - 1); i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ogr[j].toplam > ogr[i].toplam)
            {
                struct Ogrenci temp;
                temp = ogr[i];
                ogr[i] = ogr[j];
                ogr[j] = temp;
            }
        }
    }
   
     fprintf(dosya2, "%-10s %-10s %-10s %-10s %-10s %-10s\n",
        "Ad", "Soyad", "Ortalama", "ALES", "UDS", "Toplam");

    for (int i = 0; i < 5; i++)
    {
        fprintf(dosya2, "%-10s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
        ogr[i].ad,
        ogr[i].soyad,-
        ogr[i].ort,
        ogr[i].ales,
        ogr[i].uds,
        ogr[i].toplam);
    }

    free(ogr);
    fclose(dosya1);
    fclose(dosya2);
    
    return 0;
}   