#ifndef DATA_MODEL_H
#define DATA_MODEL_H
#include <stdlib.h>
#include <stdio.h>
typedef struct 
{
    size_t sutun_count;
    size_t satir_count;
};

typedef struct{
 size_t output_count;
 char** output;
}Fann_rows;

typedef struct 
{

    Fann_rows* rows;

    //kullanıcı manuel konfigrasyon
    size_t total_columns;
    size_t input_columns;
    size_t output_columns;
    size_t total_rows;
    size_t rows_alloc;

}FannDataset;

typedef enum{
    FANN_SUCCESS = 0,
    FANN_ERR_IO,
    FANN_ERR_ALLOC,
    FANN_ERR_ARG,
    FANN_ERR_DATA,
}FannError;


FannError FannDataset_create(
                                FannDataset** fannDataset,
                                size_t total_columns,
                                size_t input_columns,
                                size_t output_columns
                                );


FannError FannDataset_parse(FannDataset** fannDataset,
                            char** const file_handle,
                            char* end_ptr,
                            unsigned int skip_row,
                            const char ayrac
                            );



FannError FannDataset_parse_csv(
                                FannDataset** FannDataset,
                                const char* const dosya_yolu,
                                unsigned int skip_rows,
                                const char ayrac
                                );


FannError FannDataset_OutData(
                              FannDataset* FannDataset,
                              const char* new_name
                              );


FannError FannDataset_destroy(
                        FannDataset** FannDataset
                        );

void print_raw_string_including_null(const char *str);
#endif