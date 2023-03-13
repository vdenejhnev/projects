var
  i, j, val: integer;
  arr: array [1..10] of integer;
begin
  arr[1]:= 4;
  arr[2]:= 5;
  arr[3]:= 8;
  arr[4]:= 10;
  arr[5]:= 15;
  arr[6]:= 6;
  arr[7]:= 2;
  arr[8]:= 1;
  arr[9]:= 9;
  arr[10]:= 3;
  for i:=10 downto 1 do

      if arr[i] > arr[i + 1] then
      begin
        val:=arr[i+1];
        arr[i+1]:=arr[i];
        arr[i]:=val;  
      end;
      
  for i:=1 to 10 do
    writeln(arr[i]);
end.