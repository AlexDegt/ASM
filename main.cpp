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
#include <math.h>

#define CODENOARG 50
#define CODEARGLAB 100
#define CODEARGNUM 150
#define CODEARGRGST 200
#define CODERGST 250
#define CODELABEL 299
#define NOARGSIZE 11
#define ARGLABSIZE 2
#define ARGNUMSIZE 1
#define ARGRGSTSIZE 2
#define RGSTSIZE 4

#define ERRORPRINT(a)\
    printf("\n***************\n");\
    printf(a);\
    printf("\npress any key...");\
    printf("\n***************\n");\
    getch();\
    exit(1);
//using namespace std;

class stack
{
    public:
        stack();
        explicit stack(size_t capacit);
        ~stack();
        void push(int value);
        void push_rgst(int value, int code_rgst);
        int pop();
        int pop_stay();
        void empty();
        bool is_empty();
        size_t size();
        void out();
        void in();
        void sub();
        void mul();
        void div();
        void dump();
        void add();
        void sin_int();
        void cos_int();
        void sqrt_int();
        int ax;
        int bx;
        int cx;
        int dx;
    private:
        int * data;
        size_t size_val;
        size_t capacity_val;
        bool ok() const;
};

class stack_func{
    public:
        stack_func();
        explicit stack_func(size_t capacit);
        ~stack_func();
        void push(int value);
        int pop();
        int pop_stay();
        void dump();
        void empty();
        bool is_empty();
        size_t size();
    private:
        int * data;
        size_t size_val;
        size_t capacity_val;
        bool ok() const;
};

struct cmd_mass_struct{
    int code;
    int argcode;
    char id;
    cmd_mass_struct():
        code(),
        argcode(),
        id()
        {}
};

class ReadFile
{
    public:
    void reading(char * filename);
    std::vector<cmd_mass_struct> cmd_mass;
    ReadFile():
        cmd_mass()
        {}
    //void run
};

class class_RUN
{
    public:
    void run(std::vector<cmd_mass_struct> cmd_mass);
    void cmd_case_N(cmd_mass_struct cmd_mass_i);
    void cmd_case_R(cmd_mass_struct cmd_mass_i);
    void cmd_case_C(cmd_mass_struct cmd_mass_i);
    int cmd_case_L(cmd_mass_struct cmd_mass_i);
    stack stack_;
    stack_func stack_func_;
    class_RUN():
        stack_(1),
        stack_func_(1)
        {}
};

int main()
{
    class_RUN r;
    ReadFile file;
    file.reading("ASM.txt");
    r.run(file.cmd_mass);
    system("PAUSE");
    return 0;
}

void ReadFile::reading(char * filename)
{
    FILE * f = fopen(filename,"r");
    int endfile;
    cmd_mass_struct str_fl;
    while (endfile != EOF)
    {
        char code_read[10] = {};
        char argcode_read[10] = {};
        char id_read[1] = {};
        endfile = fscanf(f, "%s", code_read);
        if (endfile == EOF) break;
        fscanf(f, "%s", argcode_read);
        str_fl.argcode = atoi(argcode_read);
        fscanf(f, "%s", id_read);
        //str_fl.argcode = atoi(argcode_read);
        str_fl.code = atoi(code_read);
        str_fl.id = id_read[0];
        cmd_mass.push_back(str_fl);
    }
    /*for (int i = 0; i < cmd_mass.size(); i++)
    {
        printf("cmd_mass[%i].code = %i   cmd_mass[%i].argcode = %i   cmd_mass[%i].id = %c\n",i, cmd_mass[i].code, i, cmd_mass[i].argcode, i, cmd_mass[i].id);
    }*/
}

void class_RUN::run(std::vector<cmd_mass_struct> cmd_mass)
{
    size_t size_mass = cmd_mass.size();
    for (int i = 0; i < size_mass; i++)
    {
        switch (cmd_mass[i].id)
        {
            case 'N':
            {
                cmd_case_N(cmd_mass[i]);
                break;
            }
            case 'R':
            {
                cmd_case_R(cmd_mass[i]);
                break;
            }
            case 'C':
            {
                cmd_case_C(cmd_mass[i]);
                break;
            }
            case 'L':
            {
                int flag = cmd_case_L(cmd_mass[i]);
                if (flag != -2)
                    i = flag;
                break;
            }
        }
    }
}

