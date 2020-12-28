#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void filter_str(char str[]) ;
void calculate_distances();
void calculate_frequencies_bi(char str[]);
void calculate_frequencies_tri(char str[]);
void detect_lang();
float calculated_frequencies[20];
float distances [2]={0,0};
const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
const char languages[2][8]={"english", "german"};
const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };

int main(void)
{
     printf("\n\n Dil tahmin programina hos geldiniz. Fatih ve Oguzun Proje Odevidir. \n\n") ;
    char metin[500]; /*kullanıcıdan metin istedik */

    printf("Metni giriniz :\n\n\t\t");
    gets(metin);

    filter_str(metin);
    calculate_frequencies_bi(metin);         /* ^^^^^^^fonksiyonlar ^^^^^^^^ */
    calculate_frequencies_tri(metin);
    calculate_distances();
    detect_lang();
    printf("\n\n\n");

    return 0;
}
//fatih-> f memur->m oguzhan->o kahraman->k

void filter_str(char str[])  /ascii kodları a-z arası(a z dahil) tanımlandı for döngüsü ile kontrol edildi böylece filtre fonksiyonu işlevli haline getirildi./
{

     for(int i=0;i<strlen(str);i++)
      {
          if((str[i]==32)||(str[i]==0)||(str[i]>64&&str[i]<91)||(str[i]>96&&str[i]<123));

          else
            str[i]=' ';
      }
   printf("Girdiginiz metinin filtrelenmis hali asagidadir :\n\n\t ");
   puts(str);

}


void calculate_frequencies_bi(char str[]){
//tanımlanan bigramlardan yararlanarak  girilen metinimizdeki bigramları hesaplar.
char ctrl[3], text_div[3];
float sayac = 0.0;

for(int i = 0,c = 0;i < 10;i++){
    for(int j = 0;j < 2;j++){
        ctrl[j] = matrix_bigram_strings[i][j];
    }
    ctrl[2] = '\0';
    sayac = 0.0;
    c = 0;
    while(c != strlen(str)-1){
        for(int m = 0;m < 2;m++){
            text_div[m] = str[c];
            c++;
        }
        text_div[2] = '\0';
        c -= 1;

        if(strcmp(text_div,ctrl) == 0){
            sayac++;
        }
    }

    calculated_frequencies[i] = sayac;

}
printf("\n\n Fatih ve Oguzun Proje Odevidir. \n\n") ;
printf("\n\n\n\n");
printf(" Iste girdiginiz metnin Bigram frekanslari :\n\t\n");

for(int i = 0;i < 10;i++){
   printf(" %.2f, ",calculated_frequencies[i]); //frekans degelerini anlamlı basamak dahilinde virgülden sonraki 2 basamaka ayalardım
}


}
//tanımlanan trigramlardan yararlanarak girilen metinimizdeki trigramları hesaplar.

void calculate_frequencies_tri(char str[]){
printf("\n");
char ctrl[4], text_div[4];
float sayac = 0.0;

for(int i = 0,c = 0;i < 10;i++){
    for(int j = 0;j < 3;j++){
        ctrl[j] = matrix_trigram_strings[i][j];
    }
    ctrl[3] = '\0';
    sayac = 0.0;
    c = 0;
    while(c != strlen(str)-2){
        for(int m = 0;m < 3;m++){
            text_div[m] = str[c];
            c++;
        }
        text_div[3] = '\0';
        c -= 2;

        if(strcmp(text_div,ctrl) == 0){
            sayac++;
        }
    }

    calculated_frequencies[i + 10] = sayac;

}
printf("\n\n  \n\n");
printf(" Iste girdiginiz metnin Trigram frekanslari :\n\t\n");
for(int i = 10;i < 20;i++){
   printf(" %.2f, ",calculated_frequencies[i]); //aynı şekilde bigramlara yaptığımızı burada da yaparak frekans degelerini anlamlı basamak dahilinde virgülden sonraki 2 basamaka ayalardık
}
}

//Öklit hesaplamasına göre distance(mesafe)(fark) hesapladık
void calculate_distances(){
    float sum = 0.0;

    printf("\n\n  \n\n");
    printf("Oklit'e gore distance degerleri :\n\n");

    for(int i = 0;i < 20;i++){
        sum += pow((calculated_frequencies[i] - frequency_eng[i]),2);
    }

    distances[0] = sqrt(sum);
    printf("\n Girdiginiz metnin Ingilizce dili ile arasindaki distance degerleri  :\n\n");
    printf("===> %f\n",distances[0]);

    sum = 0.0;
    for(int i = 0;i < 20;i++){
        sum += pow((calculated_frequencies[i] - frequency_germ[i]),2);
    }

    distances[1] = sqrt(sum) ;
    printf("\n Girdiginiz metnin Almanca dili ile arasindaki distance degerleri :\n\n");
    printf("===> %f\n",distances[1]);

}

//dili algılarken distance(mesafe) azaldıkça benzerlik o orantıda artar yani ne kadar az ise o kadar benzerdir kodu yazarken aklında olsun
void detect_lang(){

 printf("\n\n \n\n");                                         //distance mesafesi az olan dil daha benzer olacağından if-else yapısı ile tamamladık.
 printf("Tahminimizce :\n\n");
 if(distances[0] < distances[1]){
    printf("===> Bu dil ingilizce .");
 }
 else{
    printf("===> Bu dil almanca  .");
 }

}
