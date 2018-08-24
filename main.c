//
//  main.c
//  Simple z80 Emulator
//
//  Created by Alexander Stebner on 15.02.18.
//  Copyright © 2018 Alexander Stebner. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"


#define startAmount 100 //Amount of initial code bytes

byte programMemory[0x10000]; //10000 max
byte outputMemory[0x8000]; //8000 max
//unsigned int pointer = 0;
unsigned int maxProgramSteps = 1000;
unsigned int programMemorySize = 0x8000;
unsigned int dataMemorySize = 0x8000;
char * history[1000]; //1000000 max
unsigned int steps = 0;
int nopCounter = 0;
const int maxNOPs = 0x10000; //How often NOP code can be executed before the program ends (to increase steps even with an empty program)

//Registers
struct registers {
    struct {
        union {
            struct {
                unsigned char f;
                unsigned char a;
            };
            unsigned short af;
        };
    };
    
    struct {
        union {
            struct {
                unsigned char c;
                unsigned char b;
            };
            unsigned short bc;
        };
    };
    
    struct {
        union {
            struct {
                unsigned char e;
                unsigned char d;
            };
            unsigned short de;
        };
    };
    
    struct {
        union {
            struct {
                unsigned char l;
                unsigned char h;
            };
            unsigned short hl;
        };
    };
    
    
    struct {
        union {
            struct {
                unsigned char spl;
                unsigned char sph;
            };
            unsigned short sp;
        };
    };
    struct {
        union {
            struct {
                unsigned char pcl;
                unsigned char pch;
            };
            unsigned short pc;
        };
    };
} extern registers;
struct registers reg = {0,0,0,0,0,0};





byte * createRandom( ) {
    
    static byte r[startAmount];
    int i;
    
    
    for ( i = 0; i < startAmount; ++i) {
        r[i] = rand();

    }
    
    /*r[0] = 0xe8;
    r[2] = 0x20;
    r[3] = 0x67;*/

    return r;
}

void Execute(void);


int main(int argc, const char * argv[]) {
    
    /*Arguments:
     1: Inputfile (csv-Format)
     2: Maximal size of Program code
     3: Maximal size of Input / Output data
     4: Maximal number of program steps
     5: row delimiter (excel default 0x0D0A)
     */
    

    
    programMemorySize = atoi(argv[2]);
    dataMemorySize = atoi(argv[3]);
    maxProgramSteps = atoi(argv[4]);
    
    //GET Row Delimiter int-Array from Argument
    int len = (int)strlen(argv[5]) / 2;
    char rowDelimiter[len+1];
    for (int x = 0; x < len; x++){
        char subbuff[3];
        memcpy( subbuff, &argv[5][x * 2], 2 );
        subbuff[2] = '\0';
        rowDelimiter[x] = (int)strtol(subbuff, NULL, 16);
    }
    rowDelimiter[len] = '\0';
    
    //Standard values during development in Xcode
    programMemorySize = 100;
    dataMemorySize = 5;
    
    
    
    
    FILE *dic;
    /* set the random seed */
    srand( (unsigned)time( NULL ) );
    
    //Open Input file (acc. to argument 1)
    if ((dic = fopen(argv[1], "rb")) == NULL ) {
         perror("ERROR:");
        return(1);
    }
    
    char inputBuffer[1048576]; //1 MB
    
    //Retrieve the next line of data from file
    fgets(inputBuffer, 1048576, (FILE*) dic); //-load whole file instead..
    
    /* TOKENIZE STRING
     
     char *str, *token, *tofree;
     tofree = str = strdup(inputBuffer);  // We own str's memory now.
     int toggle = 1;
     while ((token = strsep(&str, rowDelimiter))){
     toggle = 1-toggle;
     if (toggle == 1) continue;
     //EXPORT TOKEN (String) HERE
     }
     free(tofree);
     */
    
    //Create initial x Bytes
    byte *random;
    
    random = createRandom();
    for (int i = 0; i < startAmount; i++){
        programMemory[i] = random[i];
    }
    for (int i = startAmount; i < sizeof programMemory; i++){
        programMemory[i] = 0;
    }
    
    for (int i = 0; i < sizeof outputMemory; i++){
        outputMemory[i] = 0;
    }
    
    //Iteration = one for each data entry (or random value)
    //Try = one for each attempt to change the code (revert back if score didn't change)
    
    Adapt(1,100000,10); //1. How many iterations, 2. How many tries, 3. after how many tries should useless code be deleted
    
   
    
    return 0;
}

int max(int a, int b){
    if (a >= b) return a;
    return b;
}

int min(int a, int b){
    if (a <= b) return a;
    return b;
}

