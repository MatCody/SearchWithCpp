#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

string info, file="0", quantidade="0", tempo="0", tempoInicial="0", tempoFinal="0", variavelMax="0", variavelMin="0", variavel="0"; 
float infoNum;
char lambda[10];
float infoLinha[94][145], maiorlinha, menorlinha; // matriz dos dados do arquivo, 94 de colunas e 145 de linhas 
string datas[150],horas[150],args[12], nomes[94]; // array das datas
int i=0,n,j=0, l=0, alpha=0, final=0, inicio=0, vmax, vmin;

fstream Canal; // Criação de um canal de somente saida nomeado 'Canal'.

class extrair_nomes{
    private:

    public:

    extrair_nomes(){
        Canal.seekg(0);
        alpha = 0;

        do{
        getline(Canal,nomes[alpha], ',');
        replace(nomes[alpha].begin(), nomes[alpha].end(),';', ' ');
        alpha++;
        }while(alpha<=92);
        

    
    }
};
class extrair_dados{
    private:
    string linha;
    int posicao;

    public:
    
        extrair_dados(){ //função construtora, está posicionando o ponteiro de leitura no fim da linha do cabeçalho e inicio da linha de dados
        Canal.seekg(0);
        getline(Canal,linha);
        posicao = Canal.tellg();
        Canal.seekg(posicao);
    
    };
    void dados(){ // função da classe com o objetivo de varrer as linhas do arquivo salvando as informações das datas e dados na array e matriz respectivamente correspondentes
        
        i=0;
        getline(Canal,info,',');
        //cout<<"informacao: "<<info<<endl;
        datas[j]=info;
        
        do{
            getline(Canal,info,',');
            infoLinha[i][j] = stof(info);
            //cout<<"informacao: "<<infoLinha[i][j]<<endl;
            i=i+1;
        }while(i<=90);
        getline(Canal,info);
        infoLinha[i][j]=stof(info);
        //cout<<"informacao: "<<infoLinha[i][j]<<endl;
    }

   
};
class aparecer{
        private:
        
        public:

        aparecer(int repetir){
            alpha=0;
            cout<<nomes[0]<<setw(80-nomes[0].length())<<right;
            do{
            cout<<internal<<datas[alpha]<<setw(30-nomes[0].length());
            alpha++;
            }while(alpha<repetir);
            cout<<endl;
            alpha=1;
            l=0;
            i=0;
            do{
            cout<<left<<nomes[alpha]<<setw(80-nomes[alpha].length())<<right;
            l=0;
            do{
                cout<<internal<<infoLinha[i][l]<< setw(20);
                l++;
            }while(l< repetir);
                cout<<endl;
                alpha++;
                i++;
            }while(alpha<=90);

        }
	 };
class editar_array{
    private:

    public:

    editar_array(){ //função construtora da classe com o objetivo de editar a array que armazena as datas e horas em arrays de mesmas posições com apenas as horas das informações
        alpha=0;
        do{
            horas[alpha]= datas[alpha].substr(11, 11+9);
            //cout<< horas[alpha]<<endl;
        alpha=alpha+1; 
        //cout<< horas[alpha]<<endl;
        }while(alpha<= 143);

    }


};

