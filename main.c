#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include <string.h>

FILE *arq;
char *pl ;
char str[50];
char mine[10] ;
int linha;

unsigned int mbr; /**declarando o MBR(Memory Buffer Register) com tamanho de 32 bits
 *                   Toda a comunicação
 *                   entre processador e Memoria RAm e feita por meio do MBR com uma frase de instrução
 *                   ciclo dos dados -> memoria -> MBR */

unsigned int mar; /**declarando MAR(Memory Adress Register) com tamanho de 32 bits
 *                  o MAR ira guardar o endereço de memoria que pode ser usado em algumas instruções
 *                  **não confunda, ele nao guarda o valor e sim o endereço a ser buscado pelo mbr ***/

unsigned char ir; /**declarando IR(Instruction Register) com tamanho de 8 bits
 *                  o IR é o registrador responsável por guardar o Opcode da instrução a ser execultada
 *                  sendo o opcode já carregado no MBR anterior mente -> ciclo = MBR -> IR*/

unsigned char ro0; /**declarando Ro0(Register Operand 0) com tamnho de 8 bits
 *                  esse registrador é um ponteiro para qual posição do vetor reg[](registrador) que haverá interação*/

unsigned char ro1; /**declarando Ro1(Register Operand 1) com tamanho de 8 bits
 *                  esse registrador assim como o ro0 é também um ponteiro para o vetor de registradore mas esse é secundário
 *                  assim com operações com 2 variáveis ele é ultilizado*/

unsigned int imm;  /**declarando IMM(Immediate) com tamanho de 32 bits
 *                  o imediato é usado em algumas operações, normalmente ele recebe um valor de um endereço de memória
 *                  (valor armazendo em um endereço apontado pelo @mar) e depois aplicado a alguma operação usando
 *                  registradores apontados por ro0 ou ro1*/

unsigned int pc = 0; /**declarando PC(Program Counter) com tamanho de 32 bits
 *                      o PC é reponsável por guardar o endereço de memória da próxima einstrução a ser
 *                      buscada na memória*/

unsigned char E, L, G;/** são registradores que guradao valores de comparação como "equal to", "lower than"
 *              e "greater than", quando uma operação ativa o bit se ativa, deverá sem implementado em variaveis
 *              com tamanhos de 1 bit, contudo implementar com 8 bits (char)
 */
unsigned int reg[8];/**vetor de registores sendo
*                       reg         sequencia de bits
*                       r0          000
*                       r1          001
*                       r2          010
*                       r3          011
*                       r4          100
*                       r5          101
*                       r6          110
*                       r7          111
*                       cada registrador tem tamanho de 32 bits e tem com indentificador 3 bits
 *                       (quantidade de bits necessários para representar 8 registradores diferentes)
 * */
unsigned char memoria[154]; /** vetor memoria com 153 posicoes e de tamanho de 1 byte(8 bits)*/

