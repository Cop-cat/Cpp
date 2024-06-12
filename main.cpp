#include <iostream>

using namespace std;
const int Size = 10;

void MakeUnVoid(char arr[][Size]){//Заполняет поля символом "_"
  for(int i = 0;i < Size;i++){
    for(int j = 0;j < Size;j++){
      arr[i][j] = '_';
      }
  }
}

void OutputPField(char arr[][Size]){//Вывод игрового поля(массива)
  char a = 'A';
  cout << " ";
  for(int i = 0, b = 0;i < Size;i++, b++){
    for(int k = 0;i == 0 && k < 10;k++, a++){
      cout << a << " ";
      if(k == 9)cout << endl;
    }
    for(int j = 0;j < Size;j++){
      if(j == 0)cout << b;
      cout << arr[i][j] << " ";
    }cout << endl; 
  }
}

void OutputNotFullField(char arr[][Size]){//Вывод игрового поля но без показания где находятся корабли
  char a = 'A';
  cout << " ";
  for(int i = 0, b = 0;i < Size;i++, b++){
    for(int k = 0;i == 0 && k < 10;k++, a++){
      cout << a << " ";
      if(k == 9)cout << endl;
    }
    for(int j = 0;j < Size;j++){
      if(j == 0)cout << b;
      if(arr[i][j] == 'D')cout << '_' << " ";
      else cout << arr[i][j] << " ";
    }cout << endl; 
  }
}

void InputShips(char arr[][Size]){//Вставляем корабли
  char a, c;
  int b, d;
  cout << "Если корабль однопалубный, то мы просто вводим координаты.\n";
  cout << "Но если он двухпалубный и больше, то надо задавать сначала начальную координату, а потом конечную.\n";
  cout << "Учтите, что корабли могут располагаться строго вертикально, или горизонатльно!\n";
  cout << "И ещё - при вводе Вы сначала вводите (латинскую ЗАГЛАВНУЮ) букву,нажимаете ENTER, затем только цифру, по-отдельности!\n";
  OutputPField(arr);
  for(int i = 0;i < 4;i++){//Цикл однопалубных кораблей
    cout << "Input " << i+1 << " oneboard ship(letter): ";
    do cin >> a;
    while (a < 'A' || a > 'J');
    cout << "Number: ";
    do cin >> b;
    while (b < 0 || b > 9);
    arr[b][a-65] = 'D';//Я от char отнимаю 65, потому что у символа А код 65
    OutputPField(arr);
  }
  for(int i = 0;i < 3;i++){//Цикл двухпалубных кораблей
    cout << "Input " << i+1 << " twoboard ship(letter 1): ";
    do cin >> a;
    while (a < 'A' || a > 'J');

    cout << "Number 1: ";
    do cin >> b;
    //Вторая координата
    while (b < 0 || b > 9);

    cout << "Input " << i+1 << " twoboard ship(letter 2): ";
    do cin >> c;
    while (!(c == a+1 || c == a-1 || c == a));
        
    if(a != c){
      d = b;
    }else {
      cout << "Number 2: ";
      do cin >> d;
      while (!(d == b+1 || d == b-1));
    }                      
      arr[b][a-65] = 'D';
      arr[d][c-65] = 'D';
      OutputPField(arr);
    }
    for(int i = 0;i < 2;i++){//Цикл трёхпалубных кораблей
      cout << "Input " << i+1 << " threeboard ship(letter 1): ";
      do cin >> a;
      while (a < 'A' || a > 'J');

      cout << "Number 1: ";
      do cin >> b;
      //Вторая координата
      while (b < 0 || b > 9);

      cout << "Input " << i+1 << " threeboard ship(letter 2): ";
      do cin >> c;
      while (!(c == a+2 || c == a-2 || a == c));

      if(a != c){
        d = b;   
      }else {
        cout << "Number 2: ";
        do cin >> d;                            
        while (!(d == b+2 || d == b-2));
      }

      arr[b][a-65] = 'D';
      arr[(b+d)/2][(a-65+c-65)/2] = 'D';
      arr[d][c-65] = 'D';
      OutputPField(arr);   
    }
    cout << "Input fourboard ship(letter 1): ";//Четырёхпалубный корабль
    do cin >> a;
    while (a < 'A' || a > 'J');

    cout << "Number 1: ";
    do cin >> b;
    //Вторая координата
    while (b < 0 || b > 9);

    cout << "Input fourboard ship(letter 2): ";
    do cin >> c;
    while (!(c == a+3 || c == a-3 || a == c));

    if(a != c){
      d = b;   
    }else {
      cout << "Number 2: ";
      do cin >> d;                            
      while (!(d == b+3 || d == b-3));
    }

    arr[b][a-65] = 'D';
    arr[(b+d)/2][(a-65+c-65)/2] = 'D';
    arr[(b+1+d)/2][(a+1-65+c-65)/2] = 'D';
    arr[d][c-65] = 'D';
    OutputPField(arr);
}

bool IsEnd(bool isEnd, char arr[][Size]){
  for(int i = 0;i < Size;i++){
    for(int j = 0;j < Size;j++){
      if(arr[i][j] == 'D')return false;
    }
  }
  return true;
}

void Fight(char arr1[][Size], char arr2[][Size]){
  bool isEnd = false;
  char a;
  int b;
  int p = 1;
  while(!isEnd){
    if(!isEnd && p == 3)p = 1;
    cout << "Player " << p << ", attack the enemy's ships!\n";
    OutputNotFullField((p == 1 ? arr2 : arr1));
    cout << "Input 1st coordinate(letter): ";
    do cin >> a;
    while (a < 'A' || a > 'J');
    cout << "Input 2nd coordinate(number): ";
    do cin >> b;
    while (b < 0 || b > 9);
    if(p == 1){
      if(arr2[b][a-65] == '_'){
        p++;
        arr2[b][a-65] = 'o';
      }
      else arr2[b][a-65] = 'x';
      OutputNotFullField(arr2);
      isEnd = IsEnd(isEnd, arr2);        
    }else{
      if(arr1[b][a-65] == '_'){
        p++;
        arr1[b][a-65] = 'o';               
      }
      else arr1[b][a-65] = 'x';
      OutputNotFullField(arr1);
      isEnd = IsEnd(isEnd, arr1);
    }
  }   
  cout << "Player " << p << " won! Mine congratulations!\n";
}

int main(){
  cout << "This is battleship. Begin!\n";
  char Player1[Size][Size];
  char Player2[Size][Size];
  MakeUnVoid(Player1);
  MakeUnVoid(Player2);
  cout << "!!!FIRST PLAYER!!!\n";
  //Player1[0][0] = 'D';
  InputShips(Player1);
  cout << "!!!SECOND PLAYER!!!\n";
  //Player2[0][0] = 'D';
  //OutputPField(Player2);
  InputShips(Player2);
  cout << "Remember, if you miss, it' only your fault.\n";
  Fight(Player1, Player2);
  cout << "End program " << endl;
  return 0;
}