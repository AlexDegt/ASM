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
#include <cstring>
#include <conio.h>

#define CODENOARG 50
#define CODEARGLAB 100
#define CODEARGNUM 150
#define CODEARGRGST 200
#define CODERGST 250
#define CODELABEL 299

#define ERRORPRINT(a)\
    printf("\n***************\n");\
    printf(a);\
    printf("\npress any key...");\
    printf("\n***************\n");\
    getch();\
    exit(1);
using namespace std;

struct token{
    std::vector<std::string> tokens;
    std::vector<int> line;
    token():
        line(),
        tokens()
        {}
};

struct commlab{
    long int code;
    char id;
    commlab():
        code(),
        id()
        {}
};

struct label{
    int labcode;
    int labnum;
    char labchar;
    std::string labstr;
    int prevnum;
    label():
        prevnum(),
        labchar(),
        labcode(),
        labnum(),
        labstr()
        {}
};

class ReadFile
{
    public:
    ReadFile(size_t filesize, token * massptr);
    token * mass;
    token * fragmentation(char * str);
    std::vector<label> masslabel;
    std::vector<char> filevec;
    std::string slovo;
    char * convert(char * filename);
};

class translation
{
    public:
    std::vector<std::string> commands;
    void commlabinit();
    void translat(token * mass, std::vector<label> masslabel);
    std::vector<commlab> masscommlab;
    void printmass();
    bool checkmass(std::string tok,int line, std::vector<std::string> commands, int startcode, char letter);
    bool checkmasslab(std::string tok, int line, std::vector<label> masslabel);
    bool is_number(std::string tok,int line);
    std::vector<std::string> cmdnoarg;
    std::vector<std::string> cmdarglab;
    std::vector<std::string> cmdargnum;
    std::vector<std::string> cmdargrgst;
    std::vector<std::string> rgst;
    translation():
        cmdnoarg(),
        cmdarglab(),
        cmdargnum(),
        cmdargrgst(),
        rgst(),
        masscommlab()
        {}
};

class semanalysis
{
    public:
    void analysis(std::vector<commlab> mass, std::vector<label> masslabel,std::vector<std::string> cmdnoarg,std::vector<std::string> cmdarglab,std::vector<std::string> cmdargnum,std::vector<std::string> cmdargrgst,std::vector<std::string> rgst);
    void checklabel(std::vector<label> masslabel);
    void output(char * filename, std::vector<commlab> mass);
    bool is_noarg(int code, std::vector<std::string> cmdnoarg);
    bool is_arglab(int code, std::vector<std::string> cmdarglab);
    bool is_argnum(int code, std::vector<std::string> cmdargnum);
    bool is_argrgst(int code, std::vector<std::string> cmdargrgst);
    bool is_label1(int code, std::vector<label> masslabel);
    std::vector<label> masslabel;
    std::vector<label> label1;
    std::vector<label> label2;
    std::vector<int> prevnum;
    semanalysis():
        prevnum(),
        masslabel(),
        label1(),
        label2()
        {}
};

int main()
{
    translation com;
    semanalysis lab;
    com.commlabinit();
    token * ptr = new token[1];
    ReadFile s(6, ptr);
    char s2[9] = "test.txt";
    token * mas = s.fragmentation(s.convert(s2));
    std::vector<label> labels = s.masslabel;
    com.translat(mas, labels);
    lab.analysis(com.masscommlab,s.masslabel,com.cmdnoarg,com.cmdarglab,com.cmdargnum, com.cmdargrgst, com.rgst);
    lab.checklabel(s.masslabel);
    lab.output("ASM.txt", com.masscommlab);
    system("PAUSE");
    return 0;
}

ReadFile::ReadFile(size_t filesize, token * massptr):
    filevec(filesize+1),
    slovo(),
    mass(massptr),
    masslabel()
    {}