__attribute__((unused)) int playing = 1; // flag para a continuidade do loop, ela é alterada caso seja fornecido a instrução @hlt (0x00)
//##################################################FUNÇÕES#############################################################
void guardarMemoria(unsigned int mem ,unsigned int a){
    memoria[mem++] = (a & 0xff000000) >> 24;
    memoria[mem++] = (a & 0x00ff0000) >> 16;
    memoria[mem++] = (a & 0x0000ff00) >> 8;
    memoria[mem] = (a & 0x0000ff);
}
void colocarInstru(int mem){
    unsigned char *pl1, ro0; // aux recebe ro0
    unsigned int count = 0, memImm;

    pl1 = strtok(pl," ,");
    while(pl1){
        if(count == 0){
            strcpy(mine,pl1);
        }
        if (count== 1){
            ro0 = (int)strtol(pl1,NULL,16);
        }
        if(count == 2){
            memImm = (int)strtol(pl1,NULL,16);
        }
        pl1 = strtok(NULL," ,r");
        count++;
    }
    if(strcmp(mine,"ld")== 0){
        unsigned int x = 0x13;
        x = (x << 3) | ro0;
        x = (x << 21)| memImm;
        guardarMemoria(mem,x);
    }else if(strcmp(mine,"st")== 0){
        unsigned int x = st;
        x = (x << 3) | ro0;
        x = (x << 21)| memImm;
        guardarMemoria(mem,x);
    }else if(strcmp(mine,"add")== 0){
        unsigned int x = add;
        x = (x << 3) |ro0;
        x = (x << 3) | memImm;
        x =  x << 18;
        guardarMemoria(mem,x);
    }else if(strcmp(mine,"sub")== 0) {
        unsigned int x = sub;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"mul")== 0) {
        unsigned int x = mul;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"div")== 0) {
        unsigned int x = div;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"cmp")== 0) {
        unsigned int x = cmp;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"movr")== 0) {
        unsigned int x = movr;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }
    else if(strcmp(mine,"and")== 0) {
        unsigned int x = and;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"or")== 0) {
        unsigned int x = or;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"xor")== 0) {
        unsigned int x = xor;
        x = (x << 3) | ro0;
        x = (x << 3) | memImm;
        x = x << 18;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"not")== 0) {
        unsigned int x = not;
        x = ((x << 3)|ro0)<<21;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"je")== 0) {
        unsigned int x = je;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jne")== 0) {
        unsigned int x = jne;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jl")== 0) {
        unsigned int x = jl;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jg")== 0) {
        unsigned int x = jg;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jle")== 0) {
        unsigned int x = jle;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jge")== 0) {
        unsigned int x = jge;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"jmp")== 0) {
        unsigned int x = jmp;
        x = (x << 24)| memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"movi")== 0) {
        unsigned int x = movi;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"addi")== 0) {
        unsigned int x = addi;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"subi")== 0) {
        unsigned int x = subi;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"muli")== 0) {
        unsigned int x = muli;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"divi")== 0) {
        unsigned int x = divi;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"lsh")== 0) {
        unsigned int x = lsh;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"rsh")== 0) {
        unsigned int x = rsh;
        x = (x << 3) | ro0;
        x = (x << 21) | memImm;
        guardarMemoria(mem, x);
    }else if(strcmp(mine,"nop")== 0) {
        unsigned int x = nop;
        x = x << 24;
        guardarMemoria(mem, x);
    }else{
        unsigned int x  = 0;
        guardarMemoria(mem,x);
    }
}
void lerTexto(){

    unsigned int mem, val;
    unsigned char tipo,valor;
    unsigned int count = 0;
    arq = fopen("a.txt", "r");

    while (fgets(str, 50, arq) != NULL){
        pl = strtok(str, "; ");
        mem = (int)strtol(pl,NULL,16); // pegando a memoria
        while(pl){
            if(count == 1){
                tipo = *pl;
                //  se é intrução retorna 0x69
                //  se é dado retorna 0x64

            }else if(count == 2){
                if(tipo == 0x64){ // se for dado
                    val = (int)strtol(pl,NULL,16);
                    memoria[mem++] = (val & 0xff000000) >> 24;
                    memoria[mem++] = (val & 0x00ff0000) >> 16;
                    memoria[mem++] = (val & 0x0000ff00) >> 8;
                    memoria[mem]   = (val & 0x000000ff);
                }else{ //se for instrução
                    colocarInstru(mem);
                }
            }

            pl = strtok(NULL ,";");
            count++;
        }
        count = 0;
    }

    if (NULL == arq)
        printf("Arquivo a.txt nao encontrado \n");
    fclose(arq);
}
/**  função @Busca
 *      função carregerMBR faz a busca na memória, que é o primeiro passo do ciclo:
 *                      -> Busca
 *                      -> Decodifica
 *                      -> Executa
 *
 *      carrega o MBR deslocando bits para a esquerda
 *      o MBR sendo de tamnha de 32 bits e memoria sendo de 8 bits por posição
 *      @return void
 */
