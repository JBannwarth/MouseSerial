% Load MouseData1.csv using default Matlab GUI parameters
t = (1:length(xRaw))'./100;
plot(t,xRaw)
xRawData = timeseries(xRaw,t);
xFiltData = timeseries(xfilt,t);
Ts = 1/100;