#include <stdio.h>
#include <stdlib.h>

void le_arquivo(char *nome, int mat[][9]){
    FILE *arq = fopen(nome,"r");
    if(arq == NULL){
        printf("Erro de leitura\n");
        system("pause");
        exit(1);
    }

    int i,j;
    for(i=0; i< 9; i++)
        for(j=0; j< 9; j++)
            fscanf(arq,"%d",&mat[i][j]);

    fclose(arq);
}

int testeL(int a, int b,int c[][9]) //a = linha b = variavel
{
    int i,j;
    i=a;
    for(j=0; j< 9; j++)
    {
        if(c[i][j]==b)                  //se não houver nenhum numero igual na linha ele retorna 0
        {
            return 0;
        }
    }
    return 1;
}

int testeC(int a, int b,int c[][9]) //a = Coluna   b = Variavel
{
    int i,j;
    j=a;
    for(i=0; i< 9; i++)                 // se não houver nenhum numero igual na coluna ele retorna 0
    {
        if(c[i][j]==b)
        {
            return 0;
        }
    }
    return 1;
}

int testeB(int a, int b, int c,int d[][9])    //a= linha b=coluna 
{
    int i,j;
    float a1;
    a1 = (a+1);                 //como a linha começa em 0 e vai até 8 acrecenta 1 para menor complexidade matematica
    a1 = a1/3;                  // são 9 linhas quando se divite em 3 forma 3 blocos de linha
    if (a1<=1){             
        a=0;
    }
    else{
        if(a1<=2){
            a=3;
        }
        else{
                a=6;
        }
    }
    float b1;
    b1 = (b+1);                     // como a coluna começa em 0 e vai até 8 acrescenta 1 para menor complexidade matematica
    b1 = b1/3;                      // são 9 colunas se divide em 3 forma 3 blocos de colunas
    if (b1<=1){
        b=0;
    }
    else{
        if(b1<=2){
            b=3;
        }
        else{
            b=6;
        }
    }
    for(i=a;i<=(a+2);i++){              // combinados os blocos forma os blocos de sudoku e se neste bloco que a variavel está inserida e sendo testada não tiver outro numero igual retorna 0
        for(j=b;j<=(b+2);j++){
            if(d[i][j]==c){
                return 0;
            }
        }
    }
    return 1;
}



int main(){
    int mat[9][9];
    int i,j;
    le_arquivo("sudoku.txt", mat);
    int x;
    int contador=0;
    int s1,s2;
    int F=1;
    while(F!=0){       // enquanto tiver numero 0 no sudoku o programa não para
        F=0;
        for(x=1;x<=9;x++){
            for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                    if(mat[i][j]==0){
                        F++;                //sinal que tem numero 0
                        if(testeL(i,x,mat)==1){             // se na linha tem algum numero que esta sendo testado
                            if(testeC(j,x,mat)==1){             // se na coluna tem algum numero que esta sendo testado
                                if(testeB(i,j,x,mat)==1){           // se no bloco 3x3 tem um nnumero que esta sendo testado
                                    contador++;             // Adiciona possibilidade de o valor ser colocado
                                    s1=i;                   // guarda a linha e coluna em que a possibilidade está adicionada
                                    s2=j;
                                }
                            }
                        }
                    }
                }
                if(contador==1){           // se só houver uma possibilidade de ter aquele numero ele coloca
                    mat[s1][s2]=x;
                }
                contador=0;
            }
        }
    }

    for(i=0;i<9;i++){
        for(j=0;j<9;j++)                        // printa a matriz para o usuario
            printf("%d ",mat[i][j]);
        printf("\n");
    }


    return 0;
}