void Busca(){
    mar = pc;
    mbr = memoria[mar++];
    for (int i = 1; i < 4;i++) {
        mbr = (mbr << 8 ) | memoria[mar++];
    }

}

/**
 *          @getMemoryAddress
 *          -> a função tem como objetivo armazenar o endereço de memoria com 21 bits no @mar
 *          esta operação e feita com a ajuda de uma mascara e realizando operações lógicas & (e) no valor do MBR
 *              ex:
 *                  1111 1111 111x xxxx xxxx xxxx xxxx xxxx
 *                  0000 0000 0001 1111 1111 1111 1111 1111
 *                  ---------------------------------------
 *                  0000 0000 000x xxxx xxxx xxxx xxxx xxxx
 *
 *          máscara=0x001fffff
 *              OBS: não precisamos dislocar casas binárias já que nao é necessário pois todas as casas já estão nas
 *              casas menos significativas.
 */

/**@inserirMemoria*/
void InserirMemoria(){
    memoria[mar++] = (mbr & 0xff000000)>> 24;
    memoria[mar++] = (mbr & 0x00ff0000)>>16;
    memoria[mar++] = (mbr & 0x0000ff00)>>8;
    memoria[mar++] = mbr & 0x000000ff;

}
/** @BuscarNaMemoria
 * função que após o @mar ser atualizado na decodificação da instrução vai na memoria e atualiza o @mbr para trazer
 * os proximos 32 bits de memoria começando pelo endereço em @mar
 * */
void BuscarNaMemoria(){
    mbr = memoria[mar++];
    for (int i = 0; i < 3; ++i) {
        mbr = (mbr << 8 ) | memoria[mar++];
    }

}
/** @PreencherRos
 *  a função é responsável por preencher os Ro0 e Ro1
 *  a separação é feita com máscaras sob a instrução usando a função lógica & (e / and)
 *  sob a forma binaria da instrução
 *      ro0 ex:
 *              1111 1111 xxx1 1111 1111 1111 1111 1111
 *              0000 0000 1110 0000 0000 0000 0000 0000
 *      máscar= 0x00e00000
 *              ---------------------------------------
 *              0000 0000 xxx0 0000 0000 0000 0000 0000
 *      e dislocamos 21 casas binárias para ter o valor nas casas menos significativas
 *          final:
 *              0000 0000 0000 0000 0000 0000 0000 1110
 *           ---#######################################---
 *      ro1 ex:
 *              1111 1111 111x xx11 1111 1111 1111 1111
 *              0000 0000 0001 1100 0000 0000 0000 0000
 *      máscara= 0x001c0000
 *          disclocando 18 casas binárias para ter o valor nas casas menos significativas
 *          final:
 *              0000 0000 0001 1100 0000 0000 0000 0000
 */
