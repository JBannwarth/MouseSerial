% Filter variable name: Hlp
N = 21;
p0_1 = round(Hlp.ScaleValues(1)*2^N);
a1_1 = round(Hlp.sosMatrix(1,5)*2^N);
a2_1 = round(Hlp.sosMatrix(1,6)*2^N);
b0_1 = Hlp.sosMatrix(1,1);
b1_1 = Hlp.sosMatrix(1,2);
b2_1 = Hlp.sosMatrix(1,3);

if ( min(size(Hlp.sosMatrix)) < 2 )
    p0_2 = 0;
    a1_2 = 0;
    a2_2 = 0;
    b0_2 = 0;
    b1_2 = 0;
    b2_2 = 0;
else
    p0_2 = round(Hlp.ScaleValues(2)*2^N);
    a1_2 = round(Hlp.sosMatrix(2,5)*2^N);
    a2_2 = round(Hlp.sosMatrix(2,6)*2^N);
    b0_2 = Hlp.sosMatrix(2,1);
    b1_2 = Hlp.sosMatrix(2,2);
    b2_2 = Hlp.sosMatrix(2,3);
end