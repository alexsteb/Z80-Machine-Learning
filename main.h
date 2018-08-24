//
//  main.h
//  z80tool
//
//  Created by Alexander Stebner on 16.02.18.
//  Copyright © 2018 Alexander Stebner. All rights reserved.
//

#ifndef main_h
#define main_h

typedef unsigned char byte;



//List of possible instructions
struct instruction {
    char *disassembly;
    unsigned char operandLength;
    void *execute;
    
} extern const instructions[256];

void Adapt(int, int, int);
long compareInputOutput(void);

void NOP(void);
void INC_BC(void);
void INC_B(void);
void INC_C(void);
void INC_DE(void);
void INC_D(void);
void INC_E(void);
void INC_HL(void);
void INC_H(void);
void INC_L(void);
void INC_SP(void);
void INC_aHL(void);
void INC_A(void);

void DEC_BC(void);
void DEC_B(void);
void DEC_C(void);
void DEC_DE(void);
void DEC_D(void);
void DEC_E(void);
void DEC_HL(void);
void DEC_H(void);
void DEC_L(void);
void DEC_SP(void);
void DEC_aHL(void);
void DEC_A(void);

void LD_B_B(void);
void LD_B_C(void);
void LD_B_D(void);
void LD_B_E(void);
void LD_B_H(void);
void LD_B_L(void);
void LD_B_aHL(void);
void LD_B_A(void);
void LD_C_B(void);
void LD_C_C(void);
void LD_C_D(void);
void LD_C_E(void);
void LD_C_H(void);
void LD_C_L(void);
void LD_C_aHL(void);
void LD_C_A(void);
void LD_D_B(void);
void LD_D_C(void);
void LD_D_D(void);
void LD_D_E(void);
void LD_D_H(void);
void LD_D_L(void);
void LD_D_aHL(void);
void LD_D_A(void);
void LD_E_B(void);
void LD_E_C(void);
void LD_E_D(void);
void LD_E_E(void);
void LD_E_H(void);
void LD_E_L(void);
void LD_E_aHL(void);
void LD_E_A(void);
void LD_H_B(void);
void LD_H_C(void);
void LD_H_D(void);
void LD_H_E(void);
void LD_H_H(void);
void LD_H_L(void);
void LD_H_aHL(void);
void LD_H_A(void);
void LD_L_B(void);
void LD_L_C(void);
void LD_L_D(void);
void LD_L_E(void);
void LD_L_H(void);
void LD_L_L(void);
void LD_L_aHL(void);
void LD_L_A(void);
void LD_aHL_B(void);
void LD_aHL_C(void);
void LD_aHL_D(void);
void LD_aHL_E(void);
void LD_aHL_H(void);
void LD_aHL_L(void);
void LD_aHL_A(void);
void LD_A_B(void);
void LD_A_C(void);
void LD_A_D(void);
void LD_A_E(void);
void LD_A_H(void);
void LD_A_L(void);
void LD_A_aHL(void);
void LD_A_A(void);

void LD_BC_nn(byte, byte);
void LD_DE_nn(byte, byte);
void LD_HL_nn(byte, byte);
void LD_SP_nn(byte, byte);

void LD_aBC_A(void);
void LD_aDE_A(void);
void LDI_aHL_A(void);
void LDD_aHL_A(void);

void LD_B_n(byte);
void LD_D_n(byte);
void LD_H_n(byte);
void LD_aHL_n(byte);

void LD_ann_SP(byte,byte);

void LD_A_aBC(void);
void LD_A_aDE(void);
void LDI_A_aHL(void);
void LDD_A_aHL(void);

void LD_C_n(byte);
void LD_E_n(byte);
void LD_L_n(byte);
void LD_A_n(byte);

void LDH_an_A(byte);
void LDH_A_an(byte);
void LDH_aC_A(void);
void LDHL_SP_d(byte);
void LD_SP_HL(void);
void LD_ann_A(byte,byte);
void LD_A_ann(byte,byte);



void ADD_A_B(void);
void ADD_A_C(void);
void ADD_A_D(void);
void ADD_A_E(void);
void ADD_A_H(void);
void ADD_A_L(void);
void ADD_A_aHL(void);
void ADD_A_A(void);

