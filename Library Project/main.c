/*Mehmet Ali Yildiz*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
typedef struct Kitap{
int Barkod;
char Isim[30];
char Yazar[30];
int Sayfa;
int StokSayisi;
}Kitap;

typedef struct Kullanici{
 int KullaniciNo;
    char Ad[25];
    char Soyad[25];
    char DogumTarihi[15];
}Kullanici;

typedef struct Odunc{
int KullaniciNo;
int Barkod;
char BaslangicTarihi[15];
char BitisTarihi[15];
}Odunc;

void KitapIslemleri();
void KitapEkle();
void KitapSil();
void KitapListele();
void KitapGuncelleme();
void KitapArama();

void KullaniciIslemleri();
void KullaniciEkle();
void KullaniciSil();
void KullaniciListele();
void KullaniciGuncelleme();
void KullaniciArama();

void OduncAlmaIslemleri();
void OduncKitapAl();
void OduncKitapVer();
void OduncKitapListele();
void StokGuncelle();

int menu()
{
    int Secim;
printf("\n\t Kutuphane Otomasyonu \n\n");
printf("\t1:Kitap Islemleri\n");
printf("\t2:Kullanici Islemleri\n");
printf("\t3:Odunc Alma Islemleri\n");
printf("\t0:Programi Kapat\n\n");
printf("\tSeciminiz :");
scanf("%d",&Secim);
return Secim;
}
int main()
{
  int Secim=menu();
while(Secim!=0)
{
  switch(Secim){
 case 1:KitapIslemleri(); break;
 case 2:KullaniciIslemleri(); break;
 case 3:OduncAlmaIslemleri(); break;
 default: printf("Hatali Secim Yaptiniz !!\n"); break;
 return 0;
  }
Secim=menu();
}
printf("\nProgrami Kapatiniz:)\n");
return 0;
}

void KitapIslemleri()
{
    system("cls");
    printf("Kitap Islemleri Ekrani:\n\n");
int Secim;
    printf("1:Kitap Ekleme\n");
     printf("2:Kitap Silme\n");
     printf("3:Kitap Listele\n");
     printf("4:Kitap Guncelleme\n");
    printf("5:Kitap Arama\n");
    printf("0:Ana Menuye Don\n");
    printf("Seciminiz:"); scanf("%d",&Secim);

    switch(Secim){
    case 1:KitapEkle(); break;
    case 2:KitapSil(); break;
    case 3:KitapListele(); break;
    case 4:KitapGuncelleme(); break;
    case 5:KitapArama(); break;
    case 0: break;
    default: printf("Hatali Secim Yaptiniz, Ana Menuye Yonlendiriliyorsunuz..."); break;
    }
}
void KitapEkle(){

srand(time(NULL));
system("cls");
printf("Kitap Ekleme Ekrani:\n\n");
Kitap b1;
b1.Barkod=rand()%100000+1;
printf("Isim:"); scanf("%s",b1.Isim);
printf("Yazar:"); scanf("%s",b1.Yazar);
printf("Sayfa Sayisi:"); scanf("%d",&b1.Sayfa);
printf("Stok Sayisi:"); scanf("%d",&b1.StokSayisi);

FILE* ptr=fopen("kitaplar.txt","a+b");
fwrite(&b1,sizeof(Kitap),1,ptr);
fclose(ptr);
printf("Kitap Kaydi Tamamlandi:)\n");
}

void KitapSil(){

system("cls");
printf("Kitap Silme Ekrani:\n\n");
Kitap b1;
int Barkod, sonuc=0;
printf("Barkod:"); scanf("%d",&Barkod);

FILE* ptr=fopen("kitaplar.txt","r+b");
FILE* yptr=fopen("yedek.txt","w+b");

while ( fread( &b1, sizeof(Kitap), 1, ptr) != 0 ){

        if(Barkod!=b1.Barkod){
    fwrite(&b1,sizeof(Kitap), 1 ,yptr);
        }
    else
    sonuc=1;
}
fclose(ptr);
fclose(yptr);
if(sonuc==0)
{
printf("%d barkod numarali kitap bulunamadi:(\n",Barkod);
}
else{

    remove("kitaplar.txt");
    rename("yedek.txt", "kitaplar.txt");
    printf("%d barkod numarali kitap silindi:\n",Barkod);
}
}

void KitapListele(){
system("cls");
    printf("Kitap Listeleme Ekrani:\n\n");
Kitap b1;
FILE* ptr=fopen("kitaplar.txt","r+b");

printf("%-20s%-30s%-20s%-20s%-20s\n","BARKOD","Isim","Yazar","SAYFA","Stok Sayisi");

while (fread(&b1,sizeof(Kitap),1,ptr)!=0 )
{
printf("%-20d%-30s%-20s%-20d%10d\n",b1.Barkod,b1.Isim,b1.Yazar,b1.Sayfa,b1.StokSayisi);
}
fclose(ptr);
}

void KitapGuncelleme(){
system("cls");
Kitap b1;
int BarkodNo;
FILE* ptr=fopen("kitaplar.txt","r+b");
printf("\nGuncellenecek Kullanicinin Numarasini Giriniz:\n"); scanf("%d",&BarkodNo);
while(fread(&b1.Barkod,sizeof(Kitap),1,ptr)!=0){
    if(strcmp(&b1.Barkod,&BarkodNo)==0){                                  //karsilastirma
        printf("Kitabin Yeni Ismini Giriniz:"); scanf("%s",b1.Isim);
        printf("Kitabin Yazarini Giriniz:"); scanf("%s",b1.Yazar);
        printf("Sayfa Sayisini Giriniz:"); scanf("%d",&b1.Sayfa);
        printf("Stok Sayisini Giriniz:"); scanf("%d",&b1.StokSayisi);
        fseek(ptr,-sizeof(Kitap),SEEK_CUR);
        fwrite(&b1.Barkod,sizeof(Kitap),1,ptr);
        printf("Kitap Bilgileri Guncellendi:\n");
        fclose(ptr);
return;
}
else{
    printf("\n Kitap Bulunamadi !:\n");
} } }

void KitapArama(){
system("cls");
Kitap b1;
char arama[20];
   printf("\nKitabin Ismini Giriniz:\n");scanf("%s",arama);
   FILE* ptr=fopen("kitaplar.txt","r+b");
fread(&b1,sizeof(Kitap),1,ptr);
if(strstr(b1.Isim,arama)!=NULL){                    //arama
    printf("\n%s Isimli Kitap Bulundu:\n",arama);
   }
   else{
    printf("%s Isimli Kitap Bulunamadi:\n",arama);
   }
fclose(ptr);
}


void KullaniciIslemleri()
{
 system("cls");
    printf("Kullanici Islemleri Ekrani:\n\n");
int Secim;
    printf("1:Kullanici Ekleme\n");
     printf("2:Kullanici Silme\n");
     printf("3:KullaniciListele\n");
     printf("4:Kullanici Guncelleme\n");
    printf("5:Kullanici Arama\n");
    printf("0:Ana Menuye Don\n");
    printf("Seciminiz:"); scanf("%d",&Secim);

    switch(Secim){

    case 1:KullaniciEkle(); break;
    case 2:KullaniciSil(); break;
    case 3:KullaniciListele(); break;
    case 4:KullaniciGuncelleme(); break;
    case 5:KullaniciArama(); break;
    case 0: break;
    default: printf("Hatali Secim Yaptiniz, Ana Menuye Yonlendiriliyorsunuz..."); break;
    }
}
void KullaniciEkle(){

srand(time(NULL));
system("cls");
    printf("Kullanici Ekleme Ekrani:\n\n");
Kullanici k1;
k1.KullaniciNo=rand()%100000+1;
printf("Adi:"); scanf("%s",k1.Ad );
printf("Soyadi:"); scanf("%s",k1.Soyad);
printf("Dogum Tarihi:"); scanf("%s",k1.DogumTarihi);

FILE* ptr=fopen("kullanicilar.txt","a+b");
fwrite(&k1,sizeof(Kullanici),1,ptr);
fclose(ptr);
printf("Kullanici Kaydi Tamamlandi:)\n");
}

void KullaniciSil(){
system("cls");
    printf("Kullanici Silme Ekrani:\n\n");
Kullanici k1;
int KullaniciNo, sonuc=0;
printf("Kullanici Numarasi:"); scanf("%d",&KullaniciNo);

FILE* ptr=fopen("kullanicilar.txt","r+b");
FILE* yptr=fopen("yedek.txt","w+b");

while (fread(&k1,sizeof(Kullanici),1, ptr)!= 0 )
{
        if(KullaniciNo!=k1.KullaniciNo){
    fwrite(&k1,sizeof(Kullanici),1,yptr);
        }
    else
    sonuc=1;
}
fclose(ptr);
fclose(yptr);
if(sonuc==0)
{
printf("\n%d Kullanici numarali kisi bulunamadi:(\n",KullaniciNo);
}
else{
    remove("kullanicilar.txt");
    rename("yedek.txt", "kullanicilar.txt");
    printf("\n%d Kullanici numarali kisi silindi:\n",KullaniciNo);
}
}

void KullaniciListele(){
system("cls");
    printf("Kullanici Listeleme Ekrani:\n\n");
Kullanici k1;
FILE* ptr=fopen("kullanicilar.txt","r+b");

printf(" %-30s%-20s%-20s%-20s\n","Kullanici Numarasi","Adi","Soyadi","Dogum Tarihi");

while (fread(&k1,sizeof(Kullanici),1,ptr)!= 0 )
{
printf(" %-30d%-20s%-20s%-20s\n",k1.KullaniciNo,k1.Ad,k1.Soyad,k1.DogumTarihi);
}
fclose(ptr);
}

void KullaniciGuncelleme(){
    system("cls");
Kullanici k1;
int No;
FILE* ptr=fopen("kullanicilar.txt","r+b");
printf("\nGuncellenecek Kullanicinin Numarasini Giriniz:\n"); scanf("%d",&No);
while(fread(&k1.KullaniciNo,sizeof(Kullanici),1,ptr)!=0){
    if(strcmp(&k1.KullaniciNo,&No)==0){
        printf("Kullanici Yeni Adini Giriniz:"); scanf("%s",k1.Ad);
        printf("Kullanicinin Yeni Soyadini Giriniz:"); scanf("%s",k1.Soyad);
        printf("Yeni Dogum Tarihini Giriniz:"); scanf("%s",k1.DogumTarihi);
        fseek(ptr,-sizeof(Kullanici),SEEK_CUR);
        fwrite(&k1.KullaniciNo,sizeof(Kullanici),1,ptr);
        printf("Kullanici Bilgileri Guncellendi:\n");
        fclose(ptr);
return;
}
else{
    printf("\n Kullanici Bulunamadi !:\n");
} } }

void KullaniciArama(){
system("cls");
Kullanici k1;
char arama[25];
   printf("\nKullanicinin Adini Giriniz:\n");scanf("%s",arama);
   FILE* ptr=fopen("kullanicilar.txt","r+b");
fread(&k1,sizeof(Kullanici),1,ptr);
if(strstr(k1.Ad,arama)!=NULL){
    printf("\n%s Isimli Kullanici Bulundu:\n",arama);
   }
   else{
    printf("\n%s Isimli Kullanici Bulunamadi:\n",arama);
   }
fclose(ptr);
}


void StokGuncelle(int Barkod ,int sayi){                       // **********************

Kitap b1;
int sayac=0;
FILE* ptr=fopen("kitaplar.txt","r+b");

while (fread(&b1,sizeof(Kitap),1,ptr)!=0 ){

   if(Barkod==b1.Barkod){
    break;
    sayac++;}
}

fseek(ptr,(sayac)*sizeof(Kitap),0);
b1.StokSayisi+=sayi;
fwrite(&b1,sizeof(Kitap),1,ptr);
fclose(ptr);
printf("\nStok Guncellendi:\n");
}

void OduncAlmaIslemleri()
{
system("cls");
    printf("Odunc Alma Islemleri Ekrani:\n\n");
int Secim;
    printf("1:Odunc Kitap Alma\n");
     printf("2:Odunc Kitap Verme\n");
     printf("3:OduncKitapListele\n");
    printf("0:Ana Menuye Don\n");
    printf("Seciminiz:"); scanf("%d",&Secim);

    switch(Secim){
    case 1:OduncKitapAl(); break;
    case 2:OduncKitapVer(); break;
    case 3:OduncKitapListele(); break;
    case 0: break;
    default: printf("Hatali Secim Yaptiniz, Ana Menuye Yonlendiriliyorsunuz..."); break;
    }
}

void OduncKitapAl(){
system("cls");
printf("Odunc Kitap Alma ekrani:");
Odunc o1;
Kitap b1;
Kullanici k1;
int ksonuc=0,bsonuc=0;

printf("\nKullanici Numarasi:"); scanf("%d",&o1.KullaniciNo);
printf("Barkod Numarasi:"); scanf("%d",&o1.Barkod);

FILE* kptr=fopen("Kullanicilar.txt","r+b");

while (fread(&k1,sizeof(Kullanici),1,kptr)!=0 ){

   if(o1.KullaniciNo==k1.KullaniciNo) {
    ksonuc=1;
    break;
   }
}
fclose(kptr);
if(ksonuc==0){
    printf("%d kullanici numarali kisi yok,ana menuye yonlendiriliyorsunuz:\n",o1.KullaniciNo);
    return ;
}
FILE* bptr=fopen("Kitaplar.txt","r+b");

while (fread(&b1,sizeof(Kitap),1,bptr)!=0 ){

   if(o1.Barkod==b1.Barkod) {
    bsonuc=1;
    break;
   }
}
fclose(bptr);
if(bsonuc==0){
    printf("%d Barkod numarali kitap yok,ana menuye yonlendiriliyorsunuz:\n",o1.Barkod);
    return ;
}
if(b1.StokSayisi<1){
    printf("%d Barkod numarali kitap stokta kalmamistir! Ana menuye yonlendiriliyorsunuz:",o1.Barkod);
    return ;
}
FILE* ptr=fopen("Oduncler.txt","a+b");
printf("Baslangic Tarihi:"); scanf("%s",o1.BaslangicTarihi);
printf("Bitis Tarihi:"); scanf("%s",o1.BitisTarihi);
fwrite(&o1,sizeof(Odunc),1,bptr);
fclose(ptr);
printf("\nOdunc Alma Kaydi tamamlandi:\n");
StokGuncelle(o1.Barkod,-1);
}

void OduncKitapVer(){
system("cls");
printf("Odunc Kitap Geri Verme ekrani:");
Odunc o1;
Kitap b1;
Kullanici k1;
int sonuc=0;
int KullaniciNo,Barkod;

printf("\nKullanici Numarasi:"); scanf("%d",&KullaniciNo);
printf("Barkod Numarasi:"); scanf("%d",&Barkod);

FILE* ptr=fopen("Oduncler.txt","r+b");

while (fread(&o1,sizeof(Odunc),1,ptr)!=0 ){

   if(KullaniciNo==o1.KullaniciNo && Barkod==o1.Barkod) {
    sonuc=1;
    break;
   }
}
if(sonuc==0){
fclose(ptr);
    printf("%d Kullanici Numarali kisi veya %d Barkod numarali kitap bulunamadi!!\n\n",KullaniciNo,Barkod);
    return ;
}
else{
rewind(ptr);
fwrite(&o1,sizeof(Odunc),1,ptr);
fclose(ptr);
printf("Odunc Alma Kaydi Silindi:\n");
StokGuncelle(o1.Barkod,+1);
}
}

void OduncKitapListele(){
system("cls");
printf("Odunc Kitap Listeleme Ekrani:\n\n");
Odunc o1;
FILE* ptr=fopen("Oduncler.txt","r+b");
while(fread(&o1,sizeof(Odunc),1,ptr)!=0){
printf("%-20s%-20s%-20s%-20s\n","Kullanici Numarasi","Barkod Numarasi","Baslangic Tarihi","Bitis Tarihi");
printf("%-20d%-20d%-20s%-20s\n",o1.KullaniciNo,o1.Barkod,o1.BaslangicTarihi,o1.BitisTarihi);}
fclose(ptr);
}
