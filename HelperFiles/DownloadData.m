%   Copyright 2020 The MathWorks, Inc.

dataZip = "AirCompressorDataset.zip";
url = "https://www.mathworks.com/supportfiles/audio/AirCompressorDataset/AirCompressorDataset.zip";
dataFolder = "AirCompressorData";

disp("Checking for dataset...");

if ~isfolder(dataFolder)
    answer = questdlg("Do you want to download the dataset now?","Dataset not found","Yes","No","Yes");
    
    switch answer
        case "Yes"
            if ~isfile(dataZip)
                outFile = websave(dataZip,url);
                disp("Data zip file saved as " + outFile);        
            end

            disp("Unzipping data file...");
            unzip(dataZip, dataFolder);
            disp("Data unzipped successfully.");
        case "No"
            disp("Dataset not downloaded. You will need to download the dataset to run the example. Please run DownloadData.")
    end
else
    disp("Dataset found.");
end
    