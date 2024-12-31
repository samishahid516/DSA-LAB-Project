#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

sf::Text aboutText;
sf::Font aboutFont;
FILE* Myfile;
FILE* about;
char ab[1000];

void file_io(int score, string name) 
{
    errno_t err;

    err = fopen_s(&Myfile, "score_file.txt", "w");

    if (err == 0) 
    {
        fprintf(Myfile, "%d  %s\n", score, name.c_str());
        fclose(Myfile);
    }
    else {
        printf("Error opening file\n");
    }
}
