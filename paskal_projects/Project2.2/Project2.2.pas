{Program project2;

var
  fin, fout: text;
  s: string;
  encoding:= Encoding.UTF8;
begin
   Assign(fin, 'fin.txt');
   Reset(fin, encoding);
   Assign(fout, 'fout.txt');
   Rewrite(fout);
   
   while not eof(fin) do
   begin
      Readln(fin, s);
      
      if (s[1] = 'А') or (s[1] = 'а') then
        Writeln(fout, s);

   end;
   
   close(fin);
   close(fout);
}
Program program2;
var 
c:string;

function simpleNum(num: string): integer;
var
  digit1, digit2, digit3, count_simple: integer;
begin
  digit1 := StrToInt(num[1]);
  digit2 := StrToInt(num[2]);
  digit3 := StrToInt(num[3]);
  count_simple:= 0;
  
  if ((digit1 = 1) or (digit1 = 3)) or ((digit1 = 5) or (digit1 = 7)) then
  begin
    count_simple+=1;
    write(digit1);
  end;
  
  if ((digit2 = 1) or (digit2 = 3)) or ((digit2 = 5) or (digit2 = 7)) then
  begin
    count_simple+=1;
    write(digit2);
  end;
  
  if ((digit3 = 1) or (digit3 = 3)) or ((digit3 = 5) or (digit3 = 7)) then
  begin
    count_simple+=1;
    write(digit3)
  end;
  
  simpleNum:=count_simple
end;

begin
 writeln('Enter nums: ');
 read(c);
 writeln('Count simple nums: ' + simpleNum(c));
end.