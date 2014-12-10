filename = sprintf('FilterCoefficients.h');

time = clock;
lines = ...
{ ...
    sprintf('// FilterCoefficients.h\n');
    sprintf('// Created: Jeremie Bannwarth, 08/12/2014');
    sprintf('// Last modified: Jeremie Bannwarth, %i/%i/%i\n', time(3), time(2), time(1));
    sprintf('// Load custom filter coefficient');
    sprintf('const int32_t rounder = %i;', 2^(N-1));
    sprintf('const int8_t  N       = %i;\n', N) ;
    sprintf('const int32_t p0_1    = %iL;', p0_1);
    sprintf('const int32_t a1_1    = %iL;', a1_1);
    sprintf('const int32_t a2_1    = %iL;', a2_1);
    sprintf('const int16_t b0_1    = %i;', b0_1);
    sprintf('const int16_t b1_1    = %i;', b1_1);
    sprintf('const int16_t b2_1    = %i;\n', b2_1);
    sprintf('const int32_t p0_2    = %iL;', p0_2);
    sprintf('const int32_t a1_2    = %iL;', a1_2);
    sprintf('const int32_t a2_2    = %iL;', a2_2);
    sprintf('const int16_t b0_2    = %i;', b0_2);
    sprintf('const int16_t b1_2    = %i;', b1_2);
    sprintf('const int16_t b2_2    = %i;', b2_2);
};

fileID = fopen(filename,'w');

for i = 1:length(lines)
    disp(lines{i})
    fprintf(fileID,[lines{i},'\n']);
end

fclose(fileID);