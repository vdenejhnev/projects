unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Grids, Spin;

type
  TMatrix = array of array of real; //������ ��� ��� ���������� ������� (�������)

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
  A, B, C: TMatrix; //������� �������

implementation

{$R *.dfm}

procedure input_arr(StringGrid: TStringGrid; rows, cols: integer; var matrix: TMatrix);  //���������� �� ������� � ������
var
  i, j: integer;   //�������� ��� ���������� � ������
begin
  setlength(matrix, rows, cols); //������ ������ �������

  for i:=low(matrix) to high(matrix) do     //���� ��� ����������
    for j:=low(matrix[i]) to high(matrix[i]) do   //���� ��� ����������
      matrix[i, j]:=StrToFloat(StringGrid.Cells[j, i]); //���������� � ��� ������ ������ �� ������ ������ �������
end;

procedure change_max(matrix: TMatrix);  //������ ������ ������������� ��������
var
  maxValue: real;  //���������� ��� ������������ ��������
  i, j: integer;  //�������� ��� ����������� �� �������
begin
  maxValue:=matrix[0,0];  //������������� ������ ������� ������� ��� ������������

  for i:=low(matrix) to high(matrix) do  //���� ��� ����������� �� �������
    for j:=low(matrix[i]) to high(matrix[i]) do //���� ��� ����������� �� �������
      if matrix[i, j]>maxValue then  //���������� ������� ������� � ������������ ���������
        maxValue:=matrix[i, j];  //���� ������� ������� ������ ������������� ��������, ������������� �������� ����������� ������� �������

  for i:=low(matrix) to high(matrix) do  //���� ��� ����������� �� �������
    for j:=low(matrix[i]) to high(matrix[i]) do //���� ��� ����������� �� �������
      if matrix[i, j] = maxValue then //���� ������� ������� ����� ������������� ��������
        matrix[i, j]:=0; // ������ ��� �� ����
end;

procedure output_arr(StringGrid: TStringGrid; matrix: TMatrix);  //������� ���������
var
  i, j: integer; //�������� ��� ����������� �� �������
begin
  for i:=low(matrix) to high(matrix) do //���� ��� ����������� �� �������
    for j:=low(matrix[i]) to high(matrix[i]) do //���� ��� ����������� �� �������
      StringGrid.Cells[j, i]:=floatToStr(matrix[i, j]); //������� ��� ������
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
  //�������� ������ ���������
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