void Decodifica()  {
    ir = mbr >> 24;
    if(ir >= hlt && ir <= nop){
        ///fazer nada.
    }else if(ir >= add && ir <= 0x08){
        ro0 = (mbr & 0x00e00000) >> 21;
        ro1 = (mbr & 0x001c0000) >> 18;
    }else if(ir == 0x0b){
        ro0 = (mbr & 0x00e00000) >> 21;
    }else if(ir >= je && ir <= jmp){
        mar = mbr & 0x001fffff;
    }else if(ir >= ld && ir <= st){
        ro0 = (mbr & 0x00e00000) >> 21;
        mar = mbr & 0x001fffff;
    }else if(ir >= movi && ir <= rsh){
        ro0 = (mbr & 0x00e00000) >> 21;
        imm = mbr & 0x001fffff;
    }
}
//##################################################BRINCADEIRA#########################################################
void Executa(){
    switch (ir) {
        case hlt:/**
*           HALT: o processador não faz nada. Em outras palavras, nenhum registrador tem o seu valor alterado
*           durante a execução de hlt. Deve-se colocar no fim do programa.
*           execução simples: apenas troco para o valor de parada do loop while assim terminando a execução do programa C
*/
            playing = 0;
            return;
        case nop:/** NO OPERATION
*           nessa operação apenas se incrementa o PC e nao se faz mais nada.
*/
            pc++;
            return;
        case add:/** ADD REGISTER
*            Esta instrução opera a soma entre dois valores armazenados nos registradores apontados por ro0 e ro1
*            e o resultado é armazenado no registrador de ro0
*/

            reg[ro0] += reg[ro1];
            pc += 4;
            return;
        case sub:/** SUBTRACT REGISTER
 *           Esta instrução opera a subtração entre dois valores armazenados nos registradores apontados por ro0 e ro1
 *           e o resultado é armazenado no registrador de ro0
 */
            reg[ro0] -= reg[ro1];
            pc += 4;
            return;
        case mul:/** MULTIPLY REGISTER
 *          Esta instrução opera a multiplicação entre dois valores armazenados nos registradores apontados por ro0 e ro1
 *          e o resultado é armazenado no registrador de ro0
*/

            reg[ro0] *= reg[ro1];
            pc += 4;
            return;
        case 0x05:/** DIVIDE REGISTER
 *          Esta instrução opera a divisão entre dois valores armazenados nos registradores apontados por ro0 e ro1
 *          e o resultado é armazenado no registrador de ro0
 */

            reg[ro0] /= reg[ro1];
            pc += 4;
            return;

        case cmp:/** COMPARE REGISTER
 *          esta instrução opera a comparação entre palavras armazenadas nos registrdore apontados por ro0 e ro1
 *          e altera os registradores internos @E @L @G de acordo com o resultado dos seguintes testes logicos:
 *              se reg[ro0]  == reg[ro1], @E = 1 senao @E = 0
 *              se reg[ro0] < reg[ro1], @L = 1 senão @L = 0
 *              se reg[ro0] > reg[ro1], @G = 1 senão @G = 0
 */

            if(reg[ro0] == reg[ro1]){
                E = 1;
                L = 0;
                G = 0;
            }else if(reg[ro0] < reg[ro1]){
                E = 0;
                L = 1;
                G = 0;
            }else{
                E = 0;
                L = 0;
                G = 1;
            }
            pc += 4;
            return;
        case movr:/** MOVE REGISTER
 *          esta instrução opera a copia o valor amazenado no registrador apontado por ro1 para o valor apontado por ro0
*/

            reg[ro0]  = reg[ro1];
            pc += 4;
            return;
        case 0x08:/** LOGICAL-AND ON REGISTER
 *          esta instrução opera um comparação logica (and / e) entre os valores armazenados nos registradores apontados
 *          por ro0 e ro1 e o resultado é armazenado no registardor apontado por ro0
 */

            reg[ro0] &= reg[ro1];
            pc += 4;
            return;
        case 0x09:/** LOGICAL-OR ON REGISTER
 *          esta instrução opera uma comparação logica (or /ou) entre os valores armazenados nos registradores apontados
 *          por ro0 e ro1 e o resultado é armazenado no resgistrador apontado por ro0
 */

            reg[ro0] |= reg[ro1];
            pc += 4;
            return;
        case 0x0a:/** LOGICAL-XOR ON REGISTER
 *          esta instrução opera uma operação logica (xor / ou exclusivo) entre os valores armazenados nos registradores
 *          apontados por ro0 e ro1 e o resultado é armazenado no registrador apontado por ro0;
 */

            reg[ro0] ^= reg[ro1];
            pc += 4;
            return;
        case 0x0b:/** LOGICAL-NOT REGISTER
 *          esta instrução opera uma operação logica (not / não) no valor armazenado no registrador apontado por ro0
 *          e o resultado é armazenado no registrador apontado por ro0
 */

            reg[ro0] = !reg[ro0];
            pc += 4;
            return;
        case je:/**JUMP IF EQUAL TO:
 *          muda o registrador PC para o endereço de memória X caso E = 1
 */
            if(E == 1)
                pc = mar;
            else
                pc += 4;
            return;
        case jne:/**JUMP IF NOT EQUAL TO:
 *          muda o registrador PC para o endereço de memória X caso E = 0.
 */
            if(E == 0)
                pc = mar;
            else
                pc += 4;
            return;
        case jl:/**JUMP IF LOWER THAN:
 *          muda o registrador PC para o endereço de memória X caso L = 1.
 */
            if(L == 1)
                pc = mar;
            else
                pc += 4;
            return;
        case jle:/**JUMP IF LOWER THAN OR EQUAL TO:
 *          muda o registrador PC para o endereço de memória X caso E = 1 ou L = 1.
 */

            if(E == 1 || L == 1)
                pc =mar;
            else
                pc += 4;
            return;
        case jg:/**JUMP IF GREATER THAN:
 *          muda o registrador PC para o endereço de memória X caso G = 1.
 */

            if(G == 1)
                pc = mar;
            else
                pc += 4;
            return;
        case jge:/**JUMP IF GREATER THAN OR EQUAL TO:
 *          muda o registrador PC para o endereço de memória X caso E = 1 ou G = 1.
 */

            if(E == 1 || G == 1)
                pc =mar;
            else
                pc += 4;
            return;
        case jmp:/**JUMP:
 *          muda o registrador PC para o endereço de memória X.
 */

            pc = mar;
            return;
        case ld:/**LOAD:
 *          carrega para o registrador X uma palavra da memória de 32 bits que se inicia no endereço Y
 */
            BuscarNaMemoria();
            reg[ro0] = mbr;
            pc += 4;
            return;

        case st://
            mbr = reg[ro0];
            guardarMemoria(mar,mbr);
            pc += 4;
            return;
        case movi:/**MOVE IMMEDIATE:
 *          regX = IMM
*/
            reg[ro0] = imm;
            pc += 4;
            return;
        case addi:/** ADD IMMEDIATE
 *           esta instrução opera a soma entre valores armazenados nos registradores apontados por ro0 e imm
 *           e o resultado é armazenado no registrador apontado por ro0
 */
            reg[ro0] += imm;
            pc += 4;
            return;
        case subi:/** SUBTRACT IMMEDIATE
 *           esta instrução opera a subtração entre valores armazenados nos registradores apontados por ro0 e imm
 *           e o resultado é armazenado no registrador apontado por ro0
 */
            reg[ro0] -= imm;
            pc += 4;
            return;
        case muli:/** MULTIPLY IMMEDIATE
 *           esta instrução opera a multiplicação entre valores armazenados nos registradores apontados por ro0 e imm
 *           e o resultado é armazenado no registrador apontado por ro0
 */
            reg[ro0] *= imm;
            pc += 4;
            return;
        case divi:/** DIVIDE IMMEDIATE
 *           esta instrução opera a divisão entre valores armazenados nos registradores apontados por ro0 e imm
 *           e o resultado é armazenado no registrador apontado por ro0
 */
            reg[ro0] /= imm;
            pc += 4;
            return;
        case lsh:/** LEFT SHIFT:
 *          esta instrução deloca a palavra armazenada no registrador apontado por ro0 na quantidade de bits armazenada
 *          em imm para a esquerda
 */

            BuscarNaMemoria();
            imm = mbr;
            reg[ro0] =reg[ro0] << imm;
            pc += 4;
            return;
        case rsh:/**
 *          esta instrução deloca a palavra armazenada no registrador apontado por ro0 na quantidade de bits armazenada
 *          em imm para a direita
 */

            BuscarNaMemoria();
            imm = mbr;
            reg[ro0] =reg[ro0] >> imm;
            pc += 4;
            return;
        default:
            printf("não foi inseria uma entrada de instrução correta verifique os opcodes e tente novamente");
    }
}

int main() {
    //--------------------------------------------------------------------------------------
    lerTexto();

    while(playing == 1) {
        Busca();
        Decodifica();
        Executa();
    }
        printf("%x",memoria[0x7d]);

    return 0;
}




