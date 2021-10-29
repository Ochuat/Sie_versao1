#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//https://www.youtube.com/watch?v=mBT79DS8fl4
//criando o tipo de dado usuario
typedef struct usuario{
    char nome[20];
    int tipo;
    int limite;
} Usuario;

//criando o tipo de dado item
typedef struct item{
    char nome[20], proprietario[20];
    int tipo, codigo;
    bool isGood;
} Item;

//criando o tipo de dado reserva
typedef struct reserva{
    char nome[20], proprietario[20];
    int codigo, dia, mes;
} Reserva;

//funcao modelo
float atualizaSaldo(float saldo, float ajuste){
    return saldo * (1+(ajuste/100));
}

//imprime a tabela
void imprimeTabela(Item itens[],int numItens){

    for(int i = 0; i <17; i++){
        printf("\n");
    }

    printf("Digite \n");
    printf("1 - Retirar item | 2 - Devolver item | 3 - Cadastrar Usuario | 4 - Cadastra Item\n");
    printf("0 - Sair | 5 - Reservar | 6 - Ver reservas \n");
    printf("Itens: \n");
    for(int i = 0; i < numItens; i++){
        if(itens[i].isGood){
            printf("%d - %s - %s \n", itens[i].codigo, itens[i].nome, itens[i].proprietario);
        }else{
            printf("%d - %s - %s \n", itens[i].codigo, itens[i].nome, "Manutencao");
        }
    }
}


int main()
{
//fflush(stdin);
    int funcao = 1, numItens = 5, codigo, tipo;
    char nome[20];

    //cria 4 itens
    Item itens[5];
    strcpy (itens[0].nome,"Extensao");
    strcpy (itens[0].proprietario, "");
    itens[0].codigo = 1001;
    itens[0].tipo = 1;
    itens[0].isGood = true;

    strcpy (itens[1].nome,"Extensao");
    strcpy (itens[1].proprietario, "");
    itens[1].codigo = 1002;
    itens[1].tipo = 1;
    itens[1].isGood = true;

    strcpy (itens[2].nome,"Extensao");
    strcpy (itens[2].proprietario, "");
    itens[2].codigo = 1003;
    itens[2].tipo = 1;
    itens[2].isGood = true;

    strcpy (itens[3].nome, "Projetor");
    strcpy (itens[3].proprietario, "");
    itens[3].codigo = 2001;
    itens[3].tipo = 2;
    itens[3].isGood = true;
    strcpy (itens[4].nome, "Caixa_de_som");
    strcpy (itens[4].proprietario, "");
    itens[4].codigo = 3001;
    itens[4].tipo = 2;
    itens[4].isGood = true;

    //cria 3 usuarios
    int numUsuario = 3;
    Usuario user[5];
    strcpy (user[0].nome, "Joao");
    user[0].tipo = 1;
    user[0].limite = 0;
    strcpy (user[1].nome, "Ana");
    user[1].tipo = 1;
    user[1].limite = 0;
    strcpy (user[2].nome, "Lucas");
    user[2].tipo = 2;
    user[2].limite = 0;

    Reserva reservados[5];
    int numReservados = 0;

    printf("..######......####.....########\n.##....##......##......##......\n.##............##......##......\n..######.......##......######..\n.......##......##......##......\n.##....##.###..##..###.##......\n..######..###.####.###.########\n");
    printf("\n\n");
    char senha[20] = "123456";
    int i = 0;
    char ch;
    char pwd[30];
    printf("Entre com a senha: ");
    ch = _getch();

    while((ch = _getch()) != 13){
        pwd[i] = ch;
        i++;
        printf("*");
    }
    pwd[i]= '\0';

    int ret = strcmp(pwd, senha);

    if(ret == 0){


        while(funcao != 0){

            imprimeTabela(itens, numItens);
            printf("Digite a funcao desejada \n");
            scanf("%d", &funcao);

            //switch case das funçoes
            switch (funcao){
                //retirar item
                case 1:



                    printf("Digite o codigo e o nome de usuario \n");
                    scanf("%d %s", &codigo, &nome);
                     int registraUsuario = 0;

                    //busca o tipo pelo nome
                    for(int i = 0; i < numUsuario; i++){
                        int ret = strcmp(user[i].nome, nome);
                        if(ret == 0){
                            tipo = user[i].tipo;
                            registraUsuario = i;
                            break;
                        }
                    }
                    //busca o idice pelo codigo
                    for(int i = 0; i < numItens; i++){
                        if(codigo == itens[i].codigo){
                            codigo = i;
                            break;
                        }
                    }
                    //verifica se o tipo bate
                    if(itens[codigo].tipo == tipo && user[registraUsuario].limite < 2){
                        strcpy (itens[codigo].proprietario, nome);
                        user[registraUsuario].limite++;
                    }else{

                        printf("\nErro, retirada nao autorizada\n\n");
                    }

                    break;

                //devolver item
                case 2:

                    printf("Codigo - estado? (r: ruim, b: bom)\n");
                    char estado;
                    scanf("%d %c", &codigo, &estado);

                    //busca o idice pelo codigo
                    for(int i = 0; i < numItens; i++){
                        if(codigo == itens[i].codigo){
                            codigo = i;
                            break;
                        }
                    }

                    //busca o usuario pelo nome
                    for(int i = 0; i < numUsuario; i++){
                        int ret = strcmp(user[i].nome, itens[codigo].proprietario);
                        if(ret == 0){
                            user[i].limite--;

                            break;
                        }
                    }

                    strcpy (itens[codigo].proprietario, "");

                    if(estado == 'b'){
                        itens[codigo].isGood = true;
                    }else{
                        itens[codigo].isGood = false;
                    }
                   break;

                 //cadastra usuario
                case 3:

                    printf("Digite o nome e o tipo (1: funcionario 2:professor) do usuario a ser cadastrado\n");
                    scanf("%s %d", &user[numUsuario].nome, &user[numUsuario].tipo);
                    numUsuario++;

                    break;

                 //cadastra item
                case 4:

                    printf("Digite o codigo, nome e tipo (1: funcionario 2:professor) do item a ser cadastrado\n");
                    scanf("%d %s %d", &itens[numItens].codigo, &itens[numItens].nome, &itens[numItens].tipo);

                    strcpy (itens[numItens].proprietario, "");
                    itens[0].isGood = true;
                    numItens++;
                    break;

                case 5:

                    printf("Digite o codigo, nome do usuario e data (dd mm)\n");

                    scanf("%d %s %d %d", &reservados[numReservados].codigo, &reservados[numReservados].proprietario, &reservados[numReservados].dia, &reservados[numReservados].mes);
                    //busca o nome pelo codigo
                    for(int i = 0; i < numItens; i++){
                        if(reservados[numReservados].codigo == itens[i].codigo){
                            strcpy(reservados[numReservados].nome, itens[i].nome);
                            break;
                        }
                    }

                    numReservados++;

                    break;

                case 6:

                    printf("\nData - Codigo - Item - Nome \n");
                    for(int i = 0; i < numReservados; i++){
                        printf("%d/%d - %d - %s - %s \n", reservados[i].dia, reservados[i].mes, reservados[i].codigo, reservados[i].nome, reservados[0].proprietario);
                    }

                    break;

            }


        }

    } else{
        printf("\nSenha incorreta");
    }
    return 0;
}
