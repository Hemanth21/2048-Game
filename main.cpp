#include "iostream"
#include "algorithm"
#include "fstream"
#include "cstdlib"
#include "cmath"
#include "ctime"
#include "iomanip"

using namespace std;

int a[4][4]={0};
int maxvalue=0;
int score=0,p;
int highscore=0;
int maxtile=0;
string pname;
int main();

struct leader{
  string name;
  int maxscore;
  int maxtilee;
};

int leaderboard(){
    struct leader a[1000];
    ifstream fp;
    int i=0,j;
    fp.open("leaderboard.dat");
    while(!fp.eof()){
      fp >> a[i].maxscore;
      fp >> a[i].maxtilee;
      fp >> a[i].name;
      if(fp.eof())break;
      i++;
    }
    struct leader temp;
    for( j=0;j<=i;j++){
      for(int p=j+1;p<i;p++){
        if(a[j].maxscore<a[p].maxscore){
          temp=a[j];
          a[j]=a[p];
          a[p]=temp;
        }
      }
    }
    j=0;
    highscore=a[0].maxscore;
    cout << setw(18) << "Name    " << setw(7) << "MaxTile    " << setw(7) << "Max Score" << "\n\n";
   while(j<i){
     cout << j+1 << ". ";
     cout << setw(12) << a[j].name << " ";
     cout << setw(7) << a[j].maxtilee << "    ";
     cout << setw(7) << a[j].maxscore << " ";
     cout << "\n\n";
     j++;
   }
   fp.close();
   return 0;
}

int check(){
  int i,j,flag=0,flag1=0;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      if(a[i][j]==0){
         flag=1;
         break;
       }
     }
  if(flag)
     break;
  }
  for(i=0;i<4;i++){
    for(j=0;j<3;j++){
      if(a[i][j]==a[i][j+1] || a[j][i]==a[j+1][i]){
        flag1=1;
        break;
      }
    }
    if(flag1)
       break;
  }
  return (flag || flag1);
}

int sink(){
  int i,j;
  ofstream fp;
  fp.open("gdata.dat",ios::trunc);
  fp << score << " ";
  fp << pname << "\n";
  for(i=0;i<4;i++){
    for(j=0;j<4;j++)
      fp << a[i][j] << "      ";
    fp << "\n";
  }
  fp.close();
  return 0;
}

int generate(int n){
  int i,j,k;
  srand(time(NULL));
  for(k=0;k<n;k++){
  i=rand()%4;
  j=rand()%4;
  if(a[i][j]==0)
     a[i][j]=((double) rand() / (RAND_MAX))>=0.9?4:2;
  else
     k--;
  }
  return 0;
}

int display(){
  int i,j;
  cout << "                                " <<"\t\t\t";
  if(score>=highscore && score!=0)cout << "Congratulations You have made a HighScore!" ;
  cout << "\n";
  cout << "________________________________" <<"\t\t\t" << "socre:"<<score <<"\n";
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      if(a[i][j]!=0){
        cout <<setw(7)<<a[i][j];
      }else
        cout << setw(7) << "  ";
      cout << "|";
  }
  cout << " \n";
  cout << "________________________________"<< "\n";
  }
  return 0;
}

int TopDown(int s,int e,int k){
  int i,j,flag=0,co=0;
  while(co++<=1)
  for(i=0;i<=3;i++)
     for(j=s;(e==0)?(j>=e):(j<=e);j=j-k)
       if(a[j][i]==0 && a[j+k][i]!=0){
          a[j][i]=a[j+k][i];
          a[j+k][i]=0;
          flag=1;
       }
   for(i=0;i<=3;i++)
    for(j=s;(e==0)?(j>=e):(j<=e);j=j-k)
      if(a[j][i]==a[j+k][i] && a[j][i]!=0){
          a[j][i]+=a[j+k][i];
          a[j+k][i]=0;
          flag=2;
          j=j-k;
       }
co=0;
    while(co++<=1)
      for(i=0;i<=3;i++)
         for(j=s;(e==0)?(j>=e):(j<=e);j=j-k)
           if(a[j][i]==0 && a[j+k][i]!=0){
              a[j][i]=a[j+k][i];
              a[j+k][i]=0;
              flag=1;
           }
    if(flag==1 || flag==2){
      generate(1);
      score=score+p;
    }
  return 0;
}

