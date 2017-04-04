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

const int CODENOARG = 50;
const int CODEARGLAB = 100;
const int CODEARGNUM = 150;
const int CODEARGRGST = 200;
const int CODERGST = 250;
const int CODELABEL = 299;

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
        bool is_empty();
        size_t size();
        void empty();
        void dump();
        bool ok() const;
        int * data;
        size_t size_val;
        size_t capacity_val;
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
};

class CPU
{
    public:
    void run(std::vector<cmd_mass_struct> cmd_mass);
    void cmd_case_N(cmd_mass_struct cmd_mass_i);
    void cmd_case_R(cmd_mass_struct cmd_mass_i);
    void cmd_case_C(cmd_mass_struct cmd_mass_i);
    int cmd_case_L(cmd_mass_struct cmd_mass_i);
    void push(int value);
    void push_func(int value);
    void push_rgst(int value, int code_rgst);
    int pop();
    int pop_func();
    int pop_stay();
    void out();
    void in();
    void sub();
    void mul();
    void div();
    void add();
    void sin_int();
    void cos_int();
    void sqrt_int();
    int ax;
    int bx;
    int cx;
    int dx;
    stack stack_;
    stack stack_func;
    CPU():
        stack_(1),
        stack_func(1)
        {}
};

int main()
{
    CPU r;
    ReadFile file;
    file.reading("C:/Users/Alex/Desktop/Codes/Assembler/ASM.txt");
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

void CPU::run(std::vector<cmd_mass_struct> cmd_mass)
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

void CPU::cmd_case_N(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    default:
    {
        push(cmd_mass_i.argcode);
    }
}

int CPU::cmd_case_L(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODEARGLAB:
        {
            return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+1:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top > down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+2:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top < down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+3:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top == down)
                return -2;
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+4:
        {
            push_func(cmd_mass_i.code);
            return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+5:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top > down)
            {
                push_func(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+6:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top < down)
            {
                push_func(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
        case CODEARGLAB+7:
        {
            int top = pop();
            int down = pop();
            push(down);
            push(top);
            if (top == down)
            {
                push_func(cmd_mass_i.code);
                return -2;
            }
            else
                return cmd_mass_i.argcode-2;
        }
    }
}

void CPU::cmd_case_R(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODEARGRGST:
        {
            switch (cmd_mass_i.argcode)
            {
                case CODERGST:
                {
                    ax = pop();
                    break;
                }
                case CODERGST+1:
                {
                    bx = pop();
                    break;
                }
                case CODERGST+2:
                {
                    cx = pop();
                    break;
                }
                case CODERGST+3:
                {
                    dx = pop();
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
                    push(ax);
                    break;
                }
                case CODERGST+1:
                {
                    push(bx);
                    break;
                }
                case CODERGST+2:
                {
                    push(cx);
                    break;
                }
                case CODERGST+3:
                {
                    push(dx);
                    break;
                }
            }
            break;
        }
    }
}

void CPU::cmd_case_C(cmd_mass_struct cmd_mass_i)
{
    switch (cmd_mass_i.code)
    {
        case CODENOARG:
        {
            int x = pop();
            break;
        }
        case CODENOARG+1:
        {
            out();
            break;
        }
        case CODENOARG+2:
        {
            in();
            break;
        }
        case CODENOARG+3:
        {
            sub();
            break;
        }
        case CODENOARG+4:
        {
            mul();
            break;
        }
        case CODENOARG+5:
        {
            div();
            break;
        }
        case CODENOARG+6:
        {
            add();
            break;
        }
        case CODENOARG+7:
        {
            sin_int();
            break;
        }
        case CODENOARG+8:
        {
            cos_int();
            break;
        }
        case CODENOARG+9:
        {
            sqrt_int();
            break;
        }
        case CODENOARG+10:  //ret()
        {
            //printf("@@@@@@@@@@@@\n");
            pop_func();
            break;
        }
        case CODENOARG+11:
        {
            int x = pop();
            push(++x);
            break;
        }
        case CODENOARG+12:
        {
            int x = pop();
            push(--x);
            break;
        }
    }
}

bool stack::ok() const
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

void CPU::push(int value)
{
    if (stack_.ok())
    {
        if (stack_.size_val >= stack_.capacity_val)
            stack_.data = (int*) realloc(stack_.data,(++stack_.capacity_val)*sizeof(int));
        stack_.data[stack_.size_val++] = value;
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using 'push()' in stack\n");
    }
}

void CPU::push_func(int value)
{
    if (stack_func.ok())
    {
        if (stack_func.size_val >= stack_func.capacity_val)
            stack_func.data = (int*) realloc(stack_func.data,(++stack_func.capacity_val)*sizeof(int));
        stack_func.data[stack_func.size_val++] = value;
    }
    else
    {
        stack_func.dump();
        ERRORPRINT("error at the stage of using 'push()' in stack_func\n");
    }
}

void CPU::push_rgst(int value, int code_rgst)
{
    if (stack_.ok())
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
        stack_.dump();
        ERRORPRINT("error at the stage of using 'push_rgst()' in stack\n");
    }
}

int CPU::pop()
{
    if (stack_.ok())
    {
        if (stack_.size_val)
        {
            int curr_size = stack_.size_val;
            stack_.size_val--;
            return stack_.data[curr_size-1];
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You can`t use 'pop' if stack is empty");
        }
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack");
    }
}

int CPU::pop_func()
{
    if (stack_func.ok())
    {
        if (stack_func.size_val)
        {
            int curr_size = stack_func.size_val;
            stack_func.size_val--;
            return stack_func.data[curr_size-1];
        }
        else
        {
            stack_func.dump();
            ERRORPRINT("You can`t use 'pop' if stack_func is empty");
        }
    }
    else
    {
        stack_func.dump();
        ERRORPRINT("error at the stage of using 'pop()' in stack_func");
    }
}

int CPU::pop_stay()
{
    if (stack_.ok())
    {
        if (stack_.size_val)
        {
            int curr_size = stack_.size_val;
            return stack_.data[curr_size];
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You can`t use 'pop' if stack_func is empty");
        }
    }
    else
    {
        stack_.dump();
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

void stack::dump()
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

void CPU::in()
{
    if (stack_.ok())
    {
        int number;
        scanf("%i", &number);
        push(number);
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using in()");
    }
}

void CPU::sub()
{
    if (stack_.ok())
    {
        if (stack_.size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top - down);
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You need more elements at stack to use 'sub'");
        }
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using sub()");
    }
}

void CPU::mul()
{
    if (stack_.ok())
    {
        if (stack_.size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top*down);
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You need more elements at stack to use 'mul'");
        }
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using mul()");
    }
}

void CPU::add()
{
    if (stack_.ok())
    {
        if (stack_.size_val>=2)
        {
            int top = pop();
            int down = pop();
            push(top+down);
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You need more elements at stack to use 'add'");
        }
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using add()");
    }
}

void CPU::div()
{
    if (stack_.ok())
    {
        if (stack_.size_val>=2)
        {
            int top = pop();
            int down = pop();
            push((int)(top/down));
        }
        else
        {
            stack_.dump();
            ERRORPRINT("You need more elements at stack to use 'div'");
        }
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using div()");
    }
}

void CPU::out()
{
    if (stack_.ok())
    {
        if (!stack_.is_empty())
            for (size_t i = 0; i < stack_.size_val; i++)
                printf("%i: %i\n",i, stack_.data[i]);
        else printf("stack is empty\n");
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using out()");
    }
}

void CPU::sin_int()
{
    if (stack_.ok())
    {
        if (!stack_.is_empty())
            push(sin(pop()));
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using sin_int()");
    }
}

void CPU::cos_int()
{
    if (stack_.ok())
    {
        if (!stack_.is_empty())
            push(cos(pop()));
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using cos_int()");
    }
}

void CPU::sqrt_int()
{
    if (stack_.ok())
    {
        if (!stack_.is_empty())
            push(sqrt(pop()));
    }
    else
    {
        stack_.dump();
        ERRORPRINT("error at the stage of using sqrt_int()");
    }
}
