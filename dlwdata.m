load('baseline_models/tmodel.mat');
mf = 'baseline_models/model.yml';

% dlmwrite('model.txt','c');
% dlmwrite('model.txt',chn,'-append');%line1
% 
% dlmwrite('model.txt','f','-append');
% dlmwrite('model.txt',fmap,'-append');%line1
% 
% dlmwrite('model.txt','p','-append');
% dlmwrite('model.txt',ps,'-append');%line1
% 
% dlmwrite('model.txt','b','-append');
% dlmwrite('model.txt',beta,'-append');%line7168 col10
% 
% dlmwrite('model.txt','i','-append');
% for i = 1:length(ca)
%     for j = 1:length(ca{i})
%         dlmwrite('model.txt',ca{i}{j},'-append');%line4 col4
%     end
% end

matlab2opencv( chn, 'chn', mf);
matlab2opencv( fmap, 'fmap', mf, 'a');
matlab2opencv( size(ca{1}{1},1), 'cs', mf, 'a');
matlab2opencv( ps, 'ps', mf, 'a');
matlab2opencv( beta, 'beta', mf, 'a');

for i = 1:length(ca)
    for j = 1:length(ca{i})
        matlab2opencv(ca{i}{j}, strcat('ca_',num2str(i),'_',num2str(j)), mf, 'a');
    end
end