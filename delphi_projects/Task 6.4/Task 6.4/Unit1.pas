unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin, Grids, Buttons;

type
  TStud = Record
    F,Im: String[15];
    G: Integer;
    B: String[1];
  end;

  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    SpinEdit1: TSpinEdit;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    BitBtn4: TBitBtn;
    BitBtn5: TBitBtn;
    BitBtn6: TBitBtn;
    BitBtn7: TBitBtn;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure SpinEdit1Change(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn7Click(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
    procedure BitBtn6Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  Fdat: File of TStud;

implementation

{$R *.dfm}

procedure LoadFile(table: TStringGrid; ext: string);
var
  A: TStud;
  i: integer;
begin
  with Form1.OpenDialog1 do
  begin
    if(ext = 'dat') then
      filter:='Исходные данные '
    else
      filter:='Данные результата ';

    filter:=filter+'('+ ext +')|*.'+ ext +'|Все файлы|*.*';

    if execute then
    begin
      assignFile(Fdat, fileName);
      reset(Fdat);
      i:=1;

      while not EOF(Fdat) do
      begin
        read(Fdat, A);

        with table do
        begin
          Cells[0,i]:=A.F;
          Cells[1,i]:=A.Im;
          Cells[2,i]:=IntToStr(A.G);
          Cells[3,i]:=A.B;
          inc(i);
        end;
      end;
    end;
  end;
end;

procedure SaveFile(table: TStringGrid; ext: string);
var
  A: TStud;
  i: integer;
begin
  with Form1.SaveDialog1 do
  begin
    if(ext = 'dat') then
      filter:='Исходные данные '
    else
      filter:='Данные результата ';

    filter:=filter+'('+ ext +')|*.'+ ext +'|Все файлы|*.*';
    defaultExt:=ext;

    if execute then
    begin
      assignFile(Fdat, fileName);
      rewrite(Fdat);

      with table do
      begin
        for i:=1 to rowCount-1 do
        begin
          A.F:=Cells[0,i];
          A.Im:=Cells[1,i];
          A.G:=strToInt(Cells[2,i]);
          A.B:=Cells[3,i];
          write(Fdat, A);
        end;
        closeFile(Fdat);
      end;
    end;
  end;
end;

procedure ClearTable(Table:TStringGrid);
var
  i:Integer;
Begin
  With Table Do
  Begin
    For i:=FixedRows To RowCount - 1 Do
      Rows[i].Clear;
    RowCount:=2;
  End;
End;

procedure TForm1.SpinEdit1Change(Sender: TObject);
begin
  StringGrid1.RowCount:=SpinEdit1.Value+1;
  StringGrid2.RowCount:=SpinEdit1.Value+1;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
var
  A: TStud;
  i, j: Integer;
  x: String;
begin
  LoadFile(StringGrid1, 'dat');
  StringGrid1.RowCount:=FileSize(Fdat)+1;
  SpinEdit1.Value:=FileSize(Fdat);
  seek(Fdat, 0);
  i:=1;

  while not EoF(Fdat) do
  begin
    read(Fdat, A);
    with A do
    begin
      StringGrid2.Cells[0,i]:=F;
      StringGrid2.Cells[1,i]:=Im;
      StringGrid2.Cells[2,i]:=intToStr(G);
      StringGrid2.Cells[3,i]:=B;

      for j:=i downto 2 do
      begin
        if StringGrid2.Cells[2,j] < StringGrid2.Cells[2,j-1] then
        begin
          x:=StringGrid2.Cells[0,j];
          StringGrid2.Cells[0,j]:=StringGrid2.Cells[0,j-1];
          StringGrid2.Cells[0,j-1]:=x;
          x:=StringGrid2.Cells[1,j];
          StringGrid2.Cells[1,j]:=StringGrid2.Cells[1,j-1];
          StringGrid2.Cells[1,j-1]:=x;
          x:=StringGrid2.Cells[2,j];
          StringGrid2.Cells[2,j]:=StringGrid2.Cells[2,j-1];
          StringGrid2.Cells[2,j-1]:=x;
          x:=StringGrid2.Cells[3,j];
          StringGrid2.Cells[3,j]:=StringGrid2.Cells[3,j-1];
          StringGrid2.Cells[3,j-1]:=x;
        end
        else if StringGrid2.Cells[2,j] = StringGrid2.Cells[2,j-1] then
        begin
          if StringGrid2.Cells[3,j] < StringGrid2.Cells[3,j-1] then
          begin
            x:=StringGrid2.Cells[0,j];
            StringGrid2.Cells[0,j]:=StringGrid2.Cells[0,j-1];
            StringGrid2.Cells[0,j-1]:=x;
            x:=StringGrid2.Cells[1,j];
            StringGrid2.Cells[1,j]:=StringGrid2.Cells[1,j-1];
            StringGrid2.Cells[1,j-1]:=x;
            x:=StringGrid2.Cells[2,j];
            StringGrid2.Cells[2,j]:=StringGrid2.Cells[2,j-1];
            StringGrid2.Cells[2,j-1]:=x;
            x:=StringGrid2.Cells[3,j];
            StringGrid2.Cells[3,j]:=StringGrid2.Cells[3,j-1];
            StringGrid2.Cells[3,j-1]:=x;
          end
          else
            break;
        end
        else
          break;
      end;
      inc(i);
    end;
  end;
  CloseFile(Fdat);
  SaveFile(StringGrid2, 'res');
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  StringGrid1.Cells[0,0]:='Фамилия';
  StringGrid1.Cells[1,0]:='Имя';
  StringGrid1.Cells[2,0]:='Год';
  StringGrid1.Cells[3,0]:='Буква';
  StringGrid1.Cells[4,0]:='Информатика';
  StringGrid1.Cells[5,0]:='Алгебра';
  StringGrid1.Cells[6,0]:='Русский язык';
  StringGrid1.Cells[7,0]:='История';
end;

procedure TForm1.BitBtn2Click(Sender: TObject);
begin
  SaveFile(StringGrid1, 'dat');
end;

procedure TForm1.BitBtn7Click(Sender: TObject);
begin
  LoadFile(StringGrid1, 'dat');
  StringGrid1.RowCount:=FileSize(Fdat)+1;
  SpinEdit1.Value:=FileSize(Fdat);
  closeFile(Fdat);
end;

procedure TForm1.BitBtn3Click(Sender: TObject);
begin
  ClearTable(StringGrid1);
end;

procedure TForm1.BitBtn4Click(Sender: TObject);
begin
  SaveFile(StringGrid2, 'res');
end;

procedure TForm1.BitBtn5Click(Sender: TObject);
begin
  LoadFile(StringGrid2, 'res');
  StringGrid2.RowCount:=FileSize(Fdat)+1;
  closeFile(Fdat);
end;

procedure TForm1.BitBtn6Click(Sender: TObject);
begin
  ClearTable(StringGrid2);
end;

end.
