unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Grids, Spin;

type
  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    Label1: TLabel;
    Label3: TLabel;
    Label2: TLabel;
    BitBtn1: TBitBtn;
    Edit2: TEdit;
    Label9: TLabel;
    StringGrid2: TStringGrid;
    StringGrid3: TStringGrid;
    Label4: TLabel;
    StringGrid4: TStringGrid;
    Label5: TLabel;
    Edit1: TEdit;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  A, B: array [0..4] of real;
  C, D: array [0..7] of real;

implementation

{$R *.dfm}

procedure inputArray(var arr1, arr2: array of real; vec1, vec2: TStringGrid);
var
  i: integer;
begin
  for i:=low(arr1) to high(arr1) do
  begin
    arr1[i]:=StrToFloat(vec1.Cells[i, 0]);
    arr2[i]:=StrToFloat(vec2.Cells[i, 0]);
  end;
end;

function vectorsProduct(arr1, arr2: array of real): real;
var
  composition: real;
  i: integer;
begin
  composition:=0;

  for i:=low(arr1) to high(arr1) do
    composition:=composition+arr1[i]*arr2[i];

  result:=composition;
end;

procedure outputResult(product: real; Edit: TEdit);
begin
  Edit.Text:=floatToStr(product);
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
var
  resAB, resCD: real;
begin
  inputArray(A, B, StringGrid1, StringGrid2);
  inputArray(C, D, StringGrid3, StringGrid4);
  resAB:=vectorsProduct(A, B);
  resCD:=vectorsProduct(C, D);
  outputResult(resAB, Edit1);
  outputResult(resCD, Edit2);
end;

end.
