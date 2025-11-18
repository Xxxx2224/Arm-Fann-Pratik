#include <stdio.h>
#include <stdlib.h>
#include "../include/data_model.h"
#define FANN_ROWS_ALLOC 100

FannError FannDataset_create(
                                FannDataset** fannDataset,
                                size_t total_columns,
                                size_t input_columns,
                                size_t output_columns
                                )
{
    if(fannDataset==NULL || 
       total_columns!=input_columns+output_columns ||
       input_columns==0 ||
       output_columns==0 ||
       total_columns==0 )
    {

        return FANN_ERR_ARG;
    }

    *fannDataset = NULL;

    FannDataset* dataset = (FannDataset*)malloc(sizeof(FannDataset));
    
    if(dataset == NULL){
        perror(NULL);
        return FANN_ERR_ALLOC; 
    }

    dataset->rows = NULL;    
    dataset->input_columns = input_columns;
    dataset->output_columns = output_columns;
    dataset->total_columns = total_columns;
    dataset->total_rows = 0;
    dataset->rows_alloc = FANN_ROWS_ALLOC;
    
    Fann_rows* rows = (Fann_rows*)malloc(FANN_ROWS_ALLOC*sizeof(Fann_rows));
    if (rows == NULL)
    {
        free(dataset);
        perror(NULL);
        return FANN_ERR_ALLOC;
    }
    dataset->rows = rows;
    for (size_t i = 0; i < FANN_ROWS_ALLOC; i++)
    {
        dataset->rows[i].output = (char**)malloc(total_columns*sizeof(char*)); 
    }
    
    *fannDataset = dataset;
    
    return FANN_SUCCESS;
}

FannError FannDataset_parse_csv(FannDataset** fannxDataset,const char* const file_path,unsigned int skip_rows,const char ayrac){
    FannDataset* fannDataset = *(fannxDataset);
    if (fannDataset==NULL ||
        file_path==NULL || file_path[0]=='\0' || 
        ayrac=='\0') 
    {
        return FANN_ERR_ARG;
    }
    
    FILE* file = fopen(file_path,"r");
    if(!file){
     
        perror(NULL);
        return FANN_ERR_IO;
    }

    fseek(file,0,SEEK_END);
    unsigned int file_size = ftell(file);
    fseek(file,0,SEEK_SET);
    
    if(file_size <= 0){
        perror(NULL);
        fclose(file);
        return FANN_ERR_IO;
    }

    char* const file_handle = malloc(file_size+100);
    if (!file_handle)
    {
        perror(NULL);
        fclose(file);
        return FANN_ERR_ALLOC;
    }

    size_t read_count = fread(file_handle,1,file_size,file);
    if (read_count != file_size)
    {
        perror(NULL);
        free(file_handle);
        fclose(file);                                                                       
        return FANN_ERR_IO;
    }

    file_handle[file_size] = '\0';
    char* end_ptr = &file_handle[file_size-1];
    fclose(file);

    FannDataset_parse(&fannDataset,&file_handle,end_ptr,skip_rows,ayrac);

    return FANN_SUCCESS;
}

FannError FannDataset_parse(FannDataset** fanndataset,char** const file_handle,char* end_ptr,unsigned int skip_rows,const char ayrac){
    char* file = *(file_handle);
    __uint64_t rows= 0;
    __uint8_t colums = 0; 
    FannDataset* fannDataset = *(fanndataset);
    char* left_ptr = file;
    while (file<end_ptr)
    {
        if (file==NULL)
        {   
            return FANN_ERR_ARG;
        }

        if (*file==ayrac)
        {
            *file='\0';
            fannDataset->rows[rows].output[colums];
            // while (left_ptr<file)
            // {
            // }
            rows++;
        }
        file++;
   }
    
}

FannError FannDataset_destroy(FannDataset** fannDataset){
    FannDataset* ds = *fannDataset;
    if (fannDataset == NULL || ds == NULL)
    {
        return FANN_ERR_ARG;
    }
    for (size_t i = 0; i <= ds->total_rows; i++)
    {
        // free(&ds->rows[i]);
    }
    
    free(ds->rows);
    
    

}