void translation::commlabinit()
{
    cmdnoarg.push_back("pop");
    cmdnoarg.push_back("out");
    cmdnoarg.push_back("in");
    cmdnoarg.push_back("sub");
    cmdnoarg.push_back("mul");
    cmdnoarg.push_back("div");
    cmdnoarg.push_back("add");
    cmdnoarg.push_back("sin");
    cmdnoarg.push_back("cos");
    cmdnoarg.push_back("sqrt");
    cmdnoarg.push_back("ret");
    cmdarglab.push_back("jmp");
    cmdarglab.push_back("call");
    cmdargnum.push_back("push");
    cmdargrgst.push_back("push");
    cmdargrgst.push_back("pop");
    rgst.push_back("ax");
    rgst.push_back("bx");
    rgst.push_back("cx");
    rgst.push_back("dx");
}

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
    //printf("FRAGMENTATION:\n****************************\n");
    std::string letter;
    std::string word;
    bool flag = false;
    bool flag1 = false;
    bool flag2 = false;
    bool errflg = false; //Esli vstrechaem ':' v seredine tokena
    int wordcount = 0;
    int linenum = 1;
    int i = 0;
    size_t cursize = 0;
    int firstcodelab = CODELABEL;
    int numoflab = 0;
    int codeoflab = firstcodelab+numoflab;
    int tokennum = 0;
    size_t size_start = filevec.size();
    while (cursize < size_start)
    {
        //printf("AAA");
        flag = false;
        while ((str[i] != '\n') && (cursize < size_start))
        {
            /*printf("size_start: %i\n", size_start);
            printf("cursizeINcicle: %i\n", cursize);
            printf("s_s > cs = %i\n\n", size_start>cursize);*/

            if (((str[i] == 32) || (str[i] == 9)) && (flag))
            {
                //printf("flaggggg1: %i\n", flag1);
                mass[0].line.push_back(linenum);
                mass[0].tokens.push_back(slovo);
                flag = false;
                if ((str[i-1] == ':')/* && (!flag1)*/)
                    flag2 = true;
                /*printf("((flag1 && (str[i-1] != ':')): %i   ", (flag1 && (str[i-1] != ':')));
                printf("flag1: %i   ", flag1);
                printf("str[i-1] != ':' : %i   ", str[i-1] != ':');
                printf("errflg: %i   ", errflg);
                printf("xor %i   ", (flag1) ^ (flag2));
                printf("flag2: %i\n", flag2);*/
                if (((flag1) ^ (flag2)) && (!errflg))
                {
                    label st1;
                    codeoflab++;
                    st1.labcode = codeoflab;
                    st1.labnum = tokennum;
                    numoflab++;
                    st1.labstr = slovo;
                    masslabel.push_back(st1);
                }
                flag1 = false;
                flag2 = false;
                tokennum++;
                errflg = false;
                //printf("@");
            }
            //printf("%c %i\n",str[i], ((str[i] != 32) && (str[i] != 9)  && (str[i] != '\n') && (flag)));
            //printf("%i\n", flag);
            if ((str[i] != 32) && (str[i] != 9) && (flag))
                {
                    slovo += str[i];
                    if ((str[i] == ':') && (str[i+1] != '\n') && (cursize+1 != size_start) && (str[i+1] != 32) && (str[i+1] != 9))
                        errflg = true;
                    if ((str[i+1] == '\n') || (cursize+1 == size_start))
                    {
                        if ((str[i] == ':')/* && (!flag1)*/)
                            flag2 = true;
                        /*printf("flag1111: %i\n",flag1);
                        printf("flag2222: %i\n",flag2);*/
                        if (((flag1) ^ (flag2)) && (!errflg))
                        {
                            flag1 = false;
                            flag2 = false;
                            label st1;
                            codeoflab++;
                            st1.labcode = codeoflab;
                            st1.labnum = tokennum;
                            numoflab++;
                            st1.labstr = slovo;
                            masslabel.push_back(st1);
                        }
                        tokennum++;
                        mass[0].line.push_back(linenum);
                        mass[0].tokens.push_back(slovo);
                        flag1 = false;
                        flag2 = false;
                        errflg = false;
                    }
                }
            if ((str[i] != 32) && (str[i] != 9) /*&& (str[i] != '\n')*/ && (!flag))
            {
                slovo.clear();
                slovo += str[i];
                flag = true;
                if (str[i] == ':')
                    flag1 = true;
                if ((str[i+1] == '\n') || (cursize == size_start-1))
                {
                    flag1 = false;
                    tokennum++;
                    mass[0].line.push_back(linenum);
                    mass[0].tokens.push_back(slovo);
                }
            }
            cursize++;
            i++;
        }
        cursize++;
        cursize++;
        i++;
        linenum++;
    }
    //~slovo();
    //printf("END OF FRAGMENTATION\n****************************\n");
    return mass;
}

