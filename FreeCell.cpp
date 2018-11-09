#include<iostream>
#include<algorithm>
#include<time.h>
#include<fstream>
using namespace std;
/////////// Assisted code
void swap (int *a, int *b);
void randomize ( int arr[], int n );
//////////
bool check_valid_move(int *col, int src_1,int dest_2, int (&cont)[9], int num_of_cards);

int max_cards_in_column(int (&cont)[9]);
int update_tableau(int *element,int from,int to,int num,int &index);

char find_number_of_card(int num);
char find_symbol_of_card(int num);
void show_cards(int *col, int (&cont)[9]);

int main()
{
ifstream inFile;
inFile.open("save.txt");

if(inFile.fail())
{
cout<<"Input file opening fail !! \n";
exit(1);
}
    int random[]={0,1,2,3,4,5,6,7,8,9 ,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,-1,-1,-1};
        randomize (random, 52);  // randomly arrange the elements of an array
    int choice,movement,column_src,column_dest,num_cards,ind=52,cell_no,home_no;
     bool win=false;
        int *tableau=new int;
        tableau=&(*random);

    
    int tableau_counter[]={0,7,14,21,28,34,40,46,52};  // count no of cards in each column
        cout<<"\t\t********THIS IS FREE CELL GAME********\n\n";
        cout<<"Press 1 to start a game\n";
        cout<<"Press 2 to resume a game\n";
        cout<<"Enter choice : ";
        cin>>choice;
// Resuming the saved game
        if(choice==2)
        {
            for(int i=0;i<69;i++)
            {
                if(i<60){
                inFile>>tableau[i];}
                else{
                inFile>>tableau_counter[i-60];}
            }
        }


        cout<<endl<<endl;
        cout<<"\t\t********THIS IS FREE CELL GAME********\n\n";
        show_cards(tableau,tableau_counter);
 while(1){
     if(tableau[56]%13==12 && tableau[57]%13==12 && tableau[58]%13==12 && tableau[59]%13==12)
        {win=true;}
     if(win==true)
     {cout<<"\t\t************* GAME COMPLETED *************";break;}
        cout<<"Press 1 for column to column move\n";
        cout<<"Press 2 for column to free-cell move\n";
        cout<<"Press 3 for free-cell to column move\n";
        cout<<"Press 4 for column to home move\n";
        cout<<"Press 5 for free-cell to home move\n";
        cout<<"Press 6 to save your unfinished game\n";
        cout<<"Enter Your Choice : ";
        cin>>movement;
// Saving the GAME
     if(movement==6)
     {
ofstream outFile;
outFile.open("save.txt");

if(outFile.fail())
{
cout<<"Output file opening fail !! \n";
exit(1);
}
           for(int i=0;i<69;i++)
            {
                if(i<60){
                outFile<<tableau[i]<<" ";}
                else{
                outFile<<tableau_counter[i-60]<<" ";}
            }
            cout<<"\n\n********* GAME HAS BEEN SAVED **********\n\n";
break;
     }
     switch(movement)
{
    // CASE 1
case 1:
    cout<<"Enter column number as source : ";
    cin>>column_src;
    cout<<"Enter column number as destination : ";
    cin>>column_dest;
    cout<<"Enter the number of cards to be moved : ";
    cin>>num_cards;
   if(check_valid_move(tableau,column_src,column_dest,tableau_counter,num_cards))
   {
    if(column_src>column_dest){
    update_tableau(tableau,tableau_counter[column_src]-num_cards,tableau_counter[column_dest],num_cards,ind);
   }else if(column_dest>column_src)
   {
    update_tableau(tableau,tableau_counter[column_src]-num_cards,tableau_counter[column_dest]-num_cards,num_cards,ind);
   }

// CHANGE THE TABLEAU COUNTER ARRAy

   if(column_src>column_dest){
    tableau_counter[column_src-1]+=num_cards;

for(int i=0;i<(column_src-column_dest)-1;i++)
{    tableau_counter[column_dest+i]+=num_cards;}
}
    else{
for(int i=0;i<(column_dest-column_src);i++){
    tableau_counter[column_src+i]-=num_cards;}
    }
  }
    else{cout<<"\n\t\t*********  INVALID MOVE  **********\n\n";}
    break;
    // CASE 2
case 2:
    cout<<"Enter column number as source : ";
    cin>>column_src;
    cout<<"Enter number of Free Cell : ";
    cin>>cell_no;
    if(tableau[ind+cell_no-1]==-1){

    tableau[ind+cell_no-1]=tableau[tableau_counter[column_src]-1];

    update_tableau(tableau,tableau_counter[column_src]-1,ind-1+cell_no,1,ind);
    for(int i=column_src;i<=8;i++){
    tableau_counter[i]-=1;}
    }
    else{cout<<"\n\t\t*********  FREE CELL ALREADY FILLED  **********\n\n";}
break;
// CASE 3
case 3:
    cout<<"Enter number of Free Cell : ";
    cin>>cell_no;
    cout<<"Enter column number as destination : ";
    cin>>column_dest;
    if(tableau[ind+cell_no-1]!=-1){

    if(check_valid_move(tableau,0,column_dest,tableau_counter,cell_no)){
    update_tableau(tableau,ind-1+cell_no,tableau_counter[column_dest],1,ind);
    tableau[ind+cell_no-1]=-1;

    for(int i=column_dest;i<=8;i++){
    tableau_counter[i]+=1;}
    }
    else{cout<<"\n\t\t*********  INVALID MOVE  **********\n\n";}
    }
    else{cout<<"\n\t\t*********  SOURCE FREE CELL IS EMPTY  **********\n\n";}
break;

 // CASE 4
case 4:
    cout<<"Enter column number as source : ";
    cin>>column_src;
    cout<<"Enter Home Number : ";
    cin>>home_no;
    if(tableau[56+home_no-1]==-1 && tableau[tableau_counter[column_src]-1]%13==0)
        {
     tableau[56+home_no-1]=tableau[tableau_counter[column_src]-1];
     update_tableau(tableau,tableau_counter[column_src]-1,55+home_no,1,ind);
    for(int i=column_src;i<=8;i++){
    tableau_counter[i]-=1;}
    }
     else if(tableau[56+home_no-1]!=-1)
        {
        if(tableau[56+home_no-1]==tableau[tableau_counter[column_src]-1]%13)
        {
     update_tableau(tableau,tableau_counter[column_src]-1,55+home_no,1,ind);
     tableau[56+home_no-1]++;
          for(int i=column_src;i<=8;i++){
    tableau_counter[i]-=1;}
    }
        }

    else{cout<<"\n\t\t*********  INVALID MOVE  **********\n\n";}
break;
 // CASE 5
case 5:
    cout<<"Enter Home Number as source : ";
    cin>>home_no;
    cout<<"Enter column number as destination : ";
    cin>>column_dest;
if((tableau[56+home_no-1]+1)%13!=0){

    if(check_valid_move(tableau,9,column_dest,tableau_counter,home_no)){
    update_tableau(tableau,55+home_no,tableau_counter[column_dest],1,ind);
    tableau[56+home_no-1]--;

    for(int i=column_dest;i<=8;i++){
    tableau_counter[i]+=1;}
    }
    else{cout<<"\n\t\t*********  INVALID MOVE  **********\n\n";}
    }
    else{cout<<"\n\t\t*********  SOURCE HOME CELL IS EMPTY  **********\n\n";}
    break;
default:
    cout<<"ERROR...Enter valid value !!!!\n\n";
    break;
}
     cout<<endl<<endl;
     cout<<"\t\t********THIS IS FREE CELL GAME********\n\n";
     show_cards(tableau,tableau_counter);
}
return 0;
}
//////////////////////////////////////////////////////////////////////////////
//#################################  ARRANDE RANDOM CARDS ##########################
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void randomize ( int arr[], int n )
{
    srand ( time(NULL) );

    for (int i = n-1; i > 0; i--)
    {
       int j = rand() % (i+1);
       swap(&arr[i], &arr[j]);
    }
}
//////////////////////////////////////////////////////////////////////////////
//#################################  CHECK WHETHER THE MOVE OF CARDS IS VALID OR NOT ##########################
bool check_valid_move(int *col, int src_1,int dest_2, int (&cont)[9], int num_of_cards)
{
int index_src;
//  0 shows that the card is from free cell
if(src_1==0)
{index_src=51+num_of_cards;
num_of_cards=1;}
else if(src_1==9)
{index_src=55+num_of_cards;
num_of_cards=1;}
else
{index_src=cont[src_1]-1;}
int index_dest=cont[dest_2]-1;
// Check source column cards, whether they are alternative or not
for(int i=0;i<(num_of_cards-1);i++)
{
    if(col[index_src-(i)]%13!=(col[index_src-(i+1)]%13)-1)
    {
        return false;
    }
    if((col[index_src-(i)]/13)%2!=((col[index_src-(i+1)]/13)%2+1)%2)
    {
        return false;
    }
}
// Check whether source column cards matches with the destination card or not.
if(col[index_src-(num_of_cards-1)]%13!=col[index_dest]%13-1)
{
    return false;
}
if((col[index_src-(num_of_cards-1)]/13)%2!=(((col[index_dest]/13)%2)+1)%2)
{
    return false;
}
return true;
}
//////////////////////////////////////////////////////////////////////////////
//#################################  SHOW CARDS FUNCTION   ##########################
char find_number_of_card(int num)
{
         char num_symbol;
         switch(num)
          {
          case 0:
            num_symbol='A';
            break;
          case 10:
            num_symbol='J';
            break;
          case 11:
            num_symbol='Q';
            break;
          case 12:
            num_symbol='K';
            break;
          }
return num_symbol;}

