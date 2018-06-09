clear all;

% set_param(0,'CharacterEncoding','UTF-8');

x =[];
y = [];

filein=fopen('data_index.txt');

while ~feof(filein)
    tline = fgetl(filein);
    disp(tline)
    s = regexp(tline, '\s+', 'split');
    i=double(imread(s{1}))/255;
    
    if size(i,2) < 19
        p=19-size(i,2);
        if ndims(i) == 3
            i=cat(2,i,zeros(31,p,3));
        elseif ndims(i) == 2
            i=cat(2,i,zeros(31,p));
        else
            error ("incorrect number of channels");
        end
    end

    ii = zeros(31,19,1,3);
    if ndims(i) == 3
        ii(:,:,1,1) = i(:,:,1);
        ii(:,:,1,2) = i(:,:,2);
        ii(:,:,1,3) = i(:,:,3);
    elseif ndims(i) == 2
        ii(:,:,1,1) = i(:,:);
        ii(:,:,1,2) = i(:,:);
        ii(:,:,1,3) = i(:,:);
    else
        error ("incorrect number of channels");
    end
    x = cat(3,x,ii);

    y = [y;zeros(1,10)];
    y(end,str2num(s{2})+1)=1;
end

save raw.mat x y