bool translation::is_number(std::string tok,int line)
{
    bool flag = false;
    commlab st;
    if (tok != "0")
    {
        char * pEnd;
        long int number = strtol(tok.c_str(), &pEnd, 10);
        //printf("NUMBER: %i\n", number);
        if (number)
        {
            char strnum[50];
            itoa(number, strnum, 10);
            if (strlen(strnum) == tok.size())
            {
                //printf("%i\n", number);
                st.code = number;
                st.id = 'N';
                masscommlab.push_back(st);
                flag = true;
            }
        }
    }
    else
    {
        st.code = 0;
        st.id = 'N';
        masscommlab.push_back(st);
        flag = true;
    }
    return flag;
}

bool translation::checkmass(std::string tok,int line, std::vector<std::string> commands, int startcode, char letter)
{
    bool flag = false;
    commlab st;
    size_t size_mass = commands.size();
    for (int j = 0; j < size_mass; j++)
    {
        if (tok == commands[j])
        {
            st.code = j+startcode;
            st.id = letter;
            masscommlab.push_back(st);
            j = size_mass+1;
            flag = true;
        }
    }
    return flag;
}

bool translation::checkmasslab(std::string tok, int line, std::vector<label> masslabel)
{
    bool flag = false;
    commlab st;
    size_t size_mass = masslabel.size();
    for (int j = 0; j < size_mass; j++)
    {
        if (tok == masslabel[j].labstr)
        {
            st.code = masslabel[j].labcode;
            if (masslabel[j].labstr[0] == ':')
                st.id = 'L';
            else
                st.id = 'K';
            masscommlab.push_back(st);
            j = size_mass+1;
            flag = true;
        }
    }
    return flag;
}

void translation::translat(token * mass, std::vector<label> masslabel)
{
    //printf("TRANSLATION:\n**************************\n");
    size_t size_tok = mass[0].tokens.size();
    //printf("sizeToken: %i\n", mass[0].tokens.size());

    //bool checkmass(std::string tok,int line, std::vector<std::string> commands, int startcode, char letter)

    /*cmdnoarg(),
        cmdarglab(),
        cmdargnum(),
        cmdargrgst(),
        rgst(),*/

    bool flag;
    for (int i = 0; i < size_tok; i++)
    {
        flag = false;
        flag = is_number(mass[0].tokens[i], mass[0].line[i]);
        if (!flag) flag = checkmass(mass[0].tokens[i], mass[0].line[i], cmdnoarg, CODENOARG, 'C');
        if (!flag) flag = checkmass(mass[0].tokens[i], mass[0].line[i], cmdarglab, CODEARGLAB, 'C');
        if (!flag) flag = checkmass(mass[0].tokens[i], mass[0].line[i], cmdargnum, CODEARGNUM, 'C');
        if (!flag) flag = checkmass(mass[0].tokens[i], mass[0].line[i], cmdargrgst, CODEARGRGST, 'C');
        if (!flag) flag = checkmass(mass[0].tokens[i], mass[0].line[i], rgst, CODERGST, 'R');
        if (!flag) flag = checkmasslab(mass[0].tokens[i], mass[0].line[i], masslabel);
        if (!flag)
        {
            printf("Uncorrect input text in line: %i\n", mass[0].line[i]);
            printf("press any key...\n");
            getch();
            exit(1);
        }
    }
    //printf("END OF TRANSLATION\n****************************\n");
}

