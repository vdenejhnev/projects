Program program2;
var data: text;
worker, gild: string;
data_str: string;
curr_sum: string;
count_space, first_space, second_space, i: integer;
total, count_sum : integer;
workers: array of string;
gilds: array of string;
salary: array of integer;
gild_exist: boolean;
encoding:= Encoding.UTF8;
begin
  assign(data, 'data.txt');
  reset(data, encoding);
  
  while not eof(data) do 
  begin
    readln(data, data_str);
   
    setLength(workers, Length(workers) + 1);
    setLength(gilds, Length(gilds) + 1);
    setLength(salary, Length(salary) + 1);
    
    count_space:= 0;
    for i := 1 to Length(data_str) do
    begin
      if data_str[i] = ' ' then
      begin
        if count_space = 0 then
        begin
          first_space:= i;
          count_space:= count_space + 1;
        end
        else 
          second_space:= i;
      end;
    end;
   
    workers[Length(workers) - 1]:=copy(data_str, 0, first_space);
    gilds[Length(gilds) - 1]:=copy(data_str, first_space + 1, second_space - first_space - 1);
    salary[Length(salary) - 1]:=strToInt(copy(data_str, second_space, Length(data_str) - second_space + 1));
  end;
  
  read(gild);
  gild_exist := false;
  
  for i:=0 to Length(gilds) - 1 do 
  begin
    if (gild = gilds[i]) then
      gild_exist:=true;
  end;
  
  if gild_exist then
  begin
    total:=0;
    count_sum:=0;
  
    writeln(#13 + 'Ведомость по цеху: ' + gild);
  
    for i:=0 to Length(salary) - 1 do 
    begin
      if (gild = gilds[i]) then
      begin
        total:=total + salary[i];  
        count_sum:=count_sum + 1;
      
        writeln(#13 + '-------------------------------');
        writeln('Рабочий: ' + workers[i]);
        writeln('Цех: ' + gilds[i]);
        writeln('Оплата: ' + salary[i] + ' руб.');
        writeln('-------------------------------');
      
      end;
    end;
  
    writeln(#13 + 'Общая сумма: ' + total + ' руб.');
    writeln('Среднемесячный заработок: ' + (total / count_sum) + ' руб.');
  end
  else 
    writeln('Цех не найден');
  
  close(data);
end.