void SUB_A_B(void);
void SUB_A_C(void);
void SUB_A_D(void);
void SUB_A_E(void);
void SUB_A_H(void);
void SUB_A_L(void);
void SUB_A_aHL(void);
void SUB_A_A(void);

void ADC_A_B(void);
void ADC_A_C(void);
void ADC_A_D(void);
void ADC_A_E(void);
void ADC_A_H(void);
void ADC_A_L(void);
void ADC_A_aHL(void);
void ADC_A_A(void);

void SBC_A_B(void);
void SBC_A_C(void);
void SBC_A_D(void);
void SBC_A_E(void);
void SBC_A_H(void);
void SBC_A_L(void);
void SBC_A_aHL(void);
void SBC_A_A(void);

void AND_B(void);
void AND_C(void);
void AND_D(void);
void AND_E(void);
void AND_H(void);
void AND_L(void);
void AND_aHL(void);
void AND_A(void);

void XOR_B(void);
void XOR_C(void);
void XOR_D(void);
void XOR_E(void);
void XOR_H(void);
void XOR_L(void);
void XOR_aHL(void);
void XOR_A(void);

void OR_B(void);
void OR_C(void);
void OR_D(void);
void OR_E(void);
void OR_H(void);
void OR_L(void);
void OR_aHL(void);
void OR_A(void);

void CP_B(void);
void CP_C(void);
void CP_D(void);
void CP_E(void);
void CP_H(void);
void CP_L(void);
void CP_aHL(void);
void CP_A(void);
void CP_n(byte);

void RST_0(void);
void RST_8(void);
void RST_10(void);
void RST_18(void);
void RST_20(void);
void RST_28(void);
void RST_30(void);
void RST_38(void);

void CALL_nn(byte, byte);
void CALL_Z_nn(byte, byte);
void CALL_NZ_nn(byte, byte);
void CALL_C_nn(byte, byte);
void CALL_NC_nn(byte, byte);

void RET(void);
void RET_Z(void);
void RET_NZ(void);
void RET_C(void);
void RET_NC(void);

void JP_nn(byte, byte);
void JP_Z_nn(byte, byte);
void JP_NZ_nn(byte, byte);
void JP_C_nn(byte, byte);
void JP_NC_nn(byte, byte);
void JP_aHL(void);

void JR_n(signed char);
void JR_Z_n(signed char);
void JR_NZ_n(signed char);
void JR_C_n(signed char);
void JR_NC_n(signed char);

void CPL(void);

void ADD_HL_BC(void);
void ADD_HL_DE(void);
void ADD_HL_HL(void);
void ADD_HL_SP(void);
void ADD_SP_d(signed char);

void RLC_A(void);
void RL_A(void);
void RRC_A(void);
void RR_A(void);

void STOP(void);

void ADD_A_n(byte);
void SUB_A_n(byte);
void ADC_A_n(byte);
void SBC_A_n(byte);
void AND_n(byte);
void OR_n(byte);
void XOR_n(byte);

void POP_BC(void);
void POP_DE(void);
void POP_HL(void);
void POP_AF(void);

void PUSH_BC(void);
void PUSH_DE(void);
void PUSH_HL(void);
void PUSH_AF(void);

void CCF(void);
void SCF(void);
void DAA(void);



