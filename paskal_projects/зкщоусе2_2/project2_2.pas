program task_numbers(input,output);
uses SysUtils;
var 
    c,i,p,q: integer;
    sym: char;
    result: int64 = 0;
    temp_result: int64 = 0;
    flag: integer = 0;
    num_base, wide, temp_wide: integer;
    code: integer;
    minus_exist: boolean = false;
    operation, args, show_result: string;
    args1, args2: integer;
    args3: int64;
    symbols: array[0..69] of char = ('0','1','2','3','4','5','6','7','8','9',
                                     'A','B','C','D','E','F','G','H','I','J',
                                     'K','L','M','N','O','P','Q','R','S','T',
                                     'U','V','W','X','Y','Z','a','b','c','d',
                                     'e','f','g','h','i','j','k','l','m','n',
                                     'o','p','q','r','s','t','u','v','w','x',
                                     'y','z','!','@','#','$','%','^','&','*');
                                     
                                     
procedure checkNumBase(num_base: integer);
begin
  if (num_base<2) or (num_base>70) then
  begin
    writeln('Некорректный ввод системы счисления результата в командной строке');
    halt;
  end;
end; 


procedure checkWide(wide: integer);
begin
  if (wide<=0) or (wide>64) then
  begin
    writeln('Некорректный ввод битности результата в командной строке');
    halt;
  end;
end; 

function getWide(num: int64): integer;
var
  wide: integer = 0;
begin
  while num <> 0 do
  begin
    wide:=wide + 1;
    num:=num div 2;
  end;
  
  getWide:=wide;
end;

begin
if ParamCount<2 then
    begin
        writeln('Недостаточно параметров командной строки');
        exit
    end;
c:=0;
for i:=1 to Length(ParamStr(1)) do
    if ((ParamStr(1)[i])>='0') and ((ParamStr(1)[i])<='9') then
        begin
            c:=c*10+ord(ParamStr(1)[i])-ord('0');
            checkWide(c);
        end
    else 
        checkWide(0);
    
wide:=c;
for p:=2 to ParamCount do
    begin
        c:=0;
        for q:=1 to Length(ParamStr(p)) do
            if ((ParamStr(p)[q])>='0') and ((ParamStr(p)[q])<='9') then
                c:=c*10+ord(ParamStr(p)[q])-ord('0')
            else 
                begin
                    checkNumBase(0);
                end;
        checkNumBase(c);
    end;

operation:='';
args:='';
while(true) do
  begin

    if not eof and not EOLn then
      begin
        Read(sym);
        case flag of
          0:
            begin
              if sym = #32 then
                flag:=flag + 1
              else
                operation:=operation + sym;
            end;
          1:
            begin
              if sym <> ':' then
                args:= args + sym
              else
              begin
                flag:=flag + 1;
                args1:= strtoint(args);
                checkNumBase(args1);
                args:= '';  
              end;
            end;
           2:
            begin
              if sym <> ':' then
                args:= args + sym
              else
              begin
                flag:=flag + 1;
                args2:= strtoint(args);
                checkWide(args2);
                args:= '';  
              end;
            end;
           3:
            begin
              if (sym <> ';') and (sym <> ' ') then
              begin
                if (sym <> '-') then
                begin
                  args:= args + sym;
                  args3:= strtoint(args); 
                end
                else 
                  minus_exist:= true;
              end
              else 
                flag:=flag + 1;
            end;
           4:
            begin
            end;
        else
          begin
            writeln('Некорректный ввод арифметической операции');
            exit;
          end;
        end;
      end
    else
    begin
      
      for i:=1 to length(args) do
      begin
        if ord(args[i])>=(args1 + ord('0')) then
        begin
          writeln('Некорректный ввод системы счисления');
          exit
        end 
        else 
        begin          
          temp_wide:=getWide(args3);
          if (temp_wide > args2) then
          begin
            writeln('Некорректный ввод битности числа');
            exit
          end  
        end;
      end;
      
      args:= '';
      
      if not eof then
        readln;
      if (operation = 'finish') then
        break;
      case operation of
            '+': 
              begin
                if minus_exist then
                  result:=result - args3
                else
                  result:=result + args3;
              end;
            '-':
              begin
                if minus_exist then
                  result:=result + args3
                else
                  result:=result - args3;
              end;
            '*':
               begin
                if minus_exist then
                  result:=result * (-1 * args3)
                else
                  result:=result * args3;
              end;
            'div':
              begin
                if minus_exist then
                  result:=result div (-1 * args3)
                else
                  result:=result div args3;
              end;
            'mod':
              begin
                if minus_exist then
                  result:=result mod (-1 * args3)
                else
                  result:=result mod args3;
              end;
      else
        writeln('Некорректный ввод арифметической операции');
        exit;
      end;
      
      temp_result:=result;
      temp_wide:=getWide(result);
      
      if temp_wide > wide then
      begin
        writeln('Превышена битность результата');
        
        for i:=2 to ParamCount do
        begin
          show_result:='';
          write(ParamStr(i));
          Val(ParamStr(i), num_base, code); 
  
          if num_base <= 9 then
            write('  ')
          else
            write(' ');
  
          if temp_result <> 0 then 
          begin
            while temp_result <> 0 do
            begin
              show_result := symbols[abs(temp_result mod num_base)] + show_result;
              temp_result := temp_result div num_base;
            end;
            
            if result < 0 then
              show_result := '-' + show_result;
            
            writeln(show_result);
          end
          else
            writeln(0);
        end;
        exit
      end;
      
      operation:='';
      flag:=0;
      minus_exist:=false;
      
      if eof then 
        break;  
    end;
  end;
  
for i:=2 to ParamCount do
begin
  show_result:='';
  write(ParamStr(i));
  Val(ParamStr(i), num_base, code); 
  
  if num_base <= 9 then
    write('  ')
  else
    write(' ');
  temp_result := result; 
  if temp_result <> 0 then 
    begin
      while temp_result <> 0 do
      begin
        show_result := symbols[abs(temp_result mod num_base)] + show_result;
        temp_result := temp_result div num_base;
      end;
      if result < 0 then
        show_result := '-' + show_result;
        writeln(show_result);
    end
    else
      writeln(0);
  
end;
end. 