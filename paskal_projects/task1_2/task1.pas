program task_numbers(input,output);
var 
    c,i,p,q,k: integer;
    sym: char;
    str: string = '';
    result: int64 = 0;
    flag: integer;
    location: integer = 0;
    num: integer;
    space: boolean = True;
    operation: string;
    count_div: integer = 0;
    count_mod: integer = 0;
    operations: array[1..6] of char = ('+','-','*','d','m','f');
    space_char: array[1..4] of char = (chr(9),chr(10),chr(13),chr(32));
    symbols: array[0..69] of char = ('0','1','2','3','4','5','6','7','8','9',
                                     'A','B','C','D','E','F','G','H','I','J',
                                     'K','L','M','N','O','P','Q','R','S','T',
                                     'U','V','W','X','Y','Z','a','b','c','d',
                                     'e','f','g','h','i','j','k','l','m','n',
                                     'o','p','q','r','s','t','u','v','w','x',
                                     'y','z','!','@','#','$','%','^','&','*');
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
            if (c<=0) or (c>64) then
                begin
                    writeln('Некорректный ввод битности результата в командной строке');
                    exit
                end;
        end
    else 
        begin
            writeln('Некорректный ввод битности результата в командной строке');
            exit 
        end;
for p:=2 to ParamCount do
    begin
        c:=0;
        for q:=1 to Length(ParamStr(p)) do
            if ((ParamStr(p)[q])>='0') and ((ParamStr(p)[q])<='9') then
                c:=c*10+ord(ParamStr(p)[q])-ord('0')
            else 
                begin
                    writeln('Некорректный ввод системы счисления результата в командной строке');
                    exit
                end;
        if (c<2) or (c>70) then
            begin
                writeln('Некорректный ввод системы счисления результата в командной строке');
                exit
            end;
    end;
k:=0;
Repeat 
if not Eoln then
    begin
        Read(sym);
        if (pos(sym,space_char)<>0) and (space) then
            continue;
        if (pos(sym,space_char)=0) and (location=0) then
            begin
                space:=False;
                case sym of
                '+':
                    begin
                        location:=1;
                        continue
                    end;
                'd':
                    begin
                        operation:='d';
                        location:=2;
                        continue
                    end;
                'm':
                    begin
                        operation:='m';
                        location:=2;
                        continue
                    end;
                'f':
                    begin
                        location:=3;
                        continue
                    end;
                ';':
                    location:=1000
                else
                    begin
                        writeln('Некорректный ввод арифметической операции');
                        exit
                    end;
                end;
            end;
        if (location=1) then 
            if pos(sym,space_char)=0 then
                begin
                    writeln('Некорректный ввод арифметической операции');
                    exit
                end
            else
                begin
                    location:=8;
                    space:=True;
                    continue
                end;
        if (location=2) then
            if count_div<2 then
                begin
                    operation:=operation+sym;
                    count_div:=count_div+1
                end
            else
                if pos(sym,space_char)<>0 then
                    if (operation='div') or (operation='mod') then
                        begin
                            location:=5;
                            space:=True
                        end
                    else
                        begin
                            writeln('Некорректный ввод арифметической операции');
                            exit
                        end
                else
                    begin
                        writeln('Некорректный ввод арифметической операции');
                        exit
                    end;
        if (location=8) then
        begin
           result:=result + StrToInt(sym);
        end;
        
    end;
        writeln(result);
until (Eoln);
writeln('A',space_char[1],'B');
end.