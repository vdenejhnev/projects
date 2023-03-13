unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, Buttons;

type
  array_max_sum_rating = array [0..10] of Integer;

  TForm1 = class(TForm)
    strngrd1: TStringGrid;
    btn3: TButton;
    btn1: TButton;
    btn2: TButton;
    procedure FormCreate(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

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

      constructor Create( name: string;
                          surname: string;
                          year: Integer;
                          class_letter: string;
                          algebra_rating: Integer;
                          informatics_rating: Integer;
                          russian_rating: Integer;
                          history_rating: Integer);

      function sum_rating(): Integer;
      function check_ratings(): Boolean;
  end;
var
  Form1: TForm1;
  students: TList;
  list_exist: Boolean;

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

function TStudent.sum_rating(): Integer;
begin
  sum_rating:=s_algebra_rating + s_informatics_rating + s_russian_rating + s_history_rating;
end;

function TStudent.check_ratings(): Boolean;
begin
  if ((s_algebra_rating < 4) or (s_informatics_rating < 4) or (s_russian_rating < 4) or (s_history_rating < 4)) then
    check_ratings:=false
  else
    check_ratings:=true;
end;

function find_max_sum_rating(): array_max_sum_rating;
var
  i: Integer;
  student: TStudent;
  max_sum_rating : array_max_sum_rating;
begin     
  for i:=0 to Length(max_sum_rating) - 1 do
    max_sum_rating[i]:=0;

  for i:=0 to students.Count - 1 do
  begin
    student:= students[i];

    if (student.sum_rating() > max_sum_rating[student.s_year - 1]) then
      max_sum_rating[student.s_year - 1]:=student.sum_rating;
  end;

  find_max_sum_rating:=max_sum_rating;
end;

procedure check_rating();
var
  i, offset: Integer;
  student: TStudent;
  removed_students: array of Integer;
  max_sum_rating : array_max_sum_rating;
begin
  max_sum_rating:=find_max_sum_rating();

  for i:=0 to students.Count - 1 do
  begin
    student:= students[i];

    if (not student.check_ratings) then
    begin
      SetLength(removed_students, Length(removed_students) + 1);
      removed_students[Length(removed_students) - 1]:=i;
    end
    else
      if (student.sum_rating() < max_sum_rating[student.s_year - 1]) then
      begin
        SetLength(removed_students, Length(removed_students) + 1);
        removed_students[Length(removed_students) - 1]:=i;
      end;

  end;

  offset:=0;

  for i:=0 to Length(removed_students) - 1 do
  begin
    students.Delete(removed_students[i]-offset);
    inc(offset);
  end
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  list_exist:=false;
  strngrd1.Cells[0,0]:= 'Фамилия';
  strngrd1.Cells[1,0]:= 'Имя';
  strngrd1.Cells[2,0]:= 'Год';
  strngrd1.Cells[3,0]:= 'Класс';
  strngrd1.Cells[4,0]:= 'Алгебра';
  strngrd1.Cells[5,0]:= 'Информатика';
  strngrd1.Cells[6,0]:= 'Руссский язык';
  strngrd1.Cells[7,0]:= 'История';
end;

procedure TForm1.btn3Click(Sender: TObject);
var
  i, j: Integer;
begin
  for i:=1 to strngrd1.RowCount - 1 do
    for j:=0 to strngrd1.ColCount - 1 do
       strngrd1.Cells[j, i]:='';
           
  strngrd1.RowCount:=2;
  students.Clear;
  list_exist:=false;
end;

procedure TForm1.btn1Click(Sender: TObject);
var
  i, j: Integer;
  student: TStudent;
  p_student: Pointer;
  data_item: array of string;
  input_stream: TFileStream;
  data_list: TStringList;
begin
  input_stream:=TFileStream.Create('list.dat', fmOpenRead);
  input_stream.Position:=0;
  data_list:= TStringList.Create;
  data_list.LoadFromStream(input_stream);
  input_stream.Free;
  students:= TList.Create;

  for i:=0 to (data_list.Count div 8) - 1 do
    students.Add(TStudent.Create(data_list.Strings[i*8], data_list.Strings[(i*8)+1], StrToInt(data_list.Strings[(i*8)+2]), data_list.Strings[(i*8)+3],  StrToInt(data_list.Strings[(i*8)+4]),  StrToInt(data_list.Strings[(i*8)+5]),  StrToInt(data_list.Strings[(i*8)+6]),  StrToInt(data_list.Strings[(i*8)+7])));

  data_list.Free;

  check_rating();

  if (students.Count = 0) then
    strngrd1.RowCount:=2
  else
    strngrd1.RowCount:= students.Count + 1;

  for i:=0 to students.Count - 1 do
  begin
    student:= students[i];
    strngrd1.Cells[0,i + 1]:= student.s_surname;
    strngrd1.Cells[1,i + 1]:= student.s_name;
    strngrd1.Cells[2,i + 1]:= IntToStr(student.s_year);
    strngrd1.Cells[3,i + 1]:= student.s_class_letter;
    strngrd1.Cells[4,i + 1]:= IntToStr(student.s_algebra_rating);
    strngrd1.Cells[5,i + 1]:= IntToStr(student.s_informatics_rating);
    strngrd1.Cells[6,i + 1]:= IntToStr(student.s_russian_rating);
    strngrd1.Cells[7,i + 1]:= IntToStr(student.s_history_rating);
  end;
  list_exist:=true;
end;

procedure TForm1.btn2Click(Sender: TObject);
var
  i: Integer;
  student: TStudent;
  data_list: TStringList;
  output_stream: TFileStream;
begin
  if (list_exist) then
  begin
    data_list:=TStringList.Create;
    for i:=0 to students.Count - 1 do
    begin
      student:= students[i];
      data_list.Add(student.s_name);
      data_list.Add(student.s_surname);
      data_list.Add(IntToStr(student.s_year));
      data_list.Add(student.s_class_letter);
      data_list.Add(IntToStr(student.s_algebra_rating));
      data_list.Add(IntToStr(student.s_informatics_rating));
      data_list.Add(IntToStr(student.s_russian_rating));
      data_list.Add(IntToStr(student.s_history_rating));
    end;

    output_stream:=TFileStream.Create('list.res', fmCreate);
    data_list.SaveToStream(output_stream);
    data_list.Free;
    output_stream.Free;
  end;
end;

end.
