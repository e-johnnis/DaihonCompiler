#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int strbegin(const char*, const char*);
void changeext(char*, const char*, const char*);

char dhnFile[128] = { '\0' };
char htmlFile[128] = { '\0' };
char lang[8] = { '\0' };
char title[64] = { '\0' };
char font[128] = { '\0' };
char line[1024] = { '\0' };
char cv[16] = { '\0' };
char words[1024] = { '\0' };

int main(int argc, char** argv) {
    int cc = -1;
    int header = 1;
    int pb = 0;

    while((cc = getopt(argc, argv, "o:r:t:f:")) != -1) {
        switch(cc) {
            case 'o':
                strcpy(htmlFile, optarg);
                break;
            
            case 'r':
                strcpy(lang, optarg);
                break;

            case 't':
                strcpy(title, optarg);
                break;

            case 'f':
                strcpy(font, optarg);
            
            default:
                fprintf(stderr, "[!] invalid option '%c'.\n", optopt);
                break;
        }
    }

    if(optind <= argc) strcpy(dhnFile, argv[optind]);
    else {
        fprintf(stderr, "[!] no input file.\n");
        return -1;
    }

    if(!strlen(htmlFile)) changeext(htmlFile, dhnFile, ".html");

    #ifdef DEBUG
    printf("input file  : %s\n", dhnFile);
    printf("output file : %s\n", htmlFile);
    printf("html lang   : %s\n", lang);
    printf("html title  : %s\n", title);
    printf("font-family : %s\n", font);
    #endif

    FILE* html = fopen(htmlFile, "w");
    if(!html) {
        fprintf(stderr, "[!] failed to open \"%s\".\n", htmlFile);
        return -2;
    }

    FILE* dhn = fopen(dhnFile, "r");
    if(!dhn) {
        fprintf(stderr, "[!] failed to open \"%s\".\n", dhnFile);
        fclose(html);
        return -3;
    }

    fprintf(html, "<!DOCTYPE html>\n");
    if(strlen(lang)) fprintf(html, "<html lang=\"%s\">\n", lang);
    else fprintf(html, "<html>\n");
    fprintf(html, "<head>\n");
    fprintf(html, "  <meta charset=\"UTF-8\" />\n");
    if(strlen(title)) fprintf(html, "  <title>%s</title>\n", title);
    fprintf(html, "  <style>\n");
    if(strlen(font)) {
        fprintf(html, "    body {\n");
        fprintf(html, "      font-family: %s;\n", font);
        fprintf(html, "    }\n");
    }
    fprintf(html, "    p {\n");
    fprintf(html, "      break-inside: avoid;\n");
    fprintf(html, "    }\n");

    while(!feof(dhn)) {
        fscanf(dhn, "%[^\n]\n", line);

        #ifdef DEBUG
        printf("%s\n", line);
        #endif

        if(header) {
            if(strbegin(line, "---")) {
                header = 0;
                fprintf(html, "  </style>\n");
                fprintf(html, "</head>\n");
                fprintf(html, "<body>\n");
            }else if((sscanf(line, "%[^:]:%*[ ]%[^\n]", cv, words) < 2) || cv[0] != '.') {
                fprintf(stderr, "[!] invalid format: %s\n", line);
                fclose(dhn);
                fclose(html);
                return -3;
            }else {
                fprintf(html, "    %s {\n", cv);
                fprintf(html, "      color: %s;\n", words);
                fprintf(html, "    }\n");
            }
        }else if(line[0] == '.') {
            if(sscanf(line, "%*[.]%[^:]:%*[ ]%[^\n]", cv, words) < 2) {
                fprintf(stderr, "[!] invalid format: %s\n", line);
                fclose(dhn);
                fclose(html);
                return -3;
            }else {
                if(pb) fprintf(html, "  </p>\n");
                fprintf(html, "  <p class=\"%s\">\n", cv);
                fprintf(html, "    %s\n", words);
                pb = 1;
            }
        }else {
            fprintf(html, "    %s\n", line);
        }
    }

    if(pb) fprintf(html, "  </p>\n");
    fprintf(html, "</body>\n");

    fclose(html);
    fclose(dhn);

    return 0;
}

int strbegin(const char* str, const char* word) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(word[i] == '\0') return 1;
        else if(str[i] != word[i]) return 0;
    }
    return (word[i] == '\0');
}

void changeext(char* dst, const char* src, const char* ext) {
    char fsn[128];

    sscanf(src, "%[^.]", fsn);
    sprintf(dst, "%s%s", fsn, ext);
}