void class_RUN::cmd_case_N(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    default:
    {
        stack_.push(cmd_mass_i.argcode);
    }
}

int class_RUN::cmd_case_L(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODEARGLAB:
        {
            return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+1:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top > down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+2:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top < down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+3:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top == down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+4:
        {
            stack_func_.push(cmd_mass_i.code);
            return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+5:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top > down)
            {
                stack_func_.push(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+6:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top < down)
            {
                stack_func_.push(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+7:
        {
            int top = stack_.pop();
            int down = stack_.pop();
            stack_.push(down);
            stack_.push(top);
            if (top == down)
            {
                stack_func_.push(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
    }
}

void class_RUN::cmd_case_R(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODEARGRGST:
        {
            switch (cmd_mass_i.argcode)
            {
                case CODERGST:
                {
                    stack_.ax = stack_.pop();
                    break;
                }
                case CODERGST+1:
                {
                    stack_.bx = stack_.pop();
                    break;
                }
                case CODERGST+2:
                {
                    stack_.cx = stack_.pop();
                    break;
                }
                case CODERGST+3:
                {
                    stack_.dx = stack_.pop();
                    break;
                }
            }
            break;
        }
         case CODEARGRGST+1:
        {
            switch (cmd_mass_i.argcode)
            {
                case CODERGST:
                {
                    stack_.push(stack_.ax);
                    break;
                }
                case CODERGST+1:
                {
                    stack_.push(stack_.bx);
                    break;
                }
                case CODERGST+2:
                {
                    stack_.push(stack_.cx);
                    break;
                }
                case CODERGST+3:
                {
                    stack_.push(stack_.dx);
                    break;
                }
            }
            break;
        }
    }
}

void class_RUN::cmd_case_C(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODENOARG:
        {
            int x = stack_.pop();
            break;
        }
        case CODENOARG+1:
        {
            stack_.out();
            break;
        }
        case CODENOARG+2:
        {
            stack_.in();
            break;
        }
        case CODENOARG+3:
        {
            stack_.sub();
            break;
        }
        case CODENOARG+4:
        {
            stack_.mul();
            break;
        }
        case CODENOARG+5:
        {
            stack_.div();
            break;
        }
        case CODENOARG+6:
        {
            stack_.add();
            break;
        }
        case CODENOARG+7:
        {
            stack_.sin_int();
            break;
        }
        case CODENOARG+8:
        {
            stack_.cos_int();
            break;
        }
        case CODENOARG+9:
        {
            stack_.sqrt_int();
            break;
        }
        case CODENOARG+10:  //ret()
        {
            //printf("@@@@@@@@@@@@\n");
            stack_func_.pop();
            break;
        }
        case CODENOARG+11:
        {
            int x = stack_.pop();
            stack_.push(++x);
            break;
        }
        case CODENOARG+12:
        {
            int x = stack_.pop();
            stack_.push(--x);
            break;
        }
    }
}

bool stack::ok() const
{
    return (this && (data && capacity_val && size_val <= capacity_val));
}

bool stack_func::ok() const
{
    return (this && (data && capacity_val && size_val <= capacity_val));
}

stack::stack(size_t capacit):
        data(new(std::nothrow)int[capacit]),
        capacity_val(capacit),
        size_val(0)
        {}

stack::~stack()
{
    delete data;
    data = NULL;
    size_val = 0;
    capacity_val = 0;
}

stack_func::stack_func(size_t capacit):
        data(new(std::nothrow)int[capacit]),
        capacity_val(capacit),
        size_val(0)
        {}

stack_func::~stack_func()
{
    delete data;
    data = NULL;
    size_val = 0;
    capacity_val = 0;
}

size_t stack::size()
{
    if (ok())
    {
        return size_val;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'size() in stack'\n");
    }
}

size_t stack_func::size()
{
    if (ok())
    {
        return size_val;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'size()' in stack_func\n");
    }
}

void stack::push(int value)
{
    if (ok())
    {
        if (size_val >= capacity_val)
            data = (int*) realloc(data,(++capacity_val)*sizeof(int));
        data[size_val++] = value;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'push()' in stack\n");
    }
}

void stack_func::push(int value)
{
    if (ok())
    {
        if (size_val >= capacity_val)
            data = (int*) realloc(data,(++capacity_val)*sizeof(int));
        data[size_val++] = value;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'push()' in stack_func\n");
    }
}

void stack::push_rgst(int value, int code_rgst)
{
    if (ok())
    {
        switch (code_rgst)
        {
            case CODERGST:
            {
                ax = value;
            }
            case CODERGST+1:
            {
                bx = value;
            }
            case CODERGST+2:
            {
                cx = value;
            }
            case CODERGST+3:
            {
                dx = value;
            }
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'push_rgst()' in stack\n");
    }
}

int stack::pop()
{
    if (ok())
    {
        if (size_val)
        {
            int curr_size = size_val;
            size_val--;
            return data[curr_size-1];
        }
        else
        {
            dump();
            ERRORPRINT("You can`t use 'pop' if stack is empty");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack");
    }
}

int stack_func::pop()
{
    if (ok())
    {
        if (size_val)
        {
            int curr_size = size_val;
            size_val--;
            return data[curr_size-1];
        }
        else
        {
            dump();
            ERRORPRINT("You can`t use 'pop' if stack_func is empty");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack_func");
    }
}

int stack_func::pop_stay()
{
    if (ok())
    {
        if (size_val)
        {
            int curr_size = size_val;
            return data[curr_size];
        }
        else
        {
            dump();
            ERRORPRINT("You can`t use 'pop' if stack_func is empty");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack_func");
    }
}

int stack::pop_stay()
{
    if (ok())
    {
        if (size_val)
        {
            int curr_size = size_val;
            return data[curr_size];
        }
        else
        {
            dump();
            ERRORPRINT("You can`t use 'pop' if stack_func is empty");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack_func");
    }
}

void stack::empty()
{
    if (ok())
    {
        for (size_t i = 0; i < size_val; i++)
            data[i] = 0;
        size_val = 0;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'empty()' in stack");
    }
}


void stack_func::empty()
{
    if (ok())
    {
        for (size_t i = 0; i < size_val; i++)
            data[i] = 0;
        size_val = 0;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'empty()' in stack_func");
    }
}

void stack::dump()
{
    printf("\n");
    for (size_t i = 0; i < size_val; i++)
        printf("%i: %i\n",i, data[i]);
    printf("size: %i\n", size_val);
    printf("capacity: %i\n", capacity_val);
}

void stack_func::dump()
{
    printf("\n");
    for (size_t i = 0; i < size_val; i++)
        printf("%i: %i\n",i, data[i]);
    printf("size: %i\n", size_val);
    printf("capacity: %i\n", capacity_val);
}

bool stack::is_empty()
{
    if (ok())
    {
        if (!size_val)
            return 1;
        else
            return 0;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'empty()' in stack");
    }
}

bool stack_func::is_empty()
{
    if (ok())
    {
        if (!size_val)
            return 1;
        else
            return 0;
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using 'empty()' in stack_func");
    }
}

void stack::in()
{
    if (ok())
    {
        int number;
        scanf("%i", &number);
        push(number);
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using in()");
    }
}

void stack::sub()
{
    if (ok())
    {
        if (size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top - down);
        }
        else
        {
            dump();
            ERRORPRINT("You need more elements at stack to use 'sub'");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using sub()");
    }
}

void stack::mul()
{
    if (ok())
    {
        if (size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top*down);
        }
        else
        {
            dump();
            ERRORPRINT("You need more elements at stack to use 'mul'");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using mul()");
    }
}

void stack::add()
{
    if (ok())
    {
        if (size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top+down);
        }
        else
        {
            dump();
            ERRORPRINT("You need more elements at stack to use 'add'");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using add()");
    }
}


void stack::div()
{
    if (ok())
    {
        if (size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top/down);
        }
        else
        {
            dump();
            ERRORPRINT("You need more elements at stack to use 'div'");
        }
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using div()");
    }
}

void stack::out()
{
    if (ok())
    {
        if (!is_empty())
            for (size_t i = 0; i < size_val; i++)
                printf("%i: %i\n",i, data[i]);
        else printf("stack is empty\n");
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using out()");
    }
}

void stack::sin_int()
{
    if (ok())
    {
        if (!is_empty())
            push(sin(pop()));
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using sin_int()");
    }
}

void stack::cos_int()
{
    if (ok())
    {
        if (!is_empty())
            push(cos(pop()));
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using cos_int()");
    }
}

void stack::sqrt_int()
{
    if (ok())
    {
        if (!is_empty())
            push(sqrt(pop()));
    }
    else
    {
        dump();
        ERRORPRINT("error at the stage of using sqrt_int()");
    }
}
