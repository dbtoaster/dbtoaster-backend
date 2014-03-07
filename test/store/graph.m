function [] = graphs()
close all;
data=load('out.txt');

S=data(:,1);
N=data(:,2);
M=data(:,3);
L=data(:,4);
lu=data(:,5);
lnu=data(:,6);
ta=data(:,7);
tl=data(:,8);
tu=data(:,9);

x=lu;

figure;
hold on;
plot(x,ta);
plot(x,tl);
plot(x,tu)
% plot(x,la,'bo',[1:500]*2,m,'-r','LineWidth',2)
