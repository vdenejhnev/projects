var
  a,c,d,r,x: real;
begin
  writeln('Введите параметр а');
  readln(a);
  writeln('Введите параметр x');
  readln(x);
  writeln('Введите параметр c');
  readln(c);
  writeln('Введите параметр d');
  readln(d);

  r:=2-x;
  
  while ((a*x) <= d) do
  begin
    if ((a*x) >= c) and ((a*x) <= d) then
    write(a*x:0:5);
    write(' ');
    x:=x + r;
  end;
end.