char find_symbol_of_card(int num)
{
    char symbol;
    switch(num)
         {
         case 0:
            symbol='c';
            break;
         case 1:
            symbol='d';
            break;
         case 2:
            symbol='s';
            break;
         case 3:
            symbol='h';
            break;
         }
return symbol;}

void show_cards(int *col, int (&cont)[9])
{
    char symbol,num_symbol;
    int number,t_=0,t__=0;
    int  max_=max_cards_in_column(cont);

    for(int i=52;i<56;i++)
    {
        number=col[i]%13;
        num_symbol=find_number_of_card(number);
        symbol=find_symbol_of_card(col[i]/13);
        if(col[i]!=-1)
        {
     if(number==0 || number>9)
      {cout<<"|"<<num_symbol<<symbol<<"|\t";}
    else
      {cout<<"|"<<number+1<<symbol<<"|\t";}
        }
        else
        {
            cout<<"|  |\t";
        }
    }

        for(int i=56;i<60;i++)
    {
        number=col[i]%13;
        num_symbol=find_number_of_card(number);
        symbol=find_symbol_of_card(col[i]/13);
     if((col[i]+1)%13!=0)
        {
     if(number==0 || number>9)
      {cout<<"|"<<num_symbol<<symbol<<"|\t";}
    else
      {cout<<"|"<<number<<symbol<<"|\t";}
        }
        else
        {
            cout<<"|  |\t";
        }
    }

    cout<<"\n\n";
    for(int i=0;i<(8*max_);i++)
    {
        // Go to new line
      if(i%8==0 && i>0)
      {
          cout<<"\n\n";
          t_=0;
          t__++;
      }

    // find number of the card
    int hh=cont[t_]+t__;
         number=col[cont[t_]+t__]%13;
          num_symbol=find_number_of_card(number);
      // Find type of card
        symbol=find_symbol_of_card(col[cont[t_]+t__]/13);
      // print cards
    if(t__>(cont[t_+1]-cont[t_]-1))
        {cout<<"   \t";}
    else if(number==0 || number>9)
      {cout<<"|"<<num_symbol<<symbol<<"|\t";}
    else
      {cout<<"|"<<number+1<<symbol<<"|\t";}
    t_++;
    }
    cout<<"\n\n";
}
//////////////////////////////////////////////////////////////////////////////
//#################################  UPDATE THE TABLEAU ARRAY  ##########################
int max_cards_in_column(int (&cont)[9])
{
int max_=cont[2]-cont[1];
for(int i=0;i<7;i++)
{
    if((cont[i+1]-cont[i]>cont[i+2]-cont[i+1])&&(cont[i+1]-cont[i]>max_))
    {
        max_=cont[i+1]-cont[i];
    }
}
return max_;
}