long compareInputOutput(){

    //Find beginning and end of data in input and output memory
    int inputBegin = 0; int inputEnd = dataMemorySize;
    int outputBegin = 0; int outputEnd = dataMemorySize;
   
    for (int x = 0; x < dataMemorySize; x++)
        if (programMemory[programMemorySize+x] != 0x00) {
            inputBegin = x; break;
        }
    for (int x = 0; x < dataMemorySize; x++)
        if (outputMemory[x] != 0x00) {
            outputBegin = x;break;
        }
    for (int x = dataMemorySize-1; x >= 0; x--)
        if (programMemory[programMemorySize+x] != 0x00) {
            inputEnd = x;break;
        }
    for (int x = dataMemorySize-1; x >= 0; x--)
        if (outputMemory[x] != 0x00) {
            outputEnd = x;break;
        }
    
    int offset = ((outputBegin - inputBegin) + (outputEnd - inputEnd)) / 2; //add offset to inputBegin to align
    
    //Loop through all output characters and compare with the nearest input neighbors
    const int width = 4;
    long score = 0;
    for (int x = outputBegin; x < outputEnd; x++){
        int _start = max(0,x-width);
        int _diff = (x-width);
        score += (0xff - abs((int)outputMemory[x] - (int)programMemory[programMemorySize+x+offset]));
        
        /*
        for (int y = _start; y < min(dataMemorySize,x+width); y++){
            int factor = (y-_start);
            if (_diff < 0) factor += -_diff;
            if (factor > width) factor = (2*width) - factor; //set factor to 0,1,2,3,4,3,2,1,0 relative to current position
            if (factor == 0) continue;
            
            
            
         score += factor * (0xff - abs((int)outputMemory[x] - (int)programMemory[programMemorySize+y+offset]));
         
        }
         */
    }
    
    return score;
}

void FlushInputOutputMemory(){
    for (int i = 0; i < sizeof outputMemory; i++){
        outputMemory[i] = 0;
    }
    for (int i = 0; i < sizeof outputMemory; i++){
        programMemory[programMemorySize + i] = 0;
    }
}

void DoRandomInsert(int range){
    int where = rand() % range;
    for (int x = programMemorySize-2; x>=where;x--){
        programMemory[x+1] = programMemory[x];
    }
    programMemory[where] = (byte)rand();
}
void DoRandomUpdate(int range){
    int where = rand() % range;
    programMemory[where] = (byte)rand();
}
void DoRandomDelete(int range){
    int where = rand() % range;
    for (int x = where; x<programMemorySize-1;x++){
        programMemory[x] = programMemory[x+1];
    }
    programMemory[programMemorySize - 1] = 0x00;
}

int FindEndOfCode(){
    int loc = 0;
    for (int x = 0; x < programMemorySize; x++){
        if (programMemory[x] != 0x00){
            loc = x;
        }
    }
    return loc;
}

void Adapt(int iterations, int tries, int triesToReduce){
    
    byte inputBackup[dataMemorySize];
    byte programBackup[programMemorySize];
    long score = 0;
    
    for (int ite = 0; ite < iterations; ite++){
        FlushInputOutputMemory();
        
        //Create random 5 bytes
        programMemory[programMemorySize+0] = rand();
        programMemory[programMemorySize+1] = rand();
        programMemory[programMemorySize+2] = rand();
        programMemory[programMemorySize+3] = rand();
        programMemory[programMemorySize+4] = rand();
        //save opposite as ideal
        outputMemory[0] = programMemory[programMemorySize+4];
        outputMemory[1] = programMemory[programMemorySize+3];
        outputMemory[2] = programMemory[programMemorySize+2];
        outputMemory[3] = programMemory[programMemorySize+1];
        outputMemory[4] = programMemory[programMemorySize+0];
        
        //Remember input values across tries
        for (int x = programMemorySize; x < programMemorySize + dataMemorySize; x++)
            inputBackup[x - programMemorySize] = programMemory[x];
        
        
        for (int try = 0; try < tries; try++){
            if (try % 10000 == 0) {
                printf("%i\n",try);
            }
            //Initialization
            reg.sp = programMemorySize - 2;
            
            //reset input values
            for (int x = programMemorySize; x < programMemorySize + dataMemorySize; x++)
                programMemory[x] = inputBackup[x - programMemorySize];
            
            //Save program backup
            for (int x = 0; x < programMemorySize; x++)
                programBackup[x] = programMemory[x];
            
            //Make Change(s)
            byte whichChange = rand();
            int endOfCode = programMemorySize-1;//FindEndOfCode();
            if (whichChange < 0x55) DoRandomInsert(min(endOfCode+1,programMemorySize-1)); //Allow changes up until last codebyte+1 (within memory ofc)
            if (whichChange < 0xAA) DoRandomUpdate(min(endOfCode+1,programMemorySize-1));
            if (whichChange >= 0xAA) DoRandomDelete(min(endOfCode+1,programMemorySize-1));
            
            //Execute Code
            Execute();
            long oldScore = score;
            score = compareInputOutput();
            if (score > oldScore){
                printf("Score for Iteration %i, Try %i: %ld",ite,try,score);
                if (score >= oldScore) printf(" - UPDATED ");
                for (int x = 0; x<5;x++){
                    printf("(%i)",programMemory[programMemorySize+x]);
                } printf(" - ");
                for (int x = 0; x<5;x++){
                    printf("(%i)",outputMemory[x]);
                } printf ("\n");
                //if (score < oldScore) printf(" - X\n");
            }
            if (score < oldScore){
                //Restore program backup
                for (int x = 0; x < programMemorySize; x++)
                    programMemory[x] = programBackup[x];
                
                score = oldScore;
            }
            
        }
        //printf("\nScore for Iteration %i: %ld\n",ite,score);
        
    }
        
}




