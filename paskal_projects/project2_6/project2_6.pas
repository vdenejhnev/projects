var
  file_arr: text;
  num, min_num, min_num_last: integer;
  find_min: boolean;
begin
  assign(file_arr, 'file.txt');
  reset(file_arr);
  
  find_min:=false;
  
  while not EOF(file_arr) do
  begin
    read(file_arr, num);
    
    if (find_min = false) then
    begin
      min_num:=num;
      find_min:= true;
    end;
    
    if (num < min_num) then
    begin
      min_num_last:=min_num;
      min_num:=num;
    end;

  end;
  
  write(min_num_last);
  
  close(file_arr);
end.