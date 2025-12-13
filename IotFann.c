#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *csvRead[7];
typedef void (*dataSet_t)(FILE *, csvRead *, int *);

void dataSet(FILE *, csvRead *, int *);
FILE *output1(csvRead *, int);

struct IotFann {
  FILE *safData;
  char *satirlar[20600][7];
  dataSet_t parser;
  int satirSayisi;
};

struct IotFannDataset {
  int girdiSayisi;
  int satirSayisi;
  int ciktiSayisi;
  int toplamCikti;
};

int main() {

  FILE *safDatax = fopen("/home/emec/Masaüstü/C/data.csv", "r");

  if (!safDatax) {
    return 1;
  };

  struct IotFann Veri;
  struct IotFannDataset output;

  int *sayac = &Veri.satirSayisi;
  Veri.safData = safDatax;
  Veri.parser = dataSet;
  Veri.parser(Veri.safData, Veri.satirlar, sayac);

  // printf("%s \n",Veri.satirlar[20560][6]);
  // printf("%d \n",Veri.satirSayisi);

  FILE *ptr = output1(Veri.satirlar, Veri.satirSayisi);
  return 0;
};

FILE *output1(csvRead *satirlar, int satirSayisi) {

  FILE *hazirData = fopen("/home/emec/Masaüstü/C/Formatlanmis.data", "w");

  if (!(hazirData)) {
    return NULL;
  }

  fprintf(hazirData, "%d %d %d\n", satirSayisi - 2, 5, 1);

  for (int i = 0; i < satirSayisi; i++) {
    for (int a = 1; a < 7; a++) {
      if (a == 6) {

        fprintf(hazirData, "\n%s\n", satirlar[i][6]);
        break;
      }

      fprintf(hazirData, "%s ", satirlar[i][a]);
    }
  }

  return hazirData;
};

void dataSet(FILE *safData, csvRead *satirlar, int *satirSatir) {

  *satirSatir = 0;
  char satir[200];
  int satirSutun = 0;
  int satirLeft, satirTop = 0;
  char buffer[201];
  // csvRead* satirlar = (csvRead*)malloc(24999 * sizeof(csvRead));

  while (fgets(satir, sizeof(satir), safData)) {

    for (int i = 0; satir[i] != '\0'; i++) {

      if (satir[i] == ',' || satir[i] == '\n') {

        for (satirTop = satirLeft; satirTop < i; satirTop++) {

          buffer[satirTop - satirLeft] = satir[satirTop];
        };

        buffer[satirTop - satirLeft] = '\0';

        satirlar[*satirSatir][satirSutun] = malloc(satirTop - satirLeft + 1);

        strcpy(satirlar[*satirSatir][satirSutun], buffer);

        satirLeft = i + 1;
        satirSutun++;
      };
    }

    satirLeft = 0;
    satirSutun = 0;
    (*satirSatir)++;
  };

  fclose(safData);
};
