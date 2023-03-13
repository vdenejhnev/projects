program task_numbers(input,output);
var 
    c,i,p,q,k: integer;
    sym: char;
    str: string = '';
    result: int64 = 0;
    flag_args: integer = 0;
    location: integer = 0;
    num: integer;
    space: boolean = True;
    operation: string;
    count_div: integer = 0;
    count_mod: integer = 0;
    argc1, argc2, argc3: integer;
    chrstr: char = chr(0); {новый символ при вводе}
    prev_c: char = chr(0); {предыдущий символ при считывании}
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
 while (True) do
        begin
            prev_c := (char* )c;
            if eof then
                ending := True;
            if not ending and not EOLn then
                begin
                    read(c);
                    {читаем комментарий}
                    if (c = ';') or (state = read_comment) then
                        begin
                            state := read_comment;
                            continue
                        end;
                    {читаем первые пробелы, если они есть}
                    if (state = start) and (prev_c = chr(0)) and (pos(c, spaces) <> 0) then
                        begin
                            state := read_1st_spaces;
                            continue
                        end;
                    {читаем операцию}
                    if (state = start) and (prev_c = chr(0)) and (pos(c, spaces) = 0) then
                        begin
                            state := read_operation;
                            operation := operation + c;
                            continue;
                        end;
                    if (state = read_1st_spaces) and (pos(prev_c, spaces) <> 0) and
                         (pos(c, spaces) = 0) then
                            begin
                                state := read_operation;
                                operation := operation + c;
                                continue;
                            end;
                    if (state = read_operation) and (pos(prev_c, spaces) = 0) and
                         (pos(c, spaces) = 0) then
                            begin
                                operation := operation + c;
                                continue;
                            end;
                    {если операция слишком длинная, то она точно неправльная}
                    {> 7, т.к. слово finish записывается как операция}
                    if Length(operation) > 7 then
                        begin
                            state := error;
                            writeln('Недопустимая арифметическая операция, попробуйте снова:');
                            continue
                        end;
                    {читаем разделитель}
                    if (state = read_operation) and (pos(prev_c, spaces) = 0) and
                         (pos(c, spaces) <> 0) then
                            begin
                                state := read_2nd_spaces;
                                continue;
                            end;
                    {читаем первое двоеточие}
                    if (state = read_base) and (pos(prev_c, spaces) = 0) and (c = ':') then
                        begin
                            state := read_1st_colon;
                            continue
                        end;
                    {читаем base}
                    if (state = read_2nd_spaces) and (pos(prev_c, spaces) <> 0) and
                         (pos(c, spaces) = 0) or (state = read_base) and
                         (pos(prev_c, spaces) = 0) and (pos(c, spaces) = 0) then
                            if ((ord(c) - 48) <= 9) and ((ord(c) - 48) >= 0) then
                                begin
                                    base := base * 10 + (ord(c) - 48);
                                    state := read_base;
                                    if not ((base >= 2) and (base <= 70)) and 
                                       (not first_digit_in_base) then
                                        begin
                                            state := error;
                                            writeln('Основание системы счисления числа должно быть в диапазоне [2, 70], попробуйте снова');
                                            continue
                                        end;
                                    first_digit_in_base := False;
                                    continue
                                end
                            else
                                begin
                                    state := error;
                                    writeln('Недопустимый символ в основании системы счисления числа, попробуйте снова:');
                                    continue
                                end;
                    {читаем второе двоеточие}
                    if (state = read_wide) and (pos(prev_c, spaces) = 0) and (c = ':') then
                        begin
                            state := read_2nd_colon;
                            if wide <> 64 then
                                begin
                                    upper_bound_for_number := exponentation(2, wide - 1) - 1;
                                    bottom_bound_for_number := (-1) * exponentation(2, wide - 1);
                                end
                            else
                                begin
                                    upper_bound_for_number := High(int64);
                                    bottom_bound_for_number := Low(int64);
                                end;
                            continue
                        end;
                    {читаем wide}
                    if (state = read_1st_colon) and (prev_c = ':') and
                         (pos(c, spaces) = 0) or (state = read_wide) and
                         (pos(prev_c, spaces) = 0) and (pos(c, spaces) = 0) then
                            if ((ord(c) - 48) <= 9) and ((ord(c) - 48) >= 0) then
                                begin
                                    wide := wide * 10 + (ord(c) - 48);
                                    state := read_wide;
                                    if not ((wide > 0) and (wide <= 64)) and
                                         (not first_digit_in_wide) then
                                        begin
                                            state := error;
                                            writeln('Битность числа должна быть в диапазоне [1, 64], попробуйте снова:');
                                            continue
                                        end;
                                    first_digit_in_wide := False;
                                    continue;
                                end
                            else
                                begin
                                    state := error;
                                    writeln('Недопустимый символ в битности числа, попробуйте снова:');
                                    continue
                                end;
                    
                    {читаем число}
                    if (state = read_2nd_colon) and (prev_c = ':') and (c = '-') then
                        begin
                            state := read_number;
                            is_negative := True;
                            continue;
                        end;
                    if (state = read_2nd_colon) and (prev_c = ':') and
                         (pos(c, spaces) = 0) or (state = read_number) and
                         (pos(prev_c, spaces) = 0) and (pos(c, spaces) = 0) then
                            begin
                                state := read_number;
                                digit := pos(c, symbols) - 1;
                                if (digit > (base - 1)) or (digit = -1) then
                                    begin
                                        state := error;
                                        writeln('Недопустимый символ для числа в СС с основанием ',base, ', попробуйте снова:');
                                        continue;
                                    end
                                else
                                    if is_negative then
                                        if number = 0 then
                                            if bottom_bound_for_number <= ((-1) * digit) then
                                                number := (-1) * digit
                                            else
                                                begin
                                                    state := error;
                                                    writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                    continue
                                                end
                                        else
                                            if (bottom_bound_for_number div number) >= base then
                                                begin
                                                    number := number * base;
                                                    if (number - bottom_bound_for_number) >= digit then
                                                        number := number - digit
                                                    else
                                                        begin
                                                            state := error;
                                                            writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                            continue
                                                        end;
                                                end
                                            else
                                                begin
                                                    state := error;
                                                    writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                    continue
                                                end
                                    else
                                        begin
                                            if number = 0 then
                                                if upper_bound_for_number >= digit then
                                                    number := digit
                                                else
                                                    begin
                                                        state := error;
                                                        writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                        continue
                                                    end
                                            else
                                                if (upper_bound_for_number div number) >= base then
                                                    begin
                                                        number := number * base;
                                                        if (upper_bound_for_number - number) >= digit then
                                                            number := number + digit
                                                        else
                                                            begin
                                                                state := error;
                                                                writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                                continue
                                                            end;
                                                    end
                                                else
                                                    begin
                                                        state := error;
                                                        writeln('Число вне диапазона, указанного битностью, попробуйте снова:');
                                                        continue
                                                    end;
                                        end;
                                number_entered := True;
                            end;
                    {читаем пробелы в конце}
                    if (state = read_number) and (pos(prev_c, spaces) = 0) and
                         (pos(c, spaces) <> 0) or (state = read_spaces_in_the_end) and
                         (pos(prev_c, spaces) <> 0) and (pos(c, spaces) <> 0) then
                            state := read_spaces_in_the_end;
                end        
            else
                {обработка команды после нажатия ENTER}
                begin
                    {перевод строки}
                    if not ending then
                        readln;
                    {завершение по finish}
                    if (operation = 'finish') then
                        break;
                    {проверка на соответствие команды формату}
                    if not (number_entered) and (state <> error) and
                         (state <> read_operation) and (state <> start) and
                         (state <> read_1st_spaces) and (state <> read_2nd_spaces) and
                         (state <> read_comment) or ((operation <> '') and
                         (state = read_comment) and not number_entered) then
                            begin
                                state := error;
                                writeln('Неверный формат команды, попробуйте снова:');
                            end;
                    {выполнение арифметической операции}
                    if (state <> error) and (state <> start) and
                       (state <> read_1st_spaces) and not ((state = read_comment) and
                       not number_entered) and number_entered then
                        begin
                            case operation of
                                '+':
                                    begin
                                        command_was := True;
                                        if (result > 0) and (number > 0) and
                                            ((High(int64) - result) >= number) or
                                            (result > 0) and (number < 0) or
                                            (result < 0) and (number > 0) or
                                            (result < 0) and (number < 0) and
                                            ((low(int64) - result) <= number) or
                                            (result = 0) or (number = 0) then
                                            begin
                                                if ((result + number) > upper_bound_for_result) or
                                                   ((result + number) < bottom_bound_for_result) then
                                                    begin
                                                        writeln('Результат вне диапазона, заданного битностью, послений правильный результат:');
                                                        break;
                                                    end;
                                                result := result + number;
                                            end
                                        else
                                            begin
                                                writeln('Результат вне диапазона, заданного битностью, послений правильный результат:');
                                                break;
                                            end;
                                    end;
                                '-':
                                    begin
                                        command_was := True;
                                        if (result > 0) and (number > 0) or
                                            (result > 0) and (number < 0) and
                                            ((result - High(int64)) <= number) or
                                            (result < 0) and (number > 0) and
                                            ((result - low(int64)) >= number) or
                                            (result < 0) and (number < 0) or
                                            (result = 0) and (number <> low(int64)) or
                                            (number = 0) then
                                            begin
                                                if ((result - number) > upper_bound_for_result) or
                                                    ((result - number) < bottom_bound_for_result) then
                                                        begin
                                                            writeln('Результат вне диапазона, заданного битностью, послений правильный результат:');
                                                            break;
                                                        end;
                                                result := result - number;
                                            end
                                        else
                                            begin
                                                writeln('Результат вне диапазона, заданного битностью, послений правильный результат:');
                                                break;
                                            end;
                                    end;
                                '*':
                                    if (result = 0) or (number = 0) then
                                        begin
                                            result := 0;
                                            command_was := True
                                        end
                                    else
                                        if (result > 0) and (number > 0) and
                                            ((upper_bound_for_result div result) >= number) or
                                            (result < 0) and (number < 0) and
                                            ((upper_bound_for_result div result) <= number) or
                                            (result > 0) and (number < 0) and
                                            ((bottom_bound_for_result div result) <= number) or
                                            (result < 0) and (number > 0) and
                                            ((bottom_bound_for_result div result) >= number) then
                                            begin
                                                command_was := True;
                                                result := result * number;
                                            end
                                        else
                                            begin
                                                writeln('Результат вне диапазона, заданного битность, послений правильный результат:');
                                                command_was := True;
                                                break;
                                            end;
                                'div':
                                    if number = 0 then
                                        begin
                                            state := error;
                                            writeln('Деление на ноль, попробуйте снова:');
                                        end
                                    else
                                        begin
                                            command_was := True;
                                            result := result div number;
                                        end;
                                'mod':
                                    if number = 0 then
                                        begin
                                            state := error;
                                            writeln('Деление на ноль, попробуйте снова:');
                                        end
                                    else
                                        begin
                                            command_was := True;
                                            result := result mod number;
                                        end
                                else
                                    begin
                                        state := error;
                                        writeln('Недопустимая арифметическая операция, попробуйте снова:');
                                        
                                    end;
                            end;
                        end;
                    {проверка на соответствие команды формату}
                    if (operation <> '') and (not number_entered) and (state <> -1) then
                        begin
                            state := error;
                            writeln('Неверный формат команды, попробуйте снова:');
                        end;
                    {завершение по eof}
                    if ending then 
                        break;
                    {подготовка переменных к вводу новой команды}
                    state := start;
                    number := 0;
                    wide := 0;
                    operation := '';
                    base := 0;
                    digit := 0;
                    c := chr(0);
                    first_digit_in_base := True;
                    first_digit_in_wide := True;
                    number_entered := False;
                end;
        end;


    {проверка, введены ли были команды}
    if not command_was then
        begin
            writeln('Команды не были введены');
            exit;
        end;

    {вывод}
    for i:=2 to ParamCount do
        begin
            answer :='';
            write(ParamStr(i)); {вывод основания СС}
            Val(ParamStr(i), num_base, code); {получаем основание СС}
            if num_base <= 9 then {переход на 4 позицию в данной строке}
                write('  ')
            else
                write(' ');
            extra_result := result; {сохранение результата от изменений}
            if extra_result <> 0 then {если не 0, преобразуем из десятичной СС в заданную}
                begin
                    while extra_result <> 0 do
                        begin
                            answer := symbols[abs(extra_result mod num_base) + 1] + answer;
                            extra_result := extra_result div num_base;
                        end;
                    if result < 0 then
                        answer := '-' + answer;
                    writeln(answer);
                end
            else {если 0, выводим 0}
                writeln(0);
        end;
end.
