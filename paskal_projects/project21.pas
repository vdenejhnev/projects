var 
  arr: array [1..20] of integer = (1, 3, 5, 7, 9, 13, 15, 64, 74, 89, 123, 148, 241, 423, 484, 586, 589, 642, 845, 1045);
  search_num, curr_num, curr_index, last_index, temp_index, N: integer;
begin
  writeln('Введите число, которое необходимо найти: ');
  read(search_num);
  N:=20;
  curr_index:=(N div 2) + 1;
  curr_num:=arr[curr_index];
  
  if (search_num > curr_num) then
    last_index:= N;
  if (search_num < curr_num) then
    last_index:= 0;
  
  write('Разбиение на 2 части: ');
  writeln(curr_index);
  
  while (true) do
  begin
    if (search_num > curr_num ) then
    begin
      temp_index:=curr_index;
      
      if (last_index < curr_index) then
        curr_index:= curr_index + ((curr_index - last_index) div 2)
      else
        curr_index:= curr_index + ((last_index - curr_index) div 2);
      
      curr_num:=arr[curr_index];
      last_index:= temp_index;
      write('Разбиение в сторону левой границы массива: ');
      writeln(curr_index);
    end;
    if (search_num < curr_num ) then
    begin
      temp_index:=curr_index;
      curr_index:= curr_index - ((curr_index - last_index) div 2);
      curr_num:=arr[curr_index];
      last_index:= temp_index;
      write('Разбиение в сторону правой границы массива: ');
      writeln(curr_index);
    end;
    
    if search_num = curr_num then
    begin
      write('Индекс искомого элемента: ');
      writeln(curr_index);
      break;
    end;
  end;
   
end.