void setMemoryAbsolute(u_short address, byte value){
    //Change memory value at address, if address is overflowing start at zero (happens when memory smaller than 16 bit address space)
    u_short finalAddress = (address % (programMemorySize + dataMemorySize));
    programMemory[finalAddress] = value;
}

void setMemoryTopPage(byte address, byte value){
    u_short location = programMemorySize + dataMemorySize - 0x100 + address;
    programMemory[location] = value;
}

void gotoMemory(u_short address){
    u_short finalAddress = (address % (programMemorySize + dataMemorySize));
    reg.pc = finalAddress;
}



void setZeroFlag(int flag){reg.f |= (flag << 7);}
void setAddSubFlag(int flag){reg.f |= (flag << 6);}
void setHalfCarryFlag(int flag){reg.f |= (flag << 5);}
void setCarryFlag(int flag){ reg.f |= (flag << 4);}

int getZeroFlag(){return (reg.f >> 7)  & 0x01;}
int getAddSubFlag(){return (reg.f >> 6)  & 0x01;}
int getHalfCarryFlag(){return (reg.f >> 5)  & 0x01;}
int getCarryFlag(){return (reg.f >> 4)  & 0x01;}



void LD_BC_nn(byte op1, byte op2){reg.b = op1;reg.c = op2;}
void LD_DE_nn(byte op1, byte op2){reg.d = op1;reg.e = op2;}
void LD_HL_nn(byte op1, byte op2){reg.h = op1;reg.l = op2;}
void LD_SP_nn(byte op1, byte op2){reg.sph = op1;reg.spl = op2;}

void LD_aBC_A(){setMemoryAbsolute(reg.bc,reg.a);}
void LD_aDE_A(){setMemoryAbsolute(reg.de,reg.a);}
void LDI_aHL_A(){setMemoryAbsolute(reg.hl,reg.a); reg.hl++;}
void LDD_aHL_A(){setMemoryAbsolute(reg.hl,reg.a); reg.hl--;}

void LD_B_n(byte op1){reg.b = op1;}
void LD_D_n(byte op1){reg.d = op1;}
void LD_H_n(byte op1){reg.h = op1;}
void LD_aHL_n(byte op1){setMemoryAbsolute(reg.hl,op1);}

void LD_ann_SP(byte op1,byte op2){setMemoryAbsolute((op2 | (op1 << 8)),reg.sph); setMemoryAbsolute((op2 | (op1 << 8))+1,reg.spl);}

void LD_A_aBC(){reg.a = programMemory[reg.bc];}
void LD_A_aDE(){reg.a = programMemory[reg.de];}
void LDI_A_aHL(){reg.a = programMemory[reg.hl]; reg.hl++;}
void LDD_A_aHL(){reg.a = programMemory[reg.hl]; reg.hl++;}

void LD_C_n(byte op1){reg.c = op1;}
void LD_E_n(byte op1){reg.e = op1;}
void LD_L_n(byte op1){reg.l = op1;}
void LD_A_n(byte op1){reg.a = op1;}

void LDH_an_A(byte op1){setMemoryTopPage(op1,reg.a);}
void LDH_A_an(byte op1){setMemoryTopPage(reg.a,op1);}
void LDH_aC_A(){setMemoryTopPage(reg.c,reg.a);}
void LDHL_SP_d(byte op1){}
void LD_SP_HL(){reg.sp = reg.hl;}
void LD_ann_A(byte op1,byte op2){setMemoryAbsolute((op2 | (op1 << 8)),reg.a);}
void LD_A_ann(byte op1,byte op2){ reg.a = programMemory[(op2 | (op1 << 8))];}


