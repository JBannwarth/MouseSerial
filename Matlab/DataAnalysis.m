% Load MouseData1.csv using default Matlab GUI parameters
t = (1:length(x))'./100;
plot(t,x)
xData = timeseries(x,t)