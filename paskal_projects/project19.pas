var
  str: String;
  out_file: text;
  i: integer;
begin
  assign(out_file, 'file.txt');
  rewrite(out_file);
  writeln('Введите строку');
  read(str);
  writeln(out_file, length(str));  
  
  for i:= length(str) downto 1 do
    if(str[i] <> ' ') then
      write(out_file, str[i]);
    
  close(out_file);
end.