classdef SmokeTests < matlab.unittest.TestCase
    
    properties (TestParameter)
        DemoFile = struct( ... 
			'Part01_DataPreparation', {@Part01_DataPreparation}, ...
			'Part02_Modeling', {@Part02_Modeling}, ...
			'Part03_Deployment', {@Part03_Deployment});
        Shortcut = struct( ... 
			'OpenCodegenReport', {@OpenCodegenReport}, ...
			'OpenPart1', {@OpenPart1}, ...
			'OpenPart2', {@OpenPart2}, ...
			'OpenPart3', {@OpenPart3});
    end    
    
    methods (TestClassSetup)
        
        % Shut off graphics warnings
        function killGraphicsWarning(testCase)
            ws = warning('off', 'MATLAB:hg:AutoSoftwareOpenGL');
            testCase.addTeardown(@()warning(ws));
            
        end
        
        % Close any new figures created by doc
        function saveExistingFigures(testCase)            
            existingfigs = findall(groot, 'Type', 'Figure');
            testCase.addTeardown(@()delete(setdiff(findall(groot, 'Type', 'Figure'), existingfigs)))
            
        end
        
    end
    
    methods (Test)
        
        function demoShouldNotWarn(testCase, DemoFile)       
            testCase.verifyWarningFree(DemoFile);
            
        end
        
        
        function shortcutShouldNotWarn(testCase, Shortcut)
            testCase.verifyWarningFree(Shortcut);
            
        end
        
    end

end
