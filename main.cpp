#include <iostream>
#include <cstdlib>

using namespace std;

int ad[10201][10201];

//Rulati in fullscreen pentru a vizualiza corect arealul si botmapul.

void afisA(int A[101][101]); //afisarea arealului
void afisB(int A[101][101]); //afissarea hartii robotului
void generare(int areal[101][101]); //generarea arealului
void parcurgere(int areal[101][101],int ad[10201][10201], int botmap[101][101], int x, int y); //parcurgerea arealului
//void dfs(int k, long long int ad[10201][10201], int areal[101][101], int botmap [202][202]);


int main()
{
    int areal[101][101]={0},o,i,j;
    int botmap[101][101]={0};//harta din memoria robotului
    do
    {
        cout<<"Optiuni disponibile:"<<endl;
        cout<<"(1) Generare de areal"<<endl<<"(2) Parcurgere de areal"<<endl<<"(3) Afisare areal"<<endl<<"(4) Afisare harta"<<endl<<"(5) Resetare areal si harta"<<endl<<"(0) Iesire din program"<<endl<<"Alegeti optiunea: ";
        cin>>o;
        cout<<endl;
        if(o==1){
            generare(areal);
        }
        else
        if(o==2)
        {
            int x,y,i;
            x=rand()%100+1;
            y=rand()%100+1;
            while(areal[x][y]==7)
            {
                x=rand()%100+1;
                y=rand()%100+1;
            }
            for(i=0;i<101;i++)
                for(j=0;j<101;j++){
                    if((areal[i][j]==0)&&(areal[i][j+1]==0))
                        ad[i*j+j][i*(j+1)+j+1]=ad[i*(j+1)+j+1][i*j+j]=1;
                    if((areal[i][j]==0)&&(areal[i][j-1]==0))
                        ad[i*j+j][i*(j-1)+j-1]=ad[i*(j-1)+j-1][i*j+j]=1;
                    if((areal[i][j]==0)&&(areal[i-1][j]==0))
                        ad[i*j+j][(i-1)*j+j]=ad[(i-1)*j+j][i*j+j]=1;
                    if((areal[i][j]==0)&&(areal[i+1][j]==0))
                        ad[i*j+j][(i+1)*j+j]=ad[(i+1)*j+j][i*j+j]=1;
            }
            parcurgere(areal,ad,botmap,x,y);
            areal[x][y]=botmap[x][y]=6;
        }
        else if(o==3)
            afisA(areal);
        else if(o==4)
            afisB(botmap);
        else if(o==5){
            for(i=0;i<101;i++)
                for(j=0;j<101;j++){
                areal[i][j]=0;
                botmap[i][j]=0;
                ad[i*j+j][j]=ad[j][i*j+j]=0;}
        }
        else if(o!=0)
            cout<<"Optiunea selectata nu este disponibila. Va rugam alegeti una din optiunile disponibile"<<endl;
    }
    while(o!=0);
    return 0;
}


void afisA(int A[101][101])
{
    int i,j;
    for(i=0; i<=100; i++)
    {

        for(j=0; j<=100; j++)
            if(A[i][j]==0)
                cout<<".";
            else if(A[i][j]==5)
                cout<<"X"; //punct parcurs al arealului
            else if(A[i][j]==6)
                cout<<"_"; //pozitia de start a parcurgerii
            else
                cout<<"O"; //obstacol
        cout<<endl;
    }
}

void afisB(int A[101][101])
{
    int i,j;
    for(i=0; i<=100; i++)
    {

        for(j=0; j<=100; j++)
            if(A[i][j]==0)
                cout<<" ";
            else if(A[i][j]==1)
                cout<<"1";
            else if(A[i][j]==6)
                cout<<"S";
        cout<<endl;
    }
}

void generare(int areal[101][101])
{
    int x=0,y=0,i,j,ki,kj,complexitate,nrCL,szCL,nrn;
    double n;
    cout<<"Introduceti gradul de complexitate al obstacolelor [0,100]: ";
    cin>>n;
    cout<<endl;
    if(n<=25)
    {
        nrCL=rand()%15+1;
        szCL=3;
    }
    else if(n<=50)
    {
        nrCL=rand()%6+1;
        szCL=4;
    }
    else
    {
        nrCL=rand()%3+1;
        szCL=5;
    }
    complexitate=double(n/100)*98*98;
    for(i=0; i<=100; i++) //generare border
    {
        areal[i][0]=7;
        areal[0][i]=7;
        areal[i][100]=7;
        areal[100][i]=7;
    }

    for(i=0; i<complexitate; i++)
    {
        for(j=0; j<nrCL; j++)
        {
            while(areal[x][y]==7)
            {
                x=rand()%100+1;
                y=rand()%100+1;
            }
            areal[x][y]=7;
            i++;
            if(i==complexitate)
                break;
            for(ki=0; ki<szCL; ki++)
                for(kj=0; kj<szCL; kj++)
                    if(((x+ki)<100)&&((y+kj)<100))
                    {
                        areal[x+ki][y+kj]=7;
                        i++;
                        if(i==complexitate)
                            break;
                    }

        }
        nrn=0;
        while(areal[x][y]==7 && nrn<=2)
        {
            nrn=0;
            x=rand()%100+1;
            y=rand()%100+1;
            if(areal[x][y]==0)
            {
                if(areal[x][y-1]==7)
                    nrn++;
                if(areal[x][y+1]==7)
                    nrn++;
                if(areal[x-1][y]==7)
                    nrn++;
                if(areal[x+1][y]==7)
                    nrn++;
                if(areal[x-1][y-1]==7)
                    nrn++;
                if(areal[x-1][y+1]==7)
                    nrn++;
                if(areal[x+1][y-1]==7)
                    nrn++;
                if(areal[x+1][y+1]==7)
                    nrn++;
            }
        }
        areal[x][y]=7;
    }
}
void parcurgere(int areal[101][101],int ad[10201][10201], int botmap[101][101], int x, int y)
{
  int i,j;
  areal[x][y]=5;
  for(int i=0;i<101;i++)
    for(int j=0;j<101;j++)
    if(ad[x*y+y][i*j+j]==1 && areal[i][j]==0)
    {
      botmap[i][j]=1;
      parcurgere(areal,ad,botmap,i,j);
    }
}
