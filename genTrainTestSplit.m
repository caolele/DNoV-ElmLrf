clear all;

data = load('./data/numreg/raw.mat');

trainratio = 0.7;

n = size(data.x,3);

z=randperm(n);

train_x = data.x(:,:,z(1:n*trainratio),:);
train_y = data.y(z(1:n*trainratio),:);

test_x = data.x(:,:,z(n*trainratio+1:end),:);
test_y = data.y(z(n*trainratio+1:end),:);
