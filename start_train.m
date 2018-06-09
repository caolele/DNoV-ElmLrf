clear all;
pkg load image % Install for Octave: pkg install -forge image
load('raw.mat');


rand('state',0)

elmlrf.layers = {
	struct('type', 'i') %input layer
	struct('type', 'c', 'outputmaps', 16, 'kernelsize', 4) %convolution layer
	struct('type', 's', 'scale', 3) %sub sampling layer
};


opts.batchsize = 500;
opts.model = 'sequential';

elmlrf = elmlrfsetup(elmlrf, x, opts.model);

opts.C=0.01;

[elmlrf, er, training_time] = elmlrftrain(elmlrf, x, y, opts);

fprintf('Training error: %f\nTraining Time:%fs\n', er, training_time);

fmap = elmlrf.layers{2}.outputmaps;
chn = size(x,4);
beta = elmlrf.BETA;
ca = elmlrf.layers{2}.a;
cf = elmlrf.layers{2}.f;
ps = elmlrf.layers{3}.scale;
pf = elmlrf.layers{3}.f;

save baseline_models/tmodel.mat fmap chn ca ps beta;

%[er, bad, testing_time] = elmlrftest(elmlrf, test_x, test_y, opts);

%fprintf('Testing error: %f\nTesting Time:%fs\n', er, testing_time);