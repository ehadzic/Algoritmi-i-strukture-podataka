#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MIPS_REGS 32 // broj registara
#define MEM_DATA_START 0x00000000 // početak dijela memorije za podatke
#define MEM_DATA_SIZE 0x00000100 // veličina dijela memorije za podatke
#define MEM_INSTRUCTIONS_START 0x00000100 // početak dijela memorije za instrukcije
#define MEM_INSTRUCTIONS_SIZE 0x00000080 // veličina dijela memorije za instrukcije

// stanje procesora
typedef struct CPU_State {
  uint32_t PC; // programski brojac
  uint32_t REGS[MIPS_REGS]; // register file
} CPU_State;


// regioni glavne memroije (dio za podatke, dio za instrukcije)
typedef struct {
    uint32_t start, size; // početak regiona i veličina
    uint8_t *mem; // sadržaj
} mem_region;

mem_region MEM_REGIONS[] = {
    {MEM_DATA_START, MEM_DATA_SIZE, NULL},
    {MEM_INSTRUCTIONS_START, MEM_INSTRUCTIONS_SIZE, NULL}
};

#define MEM_NREGIONS 2

// trenutno stanje CPU-a
CPU_State CURRENT_STATE, NEXT_STATE;


// funkcija koja piše u glavnu memoriju
void mem_write(uint32_t address, uint32_t value) {
    int i;
    for (i = 0; i < MEM_NREGIONS; i++) {
        if (address >= MEM_REGIONS[i].start &&
                address < (MEM_REGIONS[i].start + MEM_REGIONS[i].size)) {
            uint32_t offset = address - MEM_REGIONS[i].start;
            // memorija je byte-adresabilna, pa se jedna (32-bitna) riječ "dijeli" na 4 dijela
            MEM_REGIONS[i].mem[offset+3] = (value >> 24) & 0xFF;
            MEM_REGIONS[i].mem[offset+2] = (value >> 16) & 0xFF;
            MEM_REGIONS[i].mem[offset+1] = (value >>  8) & 0xFF;
            MEM_REGIONS[i].mem[offset+0] = (value >>  0) & 0xFF;
            return;
        }
    }
}

// memorija koja čita vrijednost iz glavne memorije
uint32_t mem_read(uint32_t address) {
    int i;
    for (i = 0; i < MEM_NREGIONS; i++) {
        if (address >= MEM_REGIONS[i].start &&
                address < (MEM_REGIONS[i].start + MEM_REGIONS[i].size)) {
            uint32_t offset = address - MEM_REGIONS[i].start;
            // memorija je byte-adresabilna, pa pri čitanju 32-bitne riječi čitaju se 4 byte-a
            return
                (MEM_REGIONS[i].mem[offset+3] << 24) |
                (MEM_REGIONS[i].mem[offset+2] << 16) |
                (MEM_REGIONS[i].mem[offset+1] <<  8) |
                (MEM_REGIONS[i].mem[offset+0] <<  0);
        }
    }

    return 0;
}

// inicijalizacija glavne memorije
void init_memory() {
    int i;
    for (i = 0; i < MEM_NREGIONS; i++) {
        MEM_REGIONS[i].mem = malloc(MEM_REGIONS[i].size);
        memset(MEM_REGIONS[i].mem, 0, MEM_REGIONS[i].size);
    }
}

// funkcija koja učitava program iz .txt datoteke u memoriju instrukcija
void load_program(char *program_filename) {
    int i;
    while ((*i))
}

// funkcija koja dekodira instrukciju
void decode_instruction(uint32_t instruction) {
}



int main()
{
    init_memory();
    load_program("input/program.txt");
    return 0;
}
