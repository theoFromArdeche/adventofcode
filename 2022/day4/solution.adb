with Ada.Text_IO;      use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure solution is
    File : File_Type;
    answerPart1: Integer := 0;
    answerPart2: Integer := 0;
    startRange1 : Integer;
    endRange1 : Integer;
    startRange2 : Integer;
    endRange2 : Integer;
    c: Character;

begin
    Open (File, In_File, "input.txt");
    while not End_Of_File(File) loop
        
        Get(File, startRange1);
        Get(File, c);
        Get(File, endRange1);
        Get(File, c);
        Get(File, startRange2);
        Get(File, c);
        Get(File, endRange2);
        
        if (startRange1>=startRange2 and endRange1<=endRange2) or (startRange2>=startRange1 and endRange2<=endRange1) then
            answerPart1:=answerPart1+1;
            answerPart2:=answerPart2+1;
        elsif (startRange1>=startRange2 and startRange1<=endRange2) or (startRange2>=startRange1 and startRange2<=endRange1) then
            answerPart2:=answerPart2+1;
        end if;
    end loop;

    Put_Line ("Part 1 solution : " & Integer'Image (answerPart1));
    Put_Line ("Part 2 solution : " & Integer'Image (answerPart2));

    Close (File);
end solution;
