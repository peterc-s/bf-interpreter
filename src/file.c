#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#define MAX_FILE_SIZE 1024 * 1024 * 128 // 128MB

char* read_file(char* file_name) {
    // open source file
    FILE *file = fopen(file_name, "rb");
    if (!file) error("Failed to open file.");

    // get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // check file is not too large
    if (file_size > MAX_FILE_SIZE) {
        fclose(file);
        error("File too large.");
    };

    // allocate memory for the file array
    char *file_buffer = (char *)malloc(file_size + 1);
    if (!file_buffer) {
        fclose(file);
        error("File buffer memory allocation failed.");
    };

    // read file contents
    size_t bytes_read = fread(file_buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        free(file_buffer);
        fclose(file);
        error("Partial file read occurred.");
    };

    // close file
    fclose(file);

    // null terminate
    file_buffer[file_size] = '\0';

    return file_buffer;
}
