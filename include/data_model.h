#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <stdio.h>
#include <stdlib.h>

// Tasarim tercihimiz veri setini bellege alip ayrac lari null terminator ile
// degistirip her null terminator un solunda bir onceki terminatorden hemen
// sonra olucak sekilde bir pointer ile tutmak ve her sutun icin bir pointer her
// sutun pointer dizisi icin ise bir satir pointer i ve tum satir pointer
// dizilerini tutmak icin ise bir FannDataset adindaki struct.

// Ikinci tasarim tercihi olabilecek senaryo dusuk bellekler icin yapilan
// optimizasyon ama hizdan kaybedilecek cok sey var satir satir okuyup her ayrac
// bulundugunda kelime basini tutan pointeri ayraci tespit ettigimiz noktaya
// kadar bellegi dosyaya yazmak ve satir bittikce alani birakip yeni satir
// okumak surekli dongude yapmak ve veriyi yazarken kullanicidan aldigimiz cikti
// ile girdi sutununa gore formati duzenleyerek yazmak artilar bellekte tek
// satir ve pointer dizisi olmiyacak eksiler cok fazla io islemi ve hiz

typedef struct {
  size_t sutun_count;
  size_t satir_count;
} Fann_nebilmiyorum;

typedef struct {
  char **output;
} Fann_rows;

typedef struct FannDataset {
  char *file_handle;
  FILE *file;
  Fann_rows *rows;

  // kullanıcı manuel konfigrasyon
  size_t total_columns;
  size_t input_columns;
  size_t output_columns;
  size_t total_rows;
  size_t rows_alloc;

} FannDataset;

typedef enum {
  FANN_SUCCESS = 0,
  FANN_ERR_IO,
  FANN_ERR_ALLOC,
  FANN_ERR_ARG,
  FANN_ERR_DATA,
} FannError;

FannError FannDataset_create(FannDataset **fannDataset,
                             const char *const file_path, size_t total_columns,
                             size_t input_columns, size_t output_columns);

FannError FannDataset_parse(FannDataset *fannDataset, char *const file_handle,
                            char *end_ptr, unsigned int skip_row,
                            const char ayrac);

FannError FannDataset_parse_csv(FannDataset *FannDataset,
                                unsigned int skip_rows, const char ayrac);

FannError FannDataset_OutData(FannDataset *FannDataset, const char *new_name);

FannError FannDataset_destroy(FannDataset **FannDataset);

static FannError rows_resize(FannDataset *fannDataset);
void print_raw_string_including_null(const char *str);
#endif