void INC_BC(){reg.bc++;}
void INC_B(){reg.b++;}
void INC_C(){reg.c++;}
void INC_DE(){reg.de++;}
void INC_D(){reg.d++;}
void INC_E(){reg.e++;}
void INC_HL(){reg.hl++;}
void INC_H(){reg.h++;}
void INC_L(){reg.l++;}
void INC_SP(){reg.sp++;}
void INC_aHL(){programMemory[reg.hl]++;}
void INC_A(){reg.a++;}

void DEC_BC(){reg.bc--;}
void DEC_B(){reg.b--;}
void DEC_C(){reg.c--;}
void DEC_DE(){reg.de--;}
void DEC_D(){reg.d--;}
void DEC_E(){reg.e--;}
void DEC_HL(){reg.hl--;}
void DEC_H(){reg.h--;}
void DEC_L(){reg.l--;}
void DEC_SP(){reg.sp--;}
void DEC_aHL(){programMemory[reg.hl]--;}
void DEC_A(){reg.a--;}

void And(byte op){
    if ((reg.a & op) == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
    setAddSubFlag(0);
    setHalfCarryFlag(1);
    setCarryFlag(0);
}

void Xor(byte op){
    if ((reg.a ^ op) == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
    setAddSubFlag(0);
    setHalfCarryFlag(0);
    setCarryFlag(0);
}

void Or(byte op){
    if ((reg.a | op) == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
    setAddSubFlag(0);
    setHalfCarryFlag(0);
    setCarryFlag(0);
}

void AND_B(){And(reg.b);reg.a &= reg.b;}
void AND_C(){And(reg.c);reg.a &= reg.c;}
void AND_D(){And(reg.d);reg.a &= reg.d;}
void AND_E(){And(reg.e);reg.a &= reg.e;}
void AND_H(){And(reg.h);reg.a &= reg.h;}
void AND_L(){And(reg.l);reg.a &= reg.l;}
void AND_aHL(){And(programMemory[reg.hl]);reg.a &= programMemory[reg.hl];}
void AND_A(){And(reg.a);reg.a &= reg.a;}
void AND_n(byte op1){And(op1);reg.a &= op1;}

void XOR_B(){Xor(reg.b);reg.a ^= reg.b;}
void XOR_C(){Xor(reg.c);reg.a ^= reg.c;}
void XOR_D(){Xor(reg.d);reg.a ^= reg.d;}
void XOR_E(){Xor(reg.e);reg.a ^= reg.e;}
void XOR_H(){Xor(reg.h);reg.a ^= reg.h;}
void XOR_L(){Xor(reg.l);reg.a ^= reg.l;}
void XOR_aHL(){Xor(programMemory[reg.hl]);reg.a ^= programMemory[reg.hl];}
void XOR_A(){Xor(reg.a);reg.a ^= reg.a;}
void XOR_n(byte op1){Xor(op1);reg.a ^= op1;}


void OR_B(){Or(reg.b);reg.a |= reg.b;}
void OR_C(){Or(reg.c);reg.a |= reg.c;}
void OR_D(){Or(reg.d);reg.a |= reg.d;}
void OR_E(){Or(reg.e);reg.a |= reg.e;}
void OR_H(){Or(reg.h);reg.a |= reg.h;}
void OR_L(){Or(reg.l);reg.a |= reg.l;}
void OR_aHL(){Or(programMemory[reg.hl]);reg.a |= programMemory[reg.hl];}
void OR_A(){Or(reg.a);reg.a |= reg.a;}
void OR_n(byte op1){Or(op1);reg.a |= op1;}


void LD_B_B(){}
void LD_B_C(){reg.b = reg.c;}
void LD_B_D(){reg.b = reg.d;}
void LD_B_E(){reg.b = reg.e;}
void LD_B_H(){reg.b = reg.h;}
void LD_B_L(){reg.b = reg.l;}
void LD_B_aHL(){reg.b = programMemory[reg.hl];}
void LD_B_A(){reg.b = reg.a;}
void LD_C_B(){reg.c = reg.b;}
void LD_C_C(){}
void LD_C_D(){reg.c = reg.d;}
void LD_C_E(){reg.c = reg.e;}
void LD_C_H(){reg.c = reg.h;}
void LD_C_L(){reg.c = reg.l;}
void LD_C_aHL(){reg.c = programMemory[reg.hl];}
void LD_C_A(){reg.c = reg.a;}
void LD_D_B(){reg.d = reg.b;}
void LD_D_C(){reg.d = reg.c;}
void LD_D_D(){}
void LD_D_E(){reg.d = reg.e;}
void LD_D_H(){reg.d = reg.h;}
void LD_D_L(){reg.d = reg.l;}
void LD_D_aHL(){reg.d = programMemory[reg.hl];}
void LD_D_A(){reg.d = reg.a;}
void LD_E_B(){reg.e = reg.b;}
void LD_E_C(){reg.e = reg.c;}
void LD_E_D(){reg.e = reg.d;}
void LD_E_E(){}
void LD_E_H(){reg.e = reg.h;}
void LD_E_L(){reg.e = reg.l;}
void LD_E_aHL(){reg.e = programMemory[reg.hl];}
void LD_E_A(){reg.e = reg.a;}
void LD_H_B(){reg.h = reg.b;}
void LD_H_C(){reg.h = reg.c;}
void LD_H_D(){reg.h = reg.d;}
void LD_H_E(){reg.h = reg.e;}
void LD_H_H(){}
void LD_H_L(){reg.h = reg.l;}
void LD_H_aHL(){reg.h = programMemory[reg.hl];}
void LD_H_A(){reg.h = reg.a;}
void LD_L_B(){reg.l = reg.b;}
void LD_L_C(){reg.l = reg.c;}
void LD_L_D(){reg.l = reg.d;}
void LD_L_E(){reg.l = reg.e;}
void LD_L_H(){reg.l = reg.h;}
void LD_L_L(){}
void LD_L_aHL(){reg.l = programMemory[reg.hl];}
void LD_L_A(){reg.l = reg.a;}
void LD_aHL_B(){programMemory[reg.hl] = reg.b;}
void LD_aHL_C(){programMemory[reg.hl] = reg.c;}
void LD_aHL_D(){programMemory[reg.hl] = reg.d;}
void LD_aHL_E(){programMemory[reg.hl] = reg.e;}
void LD_aHL_H(){programMemory[reg.hl] = reg.h;}
void LD_aHL_L(){programMemory[reg.hl] = reg.l;}
void LD_aHL_A(){programMemory[reg.hl] = reg.a;}
void LD_A_B(){reg.a = reg.b;}
void LD_A_C(){reg.a = reg.c;}
void LD_A_D(){reg.a = reg.d;}
void LD_A_E(){reg.a = reg.e;}
void LD_A_H(){reg.a = reg.h;}
void LD_A_L(){reg.a = reg.l;}
void LD_A_aHL(){reg.a = programMemory[reg.hl];}
void LD_A_A(){}

void Add(byte reg1, byte reg2){
    setCarryFlag(0);
    setHalfCarryFlag(0);
    setZeroFlag(0);
    
    if ((reg1 + reg2) > 0xFF){
        setCarryFlag(1);
    }
    if ((reg1 + reg2) == 0){
        setZeroFlag(1);
    }
    if (((reg1 & 0xF) + (reg2 & 0xF)) > 0xF){
        setHalfCarryFlag(1);
    }
    setAddSubFlag(0);
}

void Add16(u_short reg1, u_short reg2){
    setAddSubFlag(0);
    setCarryFlag(0);
    setHalfCarryFlag(0);
    if ((reg1 + reg2) > 0xFFFF){
        setCarryFlag(1);
    }
    if (((reg1 & 0xFF) + (reg2 & 0xFF)) > 0xFF){
        setHalfCarryFlag(1);
    }
}

void Sub(byte reg1, byte reg2){
    setCarryFlag(0);
    setHalfCarryFlag(0);
    setZeroFlag(0);
    
    if (reg1 == reg2){
        setZeroFlag(1);
    }
    if (reg1 < reg2){
         setCarryFlag(1);
    }
    if ((((reg1 & 0xF) - (reg2 & 0xF)) < 0)){
        setHalfCarryFlag(1);
    }
    
    setAddSubFlag(1);
}

void ADD_A_B(){ Add(reg.a,reg.b); reg.a += reg.b; }
void ADD_A_C(){Add(reg.a,reg.c); reg.a += reg.b;}
void ADD_A_D(){Add(reg.a,reg.d); reg.a += reg.b;}
void ADD_A_E(){Add(reg.a,reg.e); reg.a += reg.b;}
void ADD_A_H(){Add(reg.a,reg.h); reg.a += reg.b;}
void ADD_A_L(){Add(reg.a,reg.l); reg.a += reg.b;}
void ADD_A_aHL(){Add(reg.a,programMemory[reg.hl]); reg.a += programMemory[reg.hl];}
void ADD_A_A(){Add(reg.a,reg.a); reg.a += reg.a;}
void ADD_A_n(byte op1){Add(reg.a,op1); reg.a += op1;}


void ADD_HL_BC(){Add(reg.hl,reg.bc); reg.hl += reg.bc;}
void ADD_HL_DE(){Add(reg.hl,reg.bc); reg.hl += reg.bc;}
void ADD_HL_HL(){Add(reg.hl,reg.bc); reg.hl += reg.bc;}
void ADD_HL_SP(){Add(reg.hl,reg.bc); reg.hl += reg.bc;}
void ADD_SP_d(signed char op1){Add(reg.sp,op1); reg.sp += op1;}

void SUB_A_B(){Sub(reg.a,reg.b); reg.a -= reg.b;}
void SUB_A_C(){Sub(reg.a,reg.c); reg.a -= reg.c;}
void SUB_A_D(){Sub(reg.a,reg.d); reg.a -= reg.d;}
void SUB_A_E(){Sub(reg.a,reg.e); reg.a -= reg.e;}
void SUB_A_H(){Sub(reg.a,reg.h); reg.a -= reg.h;}
void SUB_A_L(){Sub(reg.a,reg.l); reg.a -= reg.l;}
void SUB_A_aHL(){Sub(reg.a,programMemory[reg.hl]); reg.a -= programMemory[reg.hl];}
void SUB_A_A(){Sub(reg.a,reg.a); reg.a -= reg.a;}
void SUB_A_n(byte op1){Sub(reg.a,op1); reg.a -= op1;}



void ADC_A_B(){ Add(reg.a,reg.b + getCarryFlag()); reg.a += (reg.b + getCarryFlag()); }
void ADC_A_C(){ Add(reg.a,reg.c + getCarryFlag()); reg.a += (reg.c + getCarryFlag()); }
void ADC_A_D(){ Add(reg.a,reg.d + getCarryFlag()); reg.a += (reg.d + getCarryFlag()); }
void ADC_A_E(){ Add(reg.a,reg.e + getCarryFlag()); reg.a += (reg.e + getCarryFlag()); }
void ADC_A_H(){ Add(reg.a,reg.h + getCarryFlag()); reg.a += (reg.h + getCarryFlag()); }
void ADC_A_L(){ Add(reg.a,reg.l + getCarryFlag()); reg.a += (reg.l + getCarryFlag()); }
void ADC_A_aHL(){ Add(reg.a,programMemory[reg.hl] + getCarryFlag()); reg.a += (programMemory[reg.hl] + getCarryFlag()); }
void ADC_A_A(){ Add(reg.a,reg.a + getCarryFlag()); reg.a += (reg.a + getCarryFlag()); }
void ADC_A_n(byte op1){Add(reg.a,op1 + getCarryFlag()); reg.a += (op1 + getCarryFlag());}


void SBC_A_B(){ Sub(reg.a,reg.b - getCarryFlag()); reg.a -= (reg.b + getCarryFlag()); }
void SBC_A_C(){ Sub(reg.a,reg.c - getCarryFlag()); reg.a -= (reg.c + getCarryFlag()); }
void SBC_A_D(){ Sub(reg.a,reg.d - getCarryFlag()); reg.a -= (reg.d + getCarryFlag()); }
void SBC_A_E(){ Sub(reg.a,reg.e - getCarryFlag()); reg.a -= (reg.e + getCarryFlag()); }
void SBC_A_H(){ Sub(reg.a,reg.h - getCarryFlag()); reg.a -= (reg.h + getCarryFlag()); }
void SBC_A_L(){ Sub(reg.a,reg.l - getCarryFlag()); reg.a -= (reg.l + getCarryFlag()); }
void SBC_A_aHL(){ Sub(reg.a,programMemory[reg.hl] - getCarryFlag()); reg.a -= (programMemory[reg.hl] + getCarryFlag()); }
void SBC_A_A(){ Sub(reg.a,reg.a - getCarryFlag()); reg.a -= (reg.a + getCarryFlag()); }
void SBC_A_n(byte op1){Sub(reg.a,op1 - getCarryFlag()); reg.a -= (op1 + getCarryFlag());};


void CP_B(){Sub(reg.a,reg.b); }
void CP_C(){Sub(reg.a,reg.c); }
void CP_D(){Sub(reg.a,reg.d); }
void CP_E(){Sub(reg.a,reg.e); }
void CP_H(){Sub(reg.a,reg.h); }
void CP_L(){Sub(reg.a,reg.l); }
void CP_aHL(){Sub(reg.a,programMemory[reg.hl]); }
void CP_A(){Sub(reg.a,reg.a); }
void CP_n(byte op1){Sub(reg.a,op1); }


void CALL(u_short address){
    programMemory[reg.sp-1] = reg.pch;
    programMemory[reg.sp-2] = reg.pcl;
    reg.pc = address;
    reg.sp -= 2;
}

void CALL_nn(byte op1, byte op2){CALL((op2 | (op1 << 8)));}
void CALL_Z_nn(byte op1, byte op2){if (getZeroFlag() == 1) CALL((op2 | (op1 << 8)));}
void CALL_NZ_nn(byte op1, byte op2){if (getZeroFlag() == 0) CALL((op2 | (op1 << 8)));}
void CALL_C_nn(byte op1, byte op2){if (getCarryFlag() == 1) CALL((op2 | (op1 << 8)));}
void CALL_NC_nn(byte op1, byte op2){if (getCarryFlag() == 0) CALL((op2 | (op1 << 8)));}

void RET(){
    reg.pcl = programMemory[reg.sp];
    reg.pch = programMemory[reg.sp+1];
    reg.sp += 2;
}

void RET_Z(){if (getZeroFlag() == 1) RET();}
void RET_NZ(){if (getZeroFlag() == 0) RET();}
void RET_C(){if (getCarryFlag() == 1) RET();}
void RET_NC(){if (getCarryFlag() == 0) RET();}

void RST_0(){CALL(0x0);}
void RST_8(){CALL(0x8);}
void RST_10(){CALL(0x10);}
void RST_18(){CALL(0x18);}
void RST_20(){CALL(0x20);}
void RST_28(){CALL(0x28);}
void RST_30(){CALL(0x30);}
void RST_38(){CALL(0x38);}

void JP_nn(byte op1, byte op2){reg.pc = (op2 | (op1 << 8));}
void JP_Z_nn(byte op1, byte op2){if (getZeroFlag() == 1) reg.pc = (op2 | (op1 << 8));}
void JP_NZ_nn(byte op1, byte op2){if (getZeroFlag() == 0) reg.pc = (op2 | (op1 << 8));}
void JP_C_nn(byte op1, byte op2){if (getCarryFlag() == 1) reg.pc = (op2 | (op1 << 8));}
void JP_NC_nn(byte op1, byte op2){if (getCarryFlag() == 0) reg.pc = (op2 | (op1 << 8));}
void JP_aHL(){reg.pc = reg.hl;}

void JR_n(signed char op1){gotoMemory(reg.pc+op1);}
void JR_Z_n(signed char op1){if (getZeroFlag() == 1) gotoMemory(reg.pc+op1);}
void JR_NZ_n(signed char op1){if (getZeroFlag() == 0) gotoMemory(reg.pc+op1);}
void JR_C_n(signed char op1){if (getCarryFlag() == 1) gotoMemory(reg.pc+op1);}
void JR_NC_n(signed char op1){if (getCarryFlag() == 0) gotoMemory(reg.pc+op1);}


void CPL() {reg.a = ~reg.a; setAddSubFlag(1);setHalfCarryFlag(1);}

void RL(const unsigned int value, int shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0) reg.a = value;
    reg.a = (value << shift) | (value >> (sizeof(value)*8 - shift));
}

void RR(const unsigned int value, int shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0) reg.a = value;
    reg.a = (value >> shift) | (value << (sizeof(value)*8 - shift));
    
}
void RzeroAllFlags(){
    setHalfCarryFlag(0);
    setZeroFlag(0);
    setAddSubFlag(0);
    setCarryFlag(0);
}
void RLC_A(){RzeroAllFlags(); if ((reg.a & 0x80) == 1) setCarryFlag(1); RL(reg.a,1);}
void RL_A(){RzeroAllFlags(); RL(reg.a,1);}
void RRC_A(){RzeroAllFlags(); if ((reg.a & 0x01) == 1) setCarryFlag(1); RR(reg.a,1);}
void RR_A(){RzeroAllFlags(); RR(reg.a,1);}

void STOP(){steps = maxProgramSteps+1;}

void PUSH(byte h, byte l){
    if (reg.sp > 1) {
        programMemory[reg.sp-1] = h;
        programMemory[reg.sp-2] = l;
        reg.sp -= 2;
    }
}

void PUSH_BC(){PUSH(reg.b,reg.c);}
void PUSH_DE(){PUSH(reg.d,reg.e);}
void PUSH_HL(){PUSH(reg.h,reg.l);}
void PUSH_AF(){PUSH(reg.a,reg.f);}



u_short POP(){
    byte h = 0;
    byte l = 0;
    if (reg.sp < programMemorySize-1) {
        l = programMemory[reg.sp];
        h = programMemory[reg.sp+1];
        reg.sp += 2;
    }
    return (((u_short)h << 7) | l);
}

void POP_BC(){reg.bc = POP();}
void POP_DE(){reg.de = POP();}
void POP_HL(){reg.hl = POP();}
void POP_AF(){reg.af = POP();}

void CCF(){setCarryFlag(0); setAddSubFlag(0);setHalfCarryFlag(0);}
void SCF(){setCarryFlag(1); setAddSubFlag(0);setHalfCarryFlag(0);}
void DAA(){
    byte lnibble = reg.a & 0x0F;
    if (lnibble > 9 || getHalfCarryFlag() == 1) {ADD_A_n(0x06);}
    byte hnibble = (reg.a & 0xF0) >> 4;
    if (hnibble > 9 || getCarryFlag() == 1) {ADD_A_n(0x60);}
    
    setHalfCarryFlag(0);
}

byte nextProgramByte(){
    u_short oldByte = reg.pc;
    reg.pc++;
    if (reg.pc == programMemorySize + dataMemorySize) reg.pc = 0;
    
    return programMemory[oldByte];
}

void NOP(){
    steps--;
    nopCounter++;
    if (nopCounter >= maxNOPs) steps = maxProgramSteps + 1;
}

void Execute(){
    steps = 0;
    while(steps <= maxProgramSteps){
        steps++;
        /*setCarryFlag(0);
        setHalfCarryFlag(0);
        setZeroFlag(0);
        setAddSubFlag(0);*/
        
        byte myByte = nextProgramByte();
        void (*funcPtr)(byte, byte);
        
        funcPtr = instructions[myByte].execute;
        
        if (funcPtr == NULL) {
            printf("ERROR FUNCTION NOT IMPLEMENTED:\n");
            printf(instructions[myByte].disassembly,0x12,0xab);
            printf("\nByte: %02X",myByte);
            printf("\n\n");
            printf("REGISTERS:\n##########\n");
            printf("AF: %02X%02X\n",reg.a,reg.f);
            printf("BC: %02X%02X\n",reg.b,reg.c);
            printf("DE: %02X%02X\n",reg.d,reg.e);
            printf("HL: %02X%02X\n",reg.h,reg.l);
            printf("SP: %04X\n",reg.sp);
            printf("PC: %04X\n",reg.pc);
            
            
            return;
        }
       
        //Calling functions
        char buffer[1024];
        byte op1,op2;
        switch (instructions[myByte].operandLength){
            case 0:
                snprintf(buffer, sizeof(buffer), instructions[myByte].disassembly);
                history[steps-1] = buffer;
                if (instructions[myByte].execute != NOP) {
                    nopCounter = 0;
                }
                funcPtr(0,0);
                break;
            case 1:
                op1 = nextProgramByte();
                snprintf(buffer, sizeof(buffer), instructions[myByte].disassembly, op1);
                history[steps-1] = buffer;
                funcPtr(op1,0);
                nopCounter = 0;
                break;
            case 2:
                op1 = nextProgramByte(); op2 = nextProgramByte();
                snprintf(buffer, sizeof(buffer), instructions[myByte].disassembly, op1, op2);
                history[steps-1] = buffer;
                funcPtr(op1, op2);
                nopCounter = 0;
                break;
        }
        
        if (steps == maxProgramSteps+1) break;
        
        /*if (nopCounter == 0) {
            printf("%i: ",reg.pc);
            printf(history[steps-1]);
            printf("\n");
        }*/
        
    
       
    }
    /*
    printf("\nProgram has ended without error:\n\n");
    
    printf("REGISTERS:\n##########\n");
    printf("AF: %02X%02X\n",reg.a,reg.f);
    printf("BC: %02X%02X\n",reg.b,reg.c);
    printf("DE: %02X%02X\n",reg.d,reg.e);
    printf("HL: %02X%02X\n",reg.h,reg.l);
    printf("SP: %04X\n",reg.sp);
    printf("PC: %04X\n",reg.pc);
    printf("\n");
    printf("MEMORY MAP:\n##########\n");
    byte lastVal = 0x00;
    for (int i = 0; i < dataMemorySize; i++){
        //if (i % 64 == 0) printf("\n");
        byte data = programMemory[programMemorySize+i];
        if (lastVal != 0x00 && data == 0x00) {printf(" "); lastVal = 0x00;}
        if (data != 0x00) {
            if (data < 0x20 || data > 0x7e) printf("(%i)",data);
            if (data >= 0x20 && data <= 0x7e) printf("%c",data);
            
            lastVal = data;
            
        }
        
        
    }
    //printf("\n");
    */
    
}



