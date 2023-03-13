unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, Buttons;

type
  TStudent = class
    public
      s_name: string;
      s_surname: string;
      s_year: Integer;
      s_class_letter: string;
      s_algebra_rating: Integer;
      s_informatics_rating: Integer;
      s_russian_rating: Integer;
      s_history_rating: Integer;

      //constructor Create(name: string);

      constructor Create( name: string;
                          surname: string;
                          year: Integer;
                          class_letter: string;
                          algebra_rating: Integer;
                          informatics_rating: Integer;
                          russian_rating: Integer;
                          history_rating: Integer);
  end;

  TForm1 = class(TForm)
    strngrd1: TStringGrid;
    btn1: TBitBtn;
    btn2: TBitBtn;
    btn3: TBitBtn;
    edt1: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
var
  Form1: TForm1;
  students: TList;

implementation

{$R *.dfm}

constructor TStudent.Create(name: string;
                            surname: string;
                            year: Integer;
                            class_letter: string;
                            algebra_rating: Integer;
                            informatics_rating: Integer;
                            russian_rating: Integer;
                            history_rating: Integer);
begin
  s_name:= name;
  s_surname:= surname;
  s_year:= year;
  s_class_letter:= class_letter;
  s_algebra_rating:= algebra_rating;
  s_informatics_rating:= informatics_rating;
  s_russian_rating:= russian_rating;
  s_history_rating:= history_rating;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  i: Integer;
begin
  strngrd1.Cells[0,0]:= 'Фамилия';
  strngrd1.Cells[1,0]:= 'Имя';
  strngrd1.Cells[2,0]:= 'Год';
  strngrd1.Cells[3,0]:= 'Класс';
  strngrd1.Cells[4,0]:= 'Алгебра';
  strngrd1.Cells[5,0]:= 'Информатика';
  strngrd1.Cells[6,0]:= 'Руссский язык';
  strngrd1.Cells[7,0]:= 'История';
end;

procedure TForm1.btn1Click(Sender: TObject);
var
  student: TStudent;
begin
  students.Create;
  student:= TStudent.Create('Иван', 'Петров', 10, 'А', 4, 5, 5, 4);
  ShowMessage(student.s_name);
end;
{procedure TForm1.btn1Click(Sender: TObject);
var
  f: TFileStream;
  buf: array [0..8] of char;
  f_size, n: Integer;
  s: string;
begin
 { f := TFileStream.Create('list.dat', fmOpenRead);
    f_size:= f.Seek(0, soFromEnd);
    f.Seek(0, soFromBeginning);
    f.ReadBuffer(buf, f_size);
    //f.Read(s, 1);
      edt1.Text:=buf;
    f.Free();
    //f.Seek(0, soFromBeginning);
    //f.Read(buf, f_size);


    //edt1.Text:= s;
    {fs.WriteComponent(Label1);
    n := 5650;
    fs.Write(n, SizeOf(Integer));
    s := 'Some text';
    fs.Write(s[1], Length(s));
end;}

end.
