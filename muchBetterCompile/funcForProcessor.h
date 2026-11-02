
#include "stackM.h"
#include <assert.h>


#ifndef funcForProc
#define funcForProc
const int lefterThanPC = 5;
const int righterThanPC = 10;
const int sizeOfRAMLineX = 200;
const int sizeOfRAMLineY = 200;
struct processor
{
    stack workStack;
    stack funcStack;
    int* RAM;
    int PC;
    int regOfProcessor[4];
};
void DIVO(stack *stk);

void JUMA(stack *stk, int *PC, int num);
void JUMB(stack *stk, int *PC, int num);
void JUMEA(stack *stk, int *PC, int num);
void JUMEB(stack *stk, int *PC, int num);
void JUME(stack *stk, int *PC, int num);
void JUMNE(stack *stk, int *PC, int num);
int FromPointerToInt(unsigned char* c);

void processorDump(processor *comp, unsigned char* machineCode, int PC);
void PUSHreg(processor *comp, int reg);
void POP(int num, processor *comp, unsigned char* machineCode, int* PC);
void ADD(stack *stk);
void OUTM(stack *stk);
void SUB(stack *stk);
void MUL(stack *stk);
int DIV(processor *pc);
void RET(stack* funcStack, int* PC);
void CALL(stack* funcStack, int* PC, int num);
void INM(stack *stk);
void SQRT(stack *stk);


void POPMR(processor *comp, int *RAM, int i);
void PUSHMR(processor *comp, int *RAM, int i);
void POPM(stack *stk, int *RAM, int i);
void PUSHM(stack *stk, int *RAM, int i);
void DRAW(int *RAM);
void SIN(stack *stk);
void COS(stack *stk);
void PushGOD(int x, unsigned char* machineCode, int* PC, processor *comp);

#endif