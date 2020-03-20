%   Copyright 2020 The MathWorks, Inc.

% Recreate the datastore again

dataFolder = 'AirCompressorData';
ads = audioDatastore(dataFolder,'IncludeSubfolders',true,'LabelSource','foldernames');
rng(3);
ads = shuffle(ads);
[adsTrain,adsValidation] = splitEachLabel(ads,0.9,0.1);