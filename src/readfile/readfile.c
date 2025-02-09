#include "../../includes/include.h"
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 100

char **load_map(char *filename)
{
    FILE *fptr;
    char *line;
    char **map;
    int line_number;
    int i;
    char buffer;

    i = 0;
    line_number = 1;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        return NULL;
    }

    line = malloc(BUFFER_SIZE * sizeof(char));
    map = malloc(sizeof(char *));

    while ((buffer = fgetc(fptr)) != EOF)
    {
        if (buffer != '\n' && buffer != ' ')
        {
            line[i] = buffer;
            i++;
        }
        else if (buffer == '\n')
        {
            line[i] = '\0';                                        // end of line
            map = realloc(map, line_number * sizeof(char *));      // reallocating memory for the new line
            map[line_number - 1] = malloc((i + 1) * sizeof(char)); // allocating memory for the new line
            strcpy(map[line_number - 1], line);                    // copying the line to the map
            i = 0;                                                 // reseting the index
            line[0] = '\0';                                        // reseting the line
            line_number++;                                         // incrementing the line number
        }
    }
    line[i] = '\0';
    map = realloc(map, line_number * sizeof(char *));
    map[line_number - 1] = malloc((i + 1) * sizeof(char));
    strcpy(map[line_number - 1], line);
    i = 0;
    line[0] = '\0';
    line_number++;

    fclose(fptr);

    return map;
}