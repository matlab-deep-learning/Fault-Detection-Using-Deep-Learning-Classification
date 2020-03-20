%   Copyright 2020 The MathWorks, Inc.

function features = extractFeatures(audioIn,fs)
    
    %#codegen
    
    persistent stf F winPower

    if(isempty(stf))   
        % Setup a short time fourier transform object
        FFTLength = 512;
        windowLength = 512;
        hopLength = 512;
        win = hamming(windowLength,'periodic');
        winPower =  2/(sum(win)^2);
        stf = dsp.STFT(win,windowLength-hopLength,FFTLength);
        [~,temp] = stft(zeros(windowLength,1),fs,'Window',win,'OverlapLength',windowLength-hopLength,'centered',false);
        F = temp(1:257);
    end

    Xcomp = stf(audioIn);
    Xcomp= Xcomp(1:257,:);
    
    % Get power spectrum
    X = real(Xcomp.*conj(Xcomp));
    
    % Normalize by window power 
    X = X .* winPower;
    
    X(1,:) = 0.5*X(1,:);
    X(end,:) = 0.5*X(end,:);

    S1 = spectralCentroid(X,F);
    S2 = spectralCrest(X,F);
    S3 = spectralDecrease(X,F);
    S4 = spectralEntropy(X,F);
    S5 = spectralFlatness(X,F);
%     S6 = spectralFlux(X,F);
    S7  = spectralKurtosis(X,F);
    S8  = spectralRolloffPoint(X,F);
    S9  = spectralSkewness(X,F);
    S10 = spectralSlope(X,F);
    S11 = spectralSpread(X,F);

    features = [S1 S2 S3 S4 S5 S7 S8 S9 S10 S11];

end

