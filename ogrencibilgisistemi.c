#include <stdio.h>
#include <stdlib.h>

// Öðrenci bilgi yapýsý
struct Ogrenci {
    int numara;
    char ad[50];
    char soyad[50];
    float not_ort;
};

// Fonksiyon prototipleri
void menuGoster();
void ogrenciBilgileriGuncelle(struct Ogrenci *ogrenci);
void ogrenciDosyayaYaz(struct Ogrenci *ogrenci);
void ogrenciDosyadanOku();
void ogrenciEkle();
void ogrenciListele();
void ogrenciGuncelle();
void ogrenciSil();

int main() {
    char secim;

    do {
        menuGoster();
        scanf(" %c", &secim);

        switch (secim) {
            case '1':
                ogrenciEkle();
                break;
            case '2':
                ogrenciListele();
                break;
            case '3':
                ogrenciGuncelle();
                break;
            case '4':
                ogrenciSil();
                break;
            case 'Q':
            case 'q':
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
        }

    } while (secim != 'Q' && secim != 'q');

    return 0;
}

// Menüyü gösteren fonksiyon
void menuGoster() {
    printf("\n--- Ogrenci Bilgi Sistemi ---\n");
    printf("1. Ogrenci Ekle\n");
    printf("2. Ogrenci Listele\n");
    printf("3. Ogrenci Guncelle\n");
    printf("4. Ogrenci Sil\n");
    printf("Q. Cikis\n");
    printf("Secim: ");
}

// Öðrenci bilgilerini güncelleyen fonksiyon
void ogrenciBilgileriGuncelle(struct Ogrenci *ogrenci) {
    printf("Ad: ");
    scanf("%s", ogrenci->ad);

    printf("Soyad: ");
    scanf("%s", ogrenci->soyad);

    printf("Not Ortalamasi: ");
    scanf("%f", &ogrenci->not_ort);
}

// Öðrenci bilgilerini dosyaya yazan fonksiyon
void ogrenciDosyayaYaz(struct Ogrenci *ogrenci) {
    FILE *dosya = fopen("ogrenci_bilgileri.txt", "a");

    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        exit(1);
    }

    fprintf(dosya, "%d %s %s %.2f\n", ogrenci->numara, ogrenci->ad, ogrenci->soyad, ogrenci->not_ort);

    fclose(dosya);
}

// Öðrenci bilgilerini dosyadan okuyan fonksiyon
void ogrenciDosyadanOku() {
    struct Ogrenci okunanOgrenci;
    FILE *dosya = fopen("ogrenci_bilgileri.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        exit(1);
    }

    printf("\n--- Ogrenci Listesi ---\n");
    printf("No  Ad Soyad   Not Ort\n");
    printf("----------------------\n");

    while (fscanf(dosya, "%d %s %s %f", &okunanOgrenci.numara, okunanOgrenci.ad, okunanOgrenci.soyad, &okunanOgrenci.not_ort) != EOF) {
        printf("%-4d%-10s%-10s%-5.2f\n", okunanOgrenci.numara, okunanOgrenci.ad, okunanOgrenci.soyad, okunanOgrenci.not_ort);
    }

    fclose(dosya);
}

// Yeni öðrenci ekleyen fonksiyon
void ogrenciEkle() {
    struct Ogrenci yeniOgrenci;

    printf("Ogrenci Numarasi: ");
    scanf("%d", &yeniOgrenci.numara);

    ogrenciBilgileriGuncelle(&yeniOgrenci);

    ogrenciDosyayaYaz(&yeniOgrenci);

    printf("Ogrenci basariyla eklendi.\n");
}

// Öðrenci listesini gösteren fonksiyon
void ogrenciListele() {
    ogrenciDosyadanOku();
}

// Öðrenci bilgilerini güncelleyen fonksiyon
void ogrenciGuncelle() {
    struct Ogrenci guncelOgrenci;

    int guncellenecekNumara;
    printf("Guncellenecek Ogrenci Numarasi: ");
    scanf("%d", &guncellenecekNumara);

    FILE *dosya = fopen("ogrenci_bilgileri.txt", "r");
    FILE *tempDosya = fopen("temp.txt", "w");

    if (dosya == NULL || tempDosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        exit(1);
    }

    int ogrenciVar = 0;

    while (fscanf(dosya, "%d %s %s %f", &guncelOgrenci.numara, guncelOgrenci.ad, guncelOgrenci.soyad, &guncelOgrenci.not_ort) != EOF) {
        if (guncelOgrenci.numara == guncellenecekNumara) {
            ogrenciBilgileriGuncelle(&guncelOgrenci);
            fprintf(tempDosya, "%d %s %s %.2f\n", guncelOgrenci.numara, guncelOgrenci.ad, guncelOgrenci.soyad, guncelOgrenci.not_ort);
            printf("Ogrenci basariyla guncellendi.\n");
            ogrenciVar = 1;
        } else {
            fprintf(tempDosya, "%d %s %s %.2f\n", guncelOgrenci.numara, guncelOgrenci.ad, guncelOgrenci.soyad, guncelOgrenci.not_ort);
        }
    }

    fclose(dosya);
    fclose(tempDosya);

    // Eðer öðrenci numarasý bulunamazsa temp dosyasýný sil
    if (!ogrenciVar) {
        remove("temp.txt");
    } else {
        // temp dosyasýný asýl dosya ile deðiþtir
        remove("ogrenci_bilgileri.txt");
        rename("temp.txt", "ogrenci_bilgileri.txt");
    }
}

// Öðrenci bilgilerini silen fonksiyon
void ogrenciSil() {
    struct Ogrenci silinecekOgrenci;

    int silinecekNumara;
    printf("Silinecek Ogrenci Numarasi: ");
    scanf("%d", &silinecekNumara);

    FILE *dosya = fopen("ogrenci_bilgileri.txt", "r");
    FILE *tempDosya = fopen("temp.txt", "w");

    if (dosya == NULL || tempDosya == NULL) {
        printf("Dosya acilirken bir hata olustu.\n");
        exit(1);
    }

    int ogrenciVar = 0;

    while (fscanf(dosya, "%d %s %s %f", &silinecekOgrenci.numara, silinecekOgrenci.ad, silinecekOgrenci.soyad, &silinecekOgrenci.not_ort) != EOF) {
        if (silinecekOgrenci.numara == silinecekNumara) {
            printf("Ogrenci '%s %s' basariyla silindi.\n", silinecekOgrenci.ad, silinecekOgrenci.soyad);
            ogrenciVar = 1;
        } else {
            fprintf(tempDosya, "%d %s %s %.2f\n", silinecekOgrenci.numara, silinecekOgrenci.ad, silinecekOgrenci.soyad, silinecekOgrenci.not_ort);
        }
    }

    fclose(dosya);
    fclose(tempDosya);

    // Eðer öðrenci numarasý bulunamazsa temp dosyasýný sil
    if (!ogrenciVar) {
        remove("temp.txt");
    } else {
        // temp dosyasýný asýl dosya ile deðiþtir
        remove("ogrenci_bilgileri.txt");
        rename("temp.txt", "ogrenci_bilgileri.txt");
    }
}
