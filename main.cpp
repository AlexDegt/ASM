#include <cstdio>
#include <vector>
#include <iostream>
#include <malloc.h>
#include <cstdlib>
#include <new>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <assert.h>
using namespace std;

struct token{
std::vector<std::string> tokens;
std::vector<int> line;
token():
    line(1),
    tokens(1)
    {}
};

//typedef struct massiv * token;

class ReadFile
{
    public:
    ReadFile(size_t filesize, token * massptr);
    token * mass;
    token * fragmentation(char * str);
    token * structinit(size_t massize);
    std::vector<char> filevec;

    char * convert(char * filename);
};

int main()
{
    /*char put[15];
    put[0] = *"push";   put[5] = *"sub";
    put[1] = *"pop";    put[6] = *"mal";
    put[2] = *"add";    put[7] = *"div";
    put[3] = *"out";    put[8] = *"sin";
    put[4] = *"in";     put[9] = *"cos";
                        put[10] = *"sqrt";*/
    token * ptr = new token[1];
    /*token ptr(10);
    printf("%s\n", ptr.tokens[0].c_str);*/
    /*token ptr;
    printf("%i\n", ptr.line[1]);*/
    ReadFile s(6, ptr);
    //printf("%s\n", ptr->tokens[0].c_str());
    //delete ptr;
    char s2[9] = "test.txt";
    token * mas = s.fragmentation(s.convert(s2));
    //printf("%s\n", mas[0].tokens[1].c_str());
    printf("%i\n", mas[0].line[0]);
    system("PAUSE");
    return 0;
}

ReadFile::ReadFile(size_t filesize, token * massptr):
    filevec(filesize+1),
    mass(massptr)
    {}



char * ReadFile::convert(char * filename)
{
    FILE * f = fopen(filename,"r");
    try
    {
        f = fopen(filename,"r");
    }
    catch(...)
    {
        printf("filename == NULL\n");
    }
    fseek(f, 0 , SEEK_END);
    size_t filesize = ftell(f);
    rewind(f);
    filevec.resize(filesize);
    fread(filevec.data(),sizeof(char),filesize,f);
    return filevec.data();
}

token * ReadFile::fragmentation(char * str)
{
    mass[0].line[0] = 1;
    mass[0].tokens[0] = "1";
    /*std::string letter;
    std::string word;
    bool flag = false;
    int wordcount = -1;
    int linenum = 1;
    int i = 0;
    size_t currsize = 0;
    size_t size_start = filevec.size();
    while (currsize < size_start)
    {
        flag = false;
        while (str[i] != ';')
        {
            if (str[i] == '\n')
                {
                    linenum++;
                    currsize++;
                    i++;
                }
            if (((str[i] == 32) || (str[i] == 9)) && (flag))
            {
                mass[0].line[wordcount] = linenum;
                if (flag)
                    flag = false;
            }
            if ((str[i] != 32) && (str[i] != 9) && (flag))
                {
                    mass[0].tokens[wordcount] += str[i];
                    if (str[i+1] == ';')
                        mass[0].line[wordcount] = linenum;
                }
            if ((str[i] != 32) && (str[i] != 9) && (!flag))
            {
                mass[0].tokens[++wordcount] = str[i];
                flag = true;
            }
            currsize++;
            i++;
        }
        currsize++;
        i++;
    }
    return mass;*/
}
