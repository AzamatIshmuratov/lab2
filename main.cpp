#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void simple(char *name){
  int a1, a2, k, i, j, kol, tmp;
  FILE *f, *f1, *f2;
  kol = 0;
  if ( (f = fopen(name,"r")) == NULL )
    printf("\nИсходный файл не может быть прочитан...");
  else {
    while ( !feof(f) ) {
      fscanf(f,"%d",&a1);
      kol++;
    }
    fclose(f);
  }
  k = 1;
  while ( k < kol ){
    f = fopen(name,"r");
    f1 = fopen("smsort_1","w");
    f2 = fopen("smsort_2","w");
    if ( !feof(f) ) fscanf(f,"%d",&a1);
    while ( !feof(f) ){
      for ( i = 0; i < k && !feof(f) ; i++ ){
        fprintf(f1,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
      for ( j = 0; j < k && !feof(f) ; j++ ){
        fprintf(f2,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
    }
    fclose(f2);
    fclose(f1);
    fclose(f);

    f = fopen(name,"w");
    f1 = fopen("smsort_1","r");
    f2 = fopen("smsort_2","r");
    if ( !feof(f1) ) fscanf(f1,"%d",&a1);
    if ( !feof(f2) ) fscanf(f2,"%d",&a2);
    while ( !feof(f1) && !feof(f2) ){
      i = 0;
      j = 0;
      while ( i < k && j < k && !feof(f1) && !feof(f2) ) {
        if ( a1 < a2 ) {
          fprintf(f,"%d ",a1);
          fscanf(f1,"%d",&a1);
          i++;
        }
        else {
          fprintf(f,"%d ",a2);
          fscanf(f2,"%d",&a2);
          j++;
        }
      }
      while ( i < k && !feof(f1) ) {
        fprintf(f,"%d ",a1);
        fscanf(f1,"%d",&a1);
        i++;
      }
      while ( j < k && !feof(f2) ) {
        fprintf(f,"%d ",a2);
        fscanf(f2,"%d",&a2);
        j++;
      }
    }
    while ( !feof(f1) ) {
      fprintf(f,"%d ",a1);
      fscanf(f1,"%d",&a1);
    }
    while ( !feof(f2) ) {
      fprintf(f,"%d ",a2);
      fscanf(f2,"%d",&a2);
    }
    fclose(f2);
    fclose(f1);
    fclose(f);
    k *= 2;
  }
  remove("smsort_1");
  remove("smsort_2");
  cout <<"\nСортировка выполнена успешно!\n";
}

//собственная сортировка
int sort_sobstv()
{
    int k=0,a_kol,kol=0,i,schet;
    int a,b,c,d;
    ifstream f1;
    f1.open("input.txt");
    while(!f1.eof()){
       f1>>a_kol;
       kol++;
    }
    f1.close();

    label1:
    i=0;
    ofstream f2;
    f1.open("input.txt");
    f2.open("vrem.txt");
    f1>>a;
    while (i<kol){
        f1>>b;
        if (a<=b){
            f2<<a<<" ";
            a=b;
            i++;
        }
        else{
            f2<<b<<" "<<a<<" ";
            i=i+2;
            while (i<kol){
                f1>>c;
                f2<<c<<" ";
                i++;
            }
            f1.close(); remove("input.txt");
            f2.close();
            ofstream f3; ifstream f4;
            f3.open("input.txt"); f4.open("vrem.txt");
            schet=0;
            while (schet<kol){
                f4>>d;
                f3<<d<<" ";
                schet++;
            }
            f3.close(); f4.close(); remove("vrem.txt");
            goto label1;
        }
    }
    f1.close(); f2.close(); remove("vrem.txt");
    cout <<"\nСортировка выполнена успешно!\n";
    return 0;
}

int main(){
  setlocale(LC_ALL,"rus");
  int choice;
  cout << "1. Прямое слияние\n2. Собственная сортировка\n";
  cin>>choice;

  switch (choice){
	case 1: simple("input.txt"); break;
	case 2: sort_sobstv(); break;
  }
  return 0;
}
