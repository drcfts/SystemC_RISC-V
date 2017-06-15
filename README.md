# Processador _RISC-V + Cache_ em System C

Projeto Final de Modelagem em Sistemas de Silício - 2017/1

Alunos:

* Davi Rabbouni de Carvalho Freitas - _150033010_
* Iuri
* Marcos Vinicius Prescendo Tonin - _140153233_

## Tarefas

###  Implementar processador

- [X] Decode
- [X] Fetch
- [X] Execute
- [ ] Breg

###  Implementar uma memória cache de nível 1 (interna ao processador)

- [ ] Cache
###  Implementar uma conexão ao roteador (com criação de um módulo Shell)
- [ ] Shell/ Kernel

---
## Processador RISC-V 

### Tipos de Instruções

* **Tipo R**

![](Imagens/tipoR.png)

* Respectivas Instruções que serão implementadas

Instrução  | Opcode   | Funct7    | Funct3   | Operação                      | Implementado
:---------:| :------: | :-------: | :------: |:--------                      |:-----------:
**ADD**    | 0110011  |  0000000  |    000   |R[rd] = R[rs1] + R[rs2]        |<ul><li>- [X] </li></ul>
**SUB**    | 0110011  |  0100000  |    000   |R[rd] = R[rs1] - R[rs2]        |<ul><li>- [X] </li></ul>
**SLL**    | 0110011  |  0000000  |    001   |R[rd] = R[rs1] << R[rs2](4:0)  |<ul><li>- [X] </li></ul>
**SLT**    | 0110011  |  0000000  |    010   |R[rd] = (R[rs1] < R[rs2])? 1:0 |<ul><li>- [X] </li></ul>
**SLTU**   | 0110011  |  0000000  |    011   |R[rd] = (R[rs1] < R[rs2])? 1:0 |<ul><li>- [X] </li></ul>
**XOR**    | 0110011  |  0000000  |    100   |R[rd] = R[rs1] xor R[rs2]      |<ul><li>- [X] </li></ul>
**SRL**    | 0110011  |  0000000  |    101   |R[rd] = R[rs1] >> R[rs2](4:0)  |<ul><li>- [X] </li></ul>
**SRA**    | 0110011  |  0100000  |    101   |R[rd] = R[rs1] >> R[rs2](4:0)  |<ul><li>- [X] </li></ul>
**OR**     | 0110011  |  0000000  |    110   |R[rd] = R[rs1] OR R[rs2]       |<ul><li>- [X] </li></ul>
**AND**    | 0110011  |  0000000  |    111   |R[rd] = R[rs1] & R[rs2]        |<ul><li>- [X] </li></ul>

---

* **Tipo I**

![](Imagens/tipoI.png)

* Respectivas Instruções que serão implementadas

Instrução  | Opcode   | Funct7    | Funct3   | Operação                             | Implementado
:---------:| :------: | :-------: | :------: |:--------                             | :-----------:
**ADDI**   | 0010011  |  -        |    000   |R[rd] = R[rs1] + imm[11:0]            |<ul><li>- [X] </li></ul>
**SLTI**   | 0010011  |  -        |    010   |R[rd] = (R[rs1] < imm[11:0])? 1:0     |<ul><li>- [X] </li></ul>
**SLTIU**  | 0010011  |  -        |    011   |R[rd] = (R[rs1] < imm[11:0])? 1:0     |<ul><li>- [X] </li></ul>
**X0RI**   | 0010011  |  -        |    100   |R[rd] = R[rs1] xor imm[11:0]          |<ul><li>- [X] </li></ul>
**ORI**    | 0010011  |  -        |    110   |R[rd] = R[rs1] OR imm[11:0]           |<ul><li>- [X] </li></ul>
**ANDI**   | 0010011  |  -        |    111   |R[rd] = R[rs1] & imm[11:0]            |<ul><li>- [X] </li></ul>
**LB**     | 0000011  |  -        |    000   |R[rd] = (byte)Mem[R[rs1] + imm[11:0]] |<ul><li>- [X] </li></ul>
**LH**     | 0000011  |  -        |    001   |R[rd] = (half)Mem[R[rs1] + imm[11:0]] |<ul><li>- [X] </li></ul>
**LW**     | 0000011  |  -        |    010   |R[rd] = Mem[R[rs1] + imm[11:0]]       |<ul><li>- [X] </li></ul>
**LBU**    | 0000011  |  -        |    110   |R[rd] = (ubyte)Mem[R[rs1] + imm[11:0]]|<ul><li>- [X] </li></ul>
**LHU**    | 0000011  |  -        |    101   |R[rd] = (uhalf)Mem[R[rs1] + imm[11:0]]|<ul><li>- [X] </li></ul>
**JALR**   | 1100111  |  -        |    000   |R[rd] = PC+4;PC = [{rs1 + Imm,0}]  ???|<ul><li>- [X] </li></ul>


