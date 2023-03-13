Program program1;

var f, g: text;
i: char;
begin
  assign(f, 'f.txt');
  reset(f);
  
  assign(g, 'g.txt');
  rewrite(g);
  
  while not eof(f) do 
  begin
    read(f, i);
    
    if i = #13 then
      write(g, '!') 
    else
      write(g, i);
    
  end;
  
  close(f);
  close(g);
end.
