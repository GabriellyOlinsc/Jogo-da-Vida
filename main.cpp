#include <iostream>
#include <cstdlib> //para o srand e rand
#include <ctime>
#include <cmath>
#include <conio.h> //getch()
#define TMAX 30
//CABECALHO MUNDO PLANO
int leiaNumeroInteiro(int);
void geracaoMatrizInicial(int,char [][TMAX]);
void leituraMatriz(int,char[][TMAX]);
int verificarMargens(int,int,int,char[][TMAX]);
int verificarVizinhosMeio(int,int,char[][TMAX]);
void transferenciaMatrizes(int,char[][TMAX],char[][TMAX]);
void analiseCondicaoSobrevivencia(int,int,int,char[][TMAX]);
void analiseCondicaoMorte(int,int,int,char[][TMAX],char[][TMAX]);
void exibirComparativoMatrizes(int,char[][TMAX],char[][TMAX]);
void atualizarMatriz(int,char[][TMAX],char[][TMAX]);
bool ultimaGeracao(int,char[][TMAX],char[][TMAX]);
void swapMatrizes(int, char[][TMAX], char [][TMAX]);
using namespace std;

int main(){
    int n = leiaNumeroInteiro(TMAX);
    int cont=1;
    char mundoAtual[TMAX][TMAX];
    char novaGeracao[TMAX][TMAX];
    geracaoMatrizInicial(n,mundoAtual);
    leituraMatriz(n, mundoAtual);
    cout<<"Exibicao da geracao original: (pressione uma tecla para continuar...)"<<endl;

    do{
       getch();
       system("cls");
       cout<<"CICLO "<<cont<<endl;
       atualizarMatriz(n,mundoAtual,novaGeracao);
       exibirComparativoMatrizes(n,mundoAtual,novaGeracao);
       cout<<"(pressione uma tecla para exibir uma nova geracao)"<<endl;
       swapMatrizes(n,mundoAtual,novaGeracao);
       cont++;
    }while(ultimaGeracao(n,mundoAtual,novaGeracao)==false);

    cout<<"Fim das geracoes!";

    return 0;
}
int leiaNumeroInteiro (int sup){
    int n;
    do{
        cout<<"Informe o tamanho da geracao de seres vivos (10-"<<sup<<") :";
        cin>>n;
    }
    while(n<10 or n>sup);
    return n;
}
void geracaoMatrizInicial (int n, char mat[][TMAX]){
    srand(time(0));
    int col, lin;
    for(int i=0; i<(40*pow(n,2))/100; i++){ //preenche no max 40% de toda matriz
        col= rand()% n;
        lin= rand()% n;
        mat[lin][col]='*';
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(mat[i][j]!='*')
                mat[i][j]=' ';
        }
}
void leituraMatriz (int n, char mat[][TMAX]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout<<mat[i][j]<<" ";
        cout<<endl;
    }
}
int verificarMargens(int n, int lin, int col, char mat[][TMAX]){
    int vetC[n]= {col,col+1,col-1}, vetL[n]= {lin,lin+1,lin-1}; //vetor coluna e vetor coluna
    int vizinhosVivos=0,iteL=1,iteC=1; //iteC e iteL = iterador da linha e coluna

    if (lin==n-1)   //canto inferior direito e esquerdo
        vetL[1]=lin-1;
    if (col==n-1)  // canto inferior esquerdo e canto superior esquerdo
        vetC[1]=col-1;

    if ((lin==0 or lin==n-1) and (col==0 or col==n-1)){  //Caso dos Cantos
        for(int i=0; i<=iteL; i++)
            for(int j=0; j<=iteL; j++)
                if(mat[vetL[i]][vetC[j]]=='*' and (vetL[i]!=lin or vetC[j]!= col))
                    vizinhosVivos++;
    }
    else { // caso das laterais
        if (col==n-1 or col==0)
            iteL++;
        if(lin==n-1 or lin==0)
            iteC++;
        for(int i=0; i<=iteL; i++)
            for(int j=0; j<=iteC; j++)
                if(mat[vetL[i]][vetC[j]]=='*' and (vetL[i]!=lin or vetC[j]!= col))
                    vizinhosVivos++;
    }
    return vizinhosVivos;
}
int verificarVizinhosMeio(int lin, int col, char mat[][TMAX]){
    int vizinhosVivos=0;
    for(int i=lin-1; i<=lin+1; i++)
        for(int j=col-1; j<=col+1; j++)
            if((i!=lin or j!=col) and mat[i][j]=='*')
                vizinhosVivos++;
    return vizinhosVivos;
}
void transferenciaMatrizes (int n,char mat[][TMAX],char novaMat[][TMAX]){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            novaMat[i][j]=mat[i][j];
        }
}
void analiseCondicaoSobrevivencia(int vizinhosVivos, int lin, int col, char matAntiga[][TMAX], char matNova[][TMAX]){
    if(matAntiga[lin][col]==' ' and vizinhosVivos==3)
        matNova[lin][col]='@';    //reprodução
    if(matAntiga[lin][col]=='*' and (vizinhosVivos>3 or vizinhosVivos<2))
         matNova[lin][col]=' ';    //falta de comida e solidao
}
void exibirComparativoMatrizes (int n, char matAntiga[][TMAX], char novaMat[][TMAX]){
    cout<<endl;
    cout<<"Geracao anterior"<<endl;
    leituraMatriz(n,matAntiga);
    cout<<endl;
    cout<<"Nova Geracao"<<endl;
    leituraMatriz(n,novaMat);
}
void atualizarMatriz (int n, char mat[][TMAX],char novaMat[][TMAX]){
    transferenciaMatrizes(n,mat,novaMat);  //transferindo o conteudo da geração atual para a futura geração
    int celulasVivas;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            celulasVivas=0;
            if ((i==0 or i==n-1) or (j==0 or j==n-1))
                celulasVivas = verificarMargens(n, i, j,mat);
            else
                celulasVivas =  verificarVizinhosMeio(i,j,mat);
            analiseCondicaoSobrevivencia(celulasVivas,i,j,mat, novaMat);
        }
}
bool ultimaGeracao (int n, char matA[][TMAX],char matB[][TMAX]){
    bool iguais=true;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(matA[i][j]!=matB[i][j]){
                iguais=false;
                break;
            }
    return iguais;
}
void swapMatrizes(int n, char matA[][TMAX], char matB[][TMAX]){
     for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if (matB[i][j]=='@')
                matB[i][j]='*';
            swap(matA[i][j],matB[i][j]);
        }
}
