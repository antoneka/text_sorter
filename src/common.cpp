#include "common.h"
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

//-------------------------------------------------------------------------------------------------

size_t getFileSize(const char *filename)
{
    assert(filename != nullptr);

    struct stat file_info = {};

    stat(filename, &file_info);

    if (file_info.st_size <= 0)
    {
        return GETTING_FILE_SIZE_ERROR;
    }

    return (size_t)file_info.st_size;
}

//-------------------------------------------------------------------------------------------------

void swapVoid(void *element1, void *element2, size_t size)
{
    assert(element1 != nullptr);
    assert(element2 != nullptr);

    size_t size_ll = sizeof(long long);
    size_t size_i = sizeof(int);
    size_t size_ch = sizeof(char);

    while (size > 0)
    {
        if (size_ll <= size)
        {
            long long tmp = 0;

            tmp = *(long long*)element1;
            *(long long*)element1 = *(long long*)element2;
            *(long long*)element2 = tmp;

            element1 = (char*)element1 + size_ll;
            element2 = (char*)element2 + size_ll;

            size -= size_ll;
        }
        else if (size_i <= size)
        {
            int tmp = 0;

            tmp = *(int*)element1;
            *(int*)element1 = *(int*)element2;
            *(int*)element2 = tmp;

            element1 = (char*)element1 + size_i;
            element2 = (char*)element2 + size_i;

            size -= size_i;
        }
        else
        {
            char tmp = 0;

            tmp = *(char*)element1;
            *(char*)element1 = *(char*)element2;
            *(char*)element2 = tmp;

            element1 = (char*)element1 + size_ch;
            element2 = (char*)element2 + size_ch;

            size -= size_ch;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void printError(int error)
{
    switch (error)
    {
        case INPUT_FILE_OPEN_ERROR:
            fprintf(stderr, "%s\n", "Input file doesn`t exist");
            break;

        case OUTPUT_FILE_OPEN_ERROR:
            fprintf(stderr, "%s\n", "Failed to create an output file");
            break;

        case BUFFER_ALLOCATION_ERROR:
            fprintf(stderr, "%s\n", "Buffer allocation error");
            break;

        case READ_SYMBOLS_ERROR:
            fprintf(stderr, "%s\n", "Text reading error");
            break;

        case STRING_ARRAY_ALLOCATION_ERROR:
            fprintf(stderr, "%s\n", "String array allocation error");
            break;

        case GETTING_FILE_SIZE_ERROR:
            fprintf(stderr, "%s\n", "Getting file size error");
            break;

        case ONEGINFILE_ALREADY_CONSTRUCTED:
            fprintf(stderr, "%s\n", "OneginFile already exists. It can`t be constructed again");
            break;

        case ONEGINFILE_ALREADY_DESTRUCTED:
            fprintf(stderr, "%s\n", "OneginFile doesn`t exist. It can`t be destructed");
            break;

        default:
            assert(0 && "Unknown error");
    }
}
