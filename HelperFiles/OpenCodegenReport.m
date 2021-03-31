%   Copyright 2018-2020 The MathWorks, Inc.

function OpenCodegenReport

prj = currentProject;
open(fullfile(prj.RootFolder,'arm_compute','html','report.mldatx'));

end