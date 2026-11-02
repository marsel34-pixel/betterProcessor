
#include "funcForProcessor.h"

#include "stdio.h"
#include <math.h>


void ADD(stack *stk)
{
    if(stk->size < 2){
        printf("Too small stack to add");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    pushStack(stk, x+y);
}
void OUTM(stack *stk)
{
    if(stk->size < 1){
        printf("Too small stack to out");
        assert(0);
    }
    int x = 0;
    popStack(stk, &x);
    printf("%d\n", x);
}

void SUB(stack *stk)
{
    if(stk->size < 2){
        printf("Too small stack to sub");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    pushStack(stk, y-x);
}
void MUL(stack *stk)
{
    if(stk->size < 2){
        printf("Too small stack to mul");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    pushStack(stk, x*y);
}
int DIV(processor *pc)
{
    if(pc->workStack.size < 2){
        printf("Too small stack to div");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&pc->workStack, &x);
    popStack(&pc->workStack, &y);
    if(x == 0)
    {
        return 1;
    }

    pushStack(&pc->workStack, y/x);
    return 0;
}

void POP(int num, processor *comp, unsigned char* machineCode, int* PC)
{
    int len = 0;
    int x = 0;
    popStack(&comp->workStack, &x);
    //printf("num %d\n", num);
    //printf("x = %d\n",num);
    if(num & 0x80)
    {
        
        if (num & 0x40)
        {
            //printf("%d\n",comp->regOfProcessor[machineCode[(*PC)]] );
            len += comp->regOfProcessor[FromPointerToInt(machineCode + *PC)];
            (*PC) += 4;
        }
        if (num & 0x20)
        {
            len += FromPointerToInt(machineCode + *PC);
            //printf("len %d", len);
            (*PC) += 4;
        }
        
        //printf("l = %d\n",len);
        comp->RAM[len] = x;
    }
    else
    {
        comp->regOfProcessor[FromPointerToInt(machineCode + *PC)] = x;
        (*PC) += 4;
    }
    
    
}

void PUSHreg(processor *comp, int reg)
{
    pushStack(&comp->workStack, comp->regOfProcessor[reg]);
}

void processorDump(processor *comp, unsigned char* machineCode, int PC)
{
    
    stackDump(&comp->funcStack);
    stackDump(&comp->workStack);
    putchar('\n');

    for (int i = 0; i < 4; i++)
    {
        printf("%d reg = %d\n", i, comp->regOfProcessor[i]);
    }
    int startPoint = (PC - lefterThanPC) >= 0 ? PC - lefterThanPC : 0;
    for (int i = startPoint; i < PC + righterThanPC; i++)
    {
        printf("|%5d", machineCode[i]);
    }
    printf("|\n");
    for (int i = startPoint; i < PC; i++)
    {
        printf("      ");
    }
    printf("   ^");
    putchar('\n');
    printf("currectPc = %d", PC);
}

void JUMP(int* PC, int step)
{
    *PC -= step;
}

void JUMA(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x>y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}

void JUMB(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x<y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}

void JUMEA(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x>=y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}

void JUMEB(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x<=y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}

void JUME(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x==y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}
void JUMNE(stack *stk, int *PC, int num)
{
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    if (x != y)
    {
        *PC = num;
    }
    else
    {
        *PC+=4;
    }
}
void DIVO(stack *stk)
{
     if(stk->size < 2){
        printf("Too small stack to div");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(stk, &x);
    popStack(stk, &y);
    pushStack(stk, y%x);
}

void CALL(stack* funcStack, int* PC, int num)
{
    pushStack(funcStack, *PC);
    *PC = num;
}

void RET(stack* funcStack, int* PC)
{
    int x = 0;
    popStack(funcStack, &x);
    *PC = x;
}

void INM(stack *stk)
{
    int x = 0;
    scanf("%d", &x);
    pushStack(stk, x);
}

void SQRT(stack *stk)
{
    int x = 0;
    popStack(stk, &x);
    pushStack(stk, (int)sqrt(x));
}


void DRAW(int *RAM)
{
    for (int i = 0; i< sizeOfRAMLineY; i++)
    {
        for (int j = 0; j < sizeOfRAMLineX; j++)
        {
            putchar(RAM[i * sizeOfRAMLineX + j] > 0 ? ' ' : '*');
            //printf("%d ", RAM[i * sizeOfRAMLine + j]);
        }
        putchar('\n');
    }
}

void SIN(stack *stk)
{
    int x = 0;
    popStack(stk, &x);
    pushStack(stk, 1000 * sin(x * (M_PI/180)));
}

void COS(stack *stk)
{
    int x = 0;
    popStack(stk, &x);
    pushStack(stk, 1000 * cos(x * (M_PI/180)));
}
int FromPointerToInt(unsigned char* c)
{
    return c[0] << 24 | c[1] << 16 | c[2] << 8 | c[3];
}
void PushGOD(int x, unsigned char* machineCode, int* PC, processor *comp)
{
    int len = 0;
    if (x & 0x40)
    {
        //printf("%d", comp->regOfProcessor[machineCode[(*PC)]]);
        len += comp->regOfProcessor[FromPointerToInt(machineCode + *PC)];
        (*PC) += 4;
    }
    if (x & 0x20)
    {
        
        len += FromPointerToInt(machineCode + *PC);
        (*PC) += 4;
       
    }
    
    if (x & 0x80)
    {
        //printf("len2 = %d\n", len);
        len = comp->RAM[len];
    }
    pushStack(&comp->workStack, len);
}