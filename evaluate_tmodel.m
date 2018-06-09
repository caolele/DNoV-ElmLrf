clear all;

load('./tmodel.mat');
load('./data/numreg/raw.mat');

predT = mypredict(x, fmap, chn, ca, ps, beta);

[~, label0] = max(y, [], 2);
[~, label] = max(predT, [], 2);

bad = find(label0 ~= label);
er = numel(bad) / size(y, 1);  

fprintf('Testing error: %f\n', er);