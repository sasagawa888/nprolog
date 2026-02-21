
program factorial;
    begin
        read value;
        count := 1;
        result := 1;
        while count < value do 
            begin
                count := count+1;
                result := result*count 
            end;
        write result 
    end 
    