bool semanalysis::is_noarg(int code, std::vector<std::string> cmdnoarg)
{
    bool flag = false;
    size_t size_noarg = cmdnoarg.size();
    for (int i = 0; i < size_noarg; i++)
    {
        if (code == CODENOARG+i)
        {
            flag = true;
            i = size_noarg+1;
        }
    }
    return flag;
}

bool semanalysis::is_arglab(int code, std::vector<std::string> cmdarglab)
{
    bool flag = false;
    size_t size_arglab = cmdarglab.size();
    for (int i = 0; i < size_arglab; i++)
    {
        if (code == CODEARGLAB+i)
        {
            flag = true;
            i = size_arglab+1;
        }
    }
    return flag;
}

bool semanalysis::is_argnum(int code, std::vector<std::string> cmdargnum)
{
    bool flag = false;
    size_t size_argnum = cmdargnum.size();
    for (int i = 0; i < size_argnum; i++)
    {
        if (code == CODEARGNUM+i)
        {
            flag = true;
            i = size_argnum+1;
        }
    }
    return flag;
}

bool semanalysis::is_argrgst(int code, std::vector<std::string> cmdargrgst)
{
    bool flag = false;
    size_t size_argrgst = cmdargrgst.size();
    for (int i = 0; i < size_argrgst; i++)
    {
        if (code == CODEARGRGST+i)
        {
            flag = true;
            i = size_argrgst+1;
        }
    }
    return flag;
}

bool semanalysis::is_label1(int code, std::vector<label> masslabel)
{
    bool flag = false;
    size_t size_mass = masslabel.size();
    for (int i = 0; i < size_mass; i++)
    {
        if ((code == CODELABEL+1+i) && (masslabel[i].labstr[0] == ':'))
        {
            flag = true;
            i = size_mass+1;
        }
    }
    return flag;
}

void semanalysis::analysis(std::vector<commlab> mass, std::vector<label> masslabel,std::vector<std::string> cmdnoarg,std::vector<std::string> cmdarglab,std::vector<std::string> cmdargnum,std::vector<std::string> cmdargrgst,std::vector<std::string> rgst)
{
    size_t i = 0;
    size_t size_mass = mass.size();
    size_t size_noarg = cmdnoarg.size();
    size_t size_arglab = cmdarglab.size();
    size_t size_argnum = cmdargnum.size();
    size_t size_argrgst = cmdargrgst.size();
    size_t size_rgst = rgst.size();
    bool flag = false;
    label st;
    int labsize;
    int j;
    bool flag0;
    while (i < size_mass)
    {
        bool flag_noarg = is_noarg(mass[i].code, cmdnoarg);
        bool flag_arglab = is_arglab(mass[i].code, cmdarglab);
        bool flag_argnum = is_argnum(mass[i].code, cmdargnum);
        bool flag_argrgst = is_argrgst(mass[i].code, cmdargrgst);
        bool flag_label1 = is_label1(mass[i].code, masslabel);
        if ((((mass[i].id == 'N') || mass[i].id == 'R')) && (!flag))
        {
            if (!i)
            {
                ERRORPRINT("too much arguments")
            }
            else
            {
                if (!flag_noarg)
                {
                    ERRORPRINT("too much arguments")
                }
                else
                {
                    if (mass[i].id == 'N')
                    {
                        ERRORPRINT("pop can have only register as an argument")
                    }
                }
            }
        }
        if ((mass[i].id == 'C') && (flag_noarg || flag_arglab || flag_argnum || flag_argrgst))
        {
            if (flag)
            {
                ERRORPRINT("You try to use function as an argument")
            }
        }
        if ((mass[i].id == 'C') && (flag_arglab || flag_argnum || flag_argrgst) && (!flag))
        {
            if (size_mass-1 == i)
            {
                ERRORPRINT("call, push, jmp must have arguments");
            }
            flag = true;
        }
        if (((mass[i].id == 'N') || (mass[i].id == 'R')) && (flag))
        {
            if (flag_arglab)
            {
                ERRORPRINT("jmp, call must have label as an argument");
            }
            flag = false;
        }
        if ((!flag_label1) && (mass[i].id == 'K'))  //K  func1:
        {
            if (flag)
            {
                ERRORPRINT("You try to use wrong label as an argument")
            }
            else
                flag = false;
        }
        if ((flag_label1) && (mass[i].id == 'L'))  //L
        {
            if (!i)
            {
                ERRORPRINT("Not available postion of label")
            }
            else
            {
                if (is_arglab(mass[i-1].code, cmdarglab))
                    flag = false;
                else
                    {
                        ERRORPRINT("Not available use of label")
                    }
            }
        }
    i++;
    }
    int sizem = masslabel.size();
    //printf("*********************\n");
    /*for (int k = 0; k < sizem; k++)
    {
        printf("label[%i]: %i \n", k, masslabel[k].labcode);
    }*/
}

