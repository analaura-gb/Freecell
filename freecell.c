#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct no{
    short numero;
    char naipe;
    struct no *proximo;
} tCarta;
tCarta *primBaralho = NULL;
tCarta **mesa = {NULL};
tCarta **naipe = {NULL};
tCarta **temporario = {NULL};
int totalBaralho=0;
int contnaipe[4];

void gerarBaralho();
void embaralhaBaralho(int naipe, int numero, int posicao);
void distribuirMesa();
void imprime();
void moveMesaNaipe();
void moveMesaTemp();
void moveTempMesa();
void moveNaipeTemp();
void moveMesaNaipe();
void moveNaipeMesa();
void moveMesaMesa();

int main(int argc, char **argv){
    system("color 1");
    int op=0;
    srand(time(NULL));
    gerarBaralho();
    distribuirMesa();
    while(op!=8){
        imprime();
        printf("(1)Move Mesa-Naipe\n");
        printf("(2)Move Mesa-Temp\n");
        printf("(3)Move Temp-Mesa\n");
        printf("(4)Move Naipe-Temp\n");
        printf("(5)Move Temp-Naipe\n");
        printf("(6)Move Naipe-Mesa\n");
        printf("(7)Move Mesa-Mesa\n");
        printf("(8)Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                moveMesaNaipe();
                system("cls");
                break;
            case 2:
                moveMesaTemp();
                system("cls");
                break;
            case 3:
                moveTempMesa();
                system("cls");
                break;
            case 4:
                moveNaipeTemp();
                system("cls");
                break;
            case 5:
                moveTempNaipe();
                system("cls");
                break;
            case 6:
                moveNaipeMesa();
                system("cls");
                break;
            case 7:
                moveMesaMesa();
                system("cls");
                break;
            case 8:
                op=8;
                system("cls");
                printf("Obrigado por jogar!");
                break;
            default:
                printf("Opcao Invalida.\n");
                system("cls");
                break;
        }
    }
    return 0;
}//end main

void gerarBaralho(){
    mesa = (tCarta *)malloc(sizeof(tCarta)*8);
    naipe = (tCarta *)malloc(sizeof(tCarta)*4);
    temporario = (tCarta *)malloc(sizeof(tCarta)*4);
    int i, j, pos;

    for(i=0;i<4;i++){
        temporario[i]=NULL;
        naipe[i]=NULL;
        contnaipe[i]=0;
    }

    for(i=3;i<=6;i++){
        for(j=1;j<=13;j++){
            pos=rand()%(totalBaralho+1);
            embaralhaBaralho(i, j, pos);
        }
    }
}//end gerarBaralho

void embaralhaBaralho(int naipe, int numero, int posicao){
    tCarta *novo = (tCarta *)malloc(sizeof(tCarta));
    novo->numero=numero;
    novo->naipe=naipe;
    if(posicao==0){
        novo->proximo=primBaralho;
        primBaralho=novo;
    }
    else{
        tCarta *atual = primBaralho;
        int i;
        for(i=0;i<posicao-1;i++){
            atual=atual->proximo;
        }
        novo->proximo=atual->proximo;
        atual->proximo=novo;
    }
    totalBaralho++;


}//end embaralhaBaralho

void distribuirMesa(){
    int i;
    tCarta *ant = NULL;
    tCarta *atual = primBaralho;
    int quant=0;
    while(quant<8){
        if(quant<4){
            for(i=0;i<=7;i++){
                if(i==0){
                    mesa[quant]=atual;
                }
                else{
                    ant=atual;
                    atual=atual->proximo;
                }
            }
            ant->proximo=NULL;
        }
        else{
            for(i=0;i<=6;i++){
                if(i==0){
                    mesa[quant]=atual;
                }
                else{
                    ant=atual;
                    atual=atual->proximo;
                }
            }
            ant->proximo=NULL;
        }
        quant++;
    }
}//end distribuirMesa

