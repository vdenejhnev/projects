unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Grids, Spin;

type
  TMatrix = array of array of real; //Вводим тип для двумерного массива (матрицы)

  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    Label1: TLabel;
    StringGrid3: TStringGrid;
    Label3: TLabel;
    StringGrid2: TStringGrid;
    Label2: TLabel;
    BitBtn1: TBitBtn;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    StringGrid4: TStringGrid;
    StringGrid5: TStringGrid;
    StringGrid6: TStringGrid;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  A, B, C: TMatrix; //Создаем массивы

implementation

{$R *.dfm}

procedure input_arr(StringGrid: TStringGrid; rows, cols: integer; var matrix: TMatrix);  //Записываем из таблицы в массив
var
  i, j: integer;   //Счетчики для считывания в массив
begin
  setlength(matrix, rows, cols); //Задаем размер массива

  for i:=low(matrix) to high(matrix) do     //Цикл для считывания
    for j:=low(matrix[i]) to high(matrix[i]) do   //Цикл для считывания
      matrix[i, j]:=StrToFloat(StringGrid.Cells[j, i]); //Записываем в наш массив данные из каждой ячейки таблицы
end;

procedure change_max(matrix: TMatrix);  //Замена нашего максимального значения
var
  maxValue: real;  //Переменная для максимальног значения
  i, j: integer;  //Счетчики для прохождения по массиву
begin
  maxValue:=matrix[0,0];  //Устанавливаем первый элемент массива как максимальный

  for i:=low(matrix) to high(matrix) do  //Цикл для прохождения по массиву
    for j:=low(matrix[i]) to high(matrix[i]) do //Цикл для прохождения по массиву
      if matrix[i, j]>maxValue then  //Сравниваем текущий элемент с максимальным значением
        maxValue:=matrix[i, j];  //Если текущий элемент больше максимального значения, максимальному значению присваиваем текущий элемент

  for i:=low(matrix) to high(matrix) do  //Цикл для прохождения по массиву
    for j:=low(matrix[i]) to high(matrix[i]) do //Цикл для прохождения по массиву
      if matrix[i, j] = maxValue then //Если текущий элемент равен максимальному значению
        matrix[i, j]:=0; // Меняем его на ноль
end;

procedure output_arr(StringGrid: TStringGrid; matrix: TMatrix);  //Выводим результат
var
  i, j: integer; //Счетчики для прохождения по массиву
begin
  for i:=low(matrix) to high(matrix) do //Цикл для прохождения по массиву
    for j:=low(matrix[i]) to high(matrix[i]) do //Цикл для прохождения по массиву
      StringGrid.Cells[j, i]:=floatToStr(matrix[i, j]); //Выводим наш массив
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
  //Вызываем нужные процедуры
  input_arr(StringGrid1, 2, 2, A);
  input_arr(StringGrid2, 2, 3, B);
  input_arr(StringGrid3, 4, 3, C);
  change_max(A);
  change_max(B);
  change_max(C);
  output_arr(StringGrid4, A);
  output_arr(StringGrid6, B);
  output_arr(StringGrid5, C);
end;

end.
