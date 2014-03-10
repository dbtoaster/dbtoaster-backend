function [] = graphs()
close all;
data=load('out.txt');

S=data(:,1);
N=data(:,2);
M=data(:,3);
Lu=data(:,4);
Lnu=data(:,5);

x=M;

figure;
hold on;
plot(x,data(:, 6),'r-.'); % IdxHashTree - red
plot(x,data(:, 7),'r');
plot(x,data(:, 8),'r-.')
plot(x,data(:, 9),'b-.'); % IdxHashList - blue
plot(x,data(:,10),'b');
plot(x,data(:,11),'b-.');