void semanalysis::checklabel(std::vector<label> masslabel)
{
    size_t size_mass = masslabel.size();
    for (int i = 0; i < size_mass; i++)
    {
        if (masslabel[i].labstr[0] == ':')
            label2.push_back(masslabel[i]);
        else
            label1.push_back(masslabel[i]);
    }
    size_t size_label1 = label1.size();
    size_t size_label2 = label2.size();
    for (size_t i = 0; i < size_label2; i++)
    {
        int match = 0;
        std::string str2;
        str2.append(label2[i].labstr.c_str());
        str2.append(":");
        for (size_t j = 0; j < size_label1; j++)
        {
            std::string str1;
            str1.append(":");
            str1.append(label1[j].labstr);
            if (str1 == str2)
            {
                match++;
                label2[i].prevnum = j;
            }
        }
        if (!match)
        {
            printf("\nThere is no first label for the %s\n", label2[i].labstr.c_str());
            printf("press any key...\n");
            getch();
            exit(1);
        }
        if (match > 1)
        {
            printf("\nThere are too mush first labels for the %s\n", label2[i].labstr.c_str());
            printf("press any key...\n");
            getch();
            exit(1);
        }
    }
}

void semanalysis::output(char * filename, std::vector<commlab> mass)
{
    if(filename == NULL)
    {
        ERRORPRINT("Error open file")
    }
    /*for (int x = 0; x < label2.size(); x++)
    {
        printf("label2[%i].prevnum: %i\n", x, label2[x].prevnum);
    }*/
    FILE * f = fopen(filename,"wb");
    size_t size_mass = mass.size();
    int iter = 0;
    for (size_t i = 0; i < size_mass; i++)
    {
        if (mass[i].id != 'K')
        {
            int x = mass[i].code;
            size_t length_str = 0;
            while (x)
            {
                x = x / 10;
                length_str++;
            }
            char str[length_str];
            char str_id[1];
            str_id[0] = mass[i].id;
            itoa(mass[i].code, str, 10);
            fwrite(str, length_str, 1, f);
            fwrite(" ", 1, 1, f);
            fwrite(str_id, 1, 1, f);
            if (mass[i].id == 'L')
            {
                fwrite(" ", 1, 1, f);
                int jmp_num = label1[label2[iter].prevnum].labnum - label2[iter].prevnum+1;
                int y = jmp_num;
                size_t length_str1 = 0;
                while (y)
                {
                    y = y / 10;
                    length_str1++;
                }
                char str1[length_str1];
                itoa(jmp_num, str1, 10);
                fwrite(str1, length_str1, 1, f);
                iter++;
            }
            fprintf (f, "\r\n");
        }
    }
}
