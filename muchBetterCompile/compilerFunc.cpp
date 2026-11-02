#include "compilerFunc.h"

int fromComandToNum(const char* comand, int secondIsNum)
{
    if(strcmp(comand, "PUSH") == 0 && secondIsNum)
    {
        return PUSH;
    }
    else if (strcmp(comand, "PUSH") == 0 && !secondIsNum)
    {
        return PUSHr;
    }
    else if (strcmp(comand, "ADD")== 0)
    {
        return ADDc;
    }
    else if (strcmp(comand, "OUT")== 0)
    {
        return OUTc;
    }
    else if (strcmp(comand, "SUB")== 0)
    {
        return SUBc;
    }
    else if (strcmp(comand, "MUL")== 0)
    {
        return MULc;
    }
    else if (strcmp(comand, "DIV") == 0)
    {
        return DIVc;
    }
    else if (strcmp(comand, "POP") == 0)
    {
        return POPc;
    }
    else if (strcmp(comand, "JUM") == 0)
    {
        return JUMc;
    }
    else if (strcmp(comand, "JUMA") == 0)
    {
        return JUMAc;
    }
    else if (strcmp(comand, "JUMB") == 0)
    {
        return JUMBc;
    }
    else if (strcmp(comand, "JUMEB") == 0)
    {
        return JUMEBc;
    }
    else if (strcmp(comand, "JUMEA") == 0)
    {
        return JUMEAc;
    }
    else if (strcmp(comand, "JUME") == 0)
    {
        return JUMEc;
    }
    else if (strcmp(comand, "JUMNE") == 0)
    {
        return JUMNEc;
    }
    else if (strcmp(comand, "DIVO") == 0)
    {
        return DIVOc;
    }
    else if (strcmp(comand, "HLT") == 0)
    {
        return HLT;
    }
    else if (strcmp(comand, "CALL") == 0)
    {
        return CALLc;
    }
    else if (strcmp(comand, "RET") == 0)
    {
        return RETc;
    }
    else if(strcmp(comand, "IN") == 0)
    {
        return INc;
    }
    else if(strcmp(comand, "SQRT") == 0)
    {
        return SQRTc;
    }
    else if(strcmp(comand, "DRAW") == 0)
    {
        return DRAWc;
    }
    else if (strcasecmp(comand,"SIN") == 0)
    {
        return SINc;
    }
    else if (strcasecmp(comand,"COS") == 0)
    {
        return COSc;
    }
    else if (strcasecmp(comand,"GETK") == 0)
    {
        return GET_KEYc;
    }
    printf("something Wrong <%s>", comand);
    assert(0);
    return 0;
}

int fromStrToNum(const char* str)
{
    if (strcmp(str, "AX") == 0)
    {
        return AX;
    }
    else if (strcmp(str, "BX") == 0)
    {
        return BX;
    }
    else if (strcmp(str, "CX") == 0)
    {
        return CX;
    }
    else if (strcmp(str, "DX") == 0)
    {
        return DX;
    }
    
    printf("Bad str\n");
    assert(0);
    return -1;
}

void addElementToArray(bufferC *buf, int el, int bytes)
{
    if(buf->sizeofCode + 4 <= buf->len)
    {
        
        (buf->sizeofCode) *= 2;
        buf->machineCode = (unsigned char*)realloc(buf->machineCode, buf->sizeofCode);
        //printf("%p", buf);
        
    }
    for (int i = bytes - 1; i >= 0; i--)
    {
        //printf("%d ", (unsigned char)(el >> (i*8)));
        buf->machineCode[buf->len] = (unsigned char)(el >> (i*8));
        buf->len++;
    }
    
}

void addCode(bufferC *buf, FILE* CodeTxt, char numArgs, int first, int second, int third)
{
    if (numArgs == 3)
    {
        fprintf(CodeTxt, "%d %d %d\n", first, second, third);
        addElementToArray(buf, first, 1);
        addElementToArray(buf, second, 4);
        addElementToArray(buf, third, 4);
    }
    else if (numArgs == 2)
    {
        fprintf(CodeTxt, "%d %d\n", first, second);
        addElementToArray(buf, first, 1);
        addElementToArray(buf, second, 4);
    }
    else
    {
        fprintf(CodeTxt, "%d\n", first);
        addElementToArray(buf, first, 1);
    }
}
void analizePUSH(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code)
{
    int numberOfScnaf = 0;
    int numberBuf = 0;
    char nameReg[20] = {};
    (*lenCode)+=5;
    if (comand2[0] == '[')
    {
        numberOfScnaf = sscanf(comand2, "[%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0xE1, fromStrToNum(nameReg), numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            
            addCode(bufferCode, Code, 2, 0xC1, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "[%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0xA1, numberBuf, 0);
        }
    }
    else
    {
        numberOfScnaf = sscanf(comand2, "%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0x61, fromStrToNum(nameReg), numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            
            addCode(bufferCode, Code, 2, 0x41, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0x21, numberBuf, 0);
        }
    }
}

void analizePOP(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code)
{
    (*lenCode)+=5;
    int numberOfScnaf = 0;
    int numberBuf = 0;
    char nameReg[20] = {};
    if (comand2[0] == '[')
    {
        numberOfScnaf = sscanf(comand2, "[%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0xE7, fromStrToNum(nameReg), 
                numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            addCode(bufferCode, Code, 2, 0xC7, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "[%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0xA7, numberBuf, 0);
        }
    }
    else
    {
        numberOfScnaf = sscanf(comand2, "%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2 || numberOfScnaf == 0)
        {
            assert(0);
        }
        else
        {
            addCode(bufferCode, Code, 2, 0x47, fromStrToNum(nameReg), 0);
        }
    }
}

void analizeTwos(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels)
{
    char* endNumberPtr = NULL;
    int numberBuf = strtod(comand2, &endNumberPtr);

    (*lenCode)+=5;
    if (*endNumberPtr == '\0')
    {
        endNumberPtr == NULL;
        addCode(bufferCode, Code, 2, fromComandToNum(comand, 1),numberBuf,0);
    }
    else
    {
        if (comand2[0] == ':')
        {
            numberBuf = strtod(comand2 + 1, &endNumberPtr);
            assert(*endNumberPtr == '\0');
            addCode(bufferCode, Code, 2, fromComandToNum(comand, 1),labels[numberBuf],0);
        }
        else
        {
            addCode(bufferCode, Code, 2, fromComandToNum(comand, 0),fromStrToNum(comand2),0);
        }
    }
}
void analizeONEs(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels)
{
    char* endNumberPtr = NULL;
    int numberBuf = 0;
    if (comand[0] == ':')
    {
        numberBuf = strtod(comand + 1, &endNumberPtr);
        if (*endNumberPtr != '\0')
        {
            printf("wrongLabel\n");
            assert(0);
        }
        
        labels[numberBuf] = *lenCode;
        //printf("%d", labels[numberBuf]);
    }
    else
    {
        (*lenCode)++;
        addCode(bufferCode, Code, 1, fromComandToNum(comand, 0),0,0);
    }
}