function datafolder = getAirCompressorDataFolder()
% datafolder = getAirCompressorDataFolder()
% This function returns the stored setting for a data folder for the
% dataset name AirCompressorData
%
% If the setting does not exist, it prompts the user to pick a directory
% and stores it for later use.

% Setting name for this set of data
datasetname = "AirCompressorData";

% Create settings object and add DemoData group if it doesn't exist
s = settings;
if ~hasGroup(s, "DemoData")
    addGroup(s, "DemoData");
end

% If setting does not exist, let user pick a data directory
if ~hasSetting(s.DemoData, datasetname)
    p = string(uigetdir(pwd, "Select a Directory for " + datasetname));
    if p == "0"
        error("getDataDirectory:UserCancelled", "User cancelled download");
        
    end
    addSetting(s.DemoData, datasetname, 'PersonalValue', p, 'ValidationFcn', @mustBeFolder);
    
end

% Extract the active valueh
datafolder = s.DemoData.(datasetname).ActiveValue;

end