int update_tableau(int *element,int from,int to,int num,int &index)
{
        int temp1[num],temp2[52],temp3[4],temp4[4];//temp2[index-to+num];

int v_temp4=0;
for(int i=56;i<60;i++)
{
    temp4[v_temp4]=element[i];
v_temp4++;
}

int v_temp3=0;
for(int i=index;i<56;i++)
{
    temp3[v_temp3]=element[i];
v_temp3++;
}

// storing elements to move in temp array
int v_temp1=0;
for(int i=from;i<from+num;i++)
{
    temp1[v_temp1]=element[i];
v_temp1++;
}

// storing elements having index greater than the elements are being shift
int v_temp2=0;

if(from<to){
for(int i=to+num;i<index;i++)
{
    temp2[v_temp2]=element[i];
v_temp2++;
}}else if(from>to){
for(int i=from+num;i<index;i++)
{
    temp2[v_temp2]=element[i];
v_temp2++;
}}

// shifting  CONDITIONS
if(from<to){
for(int i=from;i<to;i++)
{
    element[i]=element[i+num];
}}else if(from>to){
for(int i=from;i>=to;i--)
{
    element[i+num]=element[i];
}}


// move to destination
int v_temp1_agn=0;
for(int i=to;i<to+num;i++)
{
    element[i]=temp1[v_temp1_agn];
v_temp1_agn++;
}

// join temp2
int v_temp2_agn=0;
if(from<to){

for(int i=to+num;i<index;i++)
{
    element[i]=temp2[v_temp2_agn];
v_temp2_agn++;
}}else if(from>to){
for(int i=from+num;i<index;i++)
{
    element[i]=temp2[v_temp2_agn];
v_temp2_agn++;
}}

int v_temp3_agn=0;
for(int i=index;i<56;i++)
{
    element[i]=temp3[v_temp3_agn];
v_temp3_agn++;
}


int v_temp4_agn=0;
for(int i=56;i<60;i++)
{
    element[i]=temp4[v_temp4_agn];
v_temp4_agn++;
}
}
//#################################  Completed   ##########################