int main(int argc, char *argv[]){

// armazena os valores de argv em uma array de string chamada args, facilitando sua chamada
for(int p=0;p<argc;p++){
    args[p]=argv[p];
}

for(int p=1;p<argc;p++){
    if(args[p]=="V"){
        variavel=args[p+1];
    }
    if(args[p]=="F"){
        file=args[p+1];
    }
    if(args[p]=="N"){
        quantidade=args[p+1];
    }
    
    if(args[p]=="ti"){
        tempoInicial=args[p+1];
    }
    if(args[p]=="tf"){
        tempoFinal=args[p+1];
    }
    if(args[p]=="t"){
        tempo=args[p+1];
    }
    if(args[p]=="Vmax"){
        variavelMax=args[p];
    }
    if(args[p]=="Vmin"){
        variavelMin=args[p];
    }
    p++;

}


Canal.open(file, ios::in); //Comando para abrir o arquivo csv que o usuario inserir.
if(!Canal){ // Se o arquivo não for aberto ou criado da erro e fecha o programa.
    std::cout<<"Erro"<<endl<<endl;
    return 1;
}

if(stoi(variavel)<=0){
    cout<<"Erro, variavel invalida."<<endl;
    return 2;
}

if(quantidade != "0"){ // condicional para caso o usuario na hora de executar o programa colocar como parametros F e N
cout<< "Tabela até o valor inserido de N"<<endl<<endl;


n=stoi(quantidade);



extrair_nomes caixa_de_nomes;
extrair_dados caixa_de_dados;
while(j<n){
caixa_de_dados.dados();
j++;
}
aparecer mostrar_na_tela(n);

}

if( tempoInicial != "0" && tempoFinal != "0"){ // REVER ESSE ERRO!!!!

cout<<"Tabela de um tempo (ti) ate o tempo (tf)"<<endl;

extrair_nomes caixa_de_nomes1;
extrair_dados caixa_de_dados1; // seta o ponteiro de leitura para a linha de dados

j=0;
n=91;

do{ // executa a função dados 143 vezes para pegar todas informações do arquivo
caixa_de_dados1.dados();
//cout<<j<< " "<<endl;
j=j+1;
}while(j<=143);

editar_array caixa_de_edicao; // edita todas as datas em uma array das suas horas

inicio=0;
while(horas[inicio] != tempoInicial){// verifica qual linha está o 'ti'
inicio=inicio+1;
}
cout<<"ti: "<<inicio<<endl;

final=0;
do{ // verifica onde esta o 'tf'
final=final+1;
}while(horas[final] != tempoFinal);
cout<<"tf: "<<final<<endl;

n= final - inicio+1;

l=0;
do{

alpha=0;
datas[l]=datas[inicio]; // faz com que as primeiras posições da array datas se torne a partir de datas i até datas f

do{ // muda as informacões da primeira linha da matriz para as informações da linha que o usuario quer ver
infoLinha[alpha][l]=infoLinha[alpha][inicio];
alpha++;
}while(alpha<93);

l=l+1;
inicio = inicio+1;

}while(inicio<=final);


cout<< n <<endl<<endl;
aparecer mostrar_natela2(n);
}

if(tempo != "0" ){

cout<<"Tabela especifica do tempo inserido"<<endl<<endl;

extrair_nomes caixa_de_nomes2;
extrair_dados caixa_de_dados2; // seta o ponteiro de leitura para a linha de dados

j=0;
n=90;

do{ // executa a função dados 90 vezes para pegar todas informações do arquivo
caixa_de_dados2.dados();
j=j+1;
}while(j<=143);

editar_array caixa_de_edicao1; // edita todas as datas em uma array das suas horas

i=0;
do{ // faz com que 'i' seja a linha referente a hora que o usuario quer ver
    i=i+1;
}while(horas[i] != tempo);

cout<<i<<endl;

l=0;
datas[0]=datas[i]; // faz com que a primeira posição da array datas se torne a que o usuario quer 


do{ // muda as informacões da primeira linha da matriz para as informações da linha que o usuario quer ver
infoLinha[l][0]=infoLinha[l][i];
l++;
}while(l<=91);

n=0;
aparecer mostrar_natela3(0);
}

if(variavel !=  "0"){
//alpha = atoi(argv[4]);


cout<<"Tabela com os valores da variavel inserida"<<endl<<endl;



extrair_nomes caixa_de_nomes3;
extrair_dados caixa_de_dados3; // seta o ponteiro de leitura para a linha de dados

j=0;
n=90;

do{ // executa a função dados 143 vezes para pegar todas informações do arquivo
caixa_de_dados3.dados();
j=j+1;
}while(j<=143);
l=stoi(variavel);
alpha=0;
cout<<nomes[l]<<endl;
while(alpha<=143){
    cout<<setw(20)<<infoLinha[l-1][alpha]<<endl;
    alpha++;
};

}

if(variavelMax != "0" && variavel != "0"){ // VERIFICAR ESSE ERRO!!!

vmax = stoi(variavel);
vmax = vmax-1;



extrair_dados caixa_de_dados4; // seta o ponteiro de leitura para a linha de dados

j=0;
n=91;

do{ // executa a função dados 143 vezes para pegar todas informações do arquivo
caixa_de_dados4.dados();
j=j+1;
}while(j<=143);

alpha=0;
maiorlinha = 0;
do{

if(infoLinha[vmax][alpha] >= maiorlinha){
maiorlinha = infoLinha[vmax][alpha];
}

alpha++;
}while(alpha<143); 

cout<<"Maior valor da variavel: "<< maiorlinha<< endl;



}

if(variavel !=  "0" && variavelMin != "0"){ // VERIFICAR ESSE ERRO!!!

vmin = stoi(variavel);
vmin = vmin -1;

extrair_dados caixa_de_dados5; // seta o ponteiro de leitura para a linha de dados

j=0;
n=91;

do{ // executa a função dados 143 vezes para pegar todas informações do arquivo
caixa_de_dados5.dados();
j=j+1;
}while(j<=143);

alpha=0;
menorlinha = 99999999999;
do{
    
if(infoLinha[vmin][alpha] <= menorlinha){
menorlinha = infoLinha[vmin][alpha];
}

alpha++;
}while(alpha<143); 
cout<<"Menor valor da variavel inserida: "<< menorlinha<< endl;

}



return 0;

}


