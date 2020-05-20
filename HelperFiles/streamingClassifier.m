%   Copyright 2020 The MathWorks, Inc.

function [scores,features] = streamingClassifier(audioIn,M,S)
% This is a streaming classifier function 

persistent airCompNet; 

if isempty(airCompNet)
    airCompNet = coder.loadDeepLearningNetwork('TrainedModel.mat');
end

% Extract features using function
features = extractFeatures(audioIn,16e3);

% Normalize 
features = ((features - M)./S)';

% Classify
[airCompNet, scores] = predictAndUpdateState(airCompNet,features);

end