int RightLeft(int s,int e,int k){
  int i,j,flag=0,co=0;
  while(co++<=1)
   for(i=0;i<=3;i++)
    for(j=s;(e==0)?j>=e:j<=e;j=j-k)
      if(a[i][j]==0 && a[i][j+k]!=0){
        a[i][j]=a[i][j+k];
        a[i][j+k]=0;
        flag=1;
      }
  for(i=0;i<=3;i++)
    for(j=s;(e==0)?j>=e:j<=e;j=j-k)
      if(a[i][j]==a[i][j+k] && a[i][j]!=0){
        a[i][j]+=a[i][j+k];
        a[i][j+k]=0;
        flag=2;
        j=j-k;
      }
 co=0;
  while(co++<=1)
   for(i=0;i<=3;i++)
     for(j=s;(e==0)?j>=e:j<=e;j=j-k)
      if(a[i][j]==0 && a[i][j+k]!=0){
        a[i][j]=a[i][j+k];
        a[i][j+k]=0;
        flag=1;
        }
  if(flag==1 || flag==2){
    generate(1);
    score=score+p;
  }
  return 0;
}

int Restart(){
  int i,j;
  cout << "Enter Your Name:";
  cin >> pname;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      a[i][j]=0;
  score=0;
  maxvalue=0;
  highscore=0;
  generate(2);
  return 0;
}

int Maxtile(){
  int i,j,Max=0;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      Max=max(Max,a[i][j]);
  return Max;
}

int Addtoleaderboard(){
  ofstream fp;
  fp.open("leaderboard.dat",ios::app);
  int max=Maxtile();
  fp << score << " ";
  fp << max << " ";
  fp << pname << " " << "\n";
  fp.close();
  return 0;
}

int playgame(){
  int i,j;
  int n;
  while(check()){
    leaderboard();
    system("cls");
    display();
    cout << "\n" << "********************* Welcome to the Game ********************* " << "\n\n";
    cout << "8.Move The Board Top." << "\n";
    cout << "6.Move The Board Right." << "\n";
    cout << "2.Move The Board Down." << "\n";
    cout << "4.Move The Board Left." << "\n";
    cout << "1.Restart." << "\n";
    cout << "0.Exit."  <<"\n\n";
    cout << "Enter Your Choice:";
    cin >> n;
    cout << "\n";
  switch(n){
    case 8:TopDown(2,0,1);
           break;
    case 6:RightLeft(1,3,-1);
           break;
    case 2:TopDown(1,3,-1);
           break;
    case 4:RightLeft(2,0,1);
           break;
    case 1:Restart();
           playgame();
           break;
    case 0:sink();
           main();
           break;
    default:cout << "Kindly Select the valid option." << "\n";
  }
  p=Maxtile();
  }
  system("cls");
  display();
  cout << "\n" <<"Game Over!" << "\n";
  Addtoleaderboard();
  score=0;
  maxvalue=0;
  highscore=0;
  system("Pause");
  main();
  return 0;
}

int grab(){
  int i,j,x;
  ifstream fp;
  fp.open("gdata.dat");
  if(fp){
    fp >> score;
    fp >> pname;
    while(!fp.eof()){
      for(i=0;i<4;i++){
        for(j=0;j<4;j++){
          fp >> x;
          if(fp.eof())break;
          a[i][j]=x;
        }
      }
    }
  }
  playgame();
  fp.close();
  return 0;
}

int main(){
  int n;
  while(1){
    system("cls");
    cout << "\n" << "********************* Welcome to the Game ********************* " << "\n\n";
    cout << "1.Start New Game" << "\n";
    cout << "2.Resume Game" << "\n";
    cout << "3.Leader Board" << "\n";
    cout << "4.Exit" << "\n\n";
    cout << "Enter Your Choice:";
    cin >> n;
    cout << "\n";
  switch(n){
    case 1:cout << "Enter Your Name:" ;
           cin >> pname;
           generate(2);
           playgame();
           break;
    case 2:grab();
           break;
    case 3:leaderboard();
           break;
    case 4:exit(0);
           break;
    default:cout << "Kindly Select the valid option." << "\n";
  }
  cout << "\n";
  system("pause");
  }
  return 0;
}