* Casos Especiais (Utilizando o _shamt_)

> ** shamt = rs2 **

Instrução  | Opcode   | Funct7    | Funct3   | Operação                   | Implementado
:---------:| :------: | :-------: | :------: |:--------                   |:-----------:
**SLLI**   | 0010011  |  0000000  |    001   |R[rd] = R[rs1] << shamt     |<ul><li>- [X] </li></ul>
**SRLI**   | 0010011  |  0000000  |    101   |R[rd] = R[rs1] >> shamt     |<ul><li>- [X] </li></ul>
**SRAI**   | 0010011  |  0100000  |    101   |R[rd] = R[rs1] >> shamt     |<ul><li>- [X] </li></ul>

---

* **Tipo S**

![](Imagens/tipoS.png)

* Respectivas Instruções que serão implementadas

Instrução  | Opcode   | Funct7    | Funct3   | Operação                 | Implementado
:---------:| :------: | :-------: | :------: |:--------                 |:-----------:
**SB**     | 0100011  |  -        |    000   |Mem[rs1+Imm]= R[rs2](7:0) |<ul><li>- [X] </li></ul>
**SH**     | 0100011  |  -        |    001   |Mem[rs1+Imm]= R[rs2](15:0)|<ul><li>- [X] </li></ul>
**SW**     | 0100011  |  -        |    010   |Mem[rs1+Imm]= R[rs2]      |<ul><li>- [X] </li></ul>

---

* **Tipo B**

![](Imagens/tipoB.png)

* Respectivas Instruções que serão implementadas

Instrução | Opcode   | Funct7    | Funct3   | Operação                         | Implementado
:--------:| :------: | :-------: | :------: |:--------                         |:-----------:
**BEQ**   | 1100111  |  -        |    000   |if(R[rs1] == R[rs2]) PC= PC+4+Imm |<ul><li>- [X] </li></ul>
**BNE**   | 1100111  |  -        |    001   |if(R[rs1] != R[rs2]) PC= PC+4+Imm |<ul><li>- [X] </li></ul>
**BLT**   | 1100111  |  -        |    100   |if(R[rs1] < R[rs2]) PC= PC+4+Imm  |<ul><li>- [X] </li></ul>
**BGE**   | 1100111  |  -        |    101   |if(R[rs1] >= R[rs2]) PC= PC+4+Imm |<ul><li>- [X] </li></ul>
**BLTU**  | 1100111  |  -        |    110   |if(R[rs1] < R[rs2]) PC= PC+4+Imm  |<ul><li>- [X] </li></ul>
**BGEU**  | 1100111  |  -        |    111   |if(R[rs1] >= R[rs2]) PC= PC+4+Imm |<ul><li>- [X] </li></ul>

---

* **Tipo U**

![](Imagens/tipoU.png)

* Respectivas Instruções que serão implementadas

Instrução  | Opcode   | Funct7    | Funct3   | Operação                      | Implementado
:---------:| :------: | :-------: | :------: |:--------                      |:-----------:
**LUI**    | 0110111  |  -        |    -     |R[rd] = {Imm,000000000000}     |<ul><li>- [X] </li></ul>
**AUIPC**  | 0010111  |  -        |    -     |R[rd] = PC+{Imm,000000000000}  |<ul><li>- [X] </li></ul>

---

* **Tipo J**

![](Imagens/TipoJ.png)

* Respectivas Instruções que serão implementadas


Instrução  | Opcode   | Funct7    | Funct3   | Operação            | Implementado
:---------:| :------: | :-------: | :------: |:--------            |:-----------:
**JAL**    | 1101111  |  -        |    -     |R[rd] = PC+4;PC=Imm  |<ul><li>- [X] </li></ul>

---

## Memória Cache

![](Imagens/mapeamento_direto.png)
