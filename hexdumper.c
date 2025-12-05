#include <ctype.h> // isprint() fonksiyonu için gerekli
#include <stdio.h>

void char_dump(const char *filename) {
  FILE *fp =
      fopen("data1.csv", "rb"); // Binary modda açıyoruz ki dönüşüm olmasın
  if (fp == NULL) {
    printf("Dosya acilamadi.\n");
    return;
  }

  int c;
  while ((c = fgetc(fp)) != EOF) {

    // 1. Özel Karakter Kontrolleri
    if (c == '\n') {
      printf("\\n "); // Ekrana "\n" stringini basar
    } else if (c == '\r') {
      printf("\\r "); // Windows CR karakteri
    } else if (c == '\t') {
      printf("\\t "); // Tab
    } else if (c == '\0') {
      printf("\\0 "); // Null Terminator
    }
    // 2. Yazdırılabilir Karakter mi? (A-Z, 0-9, !?., vb.)
    else if (isprint(c)) {
      printf("%c  ", c); // Karakterin kendisini bas + boşluk
    }
    // 3. Hiçbiri değilse (Garip binary karakterler)
    else {
      printf("?  ");
    }
  }

  printf("\n"); // Sonunda temiz bir alt satıra geç
  fclose(fp);
}

int main() {
  // Test verisi oluştur: "AB,C" (satır sonu) "12"

  printf("Dosya Icerigi: ");
  char_dump("test_char.txt");

  return 0;
}
