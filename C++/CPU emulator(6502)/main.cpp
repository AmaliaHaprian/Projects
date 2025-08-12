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

  void writeWord(WORD value, unsigned int addr, unsigned int& cycles){
    Data[addr]=value& 0xFF;
    Data[addr+1]=(value >> 8) & 0xFF;
    cycles-=2;
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
    BYTE V: 1;
    BYTE N: 1;

    static const BYTE JSR=0x20;
    static const BYTE LDA_IMM=0xA9;
    static const BYTE LDA_ZP=0xA5;
    static const BYTE LDA_ZPX=0xB5;
    static const BYTE LDA_ABS=0xAD;
    static const BYTE LDA_ABSX=0xBD;
    static const BYTE LDA_ABSY=0xB9;
    static const BYTE LDA_INDX=0xA1;
    static const BYTE LDA_INDY=0xB1;

    void reset(Memory& mem){
      PC=0xFFFC;  
      SP=0x0100;
      A=X=Y=0;
      C=Z=I=D=B=V=N=0;
      mem.init();
    }

    BYTE FetchByte(Memory& mem, unsigned int& cycles){
      BYTE Data=mem[PC];
      PC++;
      cycles--;
      return Data;
    }

    WORD FetchWord(Memory& mem, unsigned int& cycles){
      WORD Data=mem[PC];
      PC++;
      cycles--;

      Data=(mem[PC]<<8) | Data;
      PC++;
      cycles--;
      return Data;
    }

    BYTE ReadByte(Memory& mem, WORD addr, unsigned int& cycles){
      BYTE Data=mem[addr];
      cycles--;
      return Data;
    }

    WORD ReadWord(Memory& mem, WORD addr, unsigned int& cycles){
      BYTE lowByte=ReadByte(mem, addr, cycles);
      BYTE highByte=ReadByte(mem, addr+1, cycles);
      return (highByte << 8) | lowByte;
    }

    BYTE ReadByteFrom16Bit(Memory& mem, WORD addr, unsigned int& cycles){
      BYTE Data=mem[addr];
      cycles--;
      return Data;
    }
    void execute(Memory& mem, unsigned int cycles){
      while(cycles){
        BYTE instruction=FetchByte(mem, cycles);
        switch(instruction){
          case JSR:{
            WORD subroutineAddr=FetchWord(mem, cycles);
            mem.writeWord(PC-1, SP, cycles);
            PC=subroutineAddr;
            cycles--;
            break;
          }
          case LDA_IMM:{
            BYTE value=FetchByte(mem, cycles);
            A=value;
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_ZP:{
            BYTE ZPAddr=FetchByte(mem, cycles);
            A=ReadByte(mem, ZPAddr, cycles);
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_ZPX:{
            BYTE ZPAddr=FetchByte(mem, cycles);
            ZPAddr+=X;
            cycles--;
            A=ReadByte(mem, ZPAddr, cycles);
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_ABS:{
            WORD absAddr=FetchWord(mem, cycles);
            A=ReadByteFrom16Bit(mem, absAddr, cycles);
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_ABSX:{
            WORD absAddr=FetchWord(mem, cycles);
            absAddr+=X;
            A=ReadByteFrom16Bit(mem, absAddr, cycles);
            if((absAddr & 0xFF00) != (PC & 0xFF00)) { // absAddrX-absAddr >=0xFF
              cycles--;
            }
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_ABSY:{
            WORD absAddr=FetchWord(mem, cycles);
            absAddr+=Y;
            A=ReadByteFrom16Bit(mem, absAddr, cycles);
            if((absAddr & 0xFF00) != (PC & 0xFF00)) { //>=0xFF
              cycles--;
            }
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_INDX:{
            BYTE ZPAddr=FetchByte(mem, cycles);
            ZPAddr+=X;
            cycles--;
            WORD effectiveAddr=ReadWord(mem, ZPAddr, cycles);
            A=ReadByteFrom16Bit(mem, effectiveAddr, cycles);
            Z=(A==0);
            N=(A & 0b10000000) != 0;
            break;
          }
          case LDA_INDY:{
            BYTE ZPAddr=FetchByte(mem, cycles);
            WORD effectiveAddr=ReadWord(mem, ZPAddr, cycles);
            WORD effectiveAddrY=effectiveAddr+Y;
            A=ReadByteFrom16Bit(mem, effectiveAddr, cycles);
            if(effectiveAddrY- effectiveAddr >=0xFF)
            {
              cycles--;
            }
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