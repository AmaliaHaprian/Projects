#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
using BYTE=unsigned char;
using WORD=unsigned short;

struct Memory{
  static const unsigned int MAX_MEM=1024*64;
  BYTE Data[MAX_MEM];

  void init(){
    for(unsigned int i=0; i<MAX_MEM; ++i){
      Data[i]=0;
    }
  }
  BYTE& operator[](unsigned int addr){
    if(addr>=MAX_MEM) 
      throw std::runtime_error("Memory access out of bounds");
    return Data[addr];
  }
};

struct CPU{

    WORD PC;
    WORD SP;
    BYTE A, X, Y;
    BYTE C : 1;
    BYTE Z: 1;
    BYTE I: 1;
    BYTE D: 1;
    BYTE B: 1;
    BYTE O: 1;
    BYTE N: 1;

    static const BYTE LDA_IMM=0xA9;

    void reset(Memory& mem){
      PC=0xFFFC;  
      SP=0x0100;
      A=X=Y=0;
      C=Z=I=D=B=O=N=0;
      mem.init();
    }
    BYTE FetchByte(Memory& mem, unsigned int& cycles){
      BYTE Data=mem[PC];
      PC++;
      cycles--;
      return Data;
    }

    void execute(Memory& mem, unsigned int cycles){
      while(cycles){
        BYTE instruction=FetchByte(mem, cycles);
        switch(instruction){
          case LDA_IMM:{
            BYTE value=FetchByte(mem, cycles);
            A=value;
            Z=(A==0);
            N=(A & 0b10000000) != 0;;
            break;
          }
          default:{
            throw std::runtime_error("Unknown instruction");
            break;}
        }
      }
    }
};


int main(){
  Memory mem;
  CPU cpu;
  cpu.reset(mem);
  mem[0xFFFC]=0xA9;
  mem[0xFFFD]=0x42;
  cpu.execute(mem, 2);
 
  return 0;
}