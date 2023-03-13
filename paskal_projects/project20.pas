var
  str: String;
  in_file: text;
  i: integer;
begin
  assign(in_file, 'file.txt');
  reset(in_file);
  
  while(not EOF(in_file)) do
    read(in_file, str);
  
  for i:= 1 to length(str) do
    if(str[i] <> ' ') then
      write(str[i]);
  
  close(in_file);
end.