const struct instruction instructions[256] = {
    { "NOP", 0, NOP },                          // 0x00
    { "LD BC, 0x%02X%02X", 2, LD_BC_nn },     // 0x01
    { "LD (BC), A", 0, LD_aBC_A },            // 0x02
    { "INC BC", 0, INC_BC },                  // 0x03
    { "INC B", 0, INC_B },                  // 0x04
    { "DEC B", 0, DEC_B },                  // 0x05
    { "LD B, 0x%02X", 1, LD_B_n },                  // 0x06
    { "RLC A", 0, RLC_A },                  // 0x07
    { "LD (0x%02X%02X), SP", 2, LD_ann_SP },                  // 0x08
    { "ADD HL, BC", 0, ADD_HL_BC },                  // 0x09
    { "LD A, (BC)", 0, LD_A_aBC },                  // 0x0a
    { "DEC BC", 0, DEC_BC },                  // 0x0b
    { "INC C", 0, INC_C },                  // 0x0c
    { "DEC C", 0, DEC_C },                  // 0x0d
    { "LD C, 0x%02X", 1, LD_C_n },                  // 0x0e
    { "RRC A", 0, RRC_A },                  // 0x0f
    { "STOP", 0, STOP },                  // 0x10
    { "LD DE, 0x%02X%02X", 2, LD_DE_nn },                  // 0x11
    { "LD (DE), A", 0, LD_aDE_A },                  // 0x12
    { "INC DE", 0, INC_DE },                  // 0x13
    { "INC D", 0, INC_D },                  // 0x14
    { "DEC D", 0, DEC_D },                  // 0x15
    { "LD D, 0x%02X", 1, LD_D_n },                  // 0x16
    { "RL A", 0, RL_A },                  // 0x17
    { "JR 0x%02X", 1, JR_n },                  // 0x18
    { "ADD HL, DE", 0, ADD_HL_DE },                  // 0x19
    { "LD A (DE)", 0, LD_A_aDE },                  // 0x1a
    { "DEC DE", 0, DEC_DE },                  // 0x1b
    { "INC E", 0, INC_E },                  // 0x1c
    { "DEC E", 0, DEC_E },                  // 0x1d
    { "LD E, 0x%02X", 1, LD_E_n },                  // 0x1e
    { "RR A", 0, RR_A },                  // 0x1f
    { "JR NZ, 0x%02X", 1, JR_NZ_n },                  // 0x20
    { "LD HL, 0x%02X%02X", 2, LD_HL_nn },                  // 0x21
    { "LDI (HL), A", 0, LDI_aHL_A },                  // 0x22
    { "INC HL", 0, INC_HL },                  // 0x23
    { "INC H", 0, INC_H },                  // 0x24
    { "DEC H", 0, DEC_H },                  // 0x25
    { "LD H, 0x%02X", 1, LD_H_n },                  // 0x26
    { "DAA", 0, DAA },                  // 0x27
    { "JR Z, 0x%02X", 1, JR_Z_n },                  // 0x28
    { "ADD HL, HL", 0, ADD_HL_HL },                  // 0x29
    { "LDI A, (HL)", 0, LDI_A_aHL },                  // 0x2a
    { "DEC HL", 0, DEC_HL },                  // 0x2b
    { "INC L", 0, INC_L },                  // 0x2c
    { "DEC L", 0, DEC_L },                  // 0x2d
    { "LD L, 0x%02X", 1, LD_L_n },                  // 0x2e
    { "CPL", 0, CPL },                  // 0x2f
    { "JR NC, 0x%02X", 1, JR_NC_n },                  // 0x30
    { "LD SP, 0x%02X%02X", 2, LD_SP_nn },                  // 0x31
    { "LDD (HL), A", 0, LDD_aHL_A },                  // 0x32
    { "INC SP", 0, INC_SP },                  // 0x33
    { "INC (HL)", 0, INC_aHL },                  // 0x34
    { "DEC (HL)", 0, DEC_aHL },                  // 0x35
    { "LD (HL), 0x%02X", 1, LD_aHL_n },                  // 0x36
    { "SCF", 0, SCF },                  // 0x37
    { "JR C, 0x%02X", 1, JR_C_n },                  // 0x38
    { "ADD HL, SP", 0, ADD_HL_SP },                  // 0x39
    { "LDD A, (HL)", 0, LDD_A_aHL },                  // 0x3a
    { "DEC SP", 0, DEC_SP },                  // 0x3b
    { "INC A", 0, INC_A },                  // 0x3c
    { "DEC A", 0, DEC_A },                  // 0x3d
    { "LD A, 0x%02X", 1, LD_A_n },                  // 0x3e
    { "CCF", 0, CCF },                  // 0x3f
    { "LD B, B", 0, LD_B_B },                  // 0x40
    { "LD B, C", 0, LD_B_C },                  // 0x41
    { "LD B, D", 0, LD_B_D },                  // 0x42
    { "LD B, E", 0, LD_B_E },                  // 0x43
    { "LD B, H", 0, LD_B_H },                  // 0x44
    { "LD B, L", 0, LD_B_L },                  // 0x45
    { "LD B, (HL)", 0, LD_B_aHL },                  // 0x46
    { "LD B, A", 0, LD_B_A },                  // 0x47
    { "LD C, B", 0, LD_C_B },                  // 0x48
    { "LD C, C", 0, LD_C_C },                  // 0x49
    { "LD C, D", 0, LD_C_D },                  // 0x4a
    { "LD C, E", 0, LD_C_E },                  // 0x4b
    { "LD C, H", 0, LD_C_H },                  // 0x4c
    { "LD C, L", 0, LD_C_L },                  // 0x4d
    { "LD C, (HL)", 0, LD_C_aHL },                  // 0x4e
    { "LD C, A", 0, LD_C_A },                  // 0x4f
    { "LD D, B", 0, LD_D_B },                  // 0x50
    { "LD D, C", 0, LD_D_C },                  // 0x51
    { "LD D, D", 0, LD_D_D },                  // 0x52
    { "LD D, E", 0, LD_D_E },                  // 0x53
    { "LD D, H", 0, LD_D_H },                  // 0x54
    { "LD D, L", 0, LD_D_L },                  // 0x55
    { "LD D, (HL)", 0, LD_D_aHL },                  // 0x56
    { "LD D, A", 0, LD_D_A },                  // 0x57
    { "LD E, B", 0, LD_E_B },                  // 0x58
    { "LD E, C", 0, LD_E_C },                  // 0x59
    { "LD E, D", 0, LD_E_D },                  // 0x5a
    { "LD E, E", 0, LD_E_E },                  // 0x5b
    { "LD E, H", 0, LD_E_H },                  // 0x5c
    { "LD E, L", 0, LD_E_L },                  // 0x5d
    { "LD E, (HL)", 0, LD_E_aHL },                  // 0x5e
    { "LD E, A", 0, LD_E_A },                  // 0x5f
    { "LD H, B", 0, LD_H_B },                  // 0x60
    { "LD H, C", 0, LD_H_C },                  // 0x61
    { "LD H, D", 0, LD_H_D },                  // 0x62
    { "LD H, E", 0, LD_H_E },                  // 0x63
    { "LD H, H", 0, LD_H_H },                  // 0x64
    { "LD H, L", 0, LD_H_L },                  // 0x65
    { "LD H, (HL)", 0, LD_H_aHL },                  // 0x66
    { "LD H, A", 0, LD_H_A },                  // 0x67
    { "LD L, B", 0, LD_L_B },                  // 0x68
    { "LD L, C", 0, LD_L_C },                  // 0x69
    { "LD L, D", 0, LD_L_D },                  // 0x6a
    { "LD L, E", 0, LD_L_E },                  // 0x6b
    { "LD L, H", 0, LD_L_H },                  // 0x6c
    { "LD L, L", 0, LD_L_L },                  // 0x6d
    { "LD L, (HL)", 0, LD_L_aHL },                  // 0x6e
    { "LD L, A", 0, LD_L_A },                  // 0x6f
    { "LD (HL), B", 0, LD_aHL_B },                  // 0x70
    { "LD (HL), C", 0, LD_aHL_C },                  // 0x71
    { "LD (HL), D", 0, LD_aHL_D },                  // 0x72
    { "LD (HL), E", 0, LD_aHL_E },                  // 0x73
    { "LD (HL), H", 0, LD_aHL_H },                  // 0x74
    { "LD (HL), L", 0, LD_aHL_L },                  // 0x75
    { "HALT", 0, NOP },                  // 0x76
    { "LD (HL), A", 0, LD_aHL_A },                  // 0x77
    { "LD A, B", 0, LD_A_B },                  // 0x78
    { "LD A, C", 0, LD_A_C },                  // 0x79
    { "LD A, D", 0, LD_A_D },                  // 0x7a
    { "LD A, E", 0, LD_A_E },                  // 0x7b
    { "LD A, H", 0, LD_A_H },                  // 0x7c
    { "LD A, L", 0, LD_A_L },                  // 0x7d
    { "LD A, (HL)", 0, LD_A_aHL },                  // 0x7e
    { "LD A, A", 0, LD_A_A },                  // 0x7f
    { "ADD A, B", 0, ADD_A_B },                  // 0x80
    { "ADD A, C", 0, ADD_A_C },                  // 0x81
    { "ADD A, D", 0, ADD_A_D },                  // 0x82
    { "ADD A, E", 0, ADD_A_E },                  // 0x83
    { "ADD A, H", 0, ADD_A_H },                  // 0x84
    { "ADD A, L", 0, ADD_A_L },                  // 0x85
    { "ADD A, (HL)", 0, ADD_A_aHL },                  // 0x86
    { "ADD A, A", 0, ADD_A_A },                  // 0x87
    { "ADC A, B", 0, ADC_A_B },                  // 0x88
    { "ADC A, C", 0, ADC_A_C },                  // 0x89
    { "ADC A, D", 0, ADC_A_D },                  // 0x8a
    { "ADC A, E", 0, ADC_A_E },                  // 0x8b
    { "ADC A, H", 0, ADC_A_H },                  // 0x8c
    { "ADC A, L", 0, ADC_A_L },                  // 0x8d
    { "ADC A, (HL)", 0, ADC_A_aHL },                  // 0x8e
    { "ADC A, A", 0, ADC_A_A },                  // 0x8f
    { "SUB A, B", 0, SUB_A_B },                  // 0x90
    { "SUB A, C", 0, SUB_A_C },                  // 0x91
    { "SUB A, D", 0, SUB_A_D },                  // 0x92
    { "SUB A, E", 0, SUB_A_E },                  // 0x93
    { "SUB A, H", 0, SUB_A_H },                  // 0x94
    { "SUB A, L", 0, SUB_A_L },                  // 0x95
    { "SUB A, (HL)", 0, SUB_A_aHL },                  // 0x96
    { "SUB A, A", 0, SUB_A_A },                  // 0x97
    { "SBC A, B", 0, SBC_A_B },                  // 0x98
    { "SBC A, C", 0, SBC_A_C },                  // 0x99
    { "SBC A, D", 0, SBC_A_D },                  // 0x9a
    { "SBC A, E", 0, SBC_A_E },                  // 0x9b
    { "SBC A, H", 0, SBC_A_H },                  // 0x9c
    { "SBC A, L", 0, SBC_A_L },                  // 0x9d
    { "SBC A, (HL)", 0, SBC_A_aHL },                  // 0x9e
    { "SBC A, A", 0, SBC_A_A },                  // 0x9f
    { "AND B", 0, AND_B },                  // 0xa0
    { "AND C", 0, AND_C },                  // 0xa1
    { "AND D", 0, AND_D },                  // 0xa2
    { "AND E", 0, AND_E },                  // 0xa3
    { "AND H", 0, AND_H },                  // 0xa4
    { "AND L", 0, AND_L },                  // 0xa5
    { "AND (HL)", 0, AND_aHL },                  // 0xa6
    { "AND A", 0, AND_A },                  // 0xa7
    { "XOR B", 0, XOR_B },                  // 0xa8
    { "XOR C", 0, XOR_C },                  // 0xa9
    { "XOR D", 0, XOR_D },                  // 0xaa
    { "XOR E", 0, XOR_E },                  // 0xab
    { "XOR H", 0, XOR_H },                  // 0xac
    { "XOR L", 0, XOR_L },                  // 0xad
    { "XOR (HL)", 0, XOR_aHL },                  // 0xae
    { "XOR A", 0, XOR_A },                  // 0xaf
    { "OR B", 0, OR_B },                  // 0xb0
    { "OR C", 0, OR_C },                  // 0xb1
    { "OR D", 0, OR_D },                  // 0xb2
    { "OR E", 0, OR_E },                  // 0xb3
    { "OR H", 0, OR_H },                  // 0xb4
    { "OR L", 0, OR_L },                  // 0xb5
    { "OR (HL)", 0, OR_aHL },                  // 0xb6
    { "OR A", 0, OR_A },                  // 0xb7
    { "CP B", 0, CP_B },                  // 0xb8
    { "CP C", 0, CP_C },                  // 0xb9
    { "CP D", 0, CP_D },                  // 0xba
    { "CP E", 0, CP_E },                  // 0xbb
    { "CP H", 0, CP_H },                  // 0xbc
    { "CP L", 0, CP_L },                  // 0xbd
    { "CP (HL)", 0, CP_aHL },                  // 0xbe
    { "CP A", 0, CP_A },                  // 0xbf
    { "RET NZ", 0, RET_NZ },                  // 0xc0
    { "POP BC", 0, POP_BC },                  // 0xc1
    { "JP NZ, 0x%02X%02X", 2, JP_NZ_nn },                  // 0xc2
    { "JP 0x%02X%02X", 2, JP_nn },                  // 0xc3
    { "CALL NZ, 0x%02X%02X", 2, CALL_NZ_nn },                  // 0xc4
    { "PUSH BC", 0, PUSH_BC },                  // 0xc5
    { "ADD A, 0x%02X", 1, ADD_A_n },                  // 0xc6
    { "RST 0", 0, RST_0 },                  // 0xc7
    { "RET Z", 0, RET_Z },                  // 0xc8
    { "RET", 0, RET },                  // 0xc9
    { "JP Z, 0x%02X%02X", 2, JP_Z_nn },                  // 0xca
    { "Ext ops", 0, NOP },                  // 0xcb
    { "CALL Z, 0x%02X%02X", 2, CALL_Z_nn },                  // 0xcc
    { "CALL 0x%02X%02X", 2, CALL_nn },                  // 0xcd
    { "ADC A, 0x%02X", 1, ADC_A_n },                  // 0xce
    { "RST 8", 0, RST_8 },                  // 0xcf
    { "RET NC", 0, RET_NC },                  // 0xd0
    { "POP DE", 0, POP_DE },                  // 0xd1
    { "JP NC, 0x%02X%02X", 2, JP_NC_nn },                  // 0xd2
    { "NOP", 0, NOP },                  // 0xd3
    { "CALL NC, 0x%02X%02X", 2, CALL_NC_nn },                  // 0xd4
    { "PUSH DE", 0, PUSH_DE },                  // 0xd5
    { "SUB A, 0x%02X", 1, SUB_A_n },                  // 0xd6
    { "RST 10", 0, RST_10 },                  // 0xd7
    { "RET C", 0, RET_C },                  // 0xd8
    { "RETI", 0, RET },                  // 0xd9
    { "JP C, 0x%02X%02X", 2, JP_C_nn },                  // 0xda
    { "NOP", 0, NOP },                  // 0xdb
    { "CALL C, 0x%02X%02X", 2, CALL_C_nn },                  // 0xdc
    { "NOP", 0, NOP },                  // 0xdd
    { "SBC A, 0x%02X", 1, SBC_A_n },                  // 0xde
    { "RST 18", 0, RST_18 },                  // 0xdf
    { "LDH (0x%02X), A", 1, LDH_an_A },                  // 0xe0
    { "POP HL", 0, POP_HL },                  // 0xe1
    { "LDH (C), A", 0, LDH_aC_A },                  // 0xe2
    { "NOP", 0, NOP },                  // 0xe3
    { "NOP", 0, NOP },                  // 0xe4
    { "PUSH HL", 0, PUSH_HL },                  // 0xe5
    { "AND 0x%02X", 1, AND_n },                  // 0xe6
    { "RST 20", 0, RST_20 },                  // 0xe7
    { "ADD SP, %d", 1, ADD_SP_d },                  // 0xe8
    { "JP (HL)", 0, JP_aHL },                  // 0xe9
    { "LD (0x%02X%02X), A", 2, LD_ann_A },                  // 0xea
    { "NOP", 0, NOP },                  // 0xeb
    { "NOP", 0, NOP },                  // 0xec
    { "NOP", 0, NOP },                  // 0xed
    { "XOR 0x%02X", 1, XOR_n },                  // 0xee
    { "RST 28", 0, RST_28 },                  // 0xef
    { "LDH A, (0x%02X)", 1, LDH_A_an },                  // 0xf0
    { "POP AF", 0, POP_AF },                  // 0xf1
    { "NOP", 0, NOP },                  // 0xf2
    { "NOP", 0, NOP },                  // 0xf3
    { "NOP", 0, NOP },                  // 0xf4
    { "PUSH AF", 0, PUSH_AF },                  // 0xf5
    { "OR 0x%02X", 1, OR_n },                  // 0xf6
    { "RST 30", 0, RST_30 },                  // 0xf7
    { "LDHL SP, %d", 0, LDHL_SP_d },                  // 0xf8
    { "LD SP, HL", 0, LD_SP_HL },                  // 0xf9
    { "LD A, (0x%02X%02X)", 2, LD_A_ann },                  // 0xfa
    { "NOP", 0, NOP },                  // 0xfb
    { "NOP", 0, NOP },                  // 0xfc
    { "NOP", 0, NOP },                  // 0xfd
    { "CP 0x%02X", 1, CP_n },                  // 0xfe
    { "RST 38", 0, RST_38 },                  // 0xff
    
    
};

#endif /* main_h */
