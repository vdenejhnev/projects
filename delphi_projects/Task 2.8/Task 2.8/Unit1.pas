unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm1 = class(TForm)
    Memo1: TMemo;
    BitBtn1: TBitBtn;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.BitBtn1Click(Sender: TObject);
type
  setNat=set of 1..255;
var
  natNumbers: setNat;
  m, n: integer;
begin
  natNumbers:=[];
  n:=1;
  m:=1;

  while (2*n+2*m)<=255 do
  begin
    natNumbers:=natNumbers+[2*n+2*m];
    inc(m);
  end;

  for m:=1 to 255 do
    begin
      if m in natNumbers then
      begin
        Memo1.Text:=Memo1.Text + ' ' + intToSTR(m);
      end;
    end;

end;

end.