void imprime(){
    int i;
    tCarta *atual = NULL;
    printf("TEMP= ");
    for(i=0;i<4;i++){
        if(temporario[i]==NULL){
            printf("%d-[    ] ",i);
        }
        else{
            printf("%d-[%2d/%c] ",i, temporario[i]->numero, temporario[i]->naipe);
        }
    }
    printf("\n\n");
    for(i=0;i<4;i++){
        if(naipe[i]==NULL){
            printf("[NAIPE %c]=\n",i+3);
        }
        else{
            atual = naipe[i];
            printf("[NAIPE %c]= ",i+3);
            while(atual!=NULL){
                printf("[%2d/%c]", atual->numero, atual->naipe);
                atual=atual->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
    for(i=0;i<8;i++){
        atual = mesa[i];
        printf("MESA[%d]= ",i);
        while(atual!=NULL){
            printf("[%2d/%c]",atual->numero,atual->naipe);
            atual=atual->proximo;
        }
        printf("\n");
    }
    printf("\n");
}//end imprime

void moveMesaNaipe(){
    int m, n;
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m);
    printf("Digite a posicao do Naipe: ");
    scanf("%d",&n);
    tCarta *antm=NULL;
    tCarta *atualm=mesa[m];
    tCarta *antn=NULL;
    tCarta *atualn=naipe[n];

    while(atualm->proximo!=NULL){
        antm=atualm;
        atualm=atualm->proximo;
    }
    while(atualn!=NULL){
        antn=atualn;
        atualn=atualn->proximo;
    }
    switch(n){
    case 0:
        if(atualm->naipe==3){
            if(atualm->numero==contnaipe[n]+1){//Mofificando aqui
                if(antn==NULL){
                    naipe[n]=atualm;
                }
                else{
                    antn->proximo=atualm;
                }
                contnaipe[n]++;
                if(antm==NULL){
                    mesa[m]=NULL;
                }
                else{
                    antm->proximo=NULL;
                }

            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 1:
        if(atualm->naipe==4){
            if(atualm->numero==contnaipe[n]+1){
                if(antn==NULL){
                    naipe[n]=atualm;
                }
                else{
                    antn->proximo=atualm;
                }
                contnaipe[n]++;
                if(antm==NULL){
                    mesa[m]=NULL;
                }
                else{
                    antm->proximo=NULL;
                }
            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 2:
        if(atualm->naipe==5){
            if(atualm->numero==contnaipe[n]+1){
                if(antn==NULL){
                    naipe[n]=atualm;
                }
                else{
                    antn->proximo=atualm;
                }
                contnaipe[n]++;
                if(antm==NULL){
                    mesa[m]=NULL;
                }
                else{
                    antm->proximo=NULL;
                }
            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 3:
        if(atualm->naipe==6){
            if(atualm->numero==contnaipe[n]+1){
                if(antn==NULL){
                    naipe[n]=atualm;
                }
                else{
                    antn->proximo=atualm;
                }
                contnaipe[n]++;
                if(antm==NULL){
                    mesa[m]=NULL;
                }
                else{
                    antm->proximo=NULL;
                }
            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    }
}//end moveMesaNape

void moveMesaTemp(){
    int m, t;
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m);
    printf("Digite a posicao do Temporario: ");
    scanf("%d",&t);
    tCarta *ant=NULL;
    tCarta *atual=mesa[m];

    if(temporario[t]==NULL){
        if(mesa[m]!=NULL){
            while(atual->proximo!=NULL){
                    ant=atual;
                    atual=atual->proximo;

            }
            if(ant==NULL){
                mesa[m]=NULL;
            }
            else{
                ant->proximo=NULL;
            }
            temporario[t]=atual;
        }
        else{
            printf("Nao ha cartas na mesa\n");
            getchar();
            getchar();
        }
    }
    else{
        printf("A posicao do temporario esta ocupada\n");
        getchar();
        getchar();
    }

}//end moveMesaTemp

void moveTempMesa(){
    int m, t;
    printf("Digite a posicao do Temporario: ");
    scanf("%d",&t);
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m);
    tCarta *atual=mesa[m];

    if(atual==NULL){
        mesa[m]=temporario[t];
        temporario[t]=NULL;
    }
    else{
        while(atual->proximo!=NULL){
            atual=atual->proximo;
        }
        if((temporario[t]->naipe==5) || (temporario[t]->naipe==6)){
            if((atual->naipe==3)|| (atual->naipe==4)){
                if(atual->numero-1==temporario[t]->numero){
                    atual->proximo=temporario[t];
                    temporario[t]=NULL;
                }
                else{
                    printf("Escolha uma carta um numero menor\n");
                    getchar();
                    getchar();
                }
            }
            else{
                printf("Escolha uma carta de cor diferente\n");
                getchar();
                getchar();
            }
        }
        else{
            if((atual->naipe==5)|| (atual->naipe==6)){
                if(atual->numero-1==temporario[t]->numero){
                    atual->proximo=temporario[t];
                    temporario[t]=NULL;
                }
                else{
                    printf("Escolha uma carta um numero menor\n");
                    getchar();
                    getchar();
                }
            }
            else{
                printf("Escolha uma carta de cor diferente\n");
                getchar();
                getchar();
            }
        }
    }
}//end moveTempMesa

void moveNaipeTemp(){
    int n, t;
    printf("Digite a posicao do Naipe: ");
    scanf("%d",&n);
    printf("Digite a posicao do Temporario: ");
    scanf("%d",&t);
    tCarta *ant=NULL;
    tCarta *atual=naipe[n];

    if(temporario[t]==NULL){
        if(naipe[n]!=NULL){
            while(atual->proximo!=NULL){
                    ant=atual;
                    atual=atual->proximo;

            }
            if(ant==NULL){
                naipe[n]=NULL;
            }
            else{
                ant->proximo=NULL;
            }
            temporario[t]=atual;
            contnaipe[n]--;
        }
        else{
            printf("Nao ha cartas na mesa\n");
            getchar();
            getchar();
        }
    }
    else{
        printf("A posicao do temporario esta ocupada\n");
        getchar();
        getchar();
    }

}//end moveNaipeTemp

void moveTempNaipe(){
    int t, n;
    printf("Digite a posicao dO Temporario: ");
    scanf("%d",&t);
    printf("Digite a posicao do Naipe: ");
    scanf("%d",&n);
    tCarta *ant=NULL;
    tCarta *atual=naipe[n];

    while(atual!=NULL){
        ant=atual;
        atual=atual->proximo;
    }
    switch(n){
    case 0:
        if(temporario[t]->naipe==3){
            if(temporario[t]->numero==contnaipe[n]+1){
                if(ant==NULL){
                    naipe[n]=temporario[t];
                }
                else{
                    ant->proximo=temporario[t];
                }
                contnaipe[n]++;
                temporario[t]=NULL;

            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 1:
        if(temporario[t]->naipe==4){
            if(temporario[t]->numero==contnaipe[n]+1){//Mofificando aqui
                if(ant==NULL){
                    naipe[n]=temporario[t];
                }
                else{
                    ant->proximo=temporario[t];
                }
                contnaipe[n]++;
                temporario[t]=NULL;

            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 2:
        if(temporario[t]->naipe==5){
            if(temporario[t]->numero==contnaipe[n]+1){//Mofificando aqui
                if(ant==NULL){
                    naipe[n]=temporario[t];
                }
                else{
                    ant->proximo=temporario[t];
                }
                contnaipe[n]++;
                temporario[t]=NULL;

            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    case 3:
        if(temporario[t]->naipe==6){
            if(temporario[t]->numero==contnaipe[n]+1){
                if(ant==NULL){
                    naipe[n]=temporario[t];
                }
                else{
                    ant->proximo=temporario[t];
                }
                contnaipe[n]++;
                temporario[t]=NULL;

            }
            else{
                printf("Escolha uma carta um numero maior\n");
                getchar();
                getchar();
            }
        }
        else{
            printf("Escolha uma carta do mesmo Naipe\n");
            getchar();
            getchar();
        }
        break;
    }
}

void moveNaipeMesa(){
    int m, n;
    printf("Digite a posicao do Naipe: ");
    scanf("%d",&n);
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m);
    tCarta *atualm=mesa[m];
    tCarta *antn=NULL;
    tCarta *atualn=naipe[n];

    while(atualn->proximo!=NULL){
        antn=atualn;
        atualn=atualn->proximo;
    }
    if(atualm==NULL){
        mesa[m]=atualn;
        if(antn==NULL){
            naipe[n]=NULL;
        }
        else{
            antn->proximo=NULL;
        }
    }
    else{
        while(atualm->proximo!=NULL){
            atualm=atualm->proximo;
        }
        if((atualn->naipe==5) || (atualn->naipe==6)){
            if((atualm->naipe==3)|| (atualm->naipe==4)){
                if(atualm->numero-1==atualn->numero){
                    atualm->proximo=atualn;
                    if(antn==NULL){
                        naipe[n]=NULL;
                    }
                    else{
                        antn->proximo=NULL;
                    }
                    contnaipe[n]--;
                }
                else{
                    printf("Escolha uma carta um numero menor\n");
                    getchar();
                    getchar();
                }
            }
            else{
                printf("Escolha uma carta de cor diferente\n");
                getchar();
                getchar();
            }
        }
        else{
            if((atualm->naipe==5)|| (atualm->naipe==6)){
                if(atualm->numero-1==atualn->numero){
                    atualm->proximo=atualn;
                    if(antn==NULL){
                        naipe[n]=NULL;
                    }
                    else{
                        antn->proximo=NULL;
                    }
                    contnaipe[n]--;
                }
                else{
                    printf("Escolha uma carta um numero menor\n");
                    getchar();
                    getchar();
                }
            }
            else{
                printf("Escolha uma carta de cor diferente\n");
                getchar();
                getchar();
            }
        }
    }
}

void moveMesaMesa(){
    int m1, m2, numero, ok=1;
    char naipe;
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m1);
    printf("Digite a posicao da Mesa: ");
    scanf("%d",&m2);

    tCarta *antm1=NULL;
    tCarta *atualm1=mesa[m1];
    tCarta *atualm2=mesa[m2];
    tCarta *blocoat=NULL;
    tCarta *blocoant=NULL;

    printf("Digite a primeira carta do bloco ou a carta a ser movida\nNumero e Naipe: ");
    scanf("%d %c",&numero, &naipe);
    naipe-=45;

    while((atualm1!=NULL) && ((atualm1->naipe!=naipe) || (atualm1->numero!=numero))){
        antm1=atualm1;
        atualm1=atualm1->proximo;
    }
    if(atualm1==NULL){
        printf("Carta nao encontrada");
        getchar();
        getchar();
    }
    else{
        if(atualm1->proximo==NULL){
            if(atualm2==NULL){
                mesa[m2]=atualm1;
                if(antm1==NULL){
                    mesa[m1]=NULL;
                }
                else{
                    antm1->proximo=NULL;
                }
            }
            else{
                while(atualm2->proximo!=NULL){
                    atualm2=atualm2->proximo;
                }
                if((atualm1->naipe==5) || (atualm1->naipe==6)){
                    if((atualm2->naipe==3)|| (atualm2->naipe==4)){
                        if(atualm2->numero-1==atualm1->numero){
                            atualm2->proximo=atualm1;
                            if(antm1==NULL){
                                mesa[m1]=NULL;
                            }
                            else{
                                antm1->proximo=NULL;
                            }
                        }
                        else{
                            printf("Escolha uma carta um numero menor\n");
                            getchar();
                            getchar();
                        }
                    }
                    else{
                        printf("Escolha uma carta de cor diferente\n");
                        getchar();
                        getchar();
                    }
                }
                else{
                    if((atualm2->naipe==5)|| (atualm2->naipe==6)){
                        if(atualm2->numero-1==atualm1->numero){
                            atualm2->proximo=atualm1;
                            if(antm1==NULL){
                                mesa[m1]=NULL;
                            }
                            else{
                                antm1->proximo=NULL;
                            }
                        }
                        else{
                            printf("Escolha uma carta um numero menor\n");
                            getchar();
                            getchar();
                        }
                    }
                    else{
                        printf("Escolha uma carta de cor diferente\n");
                        getchar();
                        getchar();
                    }
                }
            }
        }
        else{
            if(atualm2==NULL){
                mesa[m2]=atualm1;
                if(antm1==NULL){
                    mesa[m1]=NULL;
                }
                else{
                    antm1->proximo=NULL;
                }
            }
            else{
                while(atualm2->proximo!=NULL){
                    atualm2=atualm2->proximo;
                }
                if((atualm1->naipe==5) || (atualm1->naipe==6)){
                    if((atualm2->naipe==3)|| (atualm2->naipe==4)){
                        if(atualm2->numero-1==atualm1->numero){
                            blocoant=antm1;
                            blocoat=atualm1;
                            antm1=atualm1;
                            atualm1=atualm1->proximo;
                            while(atualm1->proximo!=NULL){
                                if((antm1->naipe==5) || (antm1->naipe==6)){
                                    if((atualm1->naipe==4) || (atualm1->naipe==3)){
                                        if(antm1->numero-1==atualm1->numero){
                                            antm1=atualm1;
                                            atualm1=atualm1->proximo;
                                        }
                                        else{
                                            ok=0;
                                            break;
                                        }
                                    }
                                    else{
                                        ok=0;
                                        break;
                                    }
                                }
                            }
                            if(ok!=0){
                                atualm2->proximo=blocoat;
                                if(blocoant==NULL){
                                    mesa[m1]=NULL;
                                }
                                else{
                                    blocoant->proximo=NULL;
                                }
                            }
                            else{
                                printf("O bloco deve estar em ordem decrescente e intercalando naipes de cores diferentes.");
                                getchar();
                                getchar();
                            }
                            ok=1;
                        }
                        else{
                            printf("Escolha uma carta um numero menor\n");
                            getchar();
                            getchar();
                        }
                    }
                    else{
                        printf("Escolha uma carta de cor diferente\n");
                        getchar();
                        getchar();
                    }
                }
                else{
                    if((atualm2->naipe==5)|| (atualm2->naipe==6)){
                        if(atualm2->numero-1==atualm1->numero){
                            blocoant=antm1;
                            blocoat=atualm1;
                            antm1=atualm1;
                            atualm1=atualm1->proximo;
                            while(atualm1->proximo!=NULL){
                                if((antm1->naipe==5) || (antm1->naipe==6)){
                                    if((atualm1->naipe==4) || (atualm1->naipe==3)){
                                        if(antm1->numero-1==atualm1->numero){
                                            antm1=atualm1;
                                            atualm1=atualm1->proximo;
                                        }
                                        else{
                                            ok=0;
                                            break;
                                        }
                                    }
                                    else{
                                        ok=0;
                                        break;
                                    }
                                }
                            }
                            if(ok!=0){
                                atualm2->proximo=blocoat;
                                if(blocoant==NULL){
                                    mesa[m1]=NULL;
                                }
                                else{
                                    blocoant->proximo=NULL;
                                }
                            }
                            else{
                                printf("O bloco deve estar em ordem decrescente e intercalando naipes de cores diferentes.");
                                getchar();
                                getchar();
                            }
                            ok=1;
                        }
                        else{
                            printf("Escolha uma carta um numero menor\n");
                            getchar();
                            getchar();
                        }
                    }
                    else{
                        printf("Escolha uma carta de cor diferente\n");
                        getchar();
                        getchar();
                    }
                }
            }
        }
    }
}
