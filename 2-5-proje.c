#include <stdio.h>
#include <stdlib.h>

// Öğrenci bilgilerini tutan yapı
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
    struct Ogrenci *ogr = NULL; // Dinamik öğrenci dizisi (başlangıçta boş)
    struct Ogrenci gecici; // Dosyadan okuma için geçici değişken
    int n = 0; // Okunan öğrenci sayısı
    
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
        fclose(dosya1);
        return 1;
    }

    // Dosyadan öğrenci bilgileri satır satır okunur. EOF =  End Of File
    while (fscanf(dosya1, "%s %s %f %f %f",
         gecici.ad, 
         gecici.soyad, 
         &gecici.ort, 
         &gecici.ales, 
         &gecici.uds) != EOF)
    {
        if (n == 0)
        {
            // İlk öğrenci için malloc ile bellek ayrılır.
            ogr = (struct Ogrenci *)malloc(sizeof(struct Ogrenci)); 
        }

        else
        {
            // Sonraki öğrenciler için realloc ile bellek genişletilir.
            ogr = (struct Ogrenci *)realloc(ogr, (n+1) * sizeof(struct Ogrenci));
        }

        if (ogr == NULL)
        {
            printf("Bellek ayirma hatasi!\n");
            fclose(dosya1);
            fclose(dosya2);
            return 1;
        }

        ogr[n] = gecici; // Geçici değişkende tutulan öğrenci diziye aktarılır.
        n++; //Öğrenci sayısı artırılır.
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
        // Her öğrenci için toplam puan hesaplanır.
        ogr[i].toplam = (ogr[i].ort * 0.25) + (ogr[i].ales * 0.50) + (ogr[i].uds * 0.25);
    }

    // Öğrenciler toplam puana göre büyükten küçüğe sıralanır.
    for (int i = 0; i < (n - 1); i++) // i: Her adımda sırası kesinleşen öğrencinin dizideki indeksini tutar.
    {
        for (int j = i + 1; j < n; j++)  // j: i indeksindeki öğrenciyi, kendisinden sonraki tüm öğrencilerle karşılaştırır.
        {
            if (ogr[j].toplam > ogr[i].toplam) // Eğer j indeksindeki öğrencinin toplam puanı i indeksindeki puandan daha büyükse yer değiştirirler
            {
                struct Ogrenci temp;  // Öğrencilerin yerini değiştirmek için geçici değişken
                temp = ogr[i];
                ogr[i] = ogr[j];
                ogr[j] = temp;
            }
        }
    }
   
    // Dosyaya başlık satırı yazılır.
     fprintf(dosya2, "%-10s %-10s %-10s %-10s %-10s %-10s\n",
        "Ad", "Soyad", "Ortalama", "ALES", "UDS", "Toplam");

    // En yüksek puanlı ilk 5 öğrenci dosyaya yazılır.
    for (int i = 0; i < 5; i++)
    {
        fprintf(dosya2, "%-10s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
        ogr[i].ad,
        ogr[i].soyad,
        ogr[i].ort,
        ogr[i].ales,
        ogr[i].uds,
        ogr[i].toplam);
    }

    free(ogr);  // Ayrılan bellek serbest bırakılır.

    //Dosyalar kapatılır.
    fclose(dosya1);
    fclose(dosya2);
    
    return 0;
}   