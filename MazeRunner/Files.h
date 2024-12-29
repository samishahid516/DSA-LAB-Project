#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

sf::Text aboutText;
sf::Font aboutFont;
FILE* Myfile;
FILE* about;
char ab[1000];

void file_io(int score, string name) {
    // Declare a pointer to the file
    errno_t err;

    // Use fopen_s instead of fopen
    err = fopen_s(&Myfile, "score_file.txt", "w");

    // Check if the file opened successfully
    if (err == 0) {
        fprintf(Myfile, "%d  %s\n", score, name.c_str());
        fclose(Myfile);
    }
    else {
        printf("Error opening file\n");